/* 0.3.2 Variablen und Datentypen (Vorlesung 2.2) */
#include "aufgaben.h"
#include <stddef.h>
#include <stdio.h>

/* globale Variablen fuer das Speicherlayout (Folie 2-16/2-17) */
int32_t        g_initialisiert = 4711;   /* vorinitialisiert           */
int32_t        g_uninitialisiert;        /* nicht initialisiert        */
const int32_t  g_konstante     = 0x1234; /* globale Konstante          */
static int32_t s_modulvariable = 42;     /* nur in dieser Datei sichtbar */

static int32_t zaehler_static(void)
{
    static int32_t n = 0; /* behaelt Wert zwischen den Aufrufen */
    n++;
    return n;
}

static int32_t zaehler_auto(void)
{
    int32_t n = 0; /* wird bei jedem Aufruf neu angelegt */
    n++;
    return n;
}

void Variablen(void)
{
    /* ---------- a) Auch Literale haben einen Datentyp ---------- */
    float  f1 = 1.2345678912345; // ohne Suffix => Double
    float  f2 = 1.2345678912345f;
    double f3 = 1.2345678912345;
    double f4 = 1.2345678912345f;

    float f5 = 0.0123456785f;
    float f6 = 0.0123456786f;

    float f7 = 0.1f;
    for (int i = 0; i < 100; i++)
    {
        f7 += 0.1;
    }

    uint8_t neg_zahl = -100;

    char         String[10];
    unsigned int a = 6;
    int          b = -20;
    (a + b > 6) ? sprintf(String, "a+b > 6") : sprintf(String, "a+b <= 6");

    /* Bitbreiten der Standardtypen (Folie 2-10) */
    uint32_t groesse_char     = sizeof(char);
    uint32_t groesse_short    = sizeof(short);
    uint32_t groesse_int      = sizeof(int);
    uint32_t groesse_long     = sizeof(long);
    uint32_t groesse_longlong = sizeof(long long);
    uint32_t groesse_double   = sizeof(double);
    uint32_t groesse_zeiger   = sizeof(int*);

    uint16_t zaehler16 = 65535;
    zaehler16++; // Ueberlauf?

    /* ---------- b) Speicherklassen ---------- */
    const int32_t myConst = 123;
#ifdef FEHLER_CONST
    myConst++;
#endif
    const int32_t* ptrConst     = &myConst;
    const int32_t* ptrGlobConst = &g_konstante;

    static int32_t myStatic  = 456;
    int32_t        myAuto    = 789;
    int32_t*       ptrStatic = &myStatic;
    int32_t*       ptrAuto   = &myAuto;

    int32_t z1 = zaehler_static();
    int32_t z2 = zaehler_static();
    int32_t z3 = zaehler_static();
    int32_t z4 = zaehler_auto();
    int32_t z5 = zaehler_auto();

    /* Speicherlayout: Adressen der globalen Objekte */
    int32_t* adr_init          = &g_initialisiert;
    int32_t* adr_uninit        = &g_uninitialisiert;
    int32_t* adr_modul         = &s_modulvariable;
    void (*adr_funktion)(void) = Variablen;

    /* ---------- c) Typ-Definitionen (typedef) ---------- */
    struct s
    {
        int a;
        int b;
    }; // Dummy Struct mit zwei Werten a und b
    struct s          myStruct; // Instanziierung des Structs
    typedef struct s* tPS;      // neuer Typ: Zeiger auf einen struct

    tPS myPtrStruct = &myStruct; // Zeiger auf Dummy Struct
    myPtrStruct->a  = 1;         // Zugriff auf Struktur ueber Zeiger

#define dPS struct s*
    dPS myPtrStructDef = myPtrStruct;
    myPtrStructDef->b  = 2; // Beobachtung im Watch-Fenster !!!

    tPS p1, p2; // Deklaration von zwei Zeigern vom Typ tPS
    p1 = myPtrStruct;
    p2 = myPtrStruct;

#ifdef FEHLER_TYPEDEF
    dPS p3, p4;
    p3 = myPtrStructDef;
    p4 = myPtrStructDef;
#endif

    /* Dummy-Verwendung, damit der Compiler nicht warnt */
    (void)f1;
    (void)f2;
    (void)f3;
    (void)f4;
    (void)f5;
    (void)f6;
    (void)f7;
    (void)neg_zahl;
    (void)groesse_char;
    (void)groesse_short;
    (void)groesse_int;
    (void)groesse_long;
    (void)groesse_longlong;
    (void)groesse_double;
    (void)groesse_zeiger;
    (void)zaehler16;
    (void)ptrConst;
    (void)ptrGlobConst;
    (void)ptrStatic;
    (void)ptrAuto;
    (void)z1;
    (void)z2;
    (void)z3;
    (void)z4;
    (void)z5;
    (void)adr_init;
    (void)adr_uninit;
    (void)adr_modul;
    (void)adr_funktion;
    (void)p1;
    (void)p2;
}
