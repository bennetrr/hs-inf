package de.hsco.ads.uebung06;

import de.hsco.ads.uebung06.linkedvariant1.ADsLinkedList;

public class Uebung06 {
    public static ADsList intersect(ADsList l1, ADsList l2) {
        var res = new ADsLinkedList();

        for (int i = 0; i < l1.size(); i++) {
            if (l2.find(l1.elementAt(i)) != -1) {
                res.insert(res.size(), l1.elementAt(i));
            }
        }

        return res;
    }
}
