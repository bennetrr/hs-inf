#include <cgclib/raster/Triangle.h>
#include <cgclib/sys/PixelBuffer.h>
#include <unity/unity.h>

#define TEST_HELPER(NAME__)                                                                                            \
  {                                                                                                                    \
    ComparePixelBufferResult compareResults;                                                                           \
    ComparePixelBufferToFile(p, REL_SRC_PATH "/" NAME__ "_ref.png", NAME__ "_student.png", NAME__ "_diff.png",         \
                             &compareResults, false);                                                                  \
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

static void test_draw_rainboaw_triangle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);

  Vec3 aColor = {1, 0, 1};
  Vec3 bColor = {1, 1, 0};
  Vec3 cColor = {0, 1, 1};

  DrawTriangleGouraud(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                      FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f),
                      aColor, bColor, cColor);
  TEST_HELPER("test_draw_rainboaw_triangle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_green_triangle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);

  Vec3 aColor = {0, 1, 0};
  Vec3 bColor = {0, 1, 0};
  Vec3 cColor = {0, 1, 0};

  DrawTriangleGouraud(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                      FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f),
                      aColor, bColor, cColor);

  TEST_HELPER("test_draw_green_triangle");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_blue_triangle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);

  Vec3 color = {0, 0, 1};

  Vec3 aColor = {0.9, 0, 1};
  Vec3 bColor = {0, 0, 1};
  Vec3 cColor = {0, 0.9, 1};

  DrawTriangleGouraud(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                      FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f),
                      aColor, bColor, cColor);
  TEST_HELPER("test_draw_blue_triangle");
  DESTROY_PIXEL_BUFFER();
}

static void test_screen_filling_triangle(void)
{
  CREATE_PIXEL_BUFFER(512, 512);

  Vec3 aColor = {1, 0, 1};
  Vec3 bColor = {1, 1, 0};
  Vec3 cColor = {0, 1, 1};
  DrawTriangleGouraud(p, FloatToFixed(p.width * 0.0f), FloatToFixed(p.height * 0.0f), FloatToFixed(3.0f * p.width),
                      FloatToFixed(0.0f * p.height), FloatToFixed(0.0f * p.width), FloatToFixed(p.height * 3.0f),
                      aColor, bColor, cColor);
  TEST_HELPER("test_screen_filling_triangle");
  DESTROY_PIXEL_BUFFER();
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_draw_rainboaw_triangle);
  RUN_TEST(test_draw_green_triangle);
  RUN_TEST(test_draw_blue_triangle);
  RUN_TEST(test_screen_filling_triangle);
  return UNITY_END();
}
