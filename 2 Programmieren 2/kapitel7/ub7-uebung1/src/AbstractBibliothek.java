import java.util.*;
import java.util.stream.Collectors;

public abstract class AbstractBibliothek {
    Collection<Buch> buecher;

    public void einfügen(Buch buch) {
        buecher.add(buch);
    }

    public Collection<Buch> sucheNachAutor(String autor) {
        return buecher.stream().filter(buch -> buch.autor().equalsIgnoreCase(autor)).toList();
    }

    public Buch sucheNachISBN(String isbn) {
        return buecher.stream().filter(buch -> buch.isbn().equals(isbn)).findFirst().orElse(null);
    }

    public Map<String, List<Buch>> bestandNachAutorAuflisten() {
        return buecher.stream().collect(Collectors.groupingBy(Buch::autor));
	}

    public Collection<Buch> bestandSortierenNach(Comparator<Buch> comp) {
        return buecher.stream().sorted(comp).toList();
    }

    @Override
    public String toString() {
        var out = new StringBuilder("[\n");

        for (Buch buch : buecher) {
            out.append(buch).append('\n');
        }

        out.append(']');
        return out.toString();
    }
}
