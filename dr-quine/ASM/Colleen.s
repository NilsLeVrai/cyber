global _start

section .data
	message: db "Hello", 10

section .text
_start:
	mov rdi, 1
	mov rsi, message
	mov rax, 1
	mov rdx, 6
	syscall

	mov rax, 60
	mov rdi, 0
	syscall

