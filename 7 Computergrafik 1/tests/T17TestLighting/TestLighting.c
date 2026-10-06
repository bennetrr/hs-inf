#include <cgclib/math/Lighting.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_DiffuseLighting_parallel_vectors(void)
{
  Vec3 normal = {0.0f, 0.0f, 1.0f};
  Vec3 light  = {0.0f, 0.0f, 1.0f};
  Vec3 color  = {1.0f, 0.5f, 0.25f};

  Vec3 result = DiffuseLighting(normal, light, color);

  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.25f, result.z);
}

static void test_DiffuseLighting_opposite_vectors(void)
{
  Vec3 normal = {0.0f, 0.0f, 1.0f};
  Vec3 light  = {0.0f, 0.0f, -1.0f};
  Vec3 color  = {1.0f, 1.0f, 1.0f};

  Vec3 result = DiffuseLighting(normal, light, color);

  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.z);
}

static void test_BlinnLighting_specular_peak(void)
{
  Vec3  normal    = {0.0f, 0.0f, 1.0f};
  Vec3  light     = {0.0f, 0.0f, 1.0f};
  Vec3  view      = {0.0f, 0.0f, 1.0f};
  Vec3  color     = {1.0f, 1.0f, 1.0f};
  float shinyness = 32.0f;

  Vec3 result = BlinnLighting(normal, light, view, color, shinyness);

  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.z);
}

static void test_BlinnLighting_no_specular(void)
{
  Vec3  normal    = {0.0f, 0.0f, 1.0f};
  Vec3  light     = {0.0f, 0.0f, -1.0f};
  Vec3  view      = {0.0f, 0.0f, -1.0f};
  Vec3  color     = {1.0f, 1.0f, 1.0f};
  float shinyness = 32.0f;

  Vec3 result = BlinnLighting(normal, light, view, color, shinyness);

  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.z);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_DiffuseLighting_parallel_vectors);
  RUN_TEST(test_DiffuseLighting_opposite_vectors);
  RUN_TEST(test_BlinnLighting_specular_peak);
  RUN_TEST(test_BlinnLighting_no_specular);
  return UNITY_END();
}

