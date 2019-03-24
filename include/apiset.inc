.pragma list(push, 0)
ifndef _API_SET_H_
_API_SET_H_ equ <>

API_SET_PREFIX_NAME_A	equ <"API-">
API_SET_PREFIX_NAME_A_SIZE equ 4 - 1
API_SET_PREFIX_NAME_U	equ <L"API-">
API_SET_PREFIX_NAME_U_SIZE equ (8 - sizeof(WCHAR))
API_SET_PREFIX_NAME_LENGTH equ (4 - 1)

API_SET_EXTENSION_NAME_A equ <"EXT-">
API_SET_EXTENSION_NAME_A_SIZE equ (4 - sizeof(BYTE))
API_SET_EXTENSION_NAME_U equ <L"EXT-">
API_SET_EXTENSION_NAME_U_SIZE equ (8 - sizeof(WCHAR))
API_SET_EXTENSION_NAME_LENGTH equ (4 - 1)

API_SET_SCHEMA_NAME	equ <ApiSetSchema>
API_SET_SECTION_NAME	equ <".apiset">
API_SET_SCHEMA_SUFFIX	equ <L".sys">

API_SET_SCHEMA_VERSION_V2 equ 0x00000002
API_SET_SCHEMA_VERSION_V3 equ 0x00000003 ;; No offline support.
API_SET_SCHEMA_VERSION_V4 equ 0x00000004
API_SET_SCHEMA_VERSION	equ API_SET_SCHEMA_VERSION_V4

API_SET_HELPER_NAME	equ <ApiSetHelp>

API_SET_LOAD_SCHEMA_ORDINAL equ 1
API_SET_LOOKUP_ORDINAL	equ 2
API_SET_RELEASE_SCHEMA_ORDINAL equ 3

API_SET_STRING_X macro s
	exitm<"&s&">
	endm
API_SET_STRING macro s
	exitm<API_SET_STRING_X(s)>
	endm
API_SET_STRING_U_Y macro s
	exitm<L"&s&">
	endm
API_SET_STRING_U_X macro s
	exitm<API_SET_STRING_U_Y(s)>
	endm
API_SET_STRING_U macro s
	exitm<API_SET_STRING_U_X(API_SET_STRING(s))>
	endm

API_SET_OVERRIDE macro X
	exitm<X&Implementation&>
	endm
API_SET_LEGACY_OVERRIDE_DEF macro X
	exitm<X = API_SET_OVERRIDE(X)>
	endm
API_SET_OVERRIDE_DEF macro X
	exitm<API_SET_LEGACY_OVERRIDE_DEF(X) PRIVATE>
	endm

ifdef _API_SET_HOST

undef API_SET_LIBRARY

API_SET_LIBRARY macro X
	exitm<>
	endm

undef API_SET
undef API_SET_PRIVATE
undef API_SET_BY_ORDINAL
undef API_SET_BY_ORDINAL_PRIVATE

API_SET macro X
	exitm<X PRIVATE>
	endm
API_SET_PRIVATE macro X
	exitm<X PRIVATE>
	endm
API_SET_BY_ORDINAL macro X,O,PO
	exitm<X @&O& NONAME PRIVATE>
	endm
API_SET_BY_ORDINAL_PRIVATE macro X,O,PO
	exitm<X @&O& NONAME PRIVATE>
	endm

else

ifndef _API_SET_LEGACY_TARGET

API_SET macro X
	exitm<X>
	endm
API_SET_PRIVATE macro X
	exitm<X PRIVATE>
	endm
API_SET_BY_ORDINAL macro X,O,PO
	exitm<X @##O NONAME>
	endm
API_SET_BY_ORDINAL_PRIVATE macro X,O,PO
	exitm<X @##O NONAME PRIVATE>
	endm

else

API_SET macro X
	exitm<X = _API_SET_LEGACY_TARGET##.##X>
	endm
API_SET_PRIVATE macro X
	exitm<X = _API_SET_LEGACY_TARGET##.##X PRIVATE>
	endm
API_SET_BY_ORDINAL macro X,O,PO
	exitm<X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME>
	endm
API_SET_BY_ORDINAL_PRIVATE macro X,O,PO
	exitm<X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME PRIVATE>
	endm

endif ;; _API_SET_LEGACY_TARGET

API_SET_LIBRARY macro X
	exitm<LIBRARY X>
	endm

endif ;; _API_SET_HOST

ifdef _NTDEF_

API_SET_VALUE_ENTRY	STRUC
Flags			ULONG ?
NameOffset		ULONG ?
NameLength		ULONG ?
ValueOffset		ULONG ?
ValueLength		ULONG ?
API_SET_VALUE_ENTRY	ENDS
PAPI_SET_VALUE_ENTRY	typedef ptr API_SET_VALUE_ENTRY

API_SET_VALUE_ARRAY	STRUC
Flags			ULONG ?
Count			ULONG ?
Array			API_SET_VALUE_ENTRY ANYSIZE_ARRAY dup(<>)
API_SET_VALUE_ARRAY	ENDS
PAPI_SET_VALUE_ARRAY	typedef ptr API_SET_VALUE_ARRAY

