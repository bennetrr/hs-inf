public class Main {
    public static void main(String[] args) {
        Integer[] array = {2000, 2, 99, 756, 999, 0, 666, 2345, 7492, 22};

        Utilities.print(array);
        Utilities.sortiere(array);
        Utilities.print(array);

        System.out.println(Utilities.noNull(null, 23, 45, 56, null));
        System.out.println((Object) Utilities.noNull());
        System.out.println(Utilities.noNull(null, "Hello", "WoW"));
    }
}
