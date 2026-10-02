class Main {
    public static void main(String[] args) {
        // a)
        // for ...
        for (int i = 1; i <= 10; i++) {
            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            for (int j = i; j >= 10; j--) {
                System.out.print(" ");
            }
            System.out.println();
        }

        // Abstand zwischen den Ausgaben
        System.out.println();
        System.out.println();

        // b)
        // for ...
        for (int i = 10; i >= 1; --i) {
            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            for (int j = i; j >= 10; j--) {
                System.out.print(" ");
            }
            System.out.println();
        }

        // Abstand zwischen den Ausgaben
        System.out.println();
        System.out.println();

        // c)
        // for ...
        for (int i = 10; i >= 1; i--) {
            for (int j = 10; j > i; j--) {
                System.out.print(" ");
            }
            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            System.out.println();
        }

        // Abstand zwischen den Ausgaben
        System.out.println();
        System.out.println();

        // d)
        // for ...
        for (int i = 1; i <= 10; i++) {
            for (int j = 10; j > i; j--) {
                System.out.print(" ");
            }
            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }
}
