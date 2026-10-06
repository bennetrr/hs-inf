#include <cgclib/raster/TriangleCull.h>
#include <unity/unity.h>

void setUp(void)
{
}

void tearDown(void)
{
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

static void test_IsDegenerate_NonDegenrateTriangle(void)
{
  TEST_ASSERT_FALSE(
      IsDegenerate(IntToFixed(10), IntToFixed(10), IntToFixed(100), IntToFixed(10), IntToFixed(50), IntToFixed(110)));
  TEST_ASSERT_FALSE(
      IsDegenerate(IntToFixed(10), IntToFixed(10), IntToFixed(100), IntToFixed(10), IntToFixed(10), IntToFixed(50)));
}

int main(void)
{
  UNITY_BEGIN();
  


  RUN_TEST(test_IsDegenerate_DegenrateTriangle);
  
  return UNITY_END();
}
