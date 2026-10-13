/* 0.3.6 Datenstrukturen und Alignment (Vorlesung 2.6 und 2.7) */
#include <stddef.h>
#include <string.h>
#include "aufgaben.h"

/* ---------- a) Felder ---------- */
int primes[10] = {2, 3, 5, 7, 11};
int even[]     = {2, 4, 6, 8, 10, 12};

/* ---------- c) Unions ---------- */
union dontknow {
    char guevara[4];
    int  eastwood;
};
union dontknow whatever = { "foo" };

/* ---------- d) Alignment ---------- */
struct foo {
    uint8_t  a;
    uint16_t b;
    uint32_t c;
};

struct foo_packed {
    uint8_t  a;
    uint16_t b;
    uint32_t c;
} __attribute__((packed));

struct bar {                /* ungeschickte Reihenfolge */
    uint8_t  a;
    uint32_t c;
    uint8_t  d;
    uint16_t b;
};

struct foo        g_foo        = { 0x11, 0x2222, 0x33333333 };
struct foo_packed g_foo_packed = { 0x11, 0x2222, 0x33333333 };

void Datenstrukturen(void)
{
    /* a) Felder */
    uint32_t anzahl_even = sizeof(even) / sizeof(even[0]);
    char text1[] = { 'f', 'o', 'o', 0 };
    char text2[] = { 102, 111, 111, 0 };
    char text3[] = "foo";
    int  gleich  = (strcmp(text1, text3) == 0) && (strcmp(text2, text3) == 0);

    char *s1   = "abcdefg";     /* Zeiger auf String-Literal */
    char  s2[] = "abcdefg";     /* Feld, mit Literal initialisiert */
    uint32_t groesse_s1 = sizeof(s1);
    uint32_t groesse_s2 = sizeof(s2);
    s2[0] = 'X';

    /* b) Strukturen und verkettete Liste (Folie 2-45) */
    struct listelement {
        char guevara;
        struct listelement *next;
    } la, lb, lc;
    la.guevara = 'A'; lb.guevara = 'B'; lc.guevara = 'C';
    la.next = &lb;
    lb.next = &lc;
    lc.next = NULL;
    char zeichen = la.next->next->guevara;

    /* c) Unions */
    int hexwert = whatever.eastwood;
    whatever.eastwood = 7496034;
    char erstes = whatever.guevara[0];

    /* d) Alignment */
    uint32_t sz_foo    = sizeof(struct foo);
    uint32_t sz_packed = sizeof(struct foo_packed);
    uint32_t sz_bar    = sizeof(struct bar);
    uint32_t off_b     = offsetof(struct foo, b);
    uint32_t off_c     = offsetof(struct foo, c);
    uint32_t off_bar_c = offsetof(struct bar, c);
    uint8_t *bytes_foo    = (uint8_t *)&g_foo;          /* Memory-Fenster! */
    uint8_t *bytes_packed = (uint8_t *)&g_foo_packed;

    (void)anzahl_even; (void)gleich; (void)groesse_s1; (void)groesse_s2;
    (void)s1; (void)zeichen; (void)hexwert; (void)erstes; (void)sz_foo;
    (void)sz_packed; (void)sz_bar; (void)off_b; (void)off_c; (void)off_bar_c;
    (void)bytes_foo; (void)bytes_packed;
}
