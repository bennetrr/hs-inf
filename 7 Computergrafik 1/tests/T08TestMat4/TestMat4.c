#include <cgclib/math/Mat4.h>
#include <unity/unity.h>

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_identity_matrix(void)
{
    Mat4 m = SetIdentity();
    for (int i = 0; i < 16; ++i)
        TEST_ASSERT_EQUAL_FLOAT((i % 5 == 0) ? 1.0f : 0.0f, m.m[i]);
}

static void test_rotate_z_90_degrees(void)
{
    Mat4 m = SetRotateZ((float)M_PI / 2.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(0, 0)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, m.m[M4Ofs(0, 1)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, m.m[M4Ofs(1, 0)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(1, 1)]);
}

static void test_rotate_x_180_degrees(void)
{
    Mat4 m = SetRotateX((float)M_PI);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, m.m[M4Ofs(1, 1)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(1, 2)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(2, 1)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, m.m[M4Ofs(2, 2)]);
}

static void test_rotate_y_90_degrees(void)
{
    Mat4 m = SetRotateY((float)M_PI / 2.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(0, 0)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, m.m[M4Ofs(1, 1)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, m.m[M4Ofs(2, 0)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, m.m[M4Ofs(2, 2)]);
}

static void test_translation_matrix(void)
{
    Mat4 m = SetTranslate(1.0f, 2.0f, 3.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, m.m[M4Ofs(0, 3)]);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, m.m[M4Ofs(1, 3)]);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, m.m[M4Ofs(2, 3)]);
}

static void test_scaling_matrix(void)
{
    Mat4 m = SetScale(2.0f, 3.0f, 4.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, m.m[M4Ofs(0, 0)]);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, m.m[M4Ofs(1, 1)]);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, m.m[M4Ofs(2, 2)]);
}

static void test_matrix_multiplication_identity(void)
{
    Mat4 a      = SetIdentity();
    Mat4 b      = SetScale(2.0f, 3.0f, 4.0f);
    Mat4 result = Mat4xMat4(a, b);

    for (int i = 0; i < 16; ++i)
        TEST_ASSERT_EQUAL_FLOAT(b.m[i], result.m[i]);
}

static void test_matrix_multiplication_scaling_x_translation(void)
{
    Mat4 scale     = SetScale(2.0f, 3.0f, 4.0f);
    Mat4 translate = SetTranslate(1.0f, 2.0f, 3.0f);
    Mat4 result    = Mat4xMat4(scale, translate);

    // Check that translation is scaled
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.m[M4Ofs(0, 3)]);  // 1 * 2
    TEST_ASSERT_EQUAL_FLOAT(6.0f, result.m[M4Ofs(1, 3)]);  // 2 * 3
    TEST_ASSERT_EQUAL_FLOAT(12.0f, result.m[M4Ofs(2, 3)]); // 3 * 4
}

static void test_matrix_multiplication_rotation_x_translation(void)
{
    Mat4 rotate    = SetRotateZ((float)M_PI / 2.0f);
    Mat4 translate = SetTranslate(1.0f, 0.0f, 0.0f);
    Mat4 result    = Mat4xMat4(rotate, translate);

    // Translation should be rotated
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.m[M4Ofs(0, 3)]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.m[M4Ofs(1, 3)]);
}

static void test_matrix_multiplication_associativity(void)
{
    Mat4 a = SetTranslate(1.0f, 0.0f, 0.0f);
    Mat4 b = SetScale(2.0f, 2.0f, 2.0f);
    Mat4 c = SetRotateZ((float)M_PI / 2.0f);

    Mat4 ab_c = Mat4xMat4(Mat4xMat4(a, b), c);
    Mat4 a_bc = Mat4xMat4(a, Mat4xMat4(b, c));

    for (int i = 0; i < 16; ++i)
        TEST_ASSERT_FLOAT_WITHIN(0.001f, ab_c.m[i], a_bc.m[i]);
}

static void test_mat4xvec3_affine_translation(void)
{
    Mat4 t      = SetTranslate(1.0f, 2.0f, 3.0f);
    Vec3 v      = { 0.0f, 0.0f, 0.0f };
    Vec3 result = Mat4xVec3Affine(t, v);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result.x);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.y);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, result.z);
}

static void test_mat4xvec3_scaling(void)
{
    Mat4 s      = SetScale(2.0f, 3.0f, 4.0f);
    Vec3 v      = { 1.0f, 1.0f, 1.0f };
    Vec4 result = Mat4xVec3(s, v);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result.x);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, result.y);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, result.z);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result.w);
}

static void test_mat3xvec3_rotation_z(void)
{
    Mat4 rz     = SetRotateZ((float)M_PI / 2.0f);
    Vec3 v      = { 1.0f, 0.0f, 0.0f };
    Vec3 result = Mat3xVec3(rz, v);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.x);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, result.y);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, result.z);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_identity_matrix);
    RUN_TEST(test_rotate_z_90_degrees);
    RUN_TEST(test_rotate_x_180_degrees);
    RUN_TEST(test_rotate_y_90_degrees);
    RUN_TEST(test_translation_matrix);
    RUN_TEST(test_scaling_matrix);
    RUN_TEST(test_matrix_multiplication_identity);

    RUN_TEST(test_matrix_multiplication_scaling_x_translation);
    RUN_TEST(test_matrix_multiplication_rotation_x_translation);
    RUN_TEST(test_matrix_multiplication_associativity);

    RUN_TEST(test_mat4xvec3_affine_translation);
    RUN_TEST(test_mat4xvec3_scaling);
    RUN_TEST(test_mat3xvec3_rotation_z);

    return UNITY_END();
}
