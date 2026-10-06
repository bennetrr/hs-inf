#include <cgclib/raster/TriangleCull.h>
#include <unity/unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_IsBackFace_FrontFace(void)
{
  TEST_ASSERT_FALSE(
      IsBackFace(IntToFixed(0), IntToFixed(0), IntToFixed(100), IntToFixed(0), IntToFixed(0), IntToFixed(100)));
}

static void test_IsBackFace_BackFace(void)
{
  TEST_ASSERT_TRUE(
      IsBackFace(IntToFixed(100), IntToFixed(0), IntToFixed(0), IntToFixed(0), IntToFixed(0), IntToFixed(100)));
}

static void test_IsBackFace_Degenerate(void)
{
  TEST_ASSERT_TRUE(
      IsBackFace(IntToFixed(0), IntToFixed(0), IntToFixed(100), IntToFixed(0), IntToFixed(50), IntToFixed(0)));
}

static void test_IsBoundingBoxAPixel_PixelBox(void)
{
  BoundingBox bb = {10, 10, 11, 11};
  TEST_ASSERT_TRUE(IsBoundingBoxAPixel(bb));
}

static void test_IsBoundingBoxAPixel_ZeroBox(void)
{
  BoundingBox bb = {10, 10, 11, 10};
  TEST_ASSERT_FALSE(IsBoundingBoxAPixel(bb));
}

static void test_IsBoundingBoxAPixel_FourPixelBox(void)
{
  BoundingBox bb = {10, 10, 12, 12};
  TEST_ASSERT_FALSE(IsBoundingBoxAPixel(bb));
}

int main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_IsBackFace_FrontFace);
  RUN_TEST(test_IsBackFace_BackFace);
  RUN_TEST(test_IsBackFace_Degenerate);

  RUN_TEST(test_IsBoundingBoxAPixel_PixelBox);
  RUN_TEST(test_IsBoundingBoxAPixel_ZeroBox);
  RUN_TEST(test_IsBoundingBoxAPixel_FourPixelBox);

  return UNITY_END();
}
