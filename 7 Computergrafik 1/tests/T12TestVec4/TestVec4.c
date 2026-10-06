#include <cgclib/math/Vec4.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_homogenize_basic(void)
{
    const Vec4 v      = { 2.0f, 4.0f, 6.0f, 2.0f };
    const Vec3 result = Homogenize(v);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, result.z);
}

static void test_homogenize_identity(void)
{
    const Vec4 v      = { 1.0f, 2.0f, 3.0f, 1.0f };
    const Vec3 result = Homogenize(v);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, result.z);
}

static void test_homogenize_negative_w(void)
{
    const Vec4 v      = { 2.0f, -4.0f, 6.0f, -2.0f };
    const Vec3 result = Homogenize(v);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, result.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.y);
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, result.z);
}

static void test_homogenize_zero_w(void)
{
    const Vec4 v      = { 1.0f, 2.0f, 3.0f, 0.0f };
    const Vec3 result = Homogenize(v);
    TEST_ASSERT_TRUE(isinf(result.x) || isnan(result.x));
    TEST_ASSERT_TRUE(isinf(result.y) || isnan(result.y));
    TEST_ASSERT_TRUE(isinf(result.z) || isnan(result.z));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_homogenize_basic);
    RUN_TEST(test_homogenize_identity);
    RUN_TEST(test_homogenize_negative_w);
    RUN_TEST(test_homogenize_zero_w);

    return UNITY_END();
}
