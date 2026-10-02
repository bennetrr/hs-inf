package de.hsco.ads.uebung05;

import java.util.ArrayList;
import java.util.List;

public class Seminar implements ISeminar {
    private final String name;
    private final int maxAnzahlTeilnehmer;
    private final List<IStudent> teilnehmer;

    public Seminar(String name, int maxAnzahlTeilnehmer) {
        this.name = name;
        this.maxAnzahlTeilnehmer = maxAnzahlTeilnehmer;
        this.teilnehmer = new ArrayList<>(maxAnzahlTeilnehmer);
    }

    @Override
    public void einschreiben(IStudent student) {
        if (anzahlTeilnehmer() >= maxAnzahlTeilnehmer) return;
        if (istEingeschrieben(student)) return;
        teilnehmer.add(student);
    }

    @Override
    public boolean istEingeschrieben(IStudent student) {
        return teilnehmer.contains(student);
    }

    @Override
    public int anzahlTeilnehmer() {
        return teilnehmer.size();
    }

    @Override
    public String getName() {
        return name;
    }
}
