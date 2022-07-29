input_printfmt: .string "a = %d, b = %d\n"

.text
.globl multiply
multiply:
  addi sp, sp, -16
  sd ra, 8(sp)
  sw a1, 4(sp)
  sw a0, 0(sp)
  addw a2, a1, zero
  addw a1, a0, zero
  lla a0, input_printfmt
  call printf
  lw a0, 0(sp)
  lw a1, 4(sp)
  ld ra, 8(sp)
  addi sp, sp, 16
  addw a0, a0, a1
  jr ra
