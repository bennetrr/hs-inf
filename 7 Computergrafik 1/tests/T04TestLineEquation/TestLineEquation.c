#include <cgclib/math/LineEquation.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_CreateLineEquation_horizontal_line(void)
{
    LineEquation line = CreateLineEquation(0, 0, 10, 0);
    TEST_ASSERT_EQUAL_INT32(0, line.nx);
    TEST_ASSERT_EQUAL_INT32(10, line.ny);
    TEST_ASSERT_EQUAL_INT32(0, line.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f / 10.0f, line.invLength);
}

static void test_CreateLineEquation_vertical_line(void)
{
    LineEquation line = CreateLineEquation(0, 0, 0, 10);
    TEST_ASSERT_EQUAL_INT32(-10, line.nx);
    TEST_ASSERT_EQUAL_INT32(0, line.ny);
    TEST_ASSERT_EQUAL_INT32(0, line.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f / 10.0f, line.invLength);
}

static void test_EvalLineEquation_on_line(void)
{
    LineEquation line = CreateLineEquation(0, 0, 10, 0);
    int32_t      eval = EvalLineEquation(line, 5, 0);
    TEST_ASSERT_EQUAL_INT32(0, eval); // Point lies on the line
}

static void test_EvalLineEquation_above_line(void)
{
    LineEquation line = CreateLineEquation(0, 0, 10, 0);
    int32_t      eval = EvalLineEquation(line, 5, 5);
    TEST_ASSERT_EQUAL_INT32(50, eval); // Point is above the line
}

static void test_DistanceToLine(void)
{
    LineEquation line = CreateLineEquation(0, 0, 10, 0);
    float        dist = DistanceToLine(line, 5, 5);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 5.0f, dist); // Distance should be 5 units
}

static void test_DistanceToLine_negative_side(void)
{
    LineEquation line = CreateLineEquation(0, 0, 10, 0);
    float        dist = DistanceToLine(line, 5, -5);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, dist); // Negative side of the line
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_CreateLineEquation_horizontal_line);
    RUN_TEST(test_CreateLineEquation_vertical_line);
    RUN_TEST(test_EvalLineEquation_on_line);
    RUN_TEST(test_EvalLineEquation_above_line);
    RUN_TEST(test_DistanceToLine);
    RUN_TEST(test_DistanceToLine_negative_side);
    return UNITY_END();
}
