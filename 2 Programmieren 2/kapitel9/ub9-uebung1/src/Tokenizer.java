import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class Tokenizer {
    public static void main(String[] args) throws IOException {
        var stream = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));

        while (true) {
            var token = stream.nextToken();

            switch (stream.ttype) {
                case StreamTokenizer.TT_NUMBER -> System.out.println("Nummer: " + stream.nval);
                case StreamTokenizer.TT_WORD -> System.out.println("Wort: " + stream.sval);
                case StreamTokenizer.TT_EOL -> System.out.println("New line");
                case StreamTokenizer.TT_EOF -> {
                    System.out.println("End of file");
                    System.exit(0);
                }
                default -> System.out.println("Zeichen: " + Character.toChars(token)[0]);
            }
        }
    }
}
