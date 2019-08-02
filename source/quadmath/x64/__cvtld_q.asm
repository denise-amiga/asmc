; __CVTLD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

__cvtld_q proc x:ptr, ld:ptr

    mov     rax,[rdx]
    movzx   edx,word ptr [rdx+8]
    add     edx,edx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    mov     [rcx],rax
    mov     [rcx+8],rdx
    ret

__cvtld_q endp

    end