import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;

public class ElementUtils {
    // Aufgabe 1 und 2
    public static <T> List<T> allMatches(List<T> values, Predicate<T> predicate) {
//        return values.stream().filter(predicate).toList();
        List<T> result = new ArrayList<>();

        for (T value : values) {
            if (predicate.test(value)) {
                result.add(value);
            }
        }

        return result;
    }

    // Aufgabe 3 und 4
    public static <Tin, Tout> List<Tout> transformedList(List<Tin> values, Function<Tin, Tout> function) {
//        return values.stream().map(function).toList();
        List<Tout> result = new ArrayList<>();

        for (Tin value : values) {
            result.add(function.apply(value));
        }

        return result;
    }
}
