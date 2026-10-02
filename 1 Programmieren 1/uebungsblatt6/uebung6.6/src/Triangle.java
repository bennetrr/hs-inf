import java.util.Objects;

public class Triangle {
    private final Point p1;
    private final Point p2;
    private final Point p3;

    public Triangle(Point p1, Point p2, Point p3) {
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
    }

    public Point p0() {
        return p1;
    }

    public Point p1() {
        return p2;
    }

    public Point p2() {
        return p3;
    }

    public double perimeter() {
        return p1.distance(p2) + p2.distance(p3) + p3.distance(p1);
    }

    public double area() {
        double a = p1.distance(p2);
        double b = p2.distance(p3);
        double c = p3.distance(p1);
        double s = (a + b + c) / 2;
        return Math.sqrt(s * (s - a) * (s - b) * (s - c));
    }

    public Triangle moved(double dx, double dy) {
        return new Triangle(p1.moved(dx, dy), p2.moved(dx, dy), p3.moved(dx, dy));
    }

    public Triangle zoomed(Point center, double factor) {
        var p1Origin = p1.moved(-center.x(), -center.y());
        var p2Origin = p2.moved(-center.x(), -center.y());
        var p3Origin = p3.moved(-center.x(), -center.y());

        var p1Zoomed = new Point(p1Origin.x() * factor, p1Origin.y() * factor);
        var p2Zoomed = new Point(p2Origin.x() * factor, p2Origin.y() * factor);
        var p3Zoomed = new Point(p3Origin.x() * factor, p3Origin.y() * factor);

        var p1Translated = p1Zoomed.moved(center.x(), center.y());
        var p2Translated = p2Zoomed.moved(center.x(), center.y());
        var p3Translated = p3Zoomed.moved(center.x(), center.y());

        return new Triangle(p1Translated, p2Translated, p3Translated);
    }

    public Point lowerLeft() {
        return new Point(Math.min(p1.x(), Math.min(p2.x(), p3.x())), Math.min(p1.y(), Math.min(p2.y(), p3.y())));
    }

    public Point upperRight() {
        return new Point(Math.max(p1.x(), Math.max(p2.x(), p3.x())), Math.max(p1.y(), Math.max(p2.y(), p3.y())));
    }

    public Triangle zoomed(double factor) {
        return zoomed(new Point(0, 0), factor);
    }

    @Override
    public String toString() {
        return "Triangle [p0=" + p0() + ", p1=" + p1() + ", p2=" + p2() + "]";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Triangle triangle = (Triangle) o;

        if (!Objects.equals(p1, triangle.p1)) return false;
        if (!Objects.equals(p2, triangle.p2)) return false;
        return Objects.equals(p3, triangle.p3);
    }
}
