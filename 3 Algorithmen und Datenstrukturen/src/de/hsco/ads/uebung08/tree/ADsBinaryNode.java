package de.hsco.ads.uebung08.tree;

public class ADsBinaryNode {
    ADsBinaryNode leftChild;      // Zeiger auf linken Kindknoten
    ADsBinaryNode rightChild;     // Zeiger auf rechten Kindknoten

    public ADsBinaryNode(Object element) {
        this.element = element;
    }

    Object element;               // Daten

    int key;                      // eindeutiger Schlüssel
}
