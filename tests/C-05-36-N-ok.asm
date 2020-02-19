

segment	.bss
align	4
x:
	resb	4
segment	.bss
align	4
y:
	resb	4
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 4
	push	dword $x
	pop	ecx
	pop	eax
	mov	[ecx], eax
	push	dword 2
	push	dword $x
	pop	eax
	push	dword [eax]
	pop	eax
	add	dword [esp], eax
	push	dword $y
	pop	ecx
	pop	eax
	mov	[ecx], eax
	push	dword $y
	pop	eax
	push	dword [eax]
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
