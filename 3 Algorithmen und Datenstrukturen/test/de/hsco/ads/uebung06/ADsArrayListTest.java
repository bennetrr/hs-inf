package de.hsco.ads.uebung06;


public class ADsArrayListTest extends AbstractADsLinkedListTest<ADsArrayList> {

    @Override
    protected ADsArrayList createInstance(Object... elements) {
        return new ADsArrayList(256, elements);
    }

}
