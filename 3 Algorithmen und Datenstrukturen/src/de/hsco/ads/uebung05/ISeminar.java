package de.hsco.ads.uebung05;

public interface ISeminar {
    void einschreiben(IStudent student);
    boolean istEingeschrieben(IStudent student);
    int anzahlTeilnehmer();
    String getName();
}
