import java.util.Vector;

public class PairTest {
    public static void main(String[] args) {
        Vector<Pair<String, Integer>> vector = new Vector<Pair<String, Integer>>();

        vector.add(new Pair<String, Integer>("I", 1));
        vector.add(new Pair<String, Integer>("V", 5));
        vector.add(new Pair<String, Integer>("C", 100));
        vector.add(new Pair<String, Integer>("II", 2));
        vector.add(new Pair<String, Integer>("IX", 9));

        System.out.println(vector.toString().equals("[(I, 1), (V, 5), (C, 100), (II, 2), (IX, 9)]"));

        Pair<String, Integer> p1 = new Pair<String, Integer>("I", 5);
        Pair<String, Integer> p2 = new Pair<String, Integer>("I", 5);

        System.out.println(p1.equals(p2));
        System.out.println(p1.hashCode() == p2.hashCode());
    }
}
