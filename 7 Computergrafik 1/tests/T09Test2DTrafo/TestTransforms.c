#include <cgclib/math/Mat4.h>
#include <cgclib/math/Transforms.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/math/Vec4.h>
#include <unity/unity.h>


void setUp(void)
{
}
void tearDown(void)
{
}

static void test_NDCToWindow_IsAffine(void)
{
  const Mat4 c = NDCToWindow(1920, 1080);

  TEST_ASSERT_EQUAL_FLOAT(c.m[M4Ofs(3, 0)], 0);
  TEST_ASSERT_EQUAL_FLOAT(c.m[M4Ofs(3, 1)], 0);
  TEST_ASSERT_EQUAL_FLOAT(c.m[M4Ofs(3, 2)], 0);
  TEST_ASSERT_EQUAL_FLOAT(c.m[M4Ofs(3, 3)], 1);
}

static void test_NDCToWindow_LowerLeft(void)
{
  const Mat4 c      = NDCToWindow(1920, 1080);
  const Vec3 v      = {-1.0f, -1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(c, v);
  TEST_ASSERT_EQUAL_FLOAT(0, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0, result.z);
}

static void test_NDCToWindow_LowerRight(void)
{
  const Mat4 c      = NDCToWindow(1920, 1080);
  const Vec3 v      = {1.0f, -1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(c, v);
  TEST_ASSERT_EQUAL_FLOAT(1920, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0, result.z);
}

static void test_NDCToWindow_UpperLeft(void)
{
  const Mat4 c      = NDCToWindow(1920, 1080);
  const Vec3 v      = {-1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(c, v);
  TEST_ASSERT_EQUAL_FLOAT(0, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1080, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0, result.z);
}

static void test_NDCToWindow_UpperRight(void)
{
  const Mat4 c      = NDCToWindow(1920, 1080);
  const Vec3 v      = {1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(c, v);
  TEST_ASSERT_EQUAL_FLOAT(1920, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1080, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0, result.z);
}

static void test_Projection2D_Isotropic(void)
{
  const Mat4 p = Projection2D(256, 256);
  for (int i = 0; i < 16; ++i)
    TEST_ASSERT_EQUAL_FLOAT((i % 5 == 0) ? 1.0f : 0.0f, p.m[i]);
}

static void test_Projection2D_WidthGreaterHeight(void)
{
  const Mat4 p      = Projection2D(512, 256);
  const Vec3 v0     = {1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(p, v0);
  TEST_ASSERT_EQUAL_FLOAT(0.5f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0, result.z);
}

static void test_Projection2D_HeightGreaterWidth(void)
{
  const Mat4 p      = Projection2D(256, 512);
  const Vec3 v0     = {1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(p, v0);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.5f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0, result.z);
}

static void test_Projection2D_FullHD(void)
{
  const Mat4 p      = Projection2D(1920, 1080);
  const Vec3 v0     = {1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(p, v0);
  TEST_ASSERT_EQUAL_FLOAT(0.5625f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0, result.z);
}

static void test_Projection2D_FullHDRotated(void)
{
  const Mat4 p      = Projection2D(1080, 1920);
  const Vec3 v0     = {1.0f, 1.0f, 0.0f};
  const Vec3 result = Mat4xVec3Affine(p, v0);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.5625f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0, result.z);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_NDCToWindow_IsAffine);
  RUN_TEST(test_NDCToWindow_LowerLeft);
  RUN_TEST(test_NDCToWindow_LowerRight);
  RUN_TEST(test_NDCToWindow_UpperLeft);

  RUN_TEST(test_Projection2D_Isotropic);
  RUN_TEST(test_Projection2D_WidthGreaterHeight);
  RUN_TEST(test_Projection2D_HeightGreaterWidth);

  RUN_TEST(test_Projection2D_FullHD);
  RUN_TEST(test_Projection2D_FullHDRotated);

  return UNITY_END();
}
