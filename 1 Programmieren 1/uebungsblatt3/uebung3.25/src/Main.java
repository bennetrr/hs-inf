import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("Operation (+,-,*,/) eingeben:");
            String operator = sc.next();

            int num1 = sc.nextInt();
            int num2 = sc.nextInt();

            String question = num1 + " " + operator + " " + num2;

            int result = switch (operator) {
                case "+" -> num1 + num2;
                case "-" -> num1 - num2;
                case "*" -> num1 * num2;
                case "/" -> num1 / num2;
                default -> throw new Error("Ungültiger Operator: " + operator);
            };

            boolean solved = false;

            for (int i = 2, j = 1; i >= 0; i--, j++) {
                System.out.println(question + " =");
                System.out.print("> ");
                int userResult = sc.nextInt();
                System.out.println(userResult);

                if (userResult == result) {
                    System.out.println("Super! Beim + " + j + ". Mal richtig");
                    solved = true;
                    break;
                }

                if (i == 0) {
                    break;
                }

                System.out.println("Denke nochmals nach und wiederhole die Aufgabe (noch " + i + " Versuche!)");
            }

            if (!solved) {
                System.out.println("Du musst es dir nochmal erklaeren lassen");
            }


            System.out.println("Neue Aufgabe? (j = ja)");
            if (sc.next().equalsIgnoreCase("j")) {
                continue;
            }
            break;
        }
    }
}
