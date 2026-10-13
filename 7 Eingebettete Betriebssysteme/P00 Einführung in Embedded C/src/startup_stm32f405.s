/* Startup-Code EBSy P0 (GNU-Assembler-Syntax, vgl. Vorlesung 2.9.1)
 * Ablauf nach Reset:
 *   1. CPU laedt SP aus 0x08000000 und PC (Reset-Vektor) aus 0x08000004
 *   2. Reset_Handler: FPU einschalten, .data kopieren, .bss nullen
 *   3. Sprung nach main()                                             */
  .syntax unified
  .cpu cortex-m4
  .fpu fpv4-sp-d16
  .thumb

  .global g_pfnVectors
  .global Reset_Handler

/* ---------------- Reset_Handler ---------------- */
  .section .text.Reset_Handler,"ax",%progbits
  .type Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack          /* Stackpointer setzen                 */

  /* FPU (Coprozessoren CP10/CP11) freischalten: SCB->CPACR |= 0xF<<20 */
  ldr   r0, =0xE000ED88
  ldr   r1, [r0]
  orr   r1, r1, #(0xF << 20)
  str   r1, [r0]
  dsb
  isb

  /* Initialwerte der Variablen (.data) aus dem Flash ins RAM kopieren */
  ldr   r0, =_sdata           /* Ziel: Anfang .data im RAM           */
  ldr   r1, =_edata           /* Ende .data im RAM                   */
  ldr   r2, =_sidata          /* Quelle: Initialwerte im Flash       */
copy_data:
  cmp   r0, r1
  bcs   zero_bss
  ldr   r3, [r2], #4
  str   r3, [r0], #4
  b     copy_data

  /* nicht initialisierte Variablen (.bss) mit 0 beschreiben */
zero_bss:
  ldr   r0, =_sbss
  ldr   r1, =_ebss
  movs  r2, #0
zero_loop:
  cmp   r0, r1
  bcs   call_main
  str   r2, [r0], #4
  b     zero_loop

call_main:
  bl    __libc_init_array     /* Konstruktoren der C-Bibliothek      */
  bl    main
endless:
  b     endless               /* main() sollte nie zurueckkehren     */
  .size Reset_Handler, .-Reset_Handler

/* ---------------- Default_Handler ---------------- */
  .section .text.Default_Handler,"ax",%progbits
  .type Default_Handler, %function
Default_Handler:
  b     Default_Handler       /* unbehandelte Ausnahme: hier stehen bleiben */
  .size Default_Handler, .-Default_Handler

/* ---------------- Vektortabelle ---------------- */
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
g_pfnVectors:
  .word _estack               /* 0x00: initialer Stackpointer        */
  .word Reset_Handler         /* 0x04: Reset-Vektor                  */
  .word NMI_Handler           /* 0x08 */
  .word HardFault_Handler     /* 0x0C */
  .word MemManage_Handler     /* 0x10 */
  .word BusFault_Handler      /* 0x14 */
  .word UsageFault_Handler    /* 0x18 */
  .word 0, 0, 0, 0            /* 0x1C-0x28: reserviert               */
  .word SVC_Handler           /* 0x2C */
  .word DebugMon_Handler      /* 0x30 */
  .word 0                     /* 0x34: reserviert                    */
  .word PendSV_Handler        /* 0x38 */
  .word SysTick_Handler       /* 0x3C */
  .size g_pfnVectors, .-g_pfnVectors

/* Alle Handler zeigen standardmaessig auf Default_Handler ("weak"),
 * eine gleichnamige C-Funktion ueberschreibt sie. */
  .weak NMI_Handler
  .thumb_set NMI_Handler, Default_Handler
  .weak HardFault_Handler
  .thumb_set HardFault_Handler, Default_Handler
  .weak MemManage_Handler
  .thumb_set MemManage_Handler, Default_Handler
  .weak BusFault_Handler
  .thumb_set BusFault_Handler, Default_Handler
  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler, Default_Handler
  .weak SVC_Handler
  .thumb_set SVC_Handler, Default_Handler
  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler, Default_Handler
  .weak PendSV_Handler
  .thumb_set PendSV_Handler, Default_Handler
  .weak SysTick_Handler
  .thumb_set SysTick_Handler, Default_Handler
