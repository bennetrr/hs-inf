
#include <cgclib/math/Vec3.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_add(void)
{
  const Vec3 a = {1, 2, 3};
  const Vec3 b = {3, 1, 5};
  const Vec3 c = Add(a, b);
  TEST_ASSERT_EQUAL_FLOAT(4.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(8.0f, c.z);
}

static void test_add_zero_vector(void)
{
  const Vec3 a = {0, 0, 0};
  const Vec3 b = {1, 2, 3};
  const Vec3 c = Add(a, b);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(2.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.z);
}

static void test_add_negative_values(void)
{
  const Vec3 a = {-1, -2, -3};
  const Vec3 b = {4, 5, 6};
  const Vec3 c = Add(a, b);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.z);
}

static void test_add_large_values(void)
{
  const Vec3 a = {1e6f, 2e6f, 3e6f};
  const Vec3 b = {4e6f, 5e6f, 6e6f};
  const Vec3 c = Add(a, b);
  TEST_ASSERT_EQUAL_FLOAT(5e6f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(7e6f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(9e6f, c.z);
}

static void test_sub(void)
{
  const Vec3 a = {5, 7, 9};
  const Vec3 b = {2, 3, 4};
  const Vec3 c = Sub(a, b);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(4.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(5.0f, c.z);
}

static void test_sub_zero_vector(void)
{
  const Vec3 a = {1, 2, 3};
  const Vec3 b = {0, 0, 0};
  const Vec3 c = Sub(a, b);
  TEST_ASSERT_EQUAL_FLOAT(1.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(2.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, c.z);
}

static void test_sub_negative_values(void)
{
  const Vec3 a = {4, 5, 6};
  const Vec3 b = {-1, -2, -3};
  const Vec3 c = Sub(a, b);
  TEST_ASSERT_EQUAL_FLOAT(5.0f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(7.0f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(9.0f, c.z);
}

static void test_sub_large_values(void)
{
  const Vec3 a = {1e6f, 2e6f, 3e6f};
  const Vec3 b = {4e6f, 5e6f, 6e6f};
  const Vec3 c = Sub(a, b);
  TEST_ASSERT_EQUAL_FLOAT(-3e6f, c.x);
  TEST_ASSERT_EQUAL_FLOAT(-3e6f, c.y);
  TEST_ASSERT_EQUAL_FLOAT(-3e6f, c.z);
}

static void test_weighted_sum(void)
{
  const Vec3 a      = {1, -1, 2};
  const Vec3 b      = {3, 2, -1};
  const Vec3 c      = {-2, 1, 5};
  const Vec3 result = WeightedSum(0.5f, 0.25f, a, b, c);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.25f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.00f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.25f, result.z);
}

static void test_weighted_sum_a(void)
{
  const Vec3 a      = {1, -1, 2};
  const Vec3 b      = {3, 2, -1};
  const Vec3 c      = {-2, 1, 5};
  const Vec3 result = WeightedSum(0.0f, 0.0f, a, b, c);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, a.x, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, a.y, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, a.z, result.z);
}

static void test_weighted_sum_b(void)
{
  const Vec3 a      = {1, -1, 2};
  const Vec3 b      = {3, 2, -1};
  const Vec3 c      = {-2, 1, 5};
  const Vec3 result = WeightedSum(1.0f, 0.0f, a, b, c);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, b.x, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, b.y, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, b.z, result.z);
}

static void test_weighted_sum_c(void)
{
  const Vec3 a      = {1, -1, 2};
  const Vec3 b      = {3, 2, -1};
  const Vec3 c      = {-2, 1, 5};
  const Vec3 result = WeightedSum(0.0f, 1.0f, a, b, c);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, c.x, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, c.y, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, c.z, result.z);
}

static void test_dot(void)
{
  const Vec3  a      = {1, 2, 3};
  const Vec3  b      = {4, -5, 6};
  const float result = Dot(a, b);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 12.0f, result);
}

static void test_dot_orthogonal_vectors_xy(void)
{
  const Vec3  a      = {1, 0, 0};
  const Vec3  b      = {0, 1, 0};
  const float result = Dot(a, b);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

static void test_dot_orthogonal_vectors_xz(void)
{
  const Vec3  a      = {1, 0, 0};
  const Vec3  b      = {0, 0, 1};
  const float result = Dot(a, b);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

static void test_dot_orthogonal_vectors_yz(void)
{
  const Vec3  a      = {0, 1, 0};
  const Vec3  b      = {0, 0, 1};
  const float result = Dot(a, b);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

static void test_dot_parallel_vectors(void)
{
  const Vec3  a      = {1, 2, 3};
  const Vec3  b      = {2, 4, 6};
  const float result = Dot(a, b);
  TEST_ASSERT_EQUAL_FLOAT(28.0f, result);
}

static void test_dot_negative_values(void)
{
  const Vec3  a      = {-1, -2, -3};
  const Vec3  b      = {4, 5, 6};
  const float result = Dot(a, b);
  TEST_ASSERT_EQUAL_FLOAT(-32.0f, result);
}

static void test_scale(void)
{
  const Vec3 v      = {1, -2, 3};
  const Vec3 result = Scale(2.0f, v);
  TEST_ASSERT_EQUAL_FLOAT(2.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(-4.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(6.0f, result.z);
}

static void test_scale_zero_scalar(void)
{
  const Vec3 v      = {1, -2, 3};
  const Vec3 result = Scale(0.0f, v);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.z);
}

static void test_scale_negative_scalar(void)
{
  const Vec3 v      = {1, 2, 3};
  const Vec3 result = Scale(-2.0f, v);
  TEST_ASSERT_EQUAL_FLOAT(-2.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(-4.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(-6.0f, result.z);
}

static void test_scale_large_scalar(void)
{
  const Vec3 v      = {1.0f, 1.0f, 1.0f};
  const Vec3 result = Scale(1e6f, v);
  TEST_ASSERT_EQUAL_FLOAT(1e6f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(1e6f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(1e6f, result.z);
}

static void test_cross_parallel_vectors(void)
{
  const Vec3 a      = {1, 2, 3};
  const Vec3 b      = {2, 4, 6};
  const Vec3 result = Cross(a, b);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.z);
}

static void test_cross_orthogonal_vectors(void)
{
  const Vec3 a      = {0, 0, 1};
  const Vec3 b      = {0, 1, 0};
  const Vec3 result = Cross(a, b);
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.z);
}

static void test_cross_negative_result(void)
{
  const Vec3 a      = {1, 0, 0};
  const Vec3 b      = {0, -1, 0};
  const Vec3 result = Cross(a, b);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.x);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result.y);
  TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.z);
}

static void test_cross_anti_commutative(void)
{
  const Vec3 a  = {2, 3, 1};
  const Vec3 b  = {1, 2, 3};
  const Vec3 ab = Cross(a, b);
  const Vec3 ba = Cross(b, a);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, ab.x, -ba.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, ab.y, -ba.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, ab.z, -ba.z);
}

static void test_length(void)
{
  const Vec3  v      = {3, 4, 0};
  const float result = Length(v);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, result);
}

static void test_length_zero_vector(void)
{
  const Vec3  v      = {0, 0, 0};
  const float result = Length(v);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

static void test_length_unit_vector(void)
{
  const Vec3  v      = {1, 0, 0};
  const float result = Length(v);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result);
}

static void test_length_diagonal_vector(void)
{
  const Vec3  v      = {1, 1, 1};
  const float result = Length(v);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, sqrtf(3.0f), result);
}

static void test_normalize(void)
{
  const Vec3 v      = {0, 3, 4};
  const Vec3 result = Normalize(v);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.6f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.8f, result.z);
}

