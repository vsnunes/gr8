





segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	lea	eax, [ebp+12]
	push	eax
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+8]
	push	eax
	pop	eax
	push	dword [eax]
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	fld	qword [esp]
	add	esp, byte 8
	fld	qword [esp]
	faddp	st1
	fstp	qword [esp]
	fld	qword [esp]
	add	esp, byte 8
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
	push	dword 10
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	push	dword 3
	call	f
	add	esp, 12
	sub	esp, byte 8
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
	push	dword 3
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	push	dword 2
	call	f
	add	esp, 12
	sub	esp, byte 8
	fstp	qword [esp]
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
