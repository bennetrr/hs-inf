import java.awt.*;

public class Circle extends GraphicalObject {
    protected int radius;

    public Circle(int x, int y, int radius) {
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    @Override
    public void draw(Window window) {
        super.draw(window);
    }

    @Override
    public String toString() {
        return "Circle{radius=%d, x=%d, y=%d}".formatted(radius, x, y);
    }
}
