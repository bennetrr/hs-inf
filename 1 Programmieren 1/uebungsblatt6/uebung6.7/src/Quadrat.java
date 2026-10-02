import java.util.Arrays;
import java.util.stream.Collectors;

public class Quadrat {
	public int[][] quad;

	public static Quadrat erzeugeMagicQuadrat(int n){
        if (n % 2 == 0) {
            return null;
        }

        var quadrat = new Quadrat(n);

        var zeile = n / 2;
        var spalte = n / 2 + 1;
        var m = 0;

        do {
            quadrat.quad[zeile][spalte] = ++m;

            if (--zeile < 0) {
                zeile = n - 1;
            }
            if (++spalte >= n) {
                spalte = 0;
            }

            if (quadrat.quad[zeile][spalte] != 0) {
                if (++zeile >= n) {
                    zeile = 0;
                }
                if (++spalte >= n) {
                    spalte = 0;
                }
            }

        } while (m < Math.pow(n, 2));

        return quadrat;
	}

	public Quadrat(int n) {
        quad = new int[n][n];
	}

	public Quadrat(int [][] q) {
        this(q.length);

        for (int i = 0; i < q.length; i++) {
            System.arraycopy(q[i], 0, quad[i], 0, q[i].length);
        }
	}

	public int zeilenSumme(int zeilenNr) {
        return Arrays.stream(quad[zeilenNr])
                .sum();
	}

	public int spaltenSumme(int spaltenNr) {
        return Arrays.stream(quad)
                .mapToInt(row -> row[spaltenNr])
                .sum();
	}

	public int diagonalSummeOToU() {
        int res = 0;
        for (int i = 0; i < quad.length; i++) {
            res += quad[i][i];
        }
        return res;
	}

	public int diagonalSummeUToO() {
        int res = 0;
        for (int i = 0; i < quad.length; i++) {
            res += quad[i][quad.length - i - 1];
        }
        return res;
	}

	public boolean isMagic() {
        for (int i = 1; i <= Math.pow(quad.length, 2) ; i++) {
            int finalI = i;
            if (Arrays.stream(quad)
                    .flatMapToInt(Arrays::stream)
                    .noneMatch(x -> x == finalI)) {
                return false;
            }
        }

        return true;
	}

	public String toString(){
        return Arrays.stream(quad)
                .map(row -> Arrays.stream(row)
                        .mapToObj(Integer::toString)
                        .collect(Collectors.joining(", ", "[", "]\n")
                )).collect(Collectors.joining(""));
	}
}
