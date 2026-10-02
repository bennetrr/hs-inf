import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        Kartenspiel spiel = new Kartenspiel();
        Karte[] originalKarten = spiel.getKarten();
        Karte[] kopieVomOriginal = Arrays.copyOf(originalKarten, originalKarten.length);

        spiel.mischen();

        Karte[] gemischteKarten = spiel.getKarten();

        boolean gemischt = false;
        int i = -1;

        while (!gemischt && ++i < originalKarten.length) {
            if (!kopieVomOriginal[i].equals(gemischteKarten[i])) {
                gemischt = true;
            }
        }

        System.out.println(Arrays.toString(spiel.getKarten()));

        if (gemischt) {
            System.out.println("Karten gemischt!");
        } else {
            System.out.println("Karten nicht gemischt!");
        }
    }
}
