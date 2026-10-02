package de.hsco.ads.uebung06.linkedvariant3;

import de.hsco.ads.uebung06.ADsList;

public class ADsLinkedList implements ADsList {

    private ADsListNode head;
    private ADsListNode tail;

    public ADsLinkedList() {
        head = new ADsListNode(null);
        tail = new ADsListNode(null);
        head.next = tail;
        tail.next = head;
    }

    public ADsLinkedList(Object... elements) {
        this();
        ADsListNode node = head;

        for( int i = 0; i < elements.length; i++ ) {
            ADsListNode next = new ADsListNode(elements[i]);
            node.next = next;
            node = next;
            tail.next = node;
        }

        node.next = tail;
    }

    @Override
    public int size() {
        var count = 0;
        var node = head.next;

        while (node != tail) {
            node = node.next;
            count++;
        }

        return count;
    }

    @Override
    public void insert(int pos, Object elem) {
        // "Entlanghangeln" an der Liste, bis wir bei der Node vor pos sind
        var node = head;

        for (int i = 0; i < pos; i++) {
            node = node.next;

            // Wenn node null hier ist, geht die Liste nicht so weit, wie angegeben
            if (node == tail) {
                throw new IndexOutOfBoundsException();
            }
        }

        var oldNext = node.next;
        node.next = new ADsListNode(elem);
        node.next.next = oldNext;
    }

    @Override
    public void remove(int pos) {
        // "Entlanghangeln" an der Liste, bis wir bei der Node vor pos sind
        var node = head;

        for (int i = 0; i < pos; i++) {
            node = node.next;

            // Wenn node null hier ist, geht die Liste nicht so weit, wie angegeben
            if (node == tail) {
                throw new IndexOutOfBoundsException();
            }
        }

        // Hier wird versucht, die "überletzte" Node zu löschen
        if (node.next == tail) {
            return;
        }

        node.next = node.next.next;
    }

    @Override
    public Object elementAt(int pos) {
        var node = head.next;

        for (int i = 0; i < pos; i++) {
            node = node.next;

            if (node == tail) {
                throw new IndexOutOfBoundsException();
            }
        }

        return node.element;
    }

    @Override
    public int find(Object element) {
        var index = 0;
        var node = head.next;

        while (node != tail) {
            if (node.element.equals(element)) {
                return index;
            }

            node = node.next;
            index++;
        }

        return -1;
    }

    @Override
    public boolean isEmpty() {
		return head.next == tail;
    }
}
