/* 0.3.5 Funktionen (Vorlesung 2.5) */
#include "aufgaben.h"

/* ---------- a) call by value / call by reference ---------- */
static void foo(int a)
{
    a++;
}

static void swap(int* a, int* b)
{
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
}

struct student
{
    int  matrikelnummer;
    int  alter;
    char name[16];
};

static void rejuvenate(struct student s)
{
    s.alter = 0;
}

static void rejuvenate_ref(struct student* s)
{
    s->alter = 0;
}

/* ---------- b) AAPCS: Parameter in R0..R3, Rueckgabe in R0 ---------- */
static int func(int a)
{
    int b;
    b = 2 * a;
    return b;
}

static int summe5(int p1, int p2, int p3, int p4, int p5)
{
    return p1 + p2 + p3 + p4 + p5; /* wo kommt p5 her? */
}

/* ---------- c) Funktionszeiger (Folie 2-28) ---------- */
static int f1(int a)
{
    return a + 1;
}
static int f2(int a)
{
    return a + 2;
}
static int f3(int a)
{
    return a + 3;
}

/* ---------- d) einfacher Scheduler mit Funktionszeigern (Folie 2-29/2-34) */
typedef struct
{
    uint16_t Interval;  // Wie oft laeuft der Task?
    uint32_t LastTick;  // Wann zuletzt gelaufen?
    void (*Func)(void); // Funktionszeiger fuer Task
} TaskType;

static uint32_t cnt_idle, cnt_10ms, cnt_50ms;
static void     Tsk(void)
{
    cnt_idle++;
}
static void Tsk_10ms(void)
{
    cnt_10ms++;
}
static void Tsk_50ms(void)
{
    cnt_50ms++;
}

static TaskType Tasks[] = {
    { 0, 0, Tsk },
    { 10, 0, Tsk_10ms },
    { 50, 0, Tsk_50ms },
};

void Funktionen(void)
{
    int a = 5;
    foo(a);

    int x = 1, y = 2;
    swap(&x, &y);

    struct student s1 = { 4711, 20, "Ada" };
    rejuvenate(s1);
    int alter1 = s1.alter;
    rejuvenate_ref(&s1);
    int alter2 = s1.alter;

    int r = func(2);
    int s = summe5(1, 2, 3, 4, 5);

    /* Assembler-Funktionen aus asm_funktionen.s */
    uint32_t sum = asm_addiere(0x10, 0x20);
    delay_loops(1000);

    int ret = 0;
    int (*fptr)(int);
    fptr = f1;
    ret  = (*fptr)(0);
    fptr = f2;
    ret  = (*fptr)(0);
    fptr = f3;
    ret  = fptr(0); /* Kurzschreibweise ohne * */

    /* Scheduler: 100 simulierte Systemticks (1 Tick = 1 ms) */
    const uint8_t NumTasks = sizeof(Tasks) / sizeof(*Tasks);
    for (uint32_t tick = 1; tick <= 100; tick++)
    {
        for (uint8_t i = 0; i < NumTasks; i++)
        {
            if (Tasks[i].Interval == 0)
            {
                (*Tasks[i].Func)();
            }
            else if ((tick - Tasks[i].LastTick) >= Tasks[i].Interval)
            {
                (*Tasks[i].Func)();
                Tasks[i].LastTick = tick;
            }
        }
    }

    (void)alter1;
    (void)alter2;
    (void)r;
    (void)s;
    (void)sum;
    (void)ret;
}
