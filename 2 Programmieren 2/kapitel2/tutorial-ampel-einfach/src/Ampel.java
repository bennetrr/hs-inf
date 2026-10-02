public class Ampel {

    private final int nummer;
    private Farbe zustand;

    public Ampel(int nummer) {
        this.zustand = Farbe.RED;
        this.nummer = nummer;
    }

    public Farbe getZustand() {
        return zustand;
    }

    public void schalten() {
        switch (zustand) {
            case RED -> zustand = Farbe.RED_YELLOW;
            case YELLOW -> zustand = Farbe.RED;
            case GREEN -> zustand = Farbe.YELLOW;
            case RED_YELLOW -> zustand = Farbe.GREEN;
        }
    }

    public String toString() {
        return "%d: zustand=%s".formatted(this.nummer, zustand.toString());
    }

    public enum Farbe {GREEN, RED, YELLOW, RED_YELLOW, OFF}
}
