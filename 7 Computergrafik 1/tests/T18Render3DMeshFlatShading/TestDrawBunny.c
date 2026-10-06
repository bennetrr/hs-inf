
#include <../../labs/A07FlatShading/Render3DMeshFlatShading.h>
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/sys/PixelBuffer.h>
#include <unity/unity.h>

#define TEST_HELPER(NAME__)                                                                                            \
  {                                                                                                                    \
    ComparePixelBufferResult compareResults;                                                                           \
    ComparePixelBufferToFile(p, REL_SRC_PATH "/" NAME__ "_ref.png", NAME__ "_student.png", NAME__ "_diff.png",         \
                             &compareResults, false);                                                                   \
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
  LoadSimpleMeshIO("../../../data/Bunny2k.smm", &mesh);
}
void tearDown(void)
{
  DestroySimpleMeshIO(&mesh);
}

static void test_draw_bunny_0_degrees(void)
{
  CREATE_PIXEL_BUFFER(512, 512);  
  float degrees = 0;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_0_degrees");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_bunny_90_degrees(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  float degrees = 90;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_90_degrees");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_bunny_180_degrees(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  float degrees = 180;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_180_degrees");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_bunny_270_degrees(void)
{
  CREATE_PIXEL_BUFFER(512, 512);
  float degrees = 270;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_270_degrees");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_bunny_width_greater_height_90_degrees(void)
{
  CREATE_PIXEL_BUFFER(768, 512);
  float degrees = 90;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_width_greater_height_90_degrees");
  DESTROY_PIXEL_BUFFER();
}

static void test_draw_bunny_height_greater_width_90_degrees(void)
{
  CREATE_PIXEL_BUFFER(512, 768);
  float degrees = 90;
  p.time        = degrees * 180.0f / (0.1f * (float)M_PI);
  RenderScene(p);
  TEST_HELPER("test_draw_bunny_height_greater_width_90_degrees");
  DESTROY_PIXEL_BUFFER();
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_draw_bunny_0_degrees);
  RUN_TEST(test_draw_bunny_90_degrees);
  RUN_TEST(test_draw_bunny_180_degrees);
  RUN_TEST(test_draw_bunny_270_degrees);
  RUN_TEST(test_draw_bunny_width_greater_height_90_degrees);
  RUN_TEST(test_draw_bunny_height_greater_width_90_degrees);

  return UNITY_END();
}
