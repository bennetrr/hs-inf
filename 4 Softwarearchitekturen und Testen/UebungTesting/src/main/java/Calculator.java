/**
 * Klasse stellt einen rudiment�ren Taschenrechner f�r *, /, - und + zur
 * Verf�gung, der sich maximal 2 Operanden merkt. Der Taschenrechner unterst�tzt
 * die infix Notation von arithmetischen Berechnungen z.B:
 * 
 * t.setOperand(4); 			// 4 
 * t.setOpcode(OpCode.MULT); 	// 4 * 
 * t.setOperand(5); 			// 4 * 5 
 * t.calculate(); 				// = 20
 * 
 * @author Volkhard Pfeiffer
 * 
 */
public class Calculator {

	/**
	 * Konstanten f�r die verschiedenen arithmetischen Operationen
	 *
	 */
	public enum OpCode {
		PLUS, MINUS, DIV, MULT, NO_OPERATOR
	}

	private double result; 		// 2. operand
	private double operand; 	// 1. operand
	private int opnb; 			// anzahl der g�ltigen Operanden
	private OpCode opcode; 		// aktuell eingestellte Operation

	/**
	 * Konstruktor: Defaultm�ssig f�hrt der Taschenrechner die Operation + durch
	 * 
	 */
	public Calculator() {
		operand = 0;
		opnb = 1;
		opcode = OpCode.PLUS;
	}

	/**
	 * F�hrt eine Berechnung durch sofern 2 Operanden gesetzt sind. Anschlie�end
	 * wird der opcode als aktueller Operationscode eingestellt
	 * 
	 * @param Operationscode
	 */
	public void setOpcode(OpCode o) {
		calculate();
		opcode = o;
	}

	/**
	 * Setzt einen Operanden des Taschenrechners
	 * 
	 * @param operand
	 */
	public void setOperand(double operand) {

		if (opnb == 1) {
			if (opcode == OpCode.NO_OPERATOR)
				result = operand;
			opnb++;
		}
		this.operand = operand;

	}

	/**
	 * Liefert aktuelles Zwischenergebnis des Taschenrechners zur�ck
	 * 
	 * @return aktuelles Zwischenergebnis
	 */
	public double getResult() {
		return result;
	}

	/**
	 * Liefert aktuellen operand des Taschenrechners zur�ck
	 * 
	 * @return aktueller Operand
	 */
	public double getOperand() {
		return operand;
	}

	/**
	 * F�hrt die aktuell eingestellte Operation mit dem aktuell eingestellten
	 * Zwischenergebnis sowie des aktuell eingestellten Operanden durch.
	 * Anschlie�end wird der opcode auf NO_OPERATOR gestellt. Falls zu wenig
	 * Operanden eingestellt sind bzw. kein g�ltiger Operator, wird keine Berechnung durchgef�hrt.
	 * 
	 * * @return aktuelles Zwischenergebnis nach Durchf�hrung der Berechnung
	 * 
	 */
	public double calculate() {

		if (opnb == 2) {
			switch (opcode) {

			case PLUS:
				result += operand;
				break;
			case MINUS:
				result -= operand;
				break;
			case DIV:
				if (operand != 0)
					result /= operand;
				break;
			case MULT:
				result *= operand;
				break;

			}

			opcode = OpCode.NO_OPERATOR;
			operand = 0;
			opnb--;
		}
		return result;

	}

	/**
	 * Setzt den Operanden und das Zwischenergebnis auf 0 sowie die eingestellte
	 * Opcode zur�ck auf NO_OPERATOR
	 * 
	 */
	public void reset() {
		opcode = OpCode.NO_OPERATOR;
		operand = result = 0;
	}

	/**
	 * toString
	 * 
	 * * @return Taschenrechner Instanzvariablen als String
	 */
	public String toString() {
		String opc = "";
		switch (opcode) {

		case PLUS:
			opc = "+";
			break;
		case MINUS:
			opc = "-";
			break;
		case DIV:
			opc = "/";
			break;
		case MULT:
			opc = "*";
			break;
		case NO_OPERATOR:
			opc = "UNDEF";
			break;

		}

		return "" + opnb + ": " + operand + " " + opc + " " + result;
	}

}
