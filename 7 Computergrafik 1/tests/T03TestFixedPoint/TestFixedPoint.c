#include <cgclib/math/FixedPoint.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_FloatToFixed_and_FixedToFloat(void)
{
  float   input  = 3.25f;
  fixed_t fixed  = FloatToFixed(input);
  float   result = FixedToFloat(fixed);
  TEST_ASSERT_FLOAT_WITHIN(0.01f, input, result);
}

static void test_IntToFixed_and_FixedToInt(void)
{
  int32_t input  = 7;
  fixed_t fixed  = IntToFixed(input);
  int32_t result = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(input, result);
}



static void test_FloatToFixed_rounding(void)
{
  float   input  = 1.5f;
  fixed_t fixed  = FloatToFixed(input);
  int32_t result = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(2, result);
}

static void test_negative_values(void)
{
  float   input  = -2.75f;
  fixed_t fixed  = FloatToFixed(input);
  float   result = FixedToFloat(fixed);
  TEST_ASSERT_FLOAT_WITHIN(0.01f, input, result);

  int32_t intInput  = -3;
  fixed_t fixedInt  = IntToFixed(intInput);
  int32_t resultInt = FixedToInt(fixedInt);
  TEST_ASSERT_EQUAL_INT32(intInput, resultInt);
}

static void test_fixed_to_int_rd_down(void)
{
  float   input  = 1.4f;
  fixed_t fixed  = FloatToFixed(input);
  int32_t result  = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(1, result);
}

static void test_fixed_to_int_rd_up(void)
{
  float   input  = 1.6f;
  fixed_t fixed  = FloatToFixed(input);
  int32_t result  = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(2, result);
}


static void test_negative_fixed_to_int_rd_down(void)
{
  float   input  = -1.4f;
  fixed_t fixed  = FloatToFixed(input);
  int32_t result  = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(-1, result);
}

static void test_negative_fixed_to_int_rd_up(void)
{
  float   input  = -1.6f;
  fixed_t fixed  = FloatToFixed(input);
  int32_t   result = FixedToInt(fixed);
  TEST_ASSERT_EQUAL_INT32(-2, result);
}

static void test_one(void)
{  
  float fixed  = FixedToFloat(fixed_one);  
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, fixed);
}

static void test_one_half(void)
{
  float  fixed = FixedToFloat(fixed_one_half);
  TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5f, fixed);
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_FloatToFixed_and_FixedToFloat);
  RUN_TEST(test_IntToFixed_and_FixedToInt);
  
  RUN_TEST(test_FloatToFixed_rounding);
  RUN_TEST(test_negative_values);
  RUN_TEST(test_fixed_to_int_rd_down);
  RUN_TEST(test_fixed_to_int_rd_up);
  RUN_TEST(test_negative_fixed_to_int_rd_down);
  RUN_TEST(test_negative_fixed_to_int_rd_up);

  RUN_TEST(test_one);
  RUN_TEST(test_one_half);

  return UNITY_END();
}
