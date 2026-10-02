import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Aufgabe 1
        var words = List.of("hi", "hello", "hola", "bye", "goodbye", "adios");
        var shortWords = ElementUtils.allMatches(words, s -> s.length() < 4);
        var wordsWithB = ElementUtils.allMatches(words, s -> s.contains("b"));
        var evenLengthWords = ElementUtils.allMatches(words, s -> (s.length() % 2) == 0);

        System.out.println("Short words: " + shortWords);
        System.out.println("Words with 'b': " + wordsWithB);
        System.out.println("Even-length words: " + evenLengthWords);
        System.out.println();

        // Aufgabe 2
        var nums = List.of(1, 10, 100, 1000, 10000);
        var bigNums = ElementUtils.allMatches(nums, n -> n > 500);
        var numsWithZero = ElementUtils.allMatches(nums, n -> n.toString().contains("0"));

        System.out.println("Big numbers: " + bigNums);
        System.out.println("Numbers with zero: " + numsWithZero);
        System.out.println();

        // Aufgabe 3
        var excitingWords = ElementUtils.transformedList(words, s -> s + "!");
        var eyeWords = ElementUtils.transformedList(words, s -> s.replace("i", "eye"));
        var upperCaseWords = ElementUtils.transformedList(words, String::toUpperCase);

        System.out.println("Exciting words: " + excitingWords);
        System.out.println("Eye words: " + eyeWords);
        System.out.println("Uppercase words: " + upperCaseWords);
        System.out.println();

        // Aufgabe 4
        var wordLengths = ElementUtils.transformedList(words, String::length);
        var numsPlus100 = ElementUtils.transformedList(nums, n -> n + 100);

        System.out.println("Word lengths: " + wordLengths);
        System.out.println("Numbers plus 100: " + numsPlus100);
        System.out.println();

        // Aufgabe 5
        double[] numsArray = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
        var min = ArrayProcessorImplementations.min.apply(numsArray);
        var max = ArrayProcessorImplementations.max.apply(numsArray);
        var sum = ArrayProcessorImplementations.sum.apply(numsArray);
        var avg = ArrayProcessorImplementations.avg.apply(numsArray);

        System.out.println("Min: " + min);
        System.out.println("Max: " + max);
        System.out.println("Sum: " + sum);
        System.out.println("Avg: " + avg);

        // Andere Aufgaben
        String firstWithO = words.stream().filter(s -> s.contains("o")).findFirst().orElse(null);
        System.out.println("First word with 'o': " + firstWithO);
    }
}
