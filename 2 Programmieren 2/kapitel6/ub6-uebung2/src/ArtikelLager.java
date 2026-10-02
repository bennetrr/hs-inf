import java.util.LinkedList;

public class ArtikelLager<E> {
    private final Ort<E>[] orte;

    @SuppressWarnings("unchecked")
    public ArtikelLager(E[] artikel, int anzahlOrte) {
        orte = (Ort<E>[]) new Ort[anzahlOrte];

        for (int i = 0; i < orte.length; i++) {
            orte[i] = new Ort<>(i);
        }

        for (int i = 0; i < artikel.length; i++) {
            orte[i].hinzufügen(artikel[i]);
        }
    }

    @SuppressWarnings("unchecked")
    public ArtikelLager(LinkedList<E> artikel, int anzahlOrte) {
        this((E[]) artikel.toArray(), anzahlOrte);
    }

    public LinkedList<E> elements() {
        var list = new LinkedList<E>();

        for (Ort<E> ort : orte) {
            if (ort.istBelegt()) {
                list.add(ort.getEingelagertesElement());
            }
        }

        return list;
    }

    public boolean einlagern(E e) {
        for (Ort<E> ort : orte) {
            if (!ort.istBelegt()) {
                ort.hinzufügen(e);
                return true;
            }
        }

        return false;
    }

    @Override
    public String toString() {
        var builder = new StringBuilder();

        for (E element : elements()) {
            builder.append(element).append('\n');
        }

        return builder.toString();
    }

    // Methoden für Übung 6.3
    public E auslagern(String artikelnummer) {
        for (Ort<E> ort : orte) {
            if (ort.istBelegt()) {
                var e = ort.getEingelagertesElement();

                if (e instanceof Artikel && ((Artikel) e).artikelNummer().equals(artikelnummer)) {
                    return ort.entnehmen();
                }
            }
        }

        return null;
    }

    public int bestandSuchen(String artikelnummer) {
        var count = 0;

        for (Ort<E> ort : orte) {
            if (ort.istBelegt()) {
                var e = ort.getEingelagertesElement();

                if (e instanceof Artikel && ((Artikel) e).artikelNummer().equals(artikelnummer)) {
                    count++;
                }
            }
        }

        return count;
    }
}
