package de.hsco.ads.uebung06.doublylinked;

public class ADsDListNode {
	ADsDListNode next;
	ADsDListNode previous;

	// die zu speichernden Daten
	Object element;

	ADsDListNode(Object element) {
		this.element = element;
	}
}
