class PointTest {
    public static void main(String[] args) {
        testThePointClass();
    }

    public static void testThePointClass() {
        Point p1 = new Point(-10, 120);
        System.out.println("p1: " + p1);

        Point p2 = new Point(50, 100);
        System.out.println("p2.x: " + p2.x());
        System.out.println("p2.y: " + p2.y());

        Point p3 = new Point(20, 28);
        System.out.println("p3: " + p3);

        System.out.println("Distance |p3 - p2|: " + (p3.distance(p2) == 78.0 ? "korrekt" : "falsch"));
    }
}
