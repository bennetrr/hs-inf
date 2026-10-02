package de.hsco.ads.uebung01;

/**
 * Represents a rational number with a numerator and a denominator.
 */
public class Rational {
    private int numerator; // Zaehler
    private int denominator; // Nenner

    /**
     * Initializes numerator to 0 and denominator to 1
     */
    public Rational() {
        numerator = 0;
        denominator = 1;
    }

    /**
     * Initializes numerator part to n and denominator part to 1
     */
    public Rational(int n) {
        numerator = n;
        denominator = 1;
    }

    /**
     * Initializes numerator part to n and denominator part to d
     */
    public Rational(int n, int d) {
        assert (d != 0);

        numerator = n;
        denominator = d;
        reduce();
    }

    private static Rational createUnreduced(int n, int d) {
        var r = new Rational();
        r.numerator = n;
        r.denominator = d;
        return r;
    }

    /**
     * Adds the given {@link Rational} to this {@link Rational} and returns the result as a new object.
     *
     * @param right the {@link Rational} to add
     * @return the sum of this and the given {@link Rational}
     */
    public Rational sum(Rational right) {
        var leftExpanded = this.expand(right.denominator);
        var rightExpanded = right.expand(right.denominator);

        assert leftExpanded.denominator == rightExpanded.denominator;
        return new Rational(leftExpanded.numerator + rightExpanded.numerator, leftExpanded.denominator);
    }

    /**
     * Subtracts the given {@link Rational} from this {@link Rational} and returns the result as a new object.
     *
     * @param right the {@link Rational} to subtract
     * @return the difference of this and the given {@link Rational}
     */
    public Rational subtract(Rational right) {
        return this.sum(right.multiply(new Rational(-1)));
    }

    /**
     * Multiplies this {@link Rational} with the given {@link Rational} and returns the result as a new object.
     *
     * @param right the {@link Rational} to multiply with
     * @return the product of this and the given {@link Rational}
     */
    public Rational multiply(Rational right) {
        return new Rational(this.numerator * right.numerator, this.denominator * right.denominator);
    }

    /**
     * Divides this {@link Rational} by the given {@link Rational} and returns the result as a new object.
     *
     * @param right the {@link Rational} to divide by
     * @return the division of this and the given {@link Rational}
     */
    public Rational divide(Rational right) {
        return this.multiply(right.inverse());
    }

    private Rational expand(int n) {
        return Rational.createUnreduced(this.numerator * n, this.denominator * n);
    }

    /**
     * Reduces this {@link Rational} to its simplest form.
     */
    private void reduce() {
        assert (denominator != 0);

        int Rest;
        var A = this.numerator;
        var B = this.denominator;

        do {
            Rest = A % B;
            A = B;
            B = Rest;
        } while (Rest != 0);

        if (this.denominator > 0 && A < 0) {
            A *= -1;
        }

        this.numerator /= A;
        this.denominator /= A;

        assert (denominator != 0);
    }

    private Rational inverse() {
        return new Rational(this.denominator, this.numerator);
    }

    /**
     * Prints the {@link Rational} to the console.
     */
    public void toScreen() {
        System.out.println("Wert " + this);
    }

    /**
     * Returns String representation of a {@link Rational} number.
     *
     * @return the {@link Rational} as a string
     */
    public String toString() {
        return numerator + "/" + denominator;
    }
}
