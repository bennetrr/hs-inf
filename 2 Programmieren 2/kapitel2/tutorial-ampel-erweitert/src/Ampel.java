public class Ampel {
    private final int nummer;
    private AmpelFarbe zustand;

    public Ampel(int nummer) {
        this.zustand = AmpelFarbe.RED;
        this.nummer = nummer;
    }

    public AmpelFarbe getZustand() {
        return zustand;
    }

    public void schalten() {
        switch (zustand) {
            case RED -> zustand = AmpelFarbe.RED_YELLOW;
            case YELLOW -> zustand = AmpelFarbe.RED;
            case GREEN -> zustand = AmpelFarbe.YELLOW;
            case RED_YELLOW -> zustand = AmpelFarbe.GREEN;
        }
    }

    public String toString() {
        return "%d: zustand=%s %s".formatted(this.nummer, zustand.toString(), zustand.toLampen());
    }
}
