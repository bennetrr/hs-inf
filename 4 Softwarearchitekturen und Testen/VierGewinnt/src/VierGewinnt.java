import java.io.InputStream;
import java.io.PrintStream;

/**
 * @author Torben Brodt
 * @version 1.1
 * <p>
 * <p />Spiel: Vier gewinnt
 * <p />Funktioniert mit Java < 1.5
 */
public class VierGewinnt {
    private final java.util.Scanner scanner;
    private final PrintStream out;
    private final PrintStream err;
    /**
     * Aktueller Spielername für die Gewinnerausgabe
     */
    private String SPIELER;
    private Spielfeld spielfeld = null;

    public VierGewinnt(InputStream in, PrintStream out, PrintStream err) {
        this.scanner = new java.util.Scanner(in);
        this.out = out;
        this.err = err;
    }

    public void play() {
        int columns, rows;
        String player1, player2;
        Character winner = null;

        //Abfragen des Spielernamens
        player1 = eingabeString("Name von SpielerIn A\t\t\t: ");

        do {
            player2 = eingabeString("Name von SpielerIn B\t\t\t: ");
        } while (player1.equals(player2)); //Frage erneut, wenn die Spielernamen gleich sind

        //Abfragen der Maße
        do {
            columns = eingabeInt("Breite des Spielfeldes (mindestens 4)\t: ");
        } while (columns < 4); //Frage erneut, wenn die Breite zu klein gewählt wurde

        do {
            rows = eingabeInt("Höhe des Spielfeldes (mindestens 4)\t: ");
        } while (rows < 4); //Frage erneut, wenn die Höhe zu klein gewählt wurde

        this.spielfeld = new Spielfeld(columns, rows);

        while (winner == null || winner == 'f') {
            SPIELER = this.spielfeld.zeichen() == 'o' ? player1 : player2;
            this.showSpielfeld();

            var eingabe = eingabeInt("\n" + SPIELER + " (" + this.spielfeld.zeichen() + ") ist am Zug. Bitte gib die Spalte ein: ");

            if (eingabe > columns || eingabe < 1) {
                this.err.println("Feld existiert nicht.. Bitte versuch es nochmal!");
                continue;
            }

            winner = this.spielfeld.setzeFeld(eingabe);

            if (winner != null && winner == 'f') {
                this.out.println("Die Reihe ist voll.. Pech!");
            }
        }

        if (winner == '\0') {
            this.showSpielfeld();
            this.out.println("Unentschieden!");
        } else {
            this.out.println("Spieler mit " + this.spielfeld.zeichen() + " hat gewonnen");
        }
    }

    /**
     * @param text Bildschirmausgabe
     * @return Tastatureingabe
     */
    int eingabeInt(String text) {
        this.out.print(text);
        return scanner.nextInt();
    }

    /**
     * @param text Bildschirmausgabe
     * @return Tastatureingabe
     */
    String eingabeString(String text) {
        this.out.print(text);
        return scanner.next();
    }

    /**
     * Zeigt das komplette this.spielfeld auf dem Bildschirm
     */
    void showSpielfeld() {
        StringBuilder Geruest = new StringBuilder();
        StringBuilder row_start = new StringBuilder(" "); // erste Zeile 1 2 3 4
        StringBuilder row_divide = new StringBuilder("|"); // Trennzeile |-----|
        StringBuilder row_end = new StringBuilder("-"); // letzte Zeile -------

        if (this.spielfeld.columns() > 9) {
            for (int i = 1; i <= this.spielfeld.columns(); i++)
                row_start.append((i / 10 == 0) ? " " : i / 10).append(" ");
            row_start.append("\n ");
        }
        for (int i = 1; i <= this.spielfeld.columns(); i++) {
            row_start.append(i % 10).append(" ");
            row_divide.append((i == this.spielfeld.columns()) ? "-|" : "--");
            row_end.append("--");
        }
        this.out.println(row_start);
        this.out.println(row_divide);

        for (char[] arrZeile : this.spielfeld) { //iteriere durch alle Zeilen
            for (char arrSpalte : arrZeile) { //iteriere durch alle Spalten
                Geruest.append("|");
                Geruest.append((arrSpalte == '\0') ? ' ' : arrSpalte);
            }
            Geruest.append("|\n");
        }
        Geruest.append(row_end).append("\n");
        this.out.println(Geruest);
    }
}
