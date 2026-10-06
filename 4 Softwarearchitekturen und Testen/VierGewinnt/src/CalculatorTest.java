import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class CalculatorTest {
    @Test
    void testAdd() {
        assertEquals(5, Calculator.add(2, 3));
        assertEquals(0, Calculator.add(-1, 1));
        assertEquals(-5, Calculator.add(-2, -3));
        assertEquals(0, Calculator.add(0, 0));
    }

    @Test
    void testSubtract() {
        assertEquals(1, Calculator.subtract(3, 2));
        assertEquals(-2, Calculator.subtract(-1, 1));
        assertEquals(1, Calculator.subtract(-2, -3));
        assertEquals(0, Calculator.subtract(0, 0));
    }

    @Test
    void testMultiply() {
        assertEquals(6, Calculator.multiply(2, 3));
        assertEquals(-1, Calculator.multiply(-1, 1));
        assertEquals(6, Calculator.multiply(-2, -3));
        assertEquals(0, Calculator.multiply(0, 5));
    }

    @Test
    void testDivide() {
        assertEquals(2, Calculator.divide(6, 3));
        assertEquals(-1, Calculator.divide(-1, 1));
        assertEquals(2, Calculator.divide(-6, -3));
        assertEquals(0, Calculator.divide(0, 5));
    }
}
