import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Notendurchschnittsermittlung");
        System.out.println("----------------------------");

        try (var scanner = new Scanner(System.in)) {
            var points = new ArrayList<Integer>();

            while (true) {
                System.out.print("Bitte Punkte eingeben (q zum auswerten): ");
                var input = scanner.next();

                if (input.toLowerCase().contains("q")) {
                    break;
                }

                var currentPoints = Integer.parseInt(input);
                if (currentPoints > 100) {
                    System.out.println("Punkte dürfen nicht größer als 100 sein!");
                    continue;
                }

                points.add(currentPoints);
                System.out.println(gradeFeedback(currentPoints));
                System.out.println();
            }

            var avg = points.stream().mapToInt(Integer::intValue).average().orElse(0.0);

            System.out.printf("Punktedurchschnitt: %.2f\n", avg);
            System.out.printf("Notendurchschnitt: %.2f\n", 6 - (avg / 20));
        }
    }

    private static String gradeFeedback(int points) {
        if (points < 20) return "Note 5. Das musst du wohl nochmal schreiben!";
        if (points < 40) return "Note 4. Das geht noch besser!";
        if (points < 60) return "Note 3. Weiter so! Schau dir nochmal die Fehler an";
        if (points < 80) return "Note 2. Gut gemacht!";
        return "Note 1: Super! Jetzt bekommt dein Lehrer einen Bonus";
    }
}
