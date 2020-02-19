








segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
segment	.rodata
align	4
_L1:
	db	"maybe", 32, "not", 32, "a", 0
segment	.text
	push	dword $_L1
	call	prints
	add	esp, 4
	call	println
	push	dword 0
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
	sub	esp, 4
	push	dword 4
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 2
	push	dword 2
	pop	eax
	add	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	call	f
	add	esp, 0
	push	eax
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	pop	eax
	or	dword [esp], eax
	pop	eax
	cmp	eax, byte 0
	je	near _L2
segment	.rodata
align	4
_L3:
	db	"gr8", 32, "day", 0
segment	.text
	push	dword $_L3
	call	prints
	add	esp, 4
	call	println
_L2:
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
