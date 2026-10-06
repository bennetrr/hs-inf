import java.util.Arrays;
import java.util.Iterator;

public class Spielfeld implements Iterable<char[]> {
    private final char[][] spielfeld;
    /**
     * Zähler, um zu erkennen, wann unentschieden ist
     */
    private int zaehler = 0;
    private char zeichen = 'o';

    public Spielfeld(int columns, int rows) {
        spielfeld = new char[rows][columns];
    }

    /**
     * Sammelstelle für die Funktionen, die überprüfen ob jmd. gewonnen hat
     *
     * @param column  die Spalte an der das Zeichen gesetzt wurde
     * @param row     die Reihe an der das Zeichen gesetzt wurde
     * @param zeichen das Zeichen
     */
    private boolean IsGameOver(int column, int row, char zeichen) {
        return (GameIsOver_row(column, row, zeichen) || GameIsOver_column(column, row, zeichen) || GameIsOver_straight1(column, row, zeichen) || GameIsOver_straight2(column, row, zeichen));
    }

    private boolean GameIsOver_row(int column, int row, char zeichen) {
        // nach links
        int go = row - 1; // mit dem Punkt links neber dem gesetzten beginne
        // ich
        int i = 1; // der gesetzte Punkt = 1 Treffer
        while (go >= 0) {
            if (spielfeld[column][go] != zeichen) break;
            go--;
            i++;
        }

        // nach rechts
        go = row + 1;
        while (go < spielfeld.length) {
            if (spielfeld[column][go] != zeichen) break;
            go++;
            i++;
        }

        return (i > 3);
    }

    private boolean GameIsOver_column(int column, int row, char zeichen) {
        // nach oben
        int go = column - 1;
        int i = 1;
        while (go >= 0) {
            if (spielfeld[go][row] != zeichen) break;
            go--;
            i++;
        }

        // nach unten
        go = column + 1;
        while (go < spielfeld.length) {
            if (spielfeld[go][row] != zeichen) break;
            go++;
            i++;
        }

        return (i > 3);
    }

    private boolean GameIsOver_straight1(int column, int row, char zeichen) {
        // nach links oben
        int go = row - 1;
        int go2 = column - 1;
        int i = 1;
        while (go >= 0 && go2 >= 0) {
            if (spielfeld[go2][go] != zeichen) break;
            go--;
            go2--;
            i++;
        }

        // nach rechts unten
        go = row + 1;
        go2 = column + 1;
        while (go < spielfeld[0].length && go2 < spielfeld.length) {
            if (spielfeld[go2][go] != zeichen) break;
            go++;
            go2++;
            i++;
        }

        return (i > 3);
    }

    private boolean GameIsOver_straight2(int column, int row, char zeichen) {
        // nach links unten
        int go = row - 1;
        int go2 = column + 1;
        int i = 1;
        while (go >= 0 && go2 < spielfeld.length) {
            if (spielfeld[go2][go] != zeichen) break;
            go--;
            go2++;
            i++;
        }

        // nach rechts oben
        go = row + 1;
        go2 = column - 1;
        while (go < spielfeld[0].length && go2 >= 0) {
            if (spielfeld[go2][go] != zeichen) break;
            go++;
            go2--;
            i++;
        }

        return (i > 3);
    }

    /**
     * Spalte wird übergeben und das Feld wird gesetzt
     *
     * @param column Eingegebene Spalte
     * @return Spieler, der gewonnen hat.<br><code>'\0'</code>, wenn unentschieden.<br><code>null</code>, wenn noch nicht entschieden.<br><code>'f'</code>, wenn Reihe voll.
     */
    public Character setzeFeld(int column) {
        column--;
        int pos2check;

        if (this.spielfeld[0][column] != '\0') {
            return 'f';
        }

        this.zeichen = this.zaehler % 2 == 0 ? 'o' : 'x'; // Spieler wechseln
        this.zaehler++;

        for (int i = 0; i < this.spielfeld.length; i++) { //Iteriere durch die Zeilen
            if (i + 1 == this.spielfeld.length) {
                // Nach der letzten Zeile kommt nichts mehr.
                // also darf in das aktuelle Kästchen geschrieben werden, obwohl im
                // nächsten nichts steht
                pos2check = i;
                if (this.spielfeld[pos2check][column] == '\0') {
                    this.spielfeld[i][column] = zeichen;
                    if (IsGameOver(i, column, zeichen)) { // Hat jmd gewonnen?
                        return zeichen;
                    }
                    break;
                }
            } else {
                //Überprüfe immer das folgende Feld
                pos2check = i + 1;
                if (this.spielfeld[pos2check][column] != '\0') {
                    this.spielfeld[i][column] = zeichen;
                    if (IsGameOver(i, column, zeichen)) { // Hat jmd gewonnen?
                        return zeichen;
                    }
                    break;
                }
            }
        }

        if (this.zaehler == this.spielfeld.length * this.spielfeld[0].length) {
            return '\0'; // Unentschieden
        }

        return null;
    }

    @Override
    public Iterator<char[]> iterator() {
        return Arrays.stream(this.spielfeld).iterator();
    }

    public int columns() {
        return this.spielfeld[0].length;
    }

    public int rows() {
        return this.spielfeld.length;
    }

    public char zeichen() {
        return this.zeichen;
    }
}
