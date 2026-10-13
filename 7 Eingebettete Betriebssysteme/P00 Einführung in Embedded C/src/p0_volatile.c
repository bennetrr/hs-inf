/* 0.3.8 volatile und Interrupts (Vorlesung 2.2.2)
 * ACHTUNG: Diese Datei wird mit Optimierung (-O2) uebersetzt,
 *          siehe Makefile!                                           */
#include "aufgaben.h"

#define SYSTICK_CTRL   (*(volatile uint32_t *)0xE000E010UL)
#define SYSTICK_LOAD   (*(volatile uint32_t *)0xE000E014UL)
#define SYSTICK_VAL    (*(volatile uint32_t *)0xE000E018UL)

uint32_t          flag_ohne_volatile;    /* wird im Interrupt gesetzt */
volatile uint32_t flag_mit_volatile;     /* wird im Interrupt gesetzt */
volatile uint32_t systick_zaehler;

uint32_t ergebnis_ohne;                  /* Rueckgabewerte merken */
uint32_t ergebnis_mit;

/* Interrupt-Service-Routine: wird jede Millisekunde aufgerufen */
void SysTick_Handler(void)
{
    systick_zaehler++;
    if (systick_zaehler >= 5)
    {
        flag_ohne_volatile = 1;
        flag_mit_volatile  = 1;
    }
}

/* Warten, bis der Interrupt das Flag setzt – mit Notausstieg */
__attribute__((noinline)) uint32_t warte_ohne_volatile(void)
{
    uint32_t n = 0;
    while (flag_ohne_volatile == 0)
    {
        if (++n >= 50000000u) return 0;    /* Timeout */
    }
    return n;
}

__attribute__((noinline)) uint32_t warte_mit_volatile(void)
{
    uint32_t n = 0;
    while (flag_mit_volatile == 0)
    {
        if (++n >= 50000000u) return 0;    /* Timeout */
    }
    return n;
}

void Volatile(void)
{
    /* SysTick: 16 MHz Takt / 16000 = 1 kHz -> Interrupt jede ms */
    SYSTICK_LOAD = 16000u - 1u;
    SYSTICK_VAL  = 0;
    SYSTICK_CTRL = 0x7;     /* Prozessortakt, Interrupt an, Zaehler an */

    ergebnis_ohne = warte_ohne_volatile();

    systick_zaehler = 0; flag_mit_volatile = 0;
    ergebnis_mit = warte_mit_volatile();

    SYSTICK_CTRL = 0;       /* SysTick wieder aus */
}
