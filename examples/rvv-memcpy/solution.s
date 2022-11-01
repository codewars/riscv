.globl rvv_memcpy

rvv_memcpy:
  mv          a4, a0

1:
  vsetvli     a3, a2, e8, m8, ta, ma
  vle8.v      v8, (a1)
  vse8.v      v8, (a0)
  add         a0, a0, a3
  add         a1, a1, a3
  sub         a2, a2, a3
  bnez        a2, 1b

  mv          a0, a4
  ret
