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

    public double distance(Point p) {
        return Math.sqrt(Math.pow(p.x() - x, 2) + Math.pow(p.y() - y, 2));
    }

    public Point moved(double dx, double dy) {
        return new Point(x + dx, y + dy);
    }

    public boolean isSame(Point p, double within) {
        return distance(p) <= within;
    }

    @Override
    public String toString() {
        return String.format("Point [x=%s, y=%s]", x, y);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Point)) {
            return false;
        }
        return x == ((Point) obj).x && y == ((Point) obj).y;
    }
}
