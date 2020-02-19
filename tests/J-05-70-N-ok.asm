




segment	.text
align	4
global	pi:function
pi:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 314
	pop	eax
	jmp	dword endpi
endpi:
	leave
	ret
segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	call	pi
	add	esp, 0
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
