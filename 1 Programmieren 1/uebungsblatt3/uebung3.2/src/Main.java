public class Main {
    public static void main(String[] args) {
        callFuncs(9, 11);
        callFuncs(11, 9);
    }

    public static void callFuncs(int x, int y) {
        x1(x, y);
        x2(x, y);
    }

    public static void x1(int x, int y) {
        System.out.println();
        System.out.println("Für x=" + x + "und y=" + y);
        if (x < 10) {
            if (y > 10) {
                System.out.println("*****");
            } else {
                System.out.println("######");
            }
        }
        System.out.println("&&&&&&");
    }

    public static void x2(int x, int y) {
        if (x < 10) {
            if (y > 10) {
                System.out.println("*****");
            }
        } else {
            System.out.println("######");
            System.out.println("&&&&&&");
        }
    }
}
