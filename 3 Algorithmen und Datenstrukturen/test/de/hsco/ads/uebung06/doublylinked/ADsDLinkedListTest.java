package de.hsco.ads.uebung06.doublylinked;

import de.hsco.ads.uebung06.ADsList;
import de.hsco.ads.uebung06.AbstractADsLinkedListTest;

public class ADsDLinkedListTest extends AbstractADsLinkedListTest<ADsList> {

	@Override
	protected ADsList createInstance(Object... elements) {
		return new ADsDLinkedList(elements);
	}


}
