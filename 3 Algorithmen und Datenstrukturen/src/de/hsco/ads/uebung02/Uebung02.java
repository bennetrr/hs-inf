package de.hsco.ads.uebung02;

public class Uebung02 {

    /**
     * Aufgabe 1:
     * Berechnet die maximale Summe eines Subarrays rekursiv
     */
    public static int maxSubSumRec(int[] a, int left, int right) {
        // Basisfall: Array der Länge 1
        // TODO: Implementiere den Basisfall

        // Halbiere Array in linkes und rechtes Teilarray
        // berechne rekursiv max Sub Wert jeder Hälfte
        // TODO: Implementiere die Aufteilung des Arrays in zwei Hälften

        // Die Berechnung von Fall 3 erfolgt jeweils durch eine for-Schleife
        // TODO: Implementiere die Berechnung der Summe von Fall 3

        // Gib das Maximum der drei Fälle zurück
        // TODO: Implementiere die Rückgabe des Maximums der drei Fälle
        return -1;
    }

    /**
     * Aufgabe 2:
     * Berechnet die Anzahl der Einsen in der Binärdarstellung einer Zahl
     * rekursiv
     */
    public static int ones(int n) {
        if (n <= 0) {
            return 0;
        }

        return ones(n / 2) + n % 2;
    }

    /**
     * Aufgabe 3:
     * Berechnet den Wert eines arithmetischen Terms rekursiv
     */
    public static int evaluateTerm(String term) {
        var addPosition = term.indexOf("+");

        if (addPosition != -1) {
            return evaluateTerm(term.substring(0, addPosition)) + evaluateTerm(term.substring(addPosition + 1));
        }

        var multPosition = term.indexOf("*");

        if (multPosition != -1) {
            return evaluateTerm(term.substring(0, multPosition)) * evaluateTerm(term.substring(multPosition + 1));
        }

        return Integer.parseInt(term);
    }

    public static int evaluateTerm2(String term) throws Exception {
        var openingBracketPosition = term.lastIndexOf("(");

        if (openingBracketPosition != -1) {
            var closingBracketPosition = term.indexOf(")", openingBracketPosition);

            if (closingBracketPosition == -1) {
                throw new Exception("Missing closing bracket!");
            }

            var bracketExpression = evaluateTerm2(term.substring(openingBracketPosition + 1, closingBracketPosition));
            return evaluateTerm2(term.substring(0, openingBracketPosition) + bracketExpression + term.substring(closingBracketPosition + 1));
        }

        var addPosition = term.indexOf("+");

        if (addPosition != -1) {
            return evaluateTerm2(term.substring(0, addPosition)) + evaluateTerm2(term.substring(addPosition + 1));
        }

        var subPosition = term.indexOf("-");

        if (subPosition != -1) {
            return evaluateTerm2(term.substring(0, subPosition)) - evaluateTerm2(term.substring(subPosition + 1));
        }

        var multPosition = term.indexOf("*");

        if (multPosition != -1) {
            return evaluateTerm2(term.substring(0, multPosition)) * evaluateTerm2(term.substring(multPosition + 1));
        }

        var divPosition = term.indexOf("/");

        if (divPosition != -1) {
            return evaluateTerm2(term.substring(0, divPosition)) / evaluateTerm2(term.substring(divPosition + 1));
        }

        return Integer.parseInt(term);
    }


    public static void main(String[] args) throws Exception {
        int[] a = {3, -4, 2, 2, -3, 1, 3, -2};
        System.out.println(maxSubSumRec(a, 0, a.length - 1));

        System.out.println(ones(42));  // Should be 3

        System.out.println(evaluateTerm("5+3+2*7+4*4*1+2*9"));  // Should be 56
        System.out.println(evaluateTerm2("5+3+2*7+4*4*1+2*9"));  // Should be 56
        System.out.println(evaluateTerm2("5+(3+2)*7+4*4*1+2*9"));  // Should be 74
        System.out.println(evaluateTerm2("5+3-2*7+4*4*1+2*9"));  // Should be 28
        System.out.println(evaluateTerm2("5-3+2*7+4*4*1+2*9"));  // Should be 50
        System.out.println(evaluateTerm2("5-3+2*7+4*4*1+2/9"));  // Should be 32
    }
}
