public class Point {
    private final double x;
    private final double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double x() {
        return x;
    }

    public double y() {
        return y;
    }

    @Override
    public String toString() {
        return String.format("Point [x=%s, y=%s]", x, y);
    }

    public double distance(Point p) {
        return Math.sqrt(Math.pow(p.x() - x, 2) + Math.pow(p.y() - y, 2));
    }
}
