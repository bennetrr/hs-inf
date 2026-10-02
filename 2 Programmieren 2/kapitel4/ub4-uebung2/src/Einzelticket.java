public class Einzelticket extends Ticket {
    protected final String verfallsDatum;
    protected final Zone zone;

    public Einzelticket(float preis, String verfallsDatum, Zone zone) {
        super(preis);
        this.verfallsDatum = verfallsDatum;
        this.zone = zone;
    }

    public String getVerfallsDatum() {
        return verfallsDatum;
    }

    public Zone getZone() {
        return zone;
    }

    @Override
    public boolean gueltigInZone(Zone zone) {
        return this.zone.equals(zone);
    }

    @Override
    public String toString() {
        return "Einzelticket [zone=%s, verfallsDatum=%s, preis=%s, entwertet=%s]".formatted(zone, verfallsDatum, preis, entwertet);
    }
}
