public class AmpelTest {
    public static void main(String[] args) {
        final int AMPEL_ANZAHL = 10;
        Ampel[] a = new Ampel[AMPEL_ANZAHL];

        // Ampeln erzeugen
        for (int i = 0; i < AMPEL_ANZAHL; i++)
            a[i] = new Ampel(i);

        // Ampeln nacheinander schalten mit Verzögerung von 1000 msec
        do {
            try {
                for (int i = 0; i < AMPEL_ANZAHL; i++) {
                    a[i].schalten();
                    System.out.println(a[i].toString());
                    Thread.sleep(1000);
                }
            } catch (Exception e) {
                System.out.println("INTERNAL ERROR");
            }
        } while (true);
    }
}
