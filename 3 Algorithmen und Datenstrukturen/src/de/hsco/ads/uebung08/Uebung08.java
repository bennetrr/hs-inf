package de.hsco.ads.uebung08;

import de.hsco.ads.uebung08.tree.ADsBinaryTree;
import de.hsco.ads.uebung08.tree.SimpleBinaryTree;

public class Uebung08 {
    public static void main(String[] args) {
        ADsBinaryTree tree = new SimpleBinaryTree();
        tree.insertLeft(tree.root(), 5);
        tree.insertLeft(tree.root(), 1);
        tree.insertRight(tree.root(), 10);
        tree.insertLeft(tree.left(tree.root()), 2);
        tree.insertLeft(tree.root(), 3);

        tree.height(tree.root());
    }
}
