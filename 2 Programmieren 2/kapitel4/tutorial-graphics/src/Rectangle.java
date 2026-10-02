import java.awt.*;

public class Rectangle extends GraphicalObject {
    protected int w;
    protected int h;

    public Rectangle(int x, int y, int w, int h) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
    }

    @Override
    public void draw(Window window) {
        super.draw(window);
    }

    @Override
    public String toString() {
        return "Rectangle{w=%d, h=%d, x=%d, y=%d}".formatted(w, h, x, y);
    }
}
