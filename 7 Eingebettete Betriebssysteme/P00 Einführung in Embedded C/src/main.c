/* EBSy – Projekt P0: Einfuehrung in die Embedded C-Programmierung
 * Zielsystem: Cortex-M4F (STM32F405) im Simulator QEMU, GNU-Toolchain
 *
 * Gehen Sie die Aufgaben im Debugger der Reihe nach durch:
 *   F11 = Step Into (in Funktion hinein), F10 = Step Over            */
#include "aufgaben.h"

int main(void)
{
    // 1. Variablen und Datentypen
    Variablen();

    // 2. Zeiger (Pointer)
    Zeiger();

    // 3. Operatoren
    Operatoren();

    // 4. Funktionen, Funktionszeiger, Assembler-Schnittstelle
    Funktionen();

    // 5. Felder, Strukturen, Unions, Alignment
    Datenstrukturen();

    // 6. Praeprozessor und Makros
    Praeprozessor();

    // 7. volatile und Interrupts (mit Optimierung -O2 uebersetzt!)
    Volatile();

    // 8. komplexe Variablendeklarationen und Funktionszeiger
    komplexeVariablendeklaration();

    /* Endlosschleife */
    while (1)
    {
    }
}
