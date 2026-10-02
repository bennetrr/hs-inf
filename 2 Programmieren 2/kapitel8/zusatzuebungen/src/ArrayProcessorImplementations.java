// Aufgabe 5
public class ArrayProcessorImplementations {
    public static final ArrayProcessor max = array -> {
        double max = 0;
        for (double d : array) {
            if (d > max) {
                max = d;
            }
        }
        return max;
    };

    public static final ArrayProcessor min = array -> {
        double min = Double.MAX_VALUE;
        for (double d : array) {
            if (d < min) {
                min = d;
            }
        }
        return min;
    };

    public static final ArrayProcessor sum = array -> {
        double sum = 0;
        for (double d : array) {
            sum += d;
        }
        return sum;
    };

    public static final ArrayProcessor avg = array -> {
        var sum = ArrayProcessorImplementations.sum.apply(array);
        return sum / array.length;
    };
}
