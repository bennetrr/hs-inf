public class Dozent extends Person {
    protected String lehrgebiet;

    public Dozent(String vorname, String nachname, String strassenname, String hausnummer, String ort, int postleitzahl, String lehrgebiet) {
        super(vorname, nachname, strassenname, hausnummer, ort, postleitzahl);
        this.lehrgebiet = lehrgebiet;
    }

    public String getLehrgebiet() {
        return lehrgebiet;
    }

    public void setLehrgebiet(String lehrgebiet) {
        this.lehrgebiet = lehrgebiet;
    }

    @Override
    public String toString() {
        return "Dozent [lehrgebiet=%s, nachname=%s, vorname=%s, strassenname=%s, hausnummer=%s, ort=%s, postleitzahl=%d]".formatted(lehrgebiet, nachname, vorname, strassenname, hausnummer, ort, postleitzahl);
    }
}
