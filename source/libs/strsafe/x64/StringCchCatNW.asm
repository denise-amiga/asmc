; STRINGCCHCATNW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCatNW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR, cchToAppend:size_t

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLengthW(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .ifs (SUCCEEDED(eax))

        .if (cchToAppend > STRSAFE_MAX_LENGTH)

            mov eax,STRSAFE_E_INVALID_PARAMETER

        .else

            mov rax,cchDestLength
            add rax,rax
            mov rcx,pszDest
            add rcx,rax
            mov rdx,cchDest
            sub rdx,rax

            StringCopyWorkerW(rcx, rdx, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    ret

StringCchCatNW endp

    end
