ifndef _GDIPLUSMEM_H
_GDIPLUSMEM_H equ <>

ifndef WINGDIPAPI
WINGDIPAPI equ <>

.pragma comment(lib, gdiplus)
endif

;void*
GdipAlloc proto WINAPI size: size_t
;void
GdipFree proto WINAPI : ptr

endif

