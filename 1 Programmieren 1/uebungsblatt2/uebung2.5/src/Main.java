import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Datum eingeben (dd-mm-yyyy): ");
        var input = sc.next();
        var inputParts = input.split("-");

        var day = Integer.parseInt(inputParts[0]);
        var month = Integer.parseInt(inputParts[1]);
        var year = Integer.parseInt(inputParts[2]);

        System.out.println(wochentag(day, month, year));
    }

    public static String wochentag(int day, int month, int year) {
        int d = day;
        int m = month;

        if (m <= 2) m += 12;
        if (m >= 13) year -= 1;

        int c = year / 100;
        int y = year % 100;

        int wd = (d + (26 * (m + 1) / 10) + (5 * y / 4) + (c / 4) + (5 * c) - 1) % 7;

        return switch (wd) {
            case 0 -> "Sonntag";
            case 1 -> "Montag";
            case 2 -> "Dienstag";
            case 3 -> "Mittwoch";
            case 4 -> "Donnerstag";
            case 5 -> "Freitag";
            case 6 -> "Samstag";
            default -> "ERROR";
        };
    }
}