static void test_normalize_unit_vector(void)
{
  const Vec3 v      = {0, 1, 0};
  const Vec3 result = Normalize(v);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.z);
}

static void test_normalize_diagonal_vector(void)
{
  const Vec3 v      = {1, 1, 1};
  const Vec3 result = Normalize(v);
  float      invLen = 1.0f / sqrtf(3.0f);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, invLen, result.x);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, invLen, result.y);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, invLen, result.z);
}

static void test_normalize_zero_vector(void)
{
  const Vec3 v      = {0, 0, 0};
  const Vec3 result = Normalize(v);  
  TEST_ASSERT_TRUE(isnan(result.x) || isinf(result.x) || 0.0f == result.x);
  TEST_ASSERT_TRUE(isnan(result.y) || isinf(result.y) || 0.0f == result.y);
  TEST_ASSERT_TRUE(isnan(result.z) || isinf(result.z) || 0.0f == result.z);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_add);
  RUN_TEST(test_add_zero_vector);
  RUN_TEST(test_add_negative_values);
  RUN_TEST(test_add_large_values);

  RUN_TEST(test_sub);
  RUN_TEST(test_sub_zero_vector);
  RUN_TEST(test_sub_negative_values);
  RUN_TEST(test_sub_large_values);

  RUN_TEST(test_weighted_sum);
  RUN_TEST(test_weighted_sum_a);
  RUN_TEST(test_weighted_sum_b);
  RUN_TEST(test_weighted_sum_c);

  RUN_TEST(test_dot);
  RUN_TEST(test_dot_orthogonal_vectors_xy);
  RUN_TEST(test_dot_orthogonal_vectors_xz);
  RUN_TEST(test_dot_orthogonal_vectors_yz);
  RUN_TEST(test_dot_parallel_vectors);
  RUN_TEST(test_dot_negative_values);

  RUN_TEST(test_scale);
  RUN_TEST(test_scale_zero_scalar);
  RUN_TEST(test_scale_negative_scalar);
  RUN_TEST(test_scale_large_scalar);

  RUN_TEST(test_cross_parallel_vectors);
  RUN_TEST(test_cross_orthogonal_vectors);
  RUN_TEST(test_cross_negative_result);
  RUN_TEST(test_cross_anti_commutative);

  RUN_TEST(test_length);
  RUN_TEST(test_length_zero_vector);
  RUN_TEST(test_length_unit_vector);
  RUN_TEST(test_length_diagonal_vector);

  RUN_TEST(test_normalize);
  RUN_TEST(test_normalize_unit_vector);
  RUN_TEST(test_normalize_diagonal_vector);
  RUN_TEST(test_normalize_zero_vector);

  return UNITY_END();
}
