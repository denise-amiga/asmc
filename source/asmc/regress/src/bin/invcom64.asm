    .x64
    .model flat, fastcall
    option win64:3

D0T typedef proto :ptr
D1T typedef proto :ptr, :ptr, :ptr, :ptr, :ptr
D0  typedef ptr D0T
D1  typedef ptr D1T

xx  struc
l1  D0 ?
l2  D1 ?
xx  ends

LPXX typedef ptr xx

ClassVtbl struct
    l1  D0 ?
    l2  D1 ?
ClassVtbl ends

Class struct
    lpVtbl dq ?
Class ends
PCLASS typedef ptr Class

.data
p LPXX ?
q D1 ?
x xx <>
o PCLASS ?

.code

    q( 0, 1, 2, 3, 4 )

    x.l1( 0 )
    x.l2( 0, 1, 2, 3, 4 )

    p.l1()
    o.l1()
    p.l2( 1, 2, 3, 4 )
    o.l2( 1, 2, 3, 4 )

    [rcx].Class.l1()
    [rcx].Class.l2(1, 2, 3, 4)

foo proc

  local lp:LPXX, lo:PCLASS

    q( 0, 1, 2, 3, 4 )

    p.l1()
    o.l1()
    p.l2( 1, 2, 3, 4 )
    o.l2( 1, 2, 3, 4 )

    lp.l1()
    lo.l1()
    lp.l2( 1, 2, 3, 4 )
    lo.l2( 1, 2, 3, 4 )

    [rax].Class.l1()
    [rax].Class.l2(1, 2, 3, 4)
    ret

foo endp

    end
