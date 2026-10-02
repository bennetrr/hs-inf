public class Mehrfahrtenticket extends Ticket {
    protected final Zone zone;
    protected int fahrten;

    public Mehrfahrtenticket(float preis, int fahrten, Zone zone) {
        super(preis);
        this.zone = zone;
        this.fahrten = fahrten;
    }

    public int getFahrten() {
        return fahrten;
    }

    public Zone getZone() {
        return zone;
    }

    @Override
    public void entwerten() {
        fahrten--;
        if (fahrten < 1) {
            super.entwerten();
        }
    }

    @Override
    public boolean gueltigInZone(Zone zone) {
        return this.zone.equals(zone);
    }

    @Override
    public String toString() {
        return "Mehrfahrtenticket [fahrten=%d, zone=%s, preis=%s, entwertet=%s]".formatted(fahrten, zone, preis, entwertet);
    }
}
