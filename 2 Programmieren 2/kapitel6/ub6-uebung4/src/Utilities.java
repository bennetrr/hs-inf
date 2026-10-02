public class Utilities {
    public static <T> void print(T[] array) {
        System.out.print('[');

        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]);

            if (i != array.length - 1) {
                System.out.print(',');
            }
        }

        System.out.println(']');
    }

    public static <T extends Comparable<T>> void sortiere(T[] array) {
        int n = array.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j].compareTo(array[j + 1]) > 0) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    @SafeVarargs
    public static <T> T noNull(T... array) {
        for (T t : array) {
            if (t != null) {
                return t;
            }
        }

        return null;
    }
}
