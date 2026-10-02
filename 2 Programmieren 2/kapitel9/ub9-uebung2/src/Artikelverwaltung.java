import java.io.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

public class Artikelverwaltung {
    List<Artikel> artikel;

    public Artikelverwaltung() {
        this.artikel = new LinkedList<>();
    }

    public Artikelverwaltung(Artikel[] artikel) {
        this.artikel = new LinkedList<>(Arrays.asList(artikel));
    }

    public void write(String filename) {
        try (var writer = new BufferedWriter(new FileWriter(filename))) {
            writer.write(artikel.stream().map(Artikel::toString).collect(Collectors.joining(",")));
        } catch (IOException exc) {
            System.out.println("ERROR: Failed to open file");
        }
    }

    public void read(String filename) {
        try(var reader = new BufferedReader(new FileReader(filename))) {
            var tokenizer = new StreamTokenizer(reader);
            this.artikel = new LinkedList<>();

            int index = 0;
            int groesse = 0;
            Kleidungsstueck.Farbe f = Kleidungsstueck.Farbe.SCHWARZ;
            String bezeichnung = "";
            int schrittlaenge = 0;

            while (true) {
                var token = tokenizer.nextToken();

                switch (tokenizer.ttype) {
                    case StreamTokenizer.TT_NUMBER -> {
                        switch (index) {
                            case 0 -> {}
                            case 2 -> groesse = (int) tokenizer.nval;
                            case 4 -> schrittlaenge = (int) tokenizer.nval;
                            default -> {
                                System.err.println("Invalid format");
                                System.exit(1);
                            }
                        }
                        index++;
                    }
                    case StreamTokenizer.TT_WORD -> {
                        switch (index) {
                            case 1 -> bezeichnung = tokenizer.sval;
                            case 3 -> f = Kleidungsstueck.Farbe.valueOf(tokenizer.sval);
                            default -> {
                                System.err.println("Invalid format");
                                System.exit(1);
                            }
                        }
                        index++;
                    }
                    default -> {
                        if (tokenizer.ttype == StreamTokenizer.TT_EOF || tokenizer.ttype == StreamTokenizer.TT_EOL || Character.toChars(token)[0] == ',') {
                            this.artikel.add(new Jeans(
                                groesse,
                                f,
                                bezeichnung,
                                schrittlaenge
                            ));
                            index = 0;

                            if (tokenizer.ttype == StreamTokenizer.TT_EOF || tokenizer.ttype == StreamTokenizer.TT_EOL) {
                                return;
                            }
                        } else {
                            System.err.println("Invalid format");
                            System.exit(1);
                        }
                    }
                }
            }
        } catch (IOException exc) {
            System.out.println("ERROR: Failed to open file");
        }
    }

    @Override
    public String toString() {
        return artikel.stream().map(Artikel::toString).collect(Collectors.joining("\n"));
    }
}
