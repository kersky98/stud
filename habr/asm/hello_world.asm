global _start

section .data
  string_hello: db "Hello, World!", 10
  
section .text
_start:
  mov rax, 1
  mov rdi, 1
  mov rsi, string_hello
  mov rdx, 14
  syscall
  
  mov rax, 60
  mov rdi, 0
  syscall
