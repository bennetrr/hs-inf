import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // -----------------------------------------------------------------
        //Eingabe einer dezimalen Zahl:
        int decimalInput = sc.nextInt();

        // Ausgabe: Hex und binär:
        System.out.println("Hex: " + Integer.toHexString(decimalInput));
        System.out.println("Binär: " + Integer.toBinaryString(decimalInput));


        // -----------------------------------------------------------------
        // Eingabe einer hexadezimalen Zahl:
        String hexInputString = sc.next();

        int hexInput = Integer.parseInt(hexInputString, 16);

        // Ausgabe: Dezimal und binär:
        System.out.println("Dezimal: " + hexInput);
        System.out.println("Binär: " + Integer.toBinaryString(hexInput));


        // -----------------------------------------------------------------
        // Eingabe einer binären Zahl:
        String binInputString = sc.next();

        int binInput = Integer.parseInt(binInputString, 2);

        // Ausgabe: Dezimal und hex:
        System.out.println("Dezimal: " + binInput);
        System.out.println("Hex: " + Integer.toHexString(binInput));


        // -----------------------------------------------------------------
        // Eingabe einer oktalen Zahl:
        String oktInputString = sc.next();

        int oktInput = Integer.parseInt(oktInputString, 8);

        // Ausgabe: Dezimal und hex:
        System.out.println("Dezimal: " + oktInput);
        System.out.println("Hex: " + Integer.toHexString(oktInput));
    }
}
