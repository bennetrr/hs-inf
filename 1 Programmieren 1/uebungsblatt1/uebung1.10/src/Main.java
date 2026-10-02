import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Bitte n eingeben: ");
        int n = sc.nextInt();
        System.out.println(n);

        StringBuilder outputStringBuilder = new StringBuilder();
        int res = 1;

        if (n == 3) {
            res = 3;
        } else {
            for (int i = 3; i <= n; i++) {
                res *= i;

                if (outputStringBuilder.isEmpty()) {
                    outputStringBuilder.append(i);
                } else {
                    outputStringBuilder.append(" * ").append(i);
                }
            }
        }

        outputStringBuilder.append(" = ").append(res);

        System.out.println(outputStringBuilder);
    }
}
