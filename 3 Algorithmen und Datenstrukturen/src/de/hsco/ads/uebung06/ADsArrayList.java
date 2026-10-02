package de.hsco.ads.uebung06;

import java.util.Arrays;

public class ADsArrayList implements ADsList {

    private Object[] array;
    private int numElems;


    public ADsArrayList(int capacity, Object... elements) {
        this.array = Arrays.copyOf(elements, capacity);
        this.numElems = elements.length;
    }

    @Override
    public int size() {
        return numElems;
    }

    @Override
    public void insert(int pos, Object elem) {
        // Verschiebe alle Items bis pos eine Position nach hinten
        for (int i = numElems - 1; i >= pos; i--) {
            array[i + 1] = array[i];
        }

        array[pos] = elem;

        numElems++;
    }

    @Override
    public void remove(int pos) {
        for (int i = pos; i < numElems - 1; i++) {
            array[i] = array[i + 1];
        }

        numElems--;
    }

    @Override
    public Object elementAt(int pos) {
        for (int i = 0; i < numElems; i++) {
            if (pos == i) {
                return array[i];
            }
        }

        throw new IndexOutOfBoundsException();
    }

    @Override
    public int find(Object element) {
        for (int i = 0; i < numElems; i++) {
            if (element.equals(array[i])) {
                return i;
            }
        }

        return -1;
    }

    @Override
    public boolean isEmpty() {
        return numElems == 0;
    }

}
