








segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	dword 0
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forTest_L1:
	push	dword 1
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setl	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near stepPositive_L1
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 29
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setge	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L1
	jmp	dword forBody_L1
stepPositive_L1:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 29
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L1
forBody_L1:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 2
	pop	ecx
	pop	eax
	cdq
	idiv	ecx
	push	edx
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	sete	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near _L1
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forTest_L2:
	push	dword 1
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setl	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near stepPositive_L2
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 14
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setge	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L2
	jmp	dword forBody_L2
stepPositive_L2:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 14
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L2
forBody_L2:
segment	.rodata
align	4
_L2:
	db	0
segment	.text
	push	dword $_L2
	call	prints
	add	esp, 4
forInc_L2:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L2
endFor_L2:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	call	printi
	add	esp, 4
_L1:
forInc_L1:
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L1
endFor_L1:
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
