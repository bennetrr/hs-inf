/* 0.3.9 Komplexe Variablendeklarationen (Vorlesung 2.10, Folie 2-76 bis 2-79) */
#include "aufgaben.h"

static int quadrat(int x)  { return x * x; }
static int negiere(int x)  { return -x; }
static int verdopple(int x){ return 2 * x; }

/* Zustandsautomat mit Funktionszeiger-Tabelle (Folie 2-79) */
static uint8_t output;
static void fct_state1(void) { output = 0; }
static void fct_state2(void) { output = 1; }

typedef struct {
    uint8_t newstate;
    void    (*fct_action)(void);
} tbl_entry;

static const tbl_entry table[2][2] =
    { { {1, fct_state1}, {2, fct_state2} },
      { {2, fct_state2}, {1, fct_state1} } };

static uint8_t StateMachine(uint8_t evt)
{
    static uint8_t State = 1;
    table[State-1][evt].fct_action();
    State = table[State-1][evt].newstate;
    return State;
}

void komplexeVariablendeklaration(void)
{
    int  i;                    /* a) */
    int  *pi;                  /* b) */
    int  **ppi;                /* c) */
    int  arr[10];              /* d) */
    int  *arrp[10];            /* e) */
    int  (*parr)[10];          /* f) */
    int  (*pf)(int);           /* g) */
    int  (*apf[10])(int);      /* h) */

    i    = 7;
    pi   = &i;
    ppi  = &pi;
    for (int k = 0; k < 10; k++) { arr[k] = k * k; arrp[k] = &arr[k]; }
    parr = &arr;
    int wert_f = (*parr)[3];

    pf = quadrat;
    int r1 = pf(i);
    pf = negiere;
    int r2 = pf(i);

    apf[0] = quadrat;
    apf[1] = negiere;
    apf[2] = verdopple;
    int r3 = 0;
    for (int k = 0; k < 3; k++)
    {
        r3 += apf[k](**ppi);
    }

    /* Zustandsautomat: Folge von Ereignissen */
    uint8_t events[] = { 0, 1, 1, 0, 1 };
    uint8_t zustaende[5];
    uint8_t ausgaben[5];
    for (int k = 0; k < 5; k++)
    {
        zustaende[k] = StateMachine(events[k]);
        ausgaben[k]  = output;
    }

    (void)arrp; (void)wert_f; (void)r1; (void)r2; (void)r3;
    (void)zustaende; (void)ausgaben;
}
