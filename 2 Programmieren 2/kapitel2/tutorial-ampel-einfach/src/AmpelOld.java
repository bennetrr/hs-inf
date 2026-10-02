public class AmpelOld {
    static final byte GREEN = 0;
    static final byte RED = 1;
    static final byte YELLOW = 2;
    static final byte RED_YELLOW = 3;
    static final byte OFF = 4;
    static String[] messages = {"GREEN", "RED", "YELLOW", "RED_YELLOW"};
    private final int nummer;
    private byte zustand;

    public AmpelOld(int nummer) {
        this.zustand = RED;
        this.nummer = nummer;
    }

    public int getZustand() {
        return zustand;
    }

    public void schalten() {
        switch (zustand) {
            case RED -> zustand = RED_YELLOW;
            case YELLOW -> zustand = RED;
            case GREEN -> zustand = YELLOW;
            case RED_YELLOW -> zustand = GREEN;
        }
    }

    public String getFarbe() {
        return "%d %s".formatted(nummer, messages[this.zustand]);
    }

    // Die folgende Methode ist nur dann erforderlich, wenn die Ampel sich selbst steuert
    public void steuernAutomatisch() {
        try {
            do {
                this.schalten();
                System.out.println(this.nummer + ":" + getFarbe());
                Thread.sleep(1000);
            } while (true);
        } catch (Exception e) {
            System.out.println("INTERNAL ERROR");
        }
    }
}
