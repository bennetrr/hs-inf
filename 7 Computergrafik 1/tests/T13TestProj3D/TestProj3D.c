#include <cgclib/math/Mat4.h>
#include <cgclib/math/Transforms.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/math/Vec4.h>
#include <unity/unity.h>

Mat4 Projection3DInverse(uint32_t width, uint32_t height, float fieldOfViewYRadians, float n, float f)
{
  Mat4        r      = {0};
  const float aspect = (float)width / height;
  const float t      = tanf(fieldOfViewYRadians * 0.5f);
  r.m[M4Ofs(0, 0)]   = (aspect * t);
  r.m[M4Ofs(1, 1)]   = t;
  r.m[M4Ofs(2, 3)]   = -1.0f;
  r.m[M4Ofs(3, 3)]   = (f - n) / (2 * f * n);
  r.m[M4Ofs(3, 2)]   = -(f + n) / (2 * f * n);

  return r;
}

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_Projection3D_IsProjective(void)
{
  uint32_t width  = 1920;
  uint32_t height = 1080;
  float    aspect = (float)width / height;
  float    fovy   = 45.0f / 180.0f * (float)M_PI;
  float    n      = -1.0f;
  float    f      = -16.0f;
  Mat4     p      = Projection3D(width, height, fovy, n, f);

  TEST_ASSERT_EQUAL_FLOAT(0.0f, p.m[M4Ofs(3, 3)]);
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, p.m[M4Ofs(3, 2)]);
}

static void test_Projection3D_NearPlanePointIsNegative1(void)
{
  uint32_t   width  = 1920;
  uint32_t   height = 1080;
  float      aspect = (float)width / height;
  float      fovy   = 45.0f / 180.0f * (float)M_PI;
  float      n      = -2.0f;
  float      f      = -16.0f;
  Mat4       p      = Projection3D(width, height, fovy, n, f);
  const Vec3 v0     = {0.0f, 0.0f, n};
  const Vec4 result = Mat4xVec3(p, v0);

  TEST_ASSERT_EQUAL_FLOAT(n, result.z);
  TEST_ASSERT_EQUAL_FLOAT(fabs(n), result.w);
}

static void test_Projection3D_FarPlanePointIsPositive1(void)
{
  uint32_t   width  = 1920;
  uint32_t   height = 1080;
  float      aspect = (float)width / height;
  float      fovy   = 45.0f / 180.0f * (float)M_PI;
  float      n      = -1.0f;
  float      f      = -16.0f;
  Mat4       p      = Projection3D(width, height, fovy, n, f);
  const Vec3 v0     = {0.0f, 0.0f, f};
  const Vec4 result = Mat4xVec3(p, v0);
  TEST_ASSERT_EQUAL_FLOAT(fabs(f), result.z);
  TEST_ASSERT_EQUAL_FLOAT(fabs(f), result.w);
}

static void test_Project3D_ViewFrustumCorners_Near_Lower_Left(void)
{
  uint32_t   width              = 1920;
  uint32_t   height             = 1080;
  float      aspect             = (float)width / height;
  float      fovy               = 45.0f / 180.0f * (float)M_PI;
  float      n                  = -1.0f;
  float      f                  = -16.0f;
  const Mat4 p                  = Projection3D(width, height, fovy, n, f);
  // Hand-crafter reference values for the parameters n, f, aspect, and fovy above.
  const Vec3 lowerLeftNearPlane = {-0.736379683f, -0.414213568f, n};
  const Vec3 result              = Homogenize(Mat4xVec3(p, lowerLeftNearPlane));
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.z);
}

static void test_Project3D_ViewFrustumCorners_Far_Upper_Right(void)
{
  uint32_t   width  = 1920;
  uint32_t   height = 1080;
  float      aspect = (float)width / height;
  float      fovy   = 45.0f / 180.0f * (float)M_PI;
  float      n      = -1.0f;
  float      f      = -16.0f;
  const Mat4 p      = Projection3D(width, height, fovy, n, f);
  // Hand-crafter reference values for the parameters n, f, aspect, and fovy above.
  const Vec3 upperRightFarPlane = {11.7820749f, 6.62741709f, f};
  const Vec3 result             = Homogenize(Mat4xVec3(p, upperRightFarPlane));
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.z);
}



int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_Projection3D_IsProjective);
  RUN_TEST(test_Projection3D_NearPlanePointIsNegative1);
  RUN_TEST(test_Projection3D_FarPlanePointIsPositive1);
  RUN_TEST(test_Project3D_ViewFrustumCorners_Near_Lower_Left);
  RUN_TEST(test_Project3D_ViewFrustumCorners_Far_Upper_Right);
  return UNITY_END();
}
