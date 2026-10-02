public record Buch(String isbn, String autor, String titel, float preis) implements Comparable<Buch> {
    @Override
    public String toString() {
        return "%s \"%s\" %s %.1f".formatted(autor, titel, isbn, preis);
    }

    @Override
    public int compareTo(Buch o) {
        return isbn.compareTo(o.isbn);
    }
}
