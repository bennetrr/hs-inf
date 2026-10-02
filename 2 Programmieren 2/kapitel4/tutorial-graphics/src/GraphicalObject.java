import java.awt.*;

public class GraphicalObject {
    protected int x;
    protected int y;

    public void draw(Window window) {

    }

    @Override
    public String toString() {
        return "GraphicalObject{x=%d, y=%d}".formatted(x, y);
    }
}
