public class Jacke extends Kleidungsstueck {
    private static final String typId = "777777";
    protected int wassersaeule;

    public Jacke(int groesse, Farbe f, String bezeichnung, int wassersaeule) {
        super(groesse, f, bezeichnung);
        this.wassersaeule = wassersaeule;
        this.artNr = typId + super.groesse;
    }

    public static String typNummer() {
        return typId;
    }

    public String artikelNummer() {
        return this.artNr;
    }

    public String toString() {
        return artNr + " " + super.toString() + " " + wassersaeule;
    }
}
