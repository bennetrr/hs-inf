/**
 * The <code>LinkedList</code> class implements a simple linked list based on
 * the specification of the abstract data type List.
 * This implementation uses a pointer implementation and not an array.
 * <p>
 * Note that the position is implemented as an integer index.
 * This implementation has disadvantages in regard to Big O(n) runtime.
 */
public class LinkedList<E> {
    private final ListNode<E> header;

    /**
     * Construct the list
     */
    public LinkedList() {
        header = new ListNode<>(null);
    }

    /**
     * Test if the list is logically empty.
     *
     * @return true if empty, false otherwise.
     */
    public boolean isEmpty() {
        return header.next == null;
    }

    /**
     * Appends the element x at the end of the list
     *
     * @param x the item to append.
     */
    public void append(E x) {
        var itr = header;

        while (itr.next != null) {
            itr = itr.next;
        }

        itr.next = new ListNode<>(x);
    }

    /**
     * Search for a specific object with the "same value"
     *
     * @param x the item to search for.
     * @return the position of the item or -1 if the item is not found.
     */
    public boolean contains(E x) {
        var itr = header;

        while (itr.next != null) {
            itr = itr.next;

            if (itr.element.equals(x)) {
                return true;
            }
        }

        return false;
    }

    /**
     * toString
     */
    public String toString() {
        var builder = new StringBuilder("LinkedList[");

        var itr = header;

        while (itr.next != null) {
            itr = itr.next;

            builder.append(itr.element);

            if (itr.next != null) {
                builder.append(", ");
            }
        }

        return builder.append(']').toString();
    }
}
