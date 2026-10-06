#include <cgclib/raster/Circle.h>
#include <cgclib/sys/PixelBuffer.h>
#include <unity/unity.h>

#define TEST_HELPER(NAME__)                                                                                            \
  {                                                                                                                    \
    ComparePixelBufferResult compareResults;                                                                           \
    ComparePixelBufferToFile(p, REL_SRC_PATH "/" NAME__ "_ref.png", NAME__ "_student.png", NAME__ "_diff.png",         \
                             &compareResults, false);                                                        \
    TEST_ASSERT_EQUAL(false, compareResults.WidthMismatch);                                                            \
    TEST_ASSERT_EQUAL(false, compareResults.HeightMismatch);                                                           \
    TEST_ASSERT_EQUAL(false, compareResults.PixelMismatch);                                                            \
  }

#define CREATE_PIXEL_BUFFER(WIDTH__, HEIGHT__)                                                                         \
  PixelBuffer p = {0};                                                                                                 \
  int32_t     r = CreatePixelBuffer(&p, WIDTH__, HEIGHT__, true);                                                      \
  if (r != 0)                                                                                                          \
    TEST_FAIL_MESSAGE("Could not allocate pixel buffer\n");                                                            \
  ClearColorBuffer(p, 0xffffffff);

#define DESTROY_PIXEL_BUFFER() DestroyPixelBuffer(&p, true);

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_draw_red_circle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  DrawCircle(p, 256, 256, 192, Color(255, 0, 0));
  TEST_HELPER("test_draw_red_circle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_green_circle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  DrawCircle(p, 256, 256, 192, Color(0, 255, 0));
  TEST_HELPER("test_draw_green_circle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_blue_circle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  DrawCircle(p, 256, 256, 192, Color(0, 0, 255));
  TEST_HELPER("test_draw_blue_circle");  
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_tall_window_circle(void)
{
  CREATE_PIXEL_BUFFER(128, 256);
  DrawCircle(p, 64, 128, 48, Color(255, 255, 0));
  TEST_HELPER("test_draw_tall_window_circle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_wide_window_circle(void)
{
  CREATE_PIXEL_BUFFER(256, 128);
  DrawCircle(p, 128, 64, 48, Color(255, 255, 0));
  TEST_HELPER("test_draw_wide_window_circle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_clipped_circle(void)
{
  CREATE_PIXEL_BUFFER(256, 256);
  DrawCircle(p, 128, 128, 160, Color(0, 255, 255));
  TEST_HELPER("test_draw_clipped_circle");
  DESTROY_PIXEL_BUFFER();
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_draw_red_circle);
  RUN_TEST(test_draw_green_circle);
  RUN_TEST(test_draw_blue_circle);

  RUN_TEST(test_draw_tall_window_circle);
  RUN_TEST(test_draw_wide_window_circle);
  RUN_TEST(test_draw_clipped_circle);

  return UNITY_END();
}
