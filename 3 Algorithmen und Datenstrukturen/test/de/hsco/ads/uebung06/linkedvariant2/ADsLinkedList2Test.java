package de.hsco.ads.uebung06.linkedvariant2;


import de.hsco.ads.uebung06.AbstractADsLinkedListTest;

public class ADsLinkedList2Test extends AbstractADsLinkedListTest<ADsLinkedList> {

    @Override
    protected ADsLinkedList createInstance(Object... elements) {
        return new ADsLinkedList(elements);
    }
}
