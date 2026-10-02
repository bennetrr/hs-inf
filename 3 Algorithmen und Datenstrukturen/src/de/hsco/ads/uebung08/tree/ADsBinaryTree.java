package de.hsco.ads.uebung08.tree;

public interface ADsBinaryTree {

	Position root();
	boolean isEmpty();

	Position left(Position pos);
	Position right(Position pos);

    Object elementAt(Position pos);

	void insertLeft(Position pos, Object value);
	void insertRight(Position pos, Object value);

	void delete(Position pos);

	// Uebung 08
	int height(Position pos);
}
