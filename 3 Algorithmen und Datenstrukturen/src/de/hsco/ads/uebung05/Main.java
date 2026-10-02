package de.hsco.ads.uebung05;

public class Main {
    public static void main(String[] args) {
        var seminar = new Seminar("ADs", 30);

        for (int i = 0; i < 28; i++) {
            seminar.einschreiben(new Student(Integer.toString(i)));
        }

        // Normales Einfügen sollte gehen
        var st1 = new Student("Ranft");
        seminar.einschreiben(st1);
        assert seminar.istEingeschrieben(st1);

        // Doppeltes Einfügen sollte nicht gehen
        var teilnehmerDavor = seminar.anzahlTeilnehmer();
        seminar.einschreiben(st1);
        assert seminar.anzahlTeilnehmer() == teilnehmerDavor;

        var st2 = new Student("Smilhin");
        seminar.einschreiben(st2);

        // Mehr Teilnehmer als zugelassen Einschreiben sollte nicht gehen
        var st3 = new Student("Virét");
        teilnehmerDavor = seminar.anzahlTeilnehmer();
        seminar.einschreiben(st3);
        assert seminar.anzahlTeilnehmer() == teilnehmerDavor;
    }
}
