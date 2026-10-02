import java.util.List;

public class SumOfList {
    public static <T extends Number> double sumOfList(List<T> arr) {
        double sum = 0;

        for (T t : arr) {
            sum += t.doubleValue();
        }

        return sum;
    }
}
