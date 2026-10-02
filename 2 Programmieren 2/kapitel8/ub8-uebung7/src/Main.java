import java.util.*;

public class Main {
    public static void main(String[] args) {
        testLambdaExpressions();
    }

    public static void testLambdaExpressions() {
        Integer[] values = {2, 9, 5, 0, 3, 7, 1, 4, 8, 6};

        // display original values
        System.out.printf("Original values: %s%n", Arrays.asList(values));

        // Ausgabe aller Werte von values in aufsteigender Reihenfolge
        System.out.println("Sorted values: " + Arrays.toString(Arrays.stream(values).mapToInt(x -> x).sorted().toArray()));

        // Ausgabe aller Werte in values, die größer als 4 sind
        System.out.println("Values greater than 4: " + Arrays.toString(Arrays.stream(values).mapToInt(x -> x).filter(x -> x > 4).toArray()));

        // Filtern von allen Werten in values, die größer als 4 sind, und
        // sortierte diese anschließend
        System.out.println("Sorted values greater than 4: " + Arrays.toString(Arrays.stream(values).mapToInt(x -> x).filter(x -> x > 4).sorted().toArray()));

        System.out.println("Values greater than 4 (ascending with streams):  " + Arrays.toString(Arrays.stream(values).mapToInt(x -> x).filter(x -> x > 4).sorted().toArray()));
    }
}
