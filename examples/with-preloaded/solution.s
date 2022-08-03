.globl pascal
pascal:
  addi sp, sp, -16
  sw a0, 0(sp)
  sw a1, 4(sp)
  sd ra, 8(sp)
  call factorial
  addw t0, a0, zero
  ld ra, 8(sp)
  lw a1, 4(sp)
  lw a0, 0(sp)
  addi sp, sp, 16
  addi sp, sp, -32
  sw a0, 0(sp)
  sw a1, 4(sp)
  sd ra, 8(sp)
  sw t0, 16(sp)
  addw a0, a1, zero
  call factorial
  addw t1, a0, zero
  lw t0, 16(sp)
  ld ra, 8(sp)
  lw a1, 4(sp)
  lw a0, 0(sp)
  addi sp, sp, 32
  subw a0, a0, a1
  addi sp, sp, -16
  sw t0, 0(sp)
  sw t1, 4(sp)
  sd ra, 8(sp)
  call factorial
  addw t2, a0, zero
  ld ra, 8(sp)
  lw t1, 4(sp)
  lw t0, 0(sp)
  addi sp, sp, 16
  addw a0, t0, zero
  divw a0, a0, t1
  divw a0, a0, t2
  ret
