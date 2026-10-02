public class Generalabo extends Ticket {
    protected final String inhaber;
    protected final String verfallsDatum;

    public Generalabo(float preis, String inhaber, String verfallsDatum) {
        super(preis);
        this.inhaber = inhaber;
        this.verfallsDatum = verfallsDatum;
    }

    public String getInhaber() {
        return inhaber;
    }

    public String getVerfallsDatum() {
        return verfallsDatum;
    }

    @Override
    public void entwerten() {}

    @Override
    public boolean gueltigInZone(Zone zone) {
        return true;
    }

    @Override
    public String toString() {
        return "Generalabo [inhaber=%s, verfallsDatum=%s, preis=%s, entwertet=%s]".formatted(inhaber, verfallsDatum, preis, entwertet);
    }
}
