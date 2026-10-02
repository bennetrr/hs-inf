class Callstack {
    static int numberOfCalls;

    public static int mystery(int a, int b) {
        System.out.println("Call#:" + ++numberOfCalls + " mystery(" + a + ", " + b + ") ");

        if (b <= 1) {
            System.out.println("Base case: (" + a + "," + b + ")" + " -> " + a);
            System.out.println();
            return a;
        } else {
            int tmp = a + mystery(a, b - 1);
            System.out.println("(" + a + "," + b + ")" + " -> " + tmp);
            return tmp;
        }
    }

    public static void main(String[] args) {
        Callstack.mystery(0, 1);
        Callstack.mystery(20, 5);
        Callstack.mystery(2222, 4);
        Callstack.mystery(100, 2);
        Callstack.mystery(0, 0);
    }
}
