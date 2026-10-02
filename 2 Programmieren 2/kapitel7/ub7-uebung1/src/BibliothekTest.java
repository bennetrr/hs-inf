import java.util.Comparator;

public class BibliothekTest {
    public static void init(AbstractBibliothek bib) {
        bib.einfügen(new Buch("9784898645133","Reinhard Schiedermeier", "Java Praktikum",                                                           23.0f));
        bib.einfügen(new Buch("01303451517",  "Harvey Deitel",          "How to program Java",                                                      134.0f));
        bib.einfügen(new Buch("0136290310",   "Bertrand Meyer",         "Object Oriented Software Construction",                                    67.0f));
        bib.einfügen(new Buch("9783642018558","Bertrand Meyer",         "Software Engineering Approaches for Offshore and Outsourced Development",  78.0f));
        bib.einfügen(new Buch("9783897214484","Kathy Sierra",           "Java von Kopf bis Fuss",                                                   110.0f));
        bib.einfügen(new Buch("9784898645133","Reinhard Schiedermeier", "Java Praktikum",                                                           23.0f));
        bib.einfügen(new Buch("01303451517",  "Harvey Deitel",          "How to program Java",                                                      134.0f));
        bib.einfügen(new Buch("0136290310",   "Bertrand Meyer",         "Object Oriented Software Construction",                                    67.0f));
        bib.einfügen(new Buch("9783642018558","Bertrand Meyer",         "Software Engineering Approaches for Offshore and Outsourced Development",  78.0f));
        bib.einfügen(new Buch("9783897214484","Kathy Sierra",           "Java von Kopf bis Fuss",                                                   110.0f));
        bib.einfügen(new Buch("9780123725011","Mark Utting",           "Pratical Model based Testing",                                                   189.0f));
    }

    public static class BuchNachTitel implements Comparator<Buch> {
        @Override
        public int compare(Buch o1, Buch o2) {
            return o1.titel().compareTo(o2.titel());
        }
    }
}
