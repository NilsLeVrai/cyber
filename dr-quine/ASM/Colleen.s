global main

extern printf
extern exit
; outside comment

section .text
	main:
		push rbp
		mov rbp, rsp

		; add arguments
		lea rdi, [str]
		mov rsi, 10
		mov rdx, 34
		mov rcx, 9
		lea r8, [rel]
		call printf
		xor rdi, rdi
		call exit

func:
	ret

section .rodata
	str: db 'global main%1$c%1$cextern printf%1$cextern exit%1$c; outside comment%1$c%1$csection .text%1$c%3$cmain:%1$c%3$c%3$cpush rbp%1$c%3$c%3$cmov rbp, rsp%1$c%1$c%3$c%3$c; add arguments%1$c%3$c%3$cmov rsi, 10%1$c%3$c%3$cmov rdx, 34%1$c%3$c%3$cmov rcx, 9%1$c%3$c%3$clea rdi, [str]%1$c%3$c%3$ccall printf%1$c%3$c%3$ccall exit%1$c%1$cfunc:%1$c%3$cret%1$c%1$csection .data:%1$c%3$c', 0xa, 0