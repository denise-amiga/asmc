include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scputfg PROC USES rsi rdi rbx rbp x, y, l, a
	mov	ebx,r9d
	and	bl,0Fh
	mov	ebp,r8d
	mov	esi,ecx
	mov	edi,edx
	.repeat
		getxya( esi, edi )
		and	al,0F0h
		or	al,bl
		scputa( esi, edi, 1, eax )
		inc	esi
		dec	ebp
	.until	ZERO?
	ret
scputfg ENDP

	END