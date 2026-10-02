public abstract class Ticket {
    protected final float preis;
    protected boolean entwertet;

    public Ticket(float preis) {
        this.preis = preis;
        entwertet = false;
    }

    public void entwerten() {
        entwertet = true;
    }

    public float getPreis() {
        return preis;
    }

    public boolean istEntwertet() {
        return entwertet;
    }

    public abstract boolean gueltigInZone(Zone zone);

    public enum Zone {A, B, C}

    @Override
    public String toString() {
        return "Ticket [preis=%s, entwertet=%s]".formatted(preis, entwertet);
    }
}
