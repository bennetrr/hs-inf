package de.hsco.ads.uebung01;

public class Uebung01 {
    public static void main(String[] args) {

        System.out.println("ggt von 1974 und 2022 (iterativ):" + ggTIter(1974, 2022));
        System.out.println("ggt von 1974 und 2022 (rekursiv):" + ggTRec(1974, 2022));

        System.out.println("Fakultät von 12 iterativ: " + facIter(12));
        System.out.println("Fakultät von 12 recursiv: " + facRec(12));
        System.out.println("Fakultät von 1 recursiv: " + facRec(1));
        System.out.println("Fakultät von 0 recursiv: " + facRec(0));
    }

    /**
     * Calculates the greatest common denominator of two numbers A and B iteratively
     *
     * @param A the first number
     * @param B the second number
     * @return the greatest common denominator of A and B
     */
    public static int ggTIter(int A, int B) {
        int Rest;

        do {
            Rest = A % B;
            A = B;
            B = Rest;
        } while (Rest != 0);

        return A;
    }

    /**
     * Calculates the greatest common denominator of two numbers A and B recursively
     *
     * @param A the first number
     * @param B the second number
     * @return the greatest common denominator of A and B
     */
    public static int ggTRec(int A, int B) {
        var Rest = A % B;

        if (Rest == 0) {
            return B;
        }

        return ggTRec(B, Rest);
    }

    /**
     * Calculates the faculty iteratively
     *
     * @param n the number to calculate the faculty for
     * @return the faculty of n
     */
    public static int facIter(int n) {
        var f = 1;

        for (var i = 2; i <= n; i++) {
            f *= i;
        }

        return f;
    }

    /**
     * Calculates the faculty recursively
     *
     * @param n the number to calculate the faculty for
     * @return the faculty of n
     */
    public static int facRec(int n) {
        if (n <= 1) {
            return 1;
        }

        return facRec(n - 1) * n;
    }
}
