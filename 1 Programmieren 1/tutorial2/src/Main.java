import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (var scanner = new Scanner(System.in)) {
            System.out.println("Bitte Messwerte eingeben:");

            int countOfNegative1 = 0;
            boolean isLastNumber0 = false;

            while (countOfNegative1 <= 3) {
                int n = scanner.nextInt();

                if (n == -1) {
                    countOfNegative1++;
                }

                if (n < 0) {
                    continue;
                }

                if (n == 0) {
                    if (isLastNumber0) {
                        continue;
                    }

                    isLastNumber0 = true;
                }

                System.out.print(n + " ");
            }
        }
    }
}
