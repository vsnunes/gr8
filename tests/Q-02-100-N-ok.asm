











segment	.text
align	4
global	main:function
main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	lea	eax, [ebp+8]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	eax
	jmp	dword endmain
endmain:
	leave
	ret
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	dword 0
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
	push	dword 3
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	sub	esp, eax
	push	esp
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
segment	.rodata
align	4
_L1_cdk_emitter_internal:
	dq	3.10000
segment	.text
	push	dword $_L1_cdk_emitter_internal
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 0
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	pop	eax
	mov	[ecx+4], eax
segment	.rodata
align	4
_L2_cdk_emitter_internal:
	dq	2.10000
segment	.text
	push	dword $_L2_cdk_emitter_internal
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 1
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	pop	eax
	mov	[ecx+4], eax
segment	.rodata
align	4
_L3_cdk_emitter_internal:
	dq	61.0000
segment	.text
	push	dword $_L3_cdk_emitter_internal
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 2
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	pop	eax
	mov	[ecx+4], eax
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	call	main
	add	esp, 4
	push	eax
	call	main
	add	esp, 4
	push	eax
	lea	eax, [ebp+-8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax]
	push	dword 0
	push	dword 8
	pop	eax
	imul	dword eax, [esp]
	mov	[esp], eax
	pop	eax
	add	dword [esp], eax
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	call	printd
	add	esp, 8
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
