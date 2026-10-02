package de.hsco.ads.uebung07;

import javax.naming.OperationNotSupportedException;
import java.io.IOException;

public class Uebung07 {
    public static void main(String[] args) throws IOException, OperationNotSupportedException {
        // Aufgabe 1
        String postfixString = "2 5 * 3 +";
        double result1 = ExpressionParser.evaluatePostfixExpression(postfixString);
        System.out.println("Ergebnis der Auswertung von '" + postfixString + "': " + result1);
        System.out.println();

        String postfixString21 = "2 5 * 3 -";
        double result2 = ExpressionParser.evaluatePostfixExpression(postfixString21);
        System.out.println("Ergebnis der Auswertung von '" + postfixString21 + "': " + result2);
        System.out.println();

        // Aufgabe 2
        String infixString1 = "2 + 5 * 3";
        String infixString2 = "2*(5 - 2) + 6/(3+2)";
        String postfixString1 = ExpressionParser.convertInfixToPostfix(infixString1);
        String postfixString2 = ExpressionParser.convertInfixToPostfix(infixString2);
        System.out.println("Infix 1 to Postfix: " + infixString1 + " => " + postfixString1);
        System.out.println("Infix 2 to Postfix: " + infixString2 + " => " + postfixString2);

        System.out.println(infixString1 + " = " + ExpressionParser.evaluatePostfixExpression(postfixString1));
        System.out.println(infixString2 + " = " + ExpressionParser.evaluatePostfixExpression(postfixString2));
    }
}
