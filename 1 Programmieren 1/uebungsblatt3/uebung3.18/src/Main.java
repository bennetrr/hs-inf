import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            String satz = sc.nextLine();
            System.out.println(satz);
            satz = satz.toLowerCase();

            int aCount = 0;
            int eCount = 0;
            int iCount = 0;
            int oCount = 0;
            int uCount = 0;
            int restCount = 0;

            for (int i = 0; i < satz.length(); i++) {
                switch (satz.charAt(i)) {
                    case 'a' -> aCount++;
                    case 'e' -> eCount++;
                    case 'i' -> iCount++;
                    case 'o' -> oCount++;
                    case 'u' -> uCount++;
                    default -> restCount++;
                }
            }

            System.out.println("a:" + aCount);
            System.out.println("e:" + eCount);
            System.out.println("i:" + iCount);
            System.out.println("o:" + oCount);
            System.out.println("u:" + uCount);
            System.out.println("Kons. u. Sonderzeichen:" + restCount);

            System.out.println("Beenden (j oder n)");
            String closeResponse = sc.nextLine();
            System.out.println(closeResponse);
            if (closeResponse.equals("j")) {
                break;
            }
        }
    }
}
