class ArtikelLagerTest {
    public static ArtikelLager<Jeans> testArtikelLagerJeansInit() {
        return new ArtikelLager<>(new Jeans[]{new Jeans(34, Kleidungsstueck.Farbe.SCHWARZ, "Jeans Levis 501", 340), new Jeans(36, Kleidungsstueck.Farbe.GRUEN, "Jeans Levis 502", 360), new Jeans(38, Kleidungsstueck.Farbe.ROT, "Jeans Wrangler 50", 380), new Jeans(40, Kleidungsstueck.Farbe.BLAU, "Jeans Denim 550 ", 400), new Jeans(42, Kleidungsstueck.Farbe.GRAU, "Jeans Denim 548", 420), new Jeans(44, Kleidungsstueck.Farbe.SCHWARZ, "Jeans Wrangler 49", 440)}, 10);
    }

    public static ArtikelLager<Jacke> testArtikelLagerJackeInit() {
        return new ArtikelLager<Jacke>(new Jacke[]{new Jacke(34, Kleidungsstueck.Farbe.SCHWARZ, "Fleece Jacke Roos", 100), new Jacke(36, Kleidungsstueck.Farbe.GRUEN, "Lederjacke Only", 1000), new Jacke(38, Kleidungsstueck.Farbe.ROT, "Blouson", 2000), new Jacke(40, Kleidungsstueck.Farbe.BLAU, "Kapuzenparka Cheer ", 3000), new Jacke(42, Kleidungsstueck.Farbe.GRAU, "Jacke Melrose", 100), new Jacke(44, Kleidungsstueck.Farbe.SCHWARZ, "BLENDSHE", 1000)}, 10);
    }

    public static ArtikelLager<? extends Kleidungsstueck> testArtikelLagerGemischtInit() {
        return new ArtikelLager<>(new Kleidungsstueck[]{new Jacke(34, Kleidungsstueck.Farbe.SCHWARZ, "Fleece Jacke Roos", 100), new Jacke(36, Kleidungsstueck.Farbe.GRUEN, "Lederjacke Only", 1000), new Jacke(38, Kleidungsstueck.Farbe.ROT, "Blouson", 2000), new Jacke(40, Kleidungsstueck.Farbe.BLAU, "Kapuzenparka Cheer ", 3000), new Jacke(42, Kleidungsstueck.Farbe.GRAU, "Jacke Melrose", 100), new Jacke(44, Kleidungsstueck.Farbe.SCHWARZ, "BLENDSHE", 1000), new Jeans(34, Kleidungsstueck.Farbe.SCHWARZ, "Jeans Levis 501", 340), new Jeans(36, Kleidungsstueck.Farbe.GRUEN, "Jeans Levis 502", 360), new Jeans(38, Kleidungsstueck.Farbe.ROT, "Jeans Wrangler 50", 380), new Jeans(40, Kleidungsstueck.Farbe.BLAU, "Jeans Denim 550 ", 400), new Jeans(42, Kleidungsstueck.Farbe.GRAU, "Jeans Denim 548", 420), new Jeans(44, Kleidungsstueck.Farbe.SCHWARZ, "Jeans Wrangler 49", 440)}, 20);
    }
}
