#include <cgclib/raster/Rectangle.h>
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

static void test_draw_red_rectangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 10, 50, 100, 200, Color(255, 0, 0));
    TEST_HELPER("test_draw_red_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_green_rectangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 10, 50, 100, 200, Color(0, 255, 0));
    TEST_HELPER("test_draw_green_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_blue_rectangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 10, 50, 100, 200, Color(0, 0, 255));
    TEST_HELPER("test_draw_blue_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_square(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 100, 100, 300, 300, Color(0, 0, 0));
    TEST_HELPER("test_draw_square");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_tall_rectangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 100, 100, 100, 300, Color(0, 0, 0));
    TEST_HELPER("test_draw_tall_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_wide_rectangle(void)
{
    CREATE_PIXEL_BUFFER(512, 512);
    DrawRectangle(p, 100, 100, 300, 100, Color(0, 0, 0));
    TEST_HELPER("test_draw_wide_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_tall_window_rectangle(void)
{
    CREATE_PIXEL_BUFFER(128, 256);
    DrawRectangle(p, 10, 10, 100, 100, Color(255, 255, 0));
    TEST_HELPER("test_draw_tall_window_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_wide_window_rectangle(void)
{
    CREATE_PIXEL_BUFFER(256, 128);
    DrawRectangle(p, 10, 10, 100, 100, Color(255, 255, 0));
    TEST_HELPER("test_draw_wide_window_rectangle");
    DESTROY_PIXEL_BUFFER();
}

static void test_draw_clipped_rectangle(void)
{
    CREATE_PIXEL_BUFFER(256, 256);
    DrawRectangle(p, 10, 10, 300, 300, Color(0, 255, 255));
    TEST_HELPER("test_draw_clipped_rectangle");
    DESTROY_PIXEL_BUFFER();
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_draw_red_rectangle);
    RUN_TEST(test_draw_green_rectangle);
    RUN_TEST(test_draw_blue_rectangle);

    RUN_TEST(test_draw_square);
    RUN_TEST(test_draw_tall_rectangle);
    RUN_TEST(test_draw_wide_rectangle);

    RUN_TEST(test_draw_tall_window_rectangle);
    RUN_TEST(test_draw_wide_window_rectangle);

    RUN_TEST(test_draw_clipped_rectangle);

    return UNITY_END();
}
