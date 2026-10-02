import java.util.Scanner;

import static java.lang.String.join;
import static java.util.Collections.nCopies;

public class Main {
    /*
     * Magisches Quadrat:
     * - Quadrat mit Kantenlänge n, gefüllt mit natürlichen Zahlen von 1 bis n²
     * - Summen aller Spalten, Zeilen und Hauptdiagonalen sind gleich (Hauptdiagonale geht von links oben nach rechts unten)
     *
     * Lösungsalgorithmus für magische Quadrate mit ungeraden n:
     * - Benutzereingabe einer Zahl n (n ungerade und 2 < n < 10)
     * - 2-dimensionales Array (jeweils n Elemente)
     * - zeile = n/2, spalte = n/2 + 1, m = 0
     * - Do while solange m < n²
     *   - m++
     *   - array[zeile][spalte] = m
     *   - zeile--, spalte++
     *   - wenn zeile < 1: zeile = n - 1
     *   - wenn spalte > n: spalte = 0
     *   - wenn array[zeile][spalte] == null:
     *     - zeile++; spalte++;
     *     - wenn zeile bzw. spalte > n: zeile bzw. spalte = 0
     */
    public static void main(String[] args) {
        var sc = new Scanner(System.in);
        int n;

        do {
            System.out.println("Bitte n eingeben (n ungerade, 2 < n < 10):");
            n = sc.nextInt();

        } while (n % 2 != 1 || 2 >= n || n >= 10);

        var arr = new int[n][n];
        var zeile = n / 2;
        var spalte = n / 2 + 1;
        var m = 0;

        do {
            arr[zeile][spalte] = ++m;
//            printArray(arr, zeile, spalte); // DEBUG

            if (--zeile < 0) {
                zeile = n - 1;
            }
            if (++spalte >= n) {
                spalte = 0;
            }

//            printArray(arr, zeile, spalte); // DEBUG

            if (arr[zeile][spalte] != 0) {
                if (++zeile >= n) {
                    zeile = 0;
                }
                if (++spalte >= n) {
                    spalte = 0;
                }
            }

//            printArray(arr, zeile, spalte); // DEBUG
        } while (m < Math.pow(n, 2));

        printArray(arr, null, null);
    }

    static void printArray(int[][] array, Integer markedRow, Integer markedColumn) {
        var maxStringSize = 4;
        var output = new StringBuilder();

        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[i].length; j++) {
                int element = array[i][j];
                var anzahlLeerzeichen = maxStringSize - String.valueOf(element).length();  // Anzahl der fehlenden Leerzeichen berechnen.
                output.append(join("", nCopies(anzahlLeerzeichen, " ")));  // Leerzeichen auffüllen.

                boolean markField = markedRow != null && markedColumn != null && markedRow == i && markedColumn == j;
                if (markField) {
                    output.append("\033[46m\033[30m");
                }

                output.append(element);  // Zahlen einfügen.

                if (markField) {
                    output.append("\033[0m");
                }
            }

            output.append("\n");  // Neue Zeile.
        }
        System.out.println(output);
    }
}
