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
  /* Load sp */
  MRS r0, PSP

  SUBS r0, #32

  /* Store sp */
  bl store_psp

  STMIA r0!, {r4-r7}
  MOV   r4, r8
  MOV   r5, r9
  MOV   r6, r10
  MOV   r7, r11
  STMIA r0!, {r4-r7}


  /**
   Setting next context
   */
  bl switch_context


  /**
   Loading context
   */
  ADDS r0, #16
  LDMIA r0!, {r4-r7}
  MOV r11, r7
  MOV r10, r6
  MOV r9, r5
  MOV r8, r4

  MSR psp, r0

  SUBS r0, #32
  LDMIA r0!, {r4-r7}

  pop {pc}
