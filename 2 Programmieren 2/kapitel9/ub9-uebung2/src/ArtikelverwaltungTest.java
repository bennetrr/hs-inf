public class ArtikelverwaltungTest {
    public static Artikel[] create10Artikel() {
        return new Artikel[]{new Jeans(34, Kleidungsstueck.Farbe.SCHWARZ, "Levis", 340), new Jeans(36, Kleidungsstueck.Farbe.GRUEN, "Boss", 360), new Jeans(38, Kleidungsstueck.Farbe.ROT, "Wrangler", 380), new Jeans(40, Kleidungsstueck.Farbe.BLAU, "Denim", 400), new Jeans(42, Kleidungsstueck.Farbe.GRAU, "Mac", 420), new Jeans(44, Kleidungsstueck.Farbe.SCHWARZ, "Brix", 440), new Jeans(34, Kleidungsstueck.Farbe.GRUEN, "Levis", 340), new Jeans(36, Kleidungsstueck.Farbe.ROT, "Boss", 360), new Jeans(38, Kleidungsstueck.Farbe.BLAU, "Wrangler", 380), new Jeans(40, Kleidungsstueck.Farbe.GRAU, "Denim", 400)};
    }

    public static void main(String[] args) {
        Artikelverwaltung av = new Artikelverwaltung(create10Artikel());
        av.write("artikel.txt");

        Artikelverwaltung av2 = new Artikelverwaltung();
        av2.read("artikel.txt");
        System.out.println(av2);
    }
}