API_SET_NAMESPACE_ENTRY	 STRUC
Flags			ULONG ?
NameOffset		ULONG ?
NameLength		ULONG ?
AliasOffset		ULONG ?
AliasLength		ULONG ?
DataOffset		ULONG ? ;; API_SET_VALUE_ARRAY
API_SET_NAMESPACE_ENTRY ENDS
PAPI_SET_NAMESPACE_ENTRY typedef ptr API_SET_NAMESPACE_ENTRY

API_SET_NAMESPACE_ARRAY STRUC
Version			ULONG ?
Size			ULONG ?
Flags			ULONG ?
Count			ULONG ?
Array			API_SET_NAMESPACE_ENTRY ANYSIZE_ARRAY dup(<>)
API_SET_NAMESPACE_ARRAY ENDS
PAPI_SET_NAMESPACE_ARRAY typedef ptr API_SET_NAMESPACE_ARRAY

PCAPI_SET_VALUE_ENTRY	typedef ptr API_SET_VALUE_ENTRY
PCAPI_SET_VALUE_ARRAY	typedef ptr API_SET_VALUE_ARRAY
PCAPI_SET_NAMESPACE_ENTRY typedef ptr API_SET_NAMESPACE_ENTRY
PCAPI_SET_NAMESPACE_ARRAY typedef ptr API_SET_NAMESPACE_ARRAY

API_SET_SCHEMA_FLAGS_SEALED equ 0x00000001
API_SET_SCHEMA_FLAGS_HOST_EXTENSION equ 0x00000002

API_SET_SCHEMA_ENTRY_FLAGS_SEALED equ 0x00000001
API_SET_SCHEMA_ENTRY_FLAGS_EXTENSION equ 0x00000002

;;
;; Support for downlevel API set schema versions.
;;

API_SET_VALUE_ENTRY_V2	STRUC
NameOffset		ULONG ?
NameLength		ULONG ?
ValueOffset		ULONG ?
ValueLength		ULONG ?
API_SET_VALUE_ENTRY_V2	ENDS
PAPI_SET_VALUE_ENTRY_V2 typedef ptr API_SET_VALUE_ENTRY_V2

API_SET_VALUE_ARRAY_V2	STRUC
Count			ULONG ?
Array			API_SET_VALUE_ENTRY_V2 ANYSIZE_ARRAY dup(<>)
API_SET_VALUE_ARRAY_V2	ENDS
PAPI_SET_VALUE_ARRAY_V2 typedef ptr API_SET_VALUE_ARRAY_V2

API_SET_NAMESPACE_ENTRY_V2 STRUC
NameOffset		ULONG ?
NameLength		ULONG ?
DataOffset		ULONG ? ;; API_SET_VALUE_ARRAY
API_SET_NAMESPACE_ENTRY_V2 ENDS
PAPI_SET_NAMESPACE_ENTRY_V2 typedef ptr API_SET_NAMESPACE_ENTRY_V2

API_SET_NAMESPACE_ARRAY_V2  STRUC
Version			ULONG ?
Count			ULONG ?
Array			API_SET_NAMESPACE_ENTRY_V2 ANYSIZE_ARRAY dup(<>)
API_SET_NAMESPACE_ARRAY_V2 ENDS
PAPI_SET_NAMESPACE_ARRAY_V2 typedef ptr API_SET_NAMESPACE_ARRAY_V2

PCAPI_SET_VALUE_ENTRY_V2 typedef ptr API_SET_VALUE_ENTRY_V2
PCAPI_SET_VALUE_ARRAY_V2 typedef ptr API_SET_VALUE_ARRAY_V2
PCAPI_SET_NAMESPACE_ENTRY_V2 typedef ptr API_SET_NAMESPACE_ENTRY
PCAPI_SET_NAMESPACE_ARRAY_V2 typedef ptr API_SET_NAMESPACE_ARRAY


CALLBACK(API_SET_LOAD_SCHEMA_RTN, :PCSTR, :ptr PCAPI_SET_NAMESPACE_ARRAY, :PVOID)
PAPI_SET_LOAD_SCHEMA_RTN typedef ptr API_SET_LOAD_SCHEMA_RTN

CALLBACK(API_SET_LOOKUP_HELPER_RTN, :PCAPI_SET_NAMESPACE_ARRAY, :PCSTR, :PCSTR, :PBOOLEAN, :PSTR, :ULONG)
PAPI_SET_LOOKUP_HELPER_RTN typedef ptr API_SET_LOOKUP_HELPER_RTN

CALLBACK(API_SET_RELEASE_SCHEMA_RTN, :PVOID)
PAPI_SET_RELEASE_SCHEMA_RTN typedef ptr API_SET_RELEASE_SCHEMA_RTN

ApiSetResolveToHost proto WINAPI

endif ;; _NTDEF_

endif ;; _API_SET_H_
.pragma list(pop)