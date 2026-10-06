import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        char inputCmd;
        int n;

        Scanner sc = new Scanner(System.in);

        do {
            System.out.println("Pl input cmd (e=exit, f=factorial, m=magicQuadrat)");
            inputCmd = sc.next().charAt(0);

            switch (inputCmd) {
                case 'm':
                    int[][] magicQuadrat;
                    do {
                        System.out.println("Pl input n  (n uneven 2 < n < 10): ");
                        n = sc.nextInt();
                    } while (n % 2 == 0 || n < 3 || n > 9);

                    magicQuadrat = Utils.erzeugeMagicQuadrat(n);
                    System.out.println("magicQuadrat =" + Utils.toString(magicQuadrat));
                    break;
                case 'f':
                    long result = 1;
                    System.out.println("Pl input n>");
                    n = sc.nextInt();

                    for (int i = 2; i <= n; i++) {
                        result *= i;
                    }

                    System.out.println(n + "! = " + result);
                    break;
                case 'e':
                case 'E':
                    System.out.println("Thanks f�r using this program!");
                    break;
                default:
                    System.out.println("Wrong input!");
            }
        } while (inputCmd != 'e' && inputCmd != 'E');
    }
}
