/* aufgaben.h – Schnittstellen der Aufgabenmodule (vgl. Vorlesung 2.9.2) */
#ifndef AUFGABEN_H
#define AUFGABEN_H

#include <stdint.h>

/* ------------------------------------------------------------------
 * Fehler-Schalter: Einkommentieren erzeugt absichtlich einen
 * Compilerfehler bzw. ein Fehlverhalten (siehe Anleitung).
 * ------------------------------------------------------------------ */
/* #define FEHLER_CONST          */  /* 0.3.2 b) const-Variable aendern     */
/* #define FEHLER_TYPEDEF        */  /* 0.3.2 c) typedef vs. #define        */
/* #define FEHLER_CONST_ZEIGER   */  /* 0.3.3 b) const-Zeiger               */
/* #define FEHLER_MAKRO_ELSE     */  /* 0.3.7 b) Makro im if/else           */
/* #define FEHLER_VERSION        */  /* 0.3.7 e) #error                     */
/* #define ZUSATZ_GPIO_ZUGRIFF   */  /* 0.3.3 d) Schreiben auf GPIOA->ODR   */

void Startup(void);              /* 0.3.1 Systemstart (nur Beobachtung) */
void Variablen(void);            /* 0.3.2 */
void Zeiger(void);               /* 0.3.3 */
void Operatoren(void);           /* 0.3.4 */
void Funktionen(void);           /* 0.3.5 */
void Datenstrukturen(void);      /* 0.3.6 */
void Praeprozessor(void);        /* 0.3.7 */
void Volatile(void);             /* 0.3.8 */
void komplexeVariablendeklaration(void); /* 0.3.9 */

/* Assembler-Funktionen (asm_funktionen.s) */
uint32_t asm_addiere(uint32_t a, uint32_t b);
void     delay_loops(uint32_t n);

#endif /* AUFGABEN_H */
