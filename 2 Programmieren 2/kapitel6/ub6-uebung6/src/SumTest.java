import java.util.Arrays;

public class SumTest {
    public static void testSumOfList() {
        var arr1 = new Integer[]{4, 6, 88, 99, -100, 78};
        var arr2 = new Double[]{3.0, 4.5, 78.0, 10.0, -10.0, 7.8};

        System.out.println(SumOfList.sumOfList(Arrays.asList(arr1)));
        System.out.println(SumOfList.sumOfList(Arrays.asList(arr2)));
    }

    public static void main(String[] args) {
        testSumOfList();
    }
}
