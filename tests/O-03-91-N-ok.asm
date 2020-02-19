





segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 9
	fild	dword [esp]
	sub	esp, byte 4
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
	call	f
	add	esp, 8
	sub	esp, byte 8
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
	push	dword 2
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	call	f
	add	esp, 8
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
