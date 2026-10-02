import java.util.Arrays;

public class OrtTest {
    public static void main(String[] args) {
        System.out.println(Arrays.toString(testEinfuegenEntfernen()));
    }

    @SuppressWarnings("unchecked")
    public static Ort<String>[] testEinfuegenEntfernen() {
        var produkte = new String[]{"PC Fujitsu LA 3740", "Miele Waschmaschine ML300", "Siemens HL 500", "OSRAM MM 100", "Bosch Rasenmäher HH "};
        Ort<String>[] orte = (Ort<String>[]) new Ort[produkte.length];

        for (int i = 0; i < produkte.length; i++) {
            var ort = new Ort<String>(i);
            ort.hinzufügen(produkte[i]);
            orte[i] = ort;
        }

        orte[0].entnehmen();
        orte[produkte.length / 2].entnehmen();
        orte[orte.length - 1].entnehmen();

        return orte;
    }
}
