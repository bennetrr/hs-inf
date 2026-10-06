#include <cgclib/raster/Triangle.h>
#include <cgclib/sys/PixelBuffer.h>
#include <unity/unity.h>

#define TEST_HELPER(NAME__)                                                                                            \
    {                                                                                                                  \
        ComparePixelBufferResult compareResults;                                                                       \
        ComparePixelBufferToFile(p, REL_SRC_PATH "/" NAME__ "_ref.png", NAME__ "_student.png", NAME__ "_diff.png",     \
                                 &compareResults, false);                                                              \
        TEST_ASSERT_EQUAL(false, compareResults.WidthMismatch);                                                        \
        TEST_ASSERT_EQUAL(false, compareResults.HeightMismatch);                                                       \
        TEST_ASSERT_EQUAL(false, compareResults.PixelMismatch);                                                        \
    }

#define CREATE_PIXEL_BUFFER(WIDTH__, HEIGHT__)                                                                         \
    PixelBuffer p = { 0 };                                                                                             \
    int32_t     r = CreatePixelBuffer(&p, WIDTH__, HEIGHT__, true);                                                    \
    if (r != 0)                                                                                                        \
        TEST_FAIL_MESSAGE("Could not allocate pixel buffer\n");                                                        \
    ClearColorBuffer(p, 0xffffffff);

#define DESTROY_PIXEL_BUFFER() DestroyPixelBuffer(&p, true);

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_draw_red_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 1, 0, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    TEST_HELPER("test_draw_red_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_green_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    TEST_HELPER("test_draw_green_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_blue_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 0, 0, 1 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    TEST_HELPER("test_draw_blue_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_degenerate_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.1f),
                     FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    TEST_HELPER("test_draw_degenerate_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_flipped_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.2f),
                     FloatToFixed(p.height * 0.9f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    TEST_HELPER("test_flipped_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_screen_filling_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);

    Vec3 color = { 0, 1, 1 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.0f), FloatToFixed(p.height * 0.0f), FloatToFixed(3.0f * p.width),
                     FloatToFixed(0.0f * p.height), FloatToFixed(0.0f * p.width), FloatToFixed(p.height * 3.0f), color);
    TEST_HELPER("test_screen_filling_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_equilateral_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    Vec3 color = { 0, 0, 1 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.45f), FloatToFixed(p.height * 0.9f),
                     color);

    TEST_HELPER("test_equilateral_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_bad_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.45f), FloatToFixed(p.height * 0.11f),
                     color);

    TEST_HELPER("test_bad_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_screen_width_bigger_height_triangle(void)
{
    CREATE_PIXEL_BUFFER(512, 256);
    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.45f), FloatToFixed(p.height * 0.9f),
                     color);

    TEST_HELPER("test_screen_width_bigger_height_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_screen_width_smaller_height_triangle(void)
{
    CREATE_PIXEL_BUFFER(256, 512);
    Vec3 color = { 0, 0, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.45f), FloatToFixed(p.height * 0.9f),
                     color);

    TEST_HELPER("test_screen_width_smaller_height_triangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_clip_bottom(void)
{
    CREATE_PIXEL_BUFFER(256, 512);
    Vec3 color = { 0, 1, 0 };

    float x0 = 0.1f;
    float y0 = 0.1f;

    float x1 = 0.9f;
    float y1 = -0.1f;

    float x2 = 0.45f;
    float y2 = 0.9f;

    DrawTriangleFlat(p, FloatToFixed(p.width * x0), FloatToFixed(p.height * y0), FloatToFixed(p.width * x1),
                     FloatToFixed(p.height * y1), FloatToFixed(p.width * x2), FloatToFixed(p.height * y2), color);

    TEST_HELPER("test_clip_bottom");
    DESTROY_PIXEL_BUFFER();
}

static void test_clip_top(void)
{
    CREATE_PIXEL_BUFFER(256, 512);
    Vec3 color = { 1, 0, 1 };

    float x0 = 0.1f;
    float y0 = 0.1f;

    float x1 = 0.9f;
    float y1 = 0.1f;

    float x2 = 0.45f;
    float y2 = 1.9f;

    DrawTriangleFlat(p, FloatToFixed(p.width * x0), FloatToFixed(p.height * y0), FloatToFixed(p.width * x1),
                     FloatToFixed(p.height * y1), FloatToFixed(p.width * x2), FloatToFixed(p.height * y2), color);

    TEST_HELPER("test_clip_top");
    DESTROY_PIXEL_BUFFER();
}

static void test_clip_left(void)
{
    CREATE_PIXEL_BUFFER(256, 512);
    Vec3 color = { 0, 1, 1 };

    float x0 = -0.1f;
    float y0 = 0.1f;

    float x1 = 0.9f;
    float y1 = 0.1f;

    float x2 = 0.45f;
    float y2 = 0.9f;

    DrawTriangleFlat(p, FloatToFixed(p.width * x0), FloatToFixed(p.height * y0), FloatToFixed(p.width * x1),
                     FloatToFixed(p.height * y1), FloatToFixed(p.width * x2), FloatToFixed(p.height * y2), color);

    TEST_HELPER("test_clip_left");
    DESTROY_PIXEL_BUFFER();
}

static void test_clip_right(void)
{
    CREATE_PIXEL_BUFFER(256, 512);
    Vec3 color = { 1, 1, 0 };

    float x0 = 0.1f;
    float y0 = 0.1f;

    float x1 = 0.9f;
    float y1 = 0.1f;

    float x2 = 1.45f;
    float y2 = 0.9f;

    DrawTriangleFlat(p, FloatToFixed(p.width * x0), FloatToFixed(p.height * y0), FloatToFixed(p.width * x1),
                     FloatToFixed(p.height * y1), FloatToFixed(p.width * x2), FloatToFixed(p.height * y2), color);

    TEST_HELPER("test_clip_right");
    DESTROY_PIXEL_BUFFER();
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_draw_red_triangle);
    RUN_TEST(test_draw_green_triangle);
    RUN_TEST(test_draw_blue_triangle);
    RUN_TEST(test_draw_degenerate_triangle);

    RUN_TEST(test_flipped_triangle);
    RUN_TEST(test_screen_filling_triangle);

    RUN_TEST(test_equilateral_triangle);
    RUN_TEST(test_bad_triangle);

    RUN_TEST(test_screen_width_bigger_height_triangle);
    RUN_TEST(test_screen_width_smaller_height_triangle);

    RUN_TEST(test_clip_bottom);
    RUN_TEST(test_clip_top);
    RUN_TEST(test_clip_left);
    RUN_TEST(test_clip_right);

    return UNITY_END();
}
