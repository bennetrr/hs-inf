import org.junit.jupiter.api.Test;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import static org.junit.jupiter.api.Assertions.*;

class TriangleUnitTest {
    @Test
    void testTheTriangleClassTest() {
        // Arrange

        // Replace System.out with a ByteArrayOutputStream
        var originalOut = System.out;
        var baos = new ByteArrayOutputStream();
        var newOut = new PrintStream(baos);
        System.setOut(newOut);

        var expected = """
            t1: Triangle [p0=Point [x=-10.0, y=0.0], p1=Point [x=0.0, y=24.0], p2=Point [x=45.0, y=100.0]]
            Umfang für t1: 228.45039197213944
            Fläche für t1: 160.00000000000503
            Strecken um den Punkt [0,1]  mit Faktor -1:
            Triangle [p0=Point [x=10.0, y=2.0], p1=Point [x=0.0, y=-22.0], p2=Point [x=-45.0, y=-98.0]]
            Verschiebe um dx 0 und dy -1:
            Triangle [p0=Point [x=10.0, y=1.0], p1=Point [x=0.0, y=-23.0], p2=Point [x=-45.0, y=-99.0]]
            """;

        // Act
        TriangleTest.testTheTriangleClass();

        System.setOut(originalOut);
        String actual = baos.toString();

        // Assert
        assertEquals(expected, actual);
    }

    @Test
    void testPerimeter() {
        // Arrange
        var t1 = new Triangle(new Point(50, 0), new Point( 100, 20), new Point( 11, 20));
        var expected = 186.6808620729673;

        // Act
        var actual = t1.perimeter();

        // Assert
        assertEquals(expected, actual, 0.0000000000001);
    }

    @Test
    void testArea() {
        // Arrange
        var t1 = new Triangle(new Point(-50, -40), new Point( 100, 120), new Point(10, 60));
        var expected = 2699.9999999999873;

        // Act
        var actual = t1.area();

        // Assert
        assertEquals(expected, actual, 0.0000000000001);
    }

    @Test
    void testPointToString() {
        // Arrange
        var t1 = new Triangle(new Point(-50, -40), new Point( 100, 120), new Point(10, 60));

        var expectedP0 = "Point [x=-50.0, y=-40.0]";
        var expectedP1 = "Point [x=100.0, y=120.0]";
        var expectedP2 = "Point [x=10.0, y=60.0]";

        // Act
        var actualP0 = t1.p0().toString();
        var actualP1 = t1.p1().toString();
        var actualP2 = t1.p2().toString();

        // Assert
        assertEquals(expectedP0, actualP0);
        assertEquals(expectedP1, actualP1);
        assertEquals(expectedP2, actualP2);
    }

    @Test
    void testZoomedFromOrigin() {
        // Arrange
        var t1 = new Triangle(new Point(-50, -40), new Point( 100, 120), new Point(10, 60));
        var expected = new Triangle(new Point(-100, -80), new Point( 200, 240), new Point(20, 120));

        // Act
        var actual = t1.zoomed(2);

        // Assert
        assertEquals(expected, actual);
    }

    @Test
    void testZoomedFromPoint() {
        // Arrange
        var t1 = new Triangle(new Point(-50, -40), new Point( 100, 120), new Point(10, 60));
        var p = new Point(30,40);
        var expected = new Triangle(new Point(-130, -120), new Point( 170, 200), new Point(-10, 80));

        // Act
        var actual = t1.zoomed(p, 2);

        // Assert
        assertEquals(expected, actual);
    }

    @Test
    void testMoved() {
        // Arrange
        var t1 = new Triangle(new Point(-50, -40), new Point( 100, 120), new Point(10, 60));
        var expected = new Triangle(new Point(-40, -20), new Point( 110, 140), new Point(20, 80));

        // Act
        var actual = t1.moved(10, 20);

        // Assert
        assertEquals(expected, actual);
    }

    @Test
    void testBoundingBox() {
        // Arrange
        var t1 = new Triangle(new Point(-150, 500), new Point( 10, 60), new Point(105, 160));
        var expectedLowerLeft = new Point(-150, 60);
        var expectedUpperRight = new Point(105, 500);

        // Act
        var actualLowerLeft = t1.lowerLeft();
        var actualUpperRight = t1.upperRight();

        // Assert
        assertEquals(expectedLowerLeft, actualLowerLeft);
        assertEquals(expectedUpperRight, actualUpperRight);
    }
}
