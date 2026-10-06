#include <cgclib/raster/TriangleCull.h>
#include <unity/unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_ComputeClippedBoundBox_TriangleInside(void)
{
  const BoundingBox bb = ComputeClippedBoundBox(1920, 1080, IntToFixed(10), IntToFixed(5), IntToFixed(100),
                                                IntToFixed(10), IntToFixed(50), IntToFixed(150));
  TEST_ASSERT_EQUAL_INT32(10, bb.x0);
  TEST_ASSERT_EQUAL_INT32(100, bb.x1);
  TEST_ASSERT_EQUAL_INT32(5, bb.y0);
  TEST_ASSERT_EQUAL_INT32(150, bb.y1);
}

static void test_ComputeClippedBoundBox_LeftClippedTriangle(void)
{
  const BoundingBox bb = ComputeClippedBoundBox(1920, 1080, IntToFixed(-10), IntToFixed(5), IntToFixed(100),
                                                IntToFixed(10), IntToFixed(50), IntToFixed(150));
  TEST_ASSERT_EQUAL_INT32(0, bb.x0);
  TEST_ASSERT_EQUAL_INT32(100, bb.x1);
  TEST_ASSERT_EQUAL_INT32(5, bb.y0);
  TEST_ASSERT_EQUAL_INT32(150, bb.y1);
}

static void test_ComputeClippedBoundBox_RightClippedTriangle(void)
{
  const BoundingBox bb = ComputeClippedBoundBox(1920, 1080, IntToFixed(10), IntToFixed(5), IntToFixed(2000),
                                                IntToFixed(10), IntToFixed(50), IntToFixed(150));
  TEST_ASSERT_EQUAL_INT32(10, bb.x0);
  TEST_ASSERT_EQUAL_INT32(1919, bb.x1);
  TEST_ASSERT_EQUAL_INT32(5, bb.y0);
  TEST_ASSERT_EQUAL_INT32(150, bb.y1);
}

static void test_ComputeClippedBoundBox_BottomClippedTriangle(void)
{
  const BoundingBox bb = ComputeClippedBoundBox(1920, 1080, IntToFixed(10), IntToFixed(-50), IntToFixed(100),
                                                IntToFixed(10), IntToFixed(50), IntToFixed(150));
  TEST_ASSERT_EQUAL_INT32(10, bb.x0);
  TEST_ASSERT_EQUAL_INT32(100, bb.x1);
  TEST_ASSERT_EQUAL_INT32(0, bb.y0);
  TEST_ASSERT_EQUAL_INT32(150, bb.y1);
}

static void test_ComputeClippedBoundBox_TopClippedTriangle(void)
{
  const BoundingBox bb = ComputeClippedBoundBox(1920, 1080, IntToFixed(10), IntToFixed(5), IntToFixed(100),
                                                IntToFixed(10), IntToFixed(50), IntToFixed(2000));
  TEST_ASSERT_EQUAL_INT32(10, bb.x0);
  TEST_ASSERT_EQUAL_INT32(100, bb.x1);
  TEST_ASSERT_EQUAL_INT32(5, bb.y0);
  TEST_ASSERT_EQUAL_INT32(1079, bb.y1);
}

static void test_IsBoundingBoxZero_PointBoundingBox(void)
{
  BoundingBox bb = {10, 10, 10, 10};
  TEST_ASSERT_TRUE(IsBoundingBoxZero(bb));
}

static void test_IsBoundingBoxZero_TinySquare(void)
{
  BoundingBox bb = {10, 10, 11, 11};
  TEST_ASSERT_FALSE(IsBoundingBoxZero(bb));
}

static void test_IsBoundingBoxZero_Line(void)
{
  BoundingBox bb = {10, 10, 10, 100};
  TEST_ASSERT_TRUE(IsBoundingBoxZero(bb));
}

static void test_IsBoundingBoxZero_NonZeroBoundingBox(void)
{
  BoundingBox bb = {10, 10, 100, 100};
  TEST_ASSERT_FALSE(IsBoundingBoxZero(bb));
}

static void test_IsBackFace_Degenerate(void)
{
  TEST_ASSERT_TRUE(
      IsBackFace(IntToFixed(0), IntToFixed(0), IntToFixed(100), IntToFixed(0), IntToFixed(50), IntToFixed(0)));
}


static void test_IsDegenerate_DegenrateTriangle(void)
{
  TEST_ASSERT_TRUE(
      IsDegenerate(IntToFixed(10), IntToFixed(20), IntToFixed(10), IntToFixed(20), IntToFixed(50), IntToFixed(0)));
  TEST_ASSERT_TRUE(
      IsDegenerate(IntToFixed(10), IntToFixed(20), IntToFixed(20), IntToFixed(30), IntToFixed(20), IntToFixed(30)));
  TEST_ASSERT_TRUE(
      IsDegenerate(IntToFixed(10), IntToFixed(20), IntToFixed(20), IntToFixed(30), IntToFixed(10), IntToFixed(20)));
}

int main(void)
{
  UNITY_BEGIN();
  


  RUN_TEST(test_ComputeClippedBoundBox_TriangleInside);
  RUN_TEST(test_ComputeClippedBoundBox_LeftClippedTriangle);
  RUN_TEST(test_ComputeClippedBoundBox_RightClippedTriangle);
  RUN_TEST(test_ComputeClippedBoundBox_BottomClippedTriangle);
  RUN_TEST(test_ComputeClippedBoundBox_TopClippedTriangle);

  RUN_TEST(test_IsBoundingBoxZero_PointBoundingBox);
  RUN_TEST(test_IsBoundingBoxZero_TinySquare);
  RUN_TEST(test_IsBoundingBoxZero_Line);
  RUN_TEST(test_IsBoundingBoxZero_NonZeroBoundingBox);

  return UNITY_END();
}
