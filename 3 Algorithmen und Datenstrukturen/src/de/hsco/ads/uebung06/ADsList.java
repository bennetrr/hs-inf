package de.hsco.ads.uebung06;


public interface ADsList {
	int size();

	void insert(int pos, Object element);
	void remove(int pos);

	Object elementAt(int pos);
	int find(Object element);

	boolean isEmpty();
}
