package de.hsco.ads.uebung01;

import java.util.Scanner;

/**
 * Test the {@link Rational} number class
 */
public class RationalTest {

    /**
     * Main method for testing the {@link Rational} class with user input
     *
     * @param args
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Rational original, right, result = null;
        int numerator, denumerator;
        char operation;

        // create the left operand
        System.out.println("Enter first de.hsco.ads.uebung01.Rational object");
        System.out.println("Enter the numerator: ");
        numerator = sc.nextInt();
        System.out.println("Enter the denumerator: ");
        denumerator = sc.nextInt();

        original = new Rational(numerator, denumerator);

        // choose the operation
        System.out.println("Enter the operation +, *, /, -");

        operation = sc.next().charAt(0);// next().charAt(0).next()
        // create the right operand
        System.out.println("Enter second de.hsco.ads.uebung01.Rational object");
        System.out.println("Enter the numerator: ");
        numerator = sc.nextInt();
        System.out.println("Enter the denumerator: ");
        denumerator = sc.nextInt();

        right = new Rational(numerator, denumerator);

        // execute the operation
        if (operation == '+')
            result = original.sum(right);
        if (operation == '-')
            result = original.subtract(right);
        if (operation == '/')
            result = original.divide(right);
        if (operation == '*')
            result = original.multiply(right);

        // print the result
        System.out.println(original + " " + operation + " " + right + " " + "=" + result);
    }
}
