public class DateTest {
    public static void main(String[] args) {
        testTheDateClass();
    }

    private static void test(int num, String expected, String actual) {
        if (expected.equals(actual)) {
            System.out.println("Testcase " + num + " correct: " + actual);
        } else {
            System.out.println("Testcase " + num + " incorrect: " + actual);
        }
    }

    public static void testTheDateClass() {
        test(
                1,
                "Month: 2 Day: 1 Year: 2001",
                new Date(2, 1, 2001).toString()
        );

        test(
                2,
                "Month: 2 Day: 11 Year: 1998",
                new Date(2, 11, 1998).toString()
        );

        test(
                3,
                "Month: 2 Day: 1 Year: 1998",
                new Date("Februar", 1, 1998).toString()
        );

        test(
                4,
                "Day:11 Month:Februar Year: 1998",
                new Date("Februar", 11, 1998).getDate(2)
        );

        test(
                5,
                "Day:11 Month: 2 Year: 1998",
                new Date("Februar", 11, 1998).getDate(3)
        );

        test(
                6,
                "Day:11 Month: 2 Year: 1998",
                new Date("Februar", 11, 1998).getDate(4)
        );

        test(
                7,
                "Day:30 Month: 6 Year: 2023",
                new Date(6, 30, 2023).getDate(3)
        );
    }
}
