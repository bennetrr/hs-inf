/* 0.3.7 Praeprozessor und Makros (Vorlesung 2.8) */
#include "aufgaben.h"
#include <stdio.h>

/* a) Praeprozessor als Taschenrechner */
#define SECONDS_PER_YEAR   (60UL * 60UL * 24UL * 365UL)
#define SECONDS_PER_YEAR16 ((uint16_t)(60 * 60 * 24 * 365)) /* Was passiert hier? */

/* b) problematische Makros (Folie 2-53) */
#define Calculation(A, B) A = B * B + B
#define Calc(A, B)                                                                                                     \
    {                                                                                                                  \
        A = A + 1;                                                                                                     \
        B = B + 2;                                                                                                     \
    }
#define MIN(A, B) ((A) <= (B) ? (A) : (B))

/* c) Stringification und Concatenation (Folie 2-56/2-57) */
#define WARNING(EXP) sprintf(meldung, "Warning: " #EXP)

static volatile uint32_t PORTA; /* simulierter Port */
#define Button_bit  1
#define Button_port PORTA
#define SetPin(pin, value)                                                                                             \
    {                                                                                                                  \
        if (value)                                                                                                     \
            pin##_port |= 1 << pin##_bit;                                                                              \
        else                                                                                                           \
            pin##_port &= ~(1 << pin##_bit);                                                                           \
    }

/* d) bedingte Uebersetzung */
#define PFERD 4711

/* e) #error */
#ifdef FEHLER_VERSION
#ifndef VERSION
#error "No version defined"
#endif
#endif

void Praeprozessor(void)
{
    /* a) */
    uint32_t sek_jahr   = SECONDS_PER_YEAR;
    uint16_t sek_jahr16 = SECONDS_PER_YEAR16;

    /* b) */
    unsigned long int a = 3, b = 3;
    Calculation(a, b); // a = ?
    unsigned long int r1 = a;
    Calculation(a, b + 2); // a = ?
    unsigned long int r2 = a;
    Calculation(a, ++b); // a = ?  b = ?
    unsigned long int r3 = a;

    int x = 3, y = 3, i = 1;
#ifdef FEHLER_MAKRO_ELSE
    if (i == 0)
        Calc(x, y);
    else
        Calc(y, x);
#endif

    int k = 2, m = 5;
    int kleinste = MIN(k++, m); // kleinste = ?  k = ?

    /* c) */
    char meldung[32];
    WARNING(E123);
    SetPin(Button, 1);
    uint32_t porta1 = PORTA;
    SetPin(Button, 0);
    uint32_t porta2 = PORTA;

    /* d) */
    int pferd = 0;
#ifdef PFERD
    pferd = 1;
#endif
#if PFERD == 815
    pferd = 2;
#endif

    (void)sek_jahr;
    (void)sek_jahr16;
    (void)r1;
    (void)r2;
    (void)r3;
    (void)x;
    (void)y;
    (void)i;
    (void)kleinste;
    (void)porta1;
    (void)porta2;
    (void)pferd;
}
