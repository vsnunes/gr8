






segment	.data
align	4
x:
	dd	10
segment	.data
align	4
y:
	dd	3
segment	.data
align	4
z:
	dd	30
segment	.text
align	4
global	f:function
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 7
	push	dword $z
	pop	ecx
	pop	eax
	mov	[ecx], eax
	push	dword $z
	pop	eax
	push	dword [eax]
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
	push	dword $x
	pop	eax
	push	dword [eax]
	push	dword $y
	pop	eax
	push	dword [eax]
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	jne	near NOTtrue_L1
	push	dword 0
	jmp	dword NOTend_L1
NOTtrue_L1:
	push	dword 1
NOTend_L1:
	push	dword 1
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	jne	near ORtrue_L2
	add	esp, 4
	call	f
	add	esp, 0
	push	eax
	push	dword 1
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	jmp	dword ORend_L2
ORtrue_L2:
	push	dword 1
ORend_L2:
	add	esp, 4
	push	dword $z
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
