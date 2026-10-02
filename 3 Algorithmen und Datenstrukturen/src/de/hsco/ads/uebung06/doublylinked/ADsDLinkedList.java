package de.hsco.ads.uebung06.doublylinked;

import de.hsco.ads.uebung06.ADsList;

public class ADsDLinkedList implements ADsList {

	private ADsDListNode head;
	private ADsDListNode tail;

	public ADsDLinkedList() {
		head = new ADsDListNode(null);
		tail = new ADsDListNode(null);

		head.next = tail;
		tail.previous = head;
		tail.next = head;
	}

	public ADsDLinkedList(Object... elements) {
		this();

		ADsDListNode prevNode = null;
		ADsDListNode node = null;
		for( int i = 0; i < elements.length; i++ ) {
			prevNode = node;
			node = new ADsDListNode(elements[i]);
			if( prevNode == null ) {
				head.next = node;
				node.previous = head;
			} else {
				prevNode.next = node;
				node.previous = prevNode;
			}
		}
		if( node != null ) {
			node.next = tail;
			tail.previous = node;
			tail.next = node;
		}
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
        node.next = new ADsDListNode(elem);
        node.next.next = oldNext;
		oldNext.previous = node;
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
		node.next.previous = node.previous;
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
