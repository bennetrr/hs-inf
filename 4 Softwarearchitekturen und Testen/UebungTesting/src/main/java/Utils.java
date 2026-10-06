public class Utils {

	/**
	 * Berechnet den durchschnittlichen Betrag zweier Zahlen
	 * 
	 * @param a
	 *            1. Wert
	 * @param b
	 *            2. Wert
	 * @return durchschnittlicher Betrag von a und b
	 */
	public static double getAverageAbsoluteValue(float a, float b) {

		float sum = 0;
		if (a < 0)
			sum -= a;
		else
			sum += a;
		if (b < 0)
			sum -= b;
		else
			sum += b;

		return (sum / 2);
	}

	public static int[][] erzeugeMagicQuadrat(int n) {

		// Erzeugen einer n x n Matrix
		int[][] quad = new int[n][n];

		// Deklaration und Initialisierung der Variablen zeile, spalte, m
		int zeile = n / 2, spalte = n / 2 + 1, m = 0;

		// Ermittlung des magischen Quadrats
		do {
			m++;
			quad[zeile][spalte] = m;
			zeile--;
			spalte++;
			zeile = (zeile + n) % n;
			spalte %= n;
			if (quad[zeile][spalte] != 0) {
				zeile++;
				spalte++;
				zeile %= n;
				spalte %= n;
			}
		} while (m < n * n);

		return quad;

	}
	
	public static String toString(int[][] arr) {
			StringBuffer sb = new StringBuffer();
			sb.append("[ ");
			for (int i = 0; i < arr.length;i++) {
				sb.append("[ ");
				for (int j = 0; j < arr[i].length;j++)
				               sb.append(arr[i][j] + " ");
				sb.append(" ]");
			}
			sb.append(" ]");
			return sb.toString();
	}
}
