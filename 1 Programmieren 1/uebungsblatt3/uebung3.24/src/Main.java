public class Main {
    public static void main(String[] args) {
        System.out.println(ermittlePythagoraeischesDreick(5));
        System.out.println(ermittlePythagoraeischesDreick(20));
    }

    public static String ermittlePythagoraeischesDreick(int side) {
        StringBuilder result = new StringBuilder();

        for (int s1 = 1; s1 <= side; s1++) {
            for (int s2 = 1; s2 <= side; s2++) {
                for (int h = 1; h <= side; h++) {
                    if (Math.pow(s1, 2) + Math.pow(s2, 2) == Math.pow(h, 2)) {
                        result.append("s1: ").append(s1).append(" s2: ").append(s2).append("  h: ").append(h).append("\n");
                    }
                }
            }
        }

        return result.toString();
    }
}
