import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Anzahl Nachkomma Genauigkeit: (1 bis 8): ");
        long precision = sc.nextLong();
        System.out.println(precision);

        if (precision > 8) {
            System.out.println("Pi kann nicht approximiert werden auf " + precision + " Stellen");
            return;
        }

        long compareFactor = (long) Math.pow(10, precision);
        long piToCompare = (long) (Math.PI * compareFactor);
        double divider = 1.0;
        long sign = 1;
        double computedPi = 0.0;
        long counter = 0;

        do {
            computedPi += (sign * 4 * compareFactor) / divider;
            divider += 2.0;
            sign *= -1;
            counter++;
        } while ((long) computedPi != piToCompare);

        System.out.println(((double) piToCompare / compareFactor) + " dem nach " + counter + ".ten Term");
    }
}
