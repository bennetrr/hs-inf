public class MobileTest {
    public static void Main() {
        var mobile = new Wire(
                new Wire(
                        new Star(2),
                        new GlitterStar(4, 3),
                        9
                ),
                new Star(9),
                10
        );

        mobile.balance();
        System.out.println(mobile);
    }
}
