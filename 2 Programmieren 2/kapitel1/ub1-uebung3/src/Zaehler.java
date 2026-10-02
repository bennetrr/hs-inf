public class Zaehler {
    private int einer;
    private int zehner;

    public Zaehler(int zehner, int einer) {
        this.einer = einer;
        this.zehner = zehner;
    }

    public void erhoeheUmEins() throws EinerUeberlauf {
        if (einer + 1 >= 10) {
            throw new EinerUeberlauf();
        }

        einer++;
    }

    public void erhoeheUmZehn() throws Ueberlauf {
        if (zehner + 1 >= 10) {
            throw new Ueberlauf();
        }

        zehner++;
    }

    public void zaehlen() {
        try {
            erhoeheUmEins();
        } catch (EinerUeberlauf e) {
            einer = 0;
            try {
                erhoeheUmZehn();
            } catch (Ueberlauf ex) {
                zehner = 0;
                System.out.println("Zähler größer 99");
            }
        }
    }

    public String toString() {
        return "" + zehner + einer;
    }
}
