public class Person {
    protected String vorname;
    protected String nachname;
    protected String strassenname;
    protected String hausnummer;
    protected String ort;
    protected int postleitzahl;

    public Person(String vorname, String nachname, String strassenname, String hausnummer, String ort, int postleitzahl) {
        this.vorname = vorname;
        this.nachname = nachname;
        this.strassenname = strassenname;
        this.hausnummer = hausnummer;
        this.ort = ort;
        this.postleitzahl = postleitzahl;
    }

    public static void Main() {
        var student1 = new Student("Peter", "Müller", "Hauptstrasse", "4a", "Coburg", 96450, 455555);
        var dozent1 = new Dozent("Dieter", "Landes", "Am Ring", "12", "Coburg", 96450, "Software Engineering");
        var person = new Person("Tim", "Schmitt", "Ayinger Str.", "4a", "München", 89006);
        var student2 = new Student("Yvonne", "Hinz", "Bahnhofstr", "30", "Nürnberg", 91000, 41622);
        var dozent2 = new Dozent("Claudia", "Ehrlicher", "Am Baum", "12", "Berlin", 30323, "Ethik");

        System.out.println(student1);
        System.out.println(dozent1);
        System.out.println(person);
        System.out.println(student2);
        System.out.println(dozent2);
    }

    public String getVorname() {
        return vorname;
    }

    public void setVorname(String vorname) {
        this.vorname = vorname;
    }

    public String getNachname() {
        return nachname;
    }

    public void setNachname(String nachname) {
        this.nachname = nachname;
    }

    public String getStrassenname() {
        return strassenname;
    }

    public void setStrassenname(String strassenname) {
        this.strassenname = strassenname;
    }

    public String getHausnummer() {
        return hausnummer;
    }

    public void setHausnummer(String hausnummer) {
        this.hausnummer = hausnummer;
    }

    public String getOrt() {
        return ort;
    }

    public void setOrt(String ort) {
        this.ort = ort;
    }

    public int getPostleitzahl() {
        return postleitzahl;
    }

    public void setPostleitzahl(int postleitzahl) {
        this.postleitzahl = postleitzahl;
    }

    @Override
    public String toString() {
        return "Person [nachname=%s, vorname=%s, strassenname=%s, hausnummer=%s, ort=%s, postleitzahl=%d]".formatted(nachname, vorname, strassenname, hausnummer, ort, postleitzahl);
    }
}
