


















segment	.bss
align	4
f:
	resb	4
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 12
	push	dword 4
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	push	dword 0
	lea	eax, [ebp+-8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	sub	esp, eax
	push	esp
	lea	eax, [ebp+-8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
segment	.rodata
align	4
_L1:
	db	32, 0
segment	.text
	push	dword $_L1
	call	prints
	add	esp, 4
	push	dword 0
	lea	eax, [ebp+-12]
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
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
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
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L1
forBody_L1:
	push	dword 2
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forInc_L1:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L1
endFor_L1:
segment	.rodata
align	4
_L2:
	db	32, 0
segment	.text
	push	dword $_L2
	call	prints
	add	esp, 4
	push	dword 0
	lea	eax, [ebp+-12]
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
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
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
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L2
forBody_L2:
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	eax
	push	dword [eax]
	call	printi
	add	esp, 4
forInc_L2:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L2
endFor_L2:
segment	.rodata
align	4
_L3:
	db	10, 0
segment	.text
	push	dword $_L3
	call	prints
	add	esp, 4
	push	dword 0
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forTest_L3:
	push	dword 1
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setl	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near stepPositive_L3
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setge	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L3
	jmp	dword forBody_L3
stepPositive_L3:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L3
forBody_L3:
	push	dword 6
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	eax
	push	dword [eax]
	pop	ecx
	pop	eax
	cdq
	idiv	ecx
	push	eax
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forInc_L3:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L3
endFor_L3:
segment	.rodata
align	4
_L4:
	db	32, 0
segment	.text
	push	dword $_L4
	call	prints
	add	esp, 4
	push	dword 0
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
forTest_L4:
	push	dword 1
	push	dword 0
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setl	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near stepPositive_L4
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setge	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L4
	jmp	dword forBody_L4
stepPositive_L4:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	sub	dword [esp], eax
	pop	eax
	xor	ecx, ecx
	cmp	[esp], eax
	setle	cl
	mov	[esp], ecx
	pop	eax
	cmp	eax, byte 0
	je	near endFor_L4
forBody_L4:
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 4
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	eax
	push	dword [eax]
	call	printi
	add	esp, 4
forInc_L4:
	lea	eax, [ebp+-12]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	pop	eax
	add	dword [esp], eax
	lea	eax, [ebp+-12]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	jmp	dword forTest_L4
endFor_L4:
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
