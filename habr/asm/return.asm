global _start

section .text
_start:
  mov rax, 60
  mov rdi, 137
  syscall
