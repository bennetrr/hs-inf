public class Jeans extends Kleidungsstueck {
    private static final String typId = "567407";
    protected int schrittlaenge;

    public Jeans(int groesse, Farbe f, String bezeichnung, int schrittlaenge) {
        super(groesse, f, bezeichnung);
        artNr = typId + super.groesse;
        this.schrittlaenge = schrittlaenge;
    }

    public static String typNummer() {
        return typId;
    }

    public static boolean isJeans(String artikelnummer) {
        String s = artikelnummer.substring(0, 5);
        return s.equals(typId);
    }

    public String artikelNummer() {
        return artNr;
    }

    public String toString() {
        return artNr + " " + super.toString() + " " + schrittlaenge;
    }
}
