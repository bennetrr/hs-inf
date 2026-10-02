public class TriangleTest {
    public static void withinTol(double a, double b) {
        System.out.println(Math.abs(a - b) < 1 ? "korrekt" : "falsch");
    }

    public static void testTheTriangleClass() {
        // Erzeuge Dreieck [-10,0], [0,24], [45,100]
        var t1 = new Triangle(new Point(-10, 0), new Point(0, 24), new Point(45, 100));
        System.out.println("t1: " + t1);

        System.out.print("Umfang für t1: ");
        System.out.println(t1.perimeter());

        System.out.print("Fläche für t1: ");
        System.out.println(t1.area());

        System.out.println("Strecken um den Punkt [0,1]  mit Faktor -1:");
        var t2 = t1.zoomed(new Point(0, 1), -1);
        System.out.println(t2);

        System.out.println("Verschiebe um dx 0 und dy -1:");
        System.out.println(t2.moved(0, -1));
    }
}
