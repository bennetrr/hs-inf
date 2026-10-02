package de.hsco.ads.uebung08.tree;

public class SimpleBinaryTree implements ADsBinaryTree {
    private ADsBinaryNode root;

    public SimpleBinaryTree() {
        root = null;
    }

    @Override
    public Position root() {
        if (root == null) {
            root = new ADsBinaryNode(null);
        }

        return new Position(root);
    }

    @Override
    public boolean isEmpty() {
        return root == null || root.element == null;
    }

    @Override
    public Position left(Position pos) {
        if (pos == null || pos.node == null) {
            return null;
        }

        ADsBinaryNode leftNode = pos.node.leftChild;

        if (leftNode == null) {
            return null;
        } else {
            return new Position(leftNode);
        }
    }

    @Override
    public Position right(Position pos) {
        if (pos == null || pos.node == null) {
            return null;
        }

        ADsBinaryNode rightNode = pos.node.rightChild;

        if (rightNode == null) {
            return null;
        } else {
            return new Position(rightNode);
        }
    }

    @Override
    public Object elementAt(Position pos) {
        return pos.node.element;
    }

    @Override
    public void insertLeft(Position pos, Object value) {
        // Wenn an der angegebenen Position schon ein Knoten existiert,
        // wird dieser danach zum rechten Kind des eingefügten Knotens gemacht
        if (pos.node.leftChild == null) {
            pos.node.leftChild = new ADsBinaryNode(value);
        } else {
            ADsBinaryNode existingsNode = pos.node.leftChild;
            pos.node.leftChild = new ADsBinaryNode(value);
            pos.node.leftChild.rightChild = existingsNode;
        }
    }

    @Override
    public void insertRight(Position pos, Object value) {
        // Wenn an der angegebenen Position schon ein Knoten existiert,
        // wird dieser danach zum rechten Kind des eingefügten Knotens gemacht
        if (pos.node.rightChild == null) {
            pos.node.rightChild = new ADsBinaryNode(value);
        } else {
            ADsBinaryNode existingsNode = pos.node.rightChild;
            pos.node.rightChild = new ADsBinaryNode(value);
            pos.node.rightChild.rightChild = existingsNode;
        }
    }

    @Override
    public void delete(Position pos) {
        pos.node = null;
    }

    @Override
    public int height(Position pos) {
        var rightNode = right(pos);
        var leftNode = left(pos);

        if (rightNode == null && leftNode == null) {
            return 0;
        }

        return 1 + Math.max(height(rightNode), height(leftNode));
    }
}
