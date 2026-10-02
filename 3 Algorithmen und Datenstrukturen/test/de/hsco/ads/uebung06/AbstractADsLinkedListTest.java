package de.hsco.ads.uebung06;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public abstract class AbstractADsLinkedListTest<L extends ADsList> {

    public static final Object ELEM1 = "1";
    public static final Object ELEM2 = "2";
    public static final Object ELEM3 = "3";
    public static final Object ELEM4 = "4";

    protected abstract L createInstance(Object... elements);

    @Test
    public void testSize() {
        var emptyList = createInstance();
        assertEquals(0, emptyList.size());

        var list1 = createInstance(ELEM1);
        assertEquals(1, list1.size());

        var list2 = createInstance(ELEM1, ELEM2);
        assertEquals(2, list2.size());

        var list3 = createInstance(ELEM1, ELEM2, ELEM3);
        assertEquals(3, list3.size());
    }

    @Test
    public void testInsert() {
        var list1 = createInstance();
        list1.insert(0, ELEM1);
        assertEquals(ELEM1, list1.elementAt(0));

        list1.insert(1, ELEM2);
        assertEquals(ELEM1, list1.elementAt(0));
        assertEquals(ELEM2, list1.elementAt(1));

        list1.insert(0, ELEM3);
        assertEquals(ELEM3, list1.elementAt(0));
        assertEquals(ELEM1, list1.elementAt(1));
        assertEquals(ELEM2, list1.elementAt(2));

        list1.insert(2, ELEM4);
        assertEquals(ELEM3, list1.elementAt(0));
        assertEquals(ELEM1, list1.elementAt(1));
        assertEquals(ELEM4, list1.elementAt(2));
        assertEquals(ELEM2, list1.elementAt(3));
    }

    @Test
    public void testRemove() {
        var list1 = createInstance(ELEM1, ELEM2, ELEM3);
        list1.remove(1);
        assertEquals(ELEM1, list1.elementAt(0));
        assertEquals(ELEM3, list1.elementAt(1));

        list1.remove(0);
        assertEquals(ELEM3, list1.elementAt(0));

        list1.remove(0);
        assertEquals(0, list1.size());
        assertTrue(list1.isEmpty());

        var list2 = createInstance(ELEM1, ELEM2, ELEM3);
        list2.remove(2);
        assertEquals(ELEM1, list2.elementAt(0));
        assertEquals(ELEM2, list2.elementAt(1));

        list2.remove(2);
}

    @Test
    public void testElementAt() {
        var list1 = createInstance();
        list1.insert(0, ELEM1);
        assertEquals(ELEM1, list1.elementAt(0));

        list1.insert(1, ELEM2);
        assertEquals(ELEM2, list1.elementAt(1));

        var list2 = createInstance(ELEM1, ELEM2, ELEM3, ELEM4);
        assertEquals(ELEM1, list2.elementAt(0));
        assertEquals(ELEM2, list2.elementAt(1));
        assertEquals(ELEM3, list2.elementAt(2));
        assertEquals(ELEM4, list2.elementAt(3));
    }

    @Test
    public void testIsEmpty() {
        var emptyList = createInstance();
        assertTrue(emptyList.isEmpty());

        var list1 = createInstance(ELEM1);
        assertFalse(list1.isEmpty());

        var list2 = createInstance(ELEM1, ELEM2);
        assertFalse(list2.isEmpty());
    }

    @Test
    public void testFind() {
        var emptyList = createInstance();
        assertEquals(-1, emptyList.find(ELEM1));
        assertEquals(-1, emptyList.find(ELEM2));
        assertEquals(-1, emptyList.find(ELEM3));

        var list1 = createInstance(ELEM1);
        assertEquals(0, list1.find(ELEM1));
        assertEquals(-1, list1.find(ELEM2));
        assertEquals(-1, list1.find(ELEM3));

        var list2 = createInstance(ELEM1, ELEM2);
        assertEquals(0, list2.find(ELEM1));
        assertEquals(1, list2.find(ELEM2));
        assertEquals(-1, list2.find(ELEM3));
    }
}
