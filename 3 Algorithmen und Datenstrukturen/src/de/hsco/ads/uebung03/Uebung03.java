package de.hsco.ads.uebung03;

public class Uebung03 {
    public static long slowPow(int x, int n) {
        long result = 1;

        for (int i = 1; i <= n; i++) {
            result *= x;
        }

        return result;
    }

    public static long fastPow(long x, long n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        if (n == 2) return x * x;

        if (n % 2 == 0) return fastPow(fastPow(x, 2), n / 2);
        return fastPow(fastPow(x, (n - 1) / 2), 2) * x;
    }

    public static String pad(String val, int length) {
        return " " + val + " ".repeat(length - val.length()) + " |";
    }

    public static void main(String[] args) {
        for (int n = 1; n <= 10; n++) {
            var resultsSlowPow = new long[100];
            var timesSlowPow = new double[100];
            var resultsFastPow = new long[100];
            var timesFastPow = new double[100];

            for (int x = 0; x < 100; x++) {
                var startSlowPow = System.nanoTime();
                resultsSlowPow[x] = slowPow(x, n);
                timesSlowPow[x] = System.nanoTime() - startSlowPow;

                var startFastPow = System.nanoTime();
                resultsFastPow[x] = fastPow(x, n);
                timesFastPow[x] = System.nanoTime() - startFastPow;
            }

            var tableHeader = new StringBuilder       ("|                |");
            var tableLine = new StringBuilder         ("|----------------|");
            var tableResultSlowPow = new StringBuilder("| Result SlowPow |");
            var tableResultFastPow = new StringBuilder("| Result FastPow |");
            var tableTimeSlowPow = new StringBuilder  ("| Time SlowPow   |");
            var tableTimeFastPow = new StringBuilder  ("| Time FastPow   |");

            for (int x = 0; x < 100; x++) {
                var resultSlowPow = resultsSlowPow[x];
                var timeSlowPow = timesSlowPow[x];
                var resultFastPow = resultsFastPow[x];
                var timeFastPow = timesFastPow[x];

                var maxLength = Math.max(Long.toString(resultFastPow).length(), Math.max(Double.toString(timeFastPow).length(), Double.toString(timeSlowPow).length()));
                tableHeader.append(pad(Integer.toString(x), maxLength));
                tableLine.append(" ").append("-".repeat(maxLength)).append(" |");
                tableResultSlowPow.append(pad(Long.toString(resultSlowPow), maxLength));
                tableResultFastPow.append(pad(Long.toString(resultFastPow), maxLength));
                tableTimeSlowPow.append(pad(Double.toString(timeSlowPow), maxLength));
                tableTimeFastPow.append(pad(Double.toString(timeFastPow), maxLength));
            }

            System.out.printf("n = %s\n", n);
            System.out.println("  " + tableHeader);
            System.out.println("  " + tableLine);
            System.out.println("  " + tableResultSlowPow);
            System.out.println("  " + tableResultFastPow);
            System.out.println("  " + tableTimeSlowPow);
            System.out.println("  " + tableTimeFastPow);
        }
    }
}
