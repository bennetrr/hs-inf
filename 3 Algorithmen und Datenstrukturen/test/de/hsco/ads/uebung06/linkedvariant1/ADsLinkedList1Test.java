package de.hsco.ads.uebung06.linkedvariant1;


import de.hsco.ads.uebung06.AbstractADsLinkedListTest;

public class ADsLinkedList1Test extends AbstractADsLinkedListTest<ADsLinkedList> {

    @Override
    protected ADsLinkedList createInstance(Object... elements) {
        return new ADsLinkedList(elements);
    }
}
