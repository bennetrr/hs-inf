public record Karte(Farbe farbe, Wert wert) implements Comparable<Karte> {
    public Karte(Karte k2) {
        this(k2.farbe, k2.wert);
    }

    enum Farbe {
        KARO, HERZ, PIK, KREUZ
    }

    enum Wert {
        SIEBEN, ACHT, NEUN, ZEHN, BUBE, DAME, KOENIG, ASS
    }

    @Override
    public int compareTo(Karte k2) {
        var farbeComp = Integer.compare(farbe.ordinal(), k2.farbe.ordinal());

        if (farbeComp == 0) {
            return Integer.compare(wert.ordinal(), k2.wert.ordinal());
        }
        return farbeComp;
    }

    @Override
    public String toString() {
        return "Karte[farbe=%s, wert=%s]".formatted(farbe, wert);
    }
}
