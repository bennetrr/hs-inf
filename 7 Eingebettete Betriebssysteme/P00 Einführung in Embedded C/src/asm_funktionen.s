/* Assembler-Funktionen fuer P0 (GNU-Syntax, vgl. Vorlesung 2.5.4, Folie 2-33)
 * Parameter nach AAPCS: R0..R3, Rueckgabewert in R0                   */
  .syntax unified
  .cpu cortex-m4
  .thumb

  .section .text.asm_addiere,"ax",%progbits
  .global asm_addiere
  .type asm_addiere, %function
/* uint32_t asm_addiere(uint32_t a, uint32_t b);  ->  return a + b */
asm_addiere:
  adds  r0, r0, r1
  bx    lr
  .size asm_addiere, .-asm_addiere

  .section .text.delay_loops,"ax",%progbits
  .global delay_loops
  .type delay_loops, %function
/* void delay_loops(uint32_t n);  ->  n Schleifendurchlaeufe warten */
delay_loops:
  push  {r1}                  /* benutztes Register sichern          */
  mov   r1, r0
loop_delay:
  subs  r1, r1, #1
  bne   loop_delay
  pop   {r1}
  bx    lr
  .size delay_loops, .-delay_loops
