/* 0.3.4 Operatoren (Vorlesung 2.3) */
#include "aufgaben.h"

/* simuliertes 32-Bit-Register (z.B. ein GPIO-Ausgangsregister) */
volatile uint32_t REG = 0x0000F00Fu;

void Operatoren(void)
{
    /* ---------- a) Bitmanipulationen ---------- */
    unsigned char op1, op2, mask;

    // bitweise Negation
    op1 = 0xF0;
    op2 = ~op1;

    // bitweises AND
    op1  = 0xF0;
    mask = 0x11;
    op2  = op1 & mask;

    // bitweises OR
    op1  = 0xF0;
    mask = 0x11;
    op2  = op1 | mask;

    // bitweises XOR
    op1  = 0xF0;
    mask = 0x11;
    op2  = op1 ^ mask;

    // Schiebeoperationen
    op1 = 0x81;
    op2 = op1 << 1;
    op2 = op1 >> 1;

    // Programmieraufgabe (Folie 2-22): Ersetzen Sie jeweils die 0 durch einen Ausdruck mit Schiebe- und Bitoperatoren.
    REG |= 0b1 << 5;                                  // Bit 5 setzen
    REG &= ~(0b1 << 0);                               // Bit 0 loeschen
    REG ^= 0b11 << 12;                                // Bit 12 und Bit 13 invertieren
    uint32_t bit3 = (REG & (0b1 << 3)) >> 3;          // 1, wenn Bit 3 gesetzt ist, sonst 0
    REG           = (REG & ~(0xF << 8)) | (0x5 << 8); // Bits 8..11 auf den Wert 0x5 setzen

    /* ---------- b) Integerdivision ---------- */
    float Fahrenheit = 50.0f;
    float Grad       = 0.0f;
    Grad             = 5 / 9 * (Fahrenheit - 32);

    /* ---------- c) Prioritaeten der C-Operationen ---------- */
    int result = -3 * 2 + 13 % 7;

    int a  = 0;
    int b  = 1;
    result = a < 10 || a > 20 && b == 0;

    /* ---------- d) Inkrement/Dekrement ---------- */
    int n  = -1;
    result = n++ < 0 && ++n > 0;

    /* ---------- e) Undurchsichtige Syntax ---------- */
    int c;
    a = 5;
    b = 7;
    c = a++ + b;

    (void)op2;
    (void)bit3;
    (void)Grad;
    (void)result;
    (void)c;
}
