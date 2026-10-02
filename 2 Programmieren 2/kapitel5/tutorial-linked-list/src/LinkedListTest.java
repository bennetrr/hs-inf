public class LinkedListTest {
    public static void main(String[] args) {
        LinkedList<Integer> theList = new LinkedList<>();
        System.out.println("isEmpty: " + theList.isEmpty());

        theList.append(10);
        theList.append(20);
        theList.append(30);
        theList.append(40);
        theList.append(40);
        theList.append(44);

        System.out.println(theList);
        System.out.println("isEmpty: " + theList.isEmpty());

        System.out.println("contains 20: " + theList.contains(20));
        System.out.println("contains 21: " + theList.contains(21));
    }
}
