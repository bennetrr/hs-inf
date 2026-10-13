/* 0.3.3 Zeiger (Vorlesung 2.2.5 und 2.6.1) */
#include "aufgaben.h"
#include "stm32g4_gpio.h"

int   intvar   = 0x7856;
char  charvar  = '4';
short shortvar = 0x1234;

void Zeiger(void)
{
    /* ---------- a) Zeiger, Adressen & Adressoperator ---------- */
    int*   pint   = &intvar;      /* zeigt auf die Variable intvar   */
    char*  pchar  = &charvar;     /* zeigt auf die Variable charvar  */
    short* pshort = &shortvar;    /* zeigt auf die Variable shortvar */

    charvar = ++(*((char*)pint + 1));

    /* Zeigerarithmetik haengt vom Datentyp ab (Folie 2-20, 2-42) */
    int*  pint_plus1  = pint + 1;
    char* pchar_plus1 = (char*)pint + 1;
    int   differenz   = (char*)pint_plus1 - pchar_plus1;

    /* ---------- b) const-Zeiger ---------- */
    int var1 = 10;
    int var2 = 20;

    const int *       pconst1 = &var1;
    int * const       pconst2 = &var1;
    const int * const pconst3 = &var1;

#ifdef FEHLER_CONST_ZEIGER
    *pconst1 = 20;  pconst1 = &var2;
    *pconst2 = 20;  pconst2 = &var2;
    *pconst3 = 20;  pconst3 = &var2;
#endif

    /* ---------- c) Felder und Zeiger (Folie 2-39 bis 2-43) ---------- */
    char text[] = "quiesel";
    char *c = text + 1;
    *c = 'w';               /* "qwiesel" */
    *(text + 4) = 'b';      /* "qwiebel" */
    *(c - 1) = 'z';         /* "zwiebel" */

    char mult[4][3] = { {0,0,0},
                        {0,1,2},
                        {0,2,4},
                        {0,3,6} };
    mult[2][1] = 5;
    *(mult[2] + 1) = 6;
    (*(mult + 2))[1] = 7;
    *(*(mult + 2) + 1) = 8;
    *(*mult + 2*3 + 1) = 9;
    *(*mult + 7) = 10;

    /* ---------- d) Zugriff auf Peripherieregister ---------- */
    uint32_t           groesse_gpio = sizeof(GPIO_TypeDef);
    GPIO_TypeDef *     portA        = GPIOA;          /* nur Adresse, kein Zugriff */
    volatile uint32_t *pODR         = &GPIOA->ODR;    /* nur Adresse, kein Zugriff */

#ifdef ZUSATZ_GPIO_ZUGRIFF
    GPIOA->ODR = 0x12345678;    /* echter Schreibzugriff auf die Adresse */
#endif

    (void)pchar; (void)pshort; (void)differenz; (void)var2;
    (void)pconst1; (void)pconst2; (void)pconst3;
    (void)groesse_gpio; (void)portA; (void)pODR;
}
