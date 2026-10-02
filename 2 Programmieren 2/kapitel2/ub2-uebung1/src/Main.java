import java.util.Arrays;

public class Main {
    public static void main(String[] s) {
        Integer[] array = {2000, 2, 45, 34, 100000, 345, 56, 78, 99, 756, 999, 0, 666, 2345, 7492, 22};

        // Ausgabe unsortiertes Array
        System.out.println("Unsortiertes Array :" + Arrays.toString(array));

        // bubbleSort Aufruf
        bubbleSort(array);

        // Ausgabe sortiertes Array
        System.out.println("Sortiertes Array :" + Arrays.toString(array));
    }

    public static void bubbleSort(Integer[] array) {
        for (int counter = 0; counter < array.length; counter++) {
            for (int pass = 0; pass < array.length; pass++) {
                for (int element = 0; element < array.length - 1 - pass; element++) {
                    if (array[element] > array[element + 1]) {
                        int temp = array[element];
                        array[element] = array[element + 1];
                        array[element + 1] = temp;
                    }
                }
            }
        }
    }
}
