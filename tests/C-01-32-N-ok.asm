

segment	.bss
align	4
x:
	resb	4
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword $x
	pop	eax
	push	dword [eax]
	push	dword $x
	pop	eax
	push	dword [eax]
	pop	eax
	sub	dword [esp], eax
	call	printi
	add	esp, 4
	push	dword 0
	pop	eax
	jmp	dword endcovfefe
extern	readi
extern	printi
extern	printd
extern	prints
extern	println
endcovfefe:
	leave
	ret
