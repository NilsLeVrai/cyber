global _start

section .bss
	outfile resd 1

section .data
	str: db 'theo qwqwqw!!!!', 0xa
	len equ $ - str
	filename: db 'outfile', 0

section .text
_start:

	; open()
	mov rax, 2
	mov rdi, filename
	mov rsi, 0o1101
	mov rdx, 0o644
	syscall

	mov [outfile], rax ; get return value of last syscall

	test rax, rax
	js error

	; write()
	mov rax, 1 
	mov rdi, [outfile]
	mov rsi, str
	mov rdx, len
	syscall

	; close()
	mov rax, 3
	mov rdi, [outfile]
	syscall

	; exit()
	mov rax, 60
	mov rdi, 0
	syscall

error:
	neg rax
	mov rdi, rax
	mov rax, 60
	syscall

; binaire --> linker --> exec