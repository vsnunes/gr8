

segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 100
	push	dword 100
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
