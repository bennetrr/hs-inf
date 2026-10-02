import java.util.Arrays;

public class Kartenspiel {
    private Karte[] karten;

    public Kartenspiel() {
        karten = new Karte[32];

        Karte.Farbe[] farben = Karte.Farbe.values();
        Karte.Wert[] werte = Karte.Wert.values();

        for (int iFarben = 0; iFarben < farben.length; iFarben++) {
            for (int iWerte = 0; iWerte < werte.length; iWerte++) {
                karten[(iFarben * werte.length) + iWerte] = new Karte(farben[iFarben], werte[iWerte]);
            }
        }
    }

    public Karte[] getKarten() {
        return karten;
    }

    public void mischen() {
        var neueKarten = new Karte[karten.length];

        for (int i = 0; i < neueKarten.length; i++) {
            Karte val;
            int index;

            do {
                index = (int) Math.floor(Math.random() * karten.length);
                val = karten[index];
            } while (val == null);

            karten[index] = null;
            neueKarten[i] = val;
        }

        karten = neueKarten;
    }

    public void kartenspielHinzufuegen(Kartenspiel neu) {
        var neueKarten = new Karte[karten.length + neu.karten.length];

        System.arraycopy(karten, 0, neueKarten, 0, karten.length);
        System.arraycopy(neu.karten, 0, neueKarten, karten.length, neu.karten.length);

        karten = neueKarten;
    }

    public void sortieren() {
        Arrays.sort(karten);
    }

    public String toString() {
        var builder = new StringBuilder();

        for (int i = 0; i < karten.length; i++) {
            builder.append(karten[i]).append(' ');

            if ((i + 1) % 8 == 0) {
                builder.append('\n');
            }
        }

        return builder.toString();
    }
}
