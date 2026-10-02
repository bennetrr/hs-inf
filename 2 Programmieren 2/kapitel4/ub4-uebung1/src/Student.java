public class Student extends Person {
    protected final int matrikelNummer;

    public Student(String vorname, String nachname, String strassenname, String hausnummer, String ort, int postleitzahl, int matrikelNummer) {
        super(vorname, nachname, strassenname, hausnummer, ort, postleitzahl);
        this.matrikelNummer = matrikelNummer;
    }

    public int getMatrikelNummer() {
        return matrikelNummer;
    }

    @Override
    public String toString() {
        return "Student [matrikelNummer=%d, nachname=%s, vorname=%s, strassenname=%s, hausnummer=%s, ort=%s, postleitzahl=%d]".formatted(matrikelNummer, nachname, vorname, strassenname, hausnummer, ort, postleitzahl);
    }
}
