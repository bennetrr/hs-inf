import org.junit.jupiter.api.Test;

import static java.lang.String.join;
import static java.util.Collections.nCopies;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;

class MainTest {
    static void printArray(int[][] array) {
        var maxStringSize = 0;
        for (int[] zeile : array) {
            for (int element : zeile) {
                var currentStringSize = String.valueOf(element).length();
                if (maxStringSize < currentStringSize) maxStringSize = currentStringSize;
            }
        }
        maxStringSize++;  // Füge ein Leerzeichen hinzu, damit die Zahlen nicht direkt aneinander gesetzt werden.

        var output = new StringBuilder();
        for (int[] zeile : array) {
            output.append("│");  // Matrix-Rahmen links zeichnen.

            for (int element : zeile) {
                var anzahlLeerzeichen = maxStringSize - String.valueOf(element).length();  // Anzahl der fehlenden Leerzeichen berechnen.
                output.append(join("", nCopies(anzahlLeerzeichen, " ")));  // Leerzeichen auffüllen.
                output.append(element);  // Zahlen einfügen.
            }

            output.append(" │");  // Matrix-Rahmen rechts zeichnen.
            output.append("\n");  // Neue Zeile.
        }
        System.out.println(output);
    }

    @Test
    void testSum() {
        // Arrange
        int[][] input = {
                {10, 11, 12, 13, 14},
                {15, 16, 17, 18, 19},
                {20, 21, 22, 23, 24},
                {25, 26, 27, 28, 29}
        };

        int[][] expected = {
                {10, 11, 12, 13, 14, 60},
                {15, 16, 17, 18, 19, 85},
                {20, 21, 22, 23, 24, 110},
                {25, 26, 27, 28, 29, 135},
                {70, 74, 78, 82, 86, 0}
        };

        // Act
        int[][] result = Main.calculateTable(input, 's');

        // Assert
        printArray(result);
        assertArrayEquals(expected, result);
    }

    @Test
    void testInit() {
        // Arrange
        int[][] input = {
                {101, 111, 112, 113, 114},
                {5, 216, 317, 418, 219},
                {0, 21, 28, 4, 20},
                {5, 6, 7, 38, 40}
        };

        int[][] expected = {
                {10, 11, 12, 13, 14},
                {15, 16, 17, 18, 19},
                {20, 21, 22, 23, 24},
                {25, 26, 27, 28, 29}
        };

        // Act
        int[][] result = Main.calculateTable(input, 'i');

        // Assert
        printArray(result);
        assertArrayEquals(expected, result);
    }

    @Test
    void testRightShift() {
        // Arrange
        int[][] input = {
                {10, 11, 12, 13, 14},
                {15, 16, 17, 18, 19},
                {20, 21, 22, 23, 24},
                {25, 26, 27, 28, 29}
        };

        int[][] expected = {
                {0, 10, 11, 12, 13},
                {0, 15, 16, 17, 18},
                {0, 20, 21, 22, 23},
                {0, 25, 26, 27, 28}
        };

        // Act
        int[][] result = Main.calculateTable(input, 'r');

        // Assert
        printArray(result);
        assertArrayEquals(expected, result);
    }
}
