





segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 5
	lea	eax, [ebp+8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	push	dword 1
	lea	eax, [ebp+8]
	push	eax
	pop	eax
	push	dword [eax]
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+12]
	push	eax
	pop	eax
	push	dword [eax]
	pop	eax
	add	dword [esp], eax
	pop	eax
	jmp	dword endf
endf:
	leave
	ret
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 4
	push	dword 3
	call	f
	add	esp, 8
	push	eax
	call	printi
	add	esp, 4
	call	println
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
