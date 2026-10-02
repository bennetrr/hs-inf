package de.hsco.ads.uebung06.linkedvariant1;

import de.hsco.ads.uebung06.ADsList;

public class ADsLinkedList implements ADsList {

    private ADsListNode head;

    public ADsLinkedList() {
        // intentionally left blank
    }

    public ADsLinkedList(Object... elements) {
        ADsListNode node = null;
        for( int i = 0; i < elements.length; i++ ) {
            if( i == 0 ) {
                head = new ADsListNode(elements[i]);
                node = head;
            } else {
                ADsListNode next = new ADsListNode(elements[i]);
                node.next = next;
                node = next;
            }
        }
    }

    @Override
    public int size() {
        var count = 0;
        var node = head;

        while (node != null) {
            node = node.next;
            count++;
        }

        return count;
    }

    @Override
    public void insert(int pos, Object elem) {
        // Sonderfall: Am Anfang einfügen
        if (pos == 0) {
            if (head == null) {
                head = new ADsListNode(elem);
            } else {
                var oldHead = head;
                head = new ADsListNode(elem);
                head.next = oldHead;
            }

            return;
        }

        // "Entlanghangeln" an der Liste, bis wir bei der Node vor pos sind
        var node = head;

        for (int i = 0; i < pos - 1; i++) {
            node = node.next;

            // Wenn node null hier ist, geht die Liste nicht so weit, wie angegeben
            if (node == null) {
                throw new IndexOutOfBoundsException();
            }
        }

        var oldNext = node.next;
        node.next = new ADsListNode(elem);
        node.next.next = oldNext;
    }

    @Override
    public void remove(int pos) {
        // Sonderfall: Erste Node löschen
        if (pos == 0) {
            if (head == null) {
                throw new IndexOutOfBoundsException();
            } else {
                head = head.next;
            }

            return;
        }

        // "Entlanghangeln" an der Liste, bis wir bei der Node vor pos sind
        var node = head;

        for (int i = 0; i < pos - 1; i++) {
            node = node.next;

            // Wenn node null hier ist, geht die Liste nicht so weit, wie angegeben
            if (node == null) {
                throw new IndexOutOfBoundsException();
            }
        }

        // Hier wird versucht, die "überletzte" Node zu löschen
        if (node.next == null) {
            return;
        }

        node.next = node.next.next;
    }

    @Override
    public Object elementAt(int pos) {
        var node = head;

        for (int i = 0; i < pos; i++) {
            node = node.next;

            if (node == null) {
                throw new IndexOutOfBoundsException();
            }
        }

        return node.element;
    }

    @Override
    public int find(Object element) {
        var index = 0;
        var node = head;

        while (node != null) {
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
		return head == null;
    }

    public void swapNext(int pos) {
        var node = head;

        for (int i = 0; i < pos; i++) {
            node = node.next;

            if (node == null) {
                throw new IndexOutOfBoundsException();
            }
        }

        var next = node.next;
        node.next = next.next;
        node.next.next = next;
    }
}
