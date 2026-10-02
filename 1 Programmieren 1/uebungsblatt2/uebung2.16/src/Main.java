import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // Get the input temperature in Fahrenheit
        var sc = new Scanner(System.in);
        int tempFahrenheit = sc.nextInt();
        System.out.println("Input: " + tempFahrenheit);

        // Convert Fahrenheit to Celsius
        double tempCelsius = (tempFahrenheit - 32) * 5 / 9.0;

        // Truncate to 1 decimal place
        double tempCelsius1Decimal = ((int) (tempCelsius * 10)) / 10.0;
        System.out.println("Output: " + tempCelsius1Decimal);
    }
}
