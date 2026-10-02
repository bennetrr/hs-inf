import java.util.TreeSet;

public class BibliothekSet extends AbstractBibliothek {
    public BibliothekSet() {
        super();
        super.buecher = new TreeSet<>();
    }
}
