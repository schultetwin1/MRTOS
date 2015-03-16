.syntax unified
.code 16

.extern switch_context
.extern store_psp

.thumb_func
.global pend_sv_handler
pend_sv_handler:
  push {lr}
  /**
   Storing context
   */
  /* Load sp from status reg */
  MRS r0, PSP

  /* Make room for 8 more regs */
  SUBS r0, #32

  /* Push r4-r11 onto that stack as well */
  STMIA r0!, {r4-r7}
  MOV   r4, r8
  MOV   r5, r9
  MOV   r6, r10
  MOV   r7, r11
  STMIA r0!, {r4-r7}

  /* Store sp in memory*/
  SUBS r0, #32
  bl store_psp


  /**
   Setting next context
   */
  bl switch_context


  /**
   Loading context
   */
  /* Load r8 - r11 */
  ADDS r0, #16
  LDMIA r0!, {r4-r7}
  MOV r11, r7
  MOV r10, r6
  MOV r9, r5
  MOV r8, r4

  /* set new sp */
  MSR psp, r0

  /* load r4 - r7 */
  SUBS r0, #32
  LDMIA r0!, {r4-r7}

  pop {pc}

.thumb_func
.global start_scheduler
start_scheduler:
  bl switch_context
  ADDS r0, #32

  MSR psp, r0
  MOVS r0, #2
  MSR control, r0
  POP {r0-r5}
  MOV lr, r5
  POP {pc}
