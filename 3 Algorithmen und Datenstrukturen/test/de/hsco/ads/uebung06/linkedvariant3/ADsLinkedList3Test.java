package de.hsco.ads.uebung06.linkedvariant3;


import de.hsco.ads.uebung06.AbstractADsLinkedListTest;

public class ADsLinkedList3Test extends AbstractADsLinkedListTest<ADsLinkedList> {

    @Override
    protected ADsLinkedList createInstance(Object... elements) {
        return new ADsLinkedList(elements);
    }
}
