/* Generated by Nim Compiler v0.18.0 */
/*   (c) 2018 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Linux, amd64, gcc */
/* Command for C compiler:
   gcc -c  -w -O3 -fno-strict-aliasing  -I/home/erik/.choosenim/toolchains/nim-0.18.0/lib -o /home/erik/Code/TFG/void/NimVoid/src/nimcache/values.o /home/erik/Code/TFG/void/NimVoid/src/nimcache/values.c */
#define NIM_NEW_MANGLING_RULES
#define NIM_INTBITS 64

#include "nimbase.h"
#include <string.h>
#undef LANGUAGE_C
#undef MIPSEB
#undef MIPSEL
#undef PPC
#undef R3000
#undef R4000
#undef i386
#undef linux
#undef mips
#undef near
#undef powerpc
#undef unix
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw;
typedef struct tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA;
typedef struct RootObj RootObj;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA;
typedef struct tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ;
typedef struct tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ;
typedef struct tySequence_49cSLhOXtIXPXzKKaGFU0eQ tySequence_49cSLhOXtIXPXzKKaGFU0eQ;
typedef struct tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA;
typedef struct tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg;
typedef struct tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg;
typedef struct tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw;
typedef struct tySequence_JAV0yhDlrNFYdAVDw2r39bQ tySequence_JAV0yhDlrNFYdAVDw2r39bQ;
typedef struct tyTuple_zXBGqNygOt4DlBCAX3NcVQ tyTuple_zXBGqNygOt4DlBCAX3NcVQ;
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef NU8 tyEnum_TNimKind_jIBKr1ejBgsfM33Kxw4j7A;
typedef NU8 tySet_tyEnum_TNimTypeFlag_v8QUszD1sWlSIWZz7mC4bQ;
typedef N_NIMCALL_PTR(void, tyProc_ojoeKfW4VYIm36I9cpDTQIg) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, tyProc_WSm2xU5ARYv9aAR4l0z9c9auQ) (void* p);
struct TNimType {
NI size;
tyEnum_TNimKind_jIBKr1ejBgsfM33Kxw4j7A kind;
tySet_tyEnum_TNimTypeFlag_v8QUszD1sWlSIWZz7mC4bQ flags;
TNimType* base;
TNimNode* node;
void* finalizer;
tyProc_ojoeKfW4VYIm36I9cpDTQIg marker;
tyProc_WSm2xU5ARYv9aAR4l0z9c9auQ deepcopy;
};
struct RootObj {
TNimType* m_type;
};
struct tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw {
  RootObj Sup;
};
struct tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
NF value;
};
struct tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
NIM_BOOL value;
};
struct tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
NimStringDesc* value;
};
struct tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
tySequence_49cSLhOXtIXPXzKKaGFU0eQ* values;
};
struct tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
NI arguments;
tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg* frame;
NimStringDesc* label;
};
typedef NU8 tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ;
struct TNimNode {
tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
struct tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg {
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw Sup;
};
struct tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw {
tySequence_JAV0yhDlrNFYdAVDw2r39bQ* data;
NI counter;
};
struct tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg {
tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw Field0;
NI Field1;
};
struct tyTuple_zXBGqNygOt4DlBCAX3NcVQ {
NI Field0;
NimStringDesc* Field1;
tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* Field2;
};
struct tySequence_49cSLhOXtIXPXzKKaGFU0eQ {
  TGenericSeq Sup;
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* data[SEQ_DECL_SIZE];
};
struct tySequence_JAV0yhDlrNFYdAVDw2r39bQ {
  TGenericSeq Sup;
  tyTuple_zXBGqNygOt4DlBCAX3NcVQ data[SEQ_DECL_SIZE];
};
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__oRBqriidBajcKLSax6U9afQ)(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* value);
N_NIMCALL(NimStringDesc*, copyString)(NimStringDesc* src);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__CezRLUdBBfznKO1nJ0B3RA)(tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA* value);
N_NIMCALL(NimStringDesc*, nimFloatToStr)(NF f);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__Izy00dpajhJFqDvnlNZGuA)(tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA* value);
N_NIMCALL(NimStringDesc*, nimBoolToStr)(NIM_BOOL x);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__1FktXOz2tb9cCnHWR8bgIig)(tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ* value);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__0zRS8qc9bCPskg7uvHtStOQ)(tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ* value);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__7fo3EMB4ZHVOeNHdcmvmHw)(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* value);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
static N_INLINE(void, copyMem_E1xtACub5WcDa3vbrIXbwgsystem)(void* dest, void* source, NI size);
N_NIMCALL(NimStringDesc*, resizeString)(NimStringDesc* dest, NI addlen);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__hJmBJ6RJqYU9cCQhj4RyKhQ)(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA* value);
N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__m4ni49cq8KvqXYMtjYSbRGw)(tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg* value);
static N_NIMCALL(void, Marker_tyRef_gOxHjz9bS5yarbZPfCpiI9ag)(void* p, NI op);
static N_NIMCALL(void, Marker_tyRef_f5gWzHwMtmnTXyOKmj74kA)(void* p, NI op);
N_NIMCALL(void, nimGCvisit)(void* d, NI op);
static N_NIMCALL(void, Marker_tyRef_eTxP9aHZt79bG9aSLwJsrW9bYA)(void* p, NI op);
static N_NIMCALL(void, Marker_tyRef_9a9cRvMBGWDRFk9av9bTYiXvsg)(void* p, NI op);
static N_NIMCALL(void, Marker_tyRef_y9c6dv0kMrsaxQCTP1qYOAA)(void* p, NI op);
static N_NIMCALL(void, Marker_tyRef_wxtX2Dn9bLzkwATjviHoHPw)(void* p, NI op);
static N_NIMCALL(void, Marker_tyRef_mW8phZov9cHZwUtCe8U2gZw)(void* p, NI op);
extern TNimType NTI_13RNkKqUOX1TtorOUlKtqA_;
TNimType NTI_73JSczcdor7tTS06v9cHOZw_;
TNimType NTI_560SkOiRWWBbF6rm9aw64dA_;
extern TNimType NTI_w9bl9a1ul9ctRJWiMl9cNnIMvg_;
TNimType NTI_gOxHjz9bS5yarbZPfCpiI9ag_;
TNimType NTI_ygkSdrtwKhJuVTe5ua9b39aA_;
extern TNimType NTI_VaVACK0bpYmqIQ0mKcHfQQ_;
TNimType NTI_f5gWzHwMtmnTXyOKmj74kA_;
TNimType NTI_PO9bUMXtlWXaezrslbDbWhQ_;
extern TNimType NTI_77mFvmsOLKik79ci2hXkHEg_;
TNimType NTI_eTxP9aHZt79bG9aSLwJsrW9bYA_;
TNimType NTI_FIkPLrBpEJy6rtwh9bFNTRA_;
extern TNimType NTI_rR5Bzr1D5krxoo1NcNyeMA_;
TNimType NTI_9a9cRvMBGWDRFk9av9bTYiXvsg_;
extern TNimType NTI_ZJnTpp110EyOkSiqN7Yliw_;
TNimType NTI_y9c6dv0kMrsaxQCTP1qYOAA_;
TNimType NTI_tKCpk3v6uzTPdzngd4khKg_;
TNimType NTI_wxtX2Dn9bLzkwATjviHoHPw_;
TNimType NTI_noD08ztngGqjHZ7t6Rl9aiQ_;
extern TNimType NTI_49cSLhOXtIXPXzKKaGFU0eQ_;
TNimType NTI_mW8phZov9cHZwUtCe8U2gZw_;
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_2, "Unknown", 7);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_3, "[", 1);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_4, ", ", 2);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_5, "]", 1);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_6, "<function ", 10);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_7, ">", 1);
STRING_LITERAL(TM_9bdoCSGEt0EMj9bAZ9amxNihA_8, "none", 4);

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__oRBqriidBajcKLSax6U9afQ)(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = copyString(((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_2));
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__CezRLUdBBfznKO1nJ0B3RA)(tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = nimFloatToStr((*value).value);
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__Izy00dpajhJFqDvnlNZGuA)(tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = nimBoolToStr((*value).value);
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__1FktXOz2tb9cCnHWR8bgIig)(tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = copyString((*value).value);
	return result;
}

static N_INLINE(void, copyMem_E1xtACub5WcDa3vbrIXbwgsystem)(void* dest, void* source, NI size) {
	void* T1_;
	T1_ = (void*)0;
	T1_ = memcpy(dest, source, ((size_t) (size)));
}

static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src) {
	copyMem_E1xtACub5WcDa3vbrIXbwgsystem(((void*) ((&(*dest).data[((*dest).Sup.len)- 0]))), ((void*) ((*src).data)), ((NI) ((NI)((*src).Sup.len + ((NI) 1)))));
	(*dest).Sup.len += (*src).Sup.len;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__0zRS8qc9bCPskg7uvHtStOQ)(tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = copyString(((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_3));
	{
		NI i;
		tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* e;
		tySequence_49cSLhOXtIXPXzKKaGFU0eQ* colontmp_;
		NI i_2;
		i = (NI)0;
		e = (tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw*)0;
		colontmp_ = (tySequence_49cSLhOXtIXPXzKKaGFU0eQ*)0;
		colontmp_ = (*value).values;
		i_2 = ((NI) 0);
		{
			while (1) {
				NI T4_;
				NimStringDesc* T5_;
				T4_ = (colontmp_ ? colontmp_->Sup.len : 0);
				if (!(i_2 < T4_)) goto LA3;
				i = i_2;
				e = colontmp_->data[i_2];
				T5_ = (NimStringDesc*)0;
				T5_ = dollar__7fo3EMB4ZHVOeNHdcmvmHw(e);
				result = resizeString(result, T5_->Sup.len + 0);
appendString(result, T5_);
				{
					NI T8_;
					T8_ = ((*value).values ? (*value).values->Sup.len : 0);
					if (!!((i == (NI)(T8_ - ((NI) 1))))) goto LA9_;
					result = resizeString(result, 2);
appendString(result, ((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_4));
				}
				LA9_: ;
				i_2 += ((NI) 1);
			} LA3: ;
		}
	}
	result = resizeString(result, 1);
appendString(result, ((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_5));
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__hJmBJ6RJqYU9cCQhj4RyKhQ)(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA* value) {
	NimStringDesc* result;
	NimStringDesc* T1_;
	result = (NimStringDesc*)0;
	T1_ = (NimStringDesc*)0;
	T1_ = rawNewString((*value).label->Sup.len + 11);
appendString(T1_, ((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_6));
appendString(T1_, (*value).label);
appendString(T1_, ((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_7));
	result = T1_;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__m4ni49cq8KvqXYMtjYSbRGw)(tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg* value) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = copyString(((NimStringDesc*) &TM_9bdoCSGEt0EMj9bAZ9amxNihA_8));
	return result;
}
static N_NIMCALL(void, Marker_tyRef_gOxHjz9bS5yarbZPfCpiI9ag)(void* p, NI op) {
	tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA* a;
	a = (tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA*)p;
}
static N_NIMCALL(void, Marker_tyRef_f5gWzHwMtmnTXyOKmj74kA)(void* p, NI op) {
	tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA* a;
	a = (tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA*)p;
}
static N_NIMCALL(void, Marker_tyRef_eTxP9aHZt79bG9aSLwJsrW9bYA)(void* p, NI op) {
	tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ* a;
	a = (tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ*)p;
	nimGCvisit((void*)(*a).value, op);
}
static N_NIMCALL(void, Marker_tyRef_9a9cRvMBGWDRFk9av9bTYiXvsg)(void* p, NI op) {
	tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* a;
	a = (tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw*)p;
}
static N_NIMCALL(void, Marker_tyRef_y9c6dv0kMrsaxQCTP1qYOAA)(void* p, NI op) {
	tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA* a;
	a = (tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA*)p;
	nimGCvisit((void*)(*a).frame, op);
	nimGCvisit((void*)(*a).label, op);
}
static N_NIMCALL(void, Marker_tyRef_wxtX2Dn9bLzkwATjviHoHPw)(void* p, NI op) {
	tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg* a;
	a = (tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg*)p;
}
static N_NIMCALL(void, Marker_tyRef_mW8phZov9cHZwUtCe8U2gZw)(void* p, NI op) {
	tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ* a;
	a = (tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ*)p;
	nimGCvisit((void*)(*a).values, op);
}
NIM_EXTERNC N_NOINLINE(void, unknown_valuesInit000)(void) {
}

NIM_EXTERNC N_NOINLINE(void, unknown_valuesDatInit000)(void) {
static TNimNode* TM_9bdoCSGEt0EMj9bAZ9amxNihA_9[3];
static TNimNode TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[10];
NTI_73JSczcdor7tTS06v9cHOZw_.size = sizeof(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw);
NTI_73JSczcdor7tTS06v9cHOZw_.kind = 17;
NTI_73JSczcdor7tTS06v9cHOZw_.base = (&NTI_13RNkKqUOX1TtorOUlKtqA_);
NTI_73JSczcdor7tTS06v9cHOZw_.flags = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[0].len = 0; TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[0].kind = 2;
NTI_73JSczcdor7tTS06v9cHOZw_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[0];
NTI_560SkOiRWWBbF6rm9aw64dA_.size = sizeof(tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA);
NTI_560SkOiRWWBbF6rm9aw64dA_.kind = 17;
NTI_560SkOiRWWBbF6rm9aw64dA_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
NTI_560SkOiRWWBbF6rm9aw64dA_.flags = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[1].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[1].offset = offsetof(tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA, value);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[1].typ = (&NTI_w9bl9a1ul9ctRJWiMl9cNnIMvg_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[1].name = "value";
NTI_560SkOiRWWBbF6rm9aw64dA_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[1];
NTI_gOxHjz9bS5yarbZPfCpiI9ag_.size = sizeof(tyObject_NumberValuecolonObjectType__560SkOiRWWBbF6rm9aw64dA*);
NTI_gOxHjz9bS5yarbZPfCpiI9ag_.kind = 22;
NTI_gOxHjz9bS5yarbZPfCpiI9ag_.base = (&NTI_560SkOiRWWBbF6rm9aw64dA_);
NTI_gOxHjz9bS5yarbZPfCpiI9ag_.marker = Marker_tyRef_gOxHjz9bS5yarbZPfCpiI9ag;
NTI_ygkSdrtwKhJuVTe5ua9b39aA_.size = sizeof(tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA);
NTI_ygkSdrtwKhJuVTe5ua9b39aA_.kind = 17;
NTI_ygkSdrtwKhJuVTe5ua9b39aA_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
NTI_ygkSdrtwKhJuVTe5ua9b39aA_.flags = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[2].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[2].offset = offsetof(tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA, value);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[2].typ = (&NTI_VaVACK0bpYmqIQ0mKcHfQQ_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[2].name = "value";
NTI_ygkSdrtwKhJuVTe5ua9b39aA_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[2];
NTI_f5gWzHwMtmnTXyOKmj74kA_.size = sizeof(tyObject_BooleanValuecolonObjectType__ygkSdrtwKhJuVTe5ua9b39aA*);
NTI_f5gWzHwMtmnTXyOKmj74kA_.kind = 22;
NTI_f5gWzHwMtmnTXyOKmj74kA_.base = (&NTI_ygkSdrtwKhJuVTe5ua9b39aA_);
NTI_f5gWzHwMtmnTXyOKmj74kA_.marker = Marker_tyRef_f5gWzHwMtmnTXyOKmj74kA;
NTI_PO9bUMXtlWXaezrslbDbWhQ_.size = sizeof(tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ);
NTI_PO9bUMXtlWXaezrslbDbWhQ_.kind = 17;
NTI_PO9bUMXtlWXaezrslbDbWhQ_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[3].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[3].offset = offsetof(tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ, value);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[3].typ = (&NTI_77mFvmsOLKik79ci2hXkHEg_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[3].name = "value";
NTI_PO9bUMXtlWXaezrslbDbWhQ_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[3];
NTI_eTxP9aHZt79bG9aSLwJsrW9bYA_.size = sizeof(tyObject_StringValuecolonObjectType__PO9bUMXtlWXaezrslbDbWhQ*);
NTI_eTxP9aHZt79bG9aSLwJsrW9bYA_.kind = 22;
NTI_eTxP9aHZt79bG9aSLwJsrW9bYA_.base = (&NTI_PO9bUMXtlWXaezrslbDbWhQ_);
NTI_eTxP9aHZt79bG9aSLwJsrW9bYA_.marker = Marker_tyRef_eTxP9aHZt79bG9aSLwJsrW9bYA;
NTI_FIkPLrBpEJy6rtwh9bFNTRA_.size = sizeof(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA);
NTI_FIkPLrBpEJy6rtwh9bFNTRA_.kind = 17;
NTI_FIkPLrBpEJy6rtwh9bFNTRA_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_9[0] = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[5];
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[5].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[5].offset = offsetof(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA, arguments);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[5].typ = (&NTI_rR5Bzr1D5krxoo1NcNyeMA_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[5].name = "arguments";
TM_9bdoCSGEt0EMj9bAZ9amxNihA_9[1] = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[6];
NTI_9a9cRvMBGWDRFk9av9bTYiXvsg_.size = sizeof(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw*);
NTI_9a9cRvMBGWDRFk9av9bTYiXvsg_.kind = 22;
NTI_9a9cRvMBGWDRFk9av9bTYiXvsg_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
NTI_9a9cRvMBGWDRFk9av9bTYiXvsg_.marker = Marker_tyRef_9a9cRvMBGWDRFk9av9bTYiXvsg;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[6].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[6].offset = offsetof(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA, frame);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[6].typ = (&NTI_ZJnTpp110EyOkSiqN7Yliw_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[6].name = "frame";
TM_9bdoCSGEt0EMj9bAZ9amxNihA_9[2] = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[7];
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[7].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[7].offset = offsetof(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA, label);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[7].typ = (&NTI_77mFvmsOLKik79ci2hXkHEg_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[7].name = "label";
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[4].len = 3; TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[4].kind = 2; TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[4].sons = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_9[0];
NTI_FIkPLrBpEJy6rtwh9bFNTRA_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[4];
NTI_y9c6dv0kMrsaxQCTP1qYOAA_.size = sizeof(tyObject_FunctionValuecolonObjectType__FIkPLrBpEJy6rtwh9bFNTRA*);
NTI_y9c6dv0kMrsaxQCTP1qYOAA_.kind = 22;
NTI_y9c6dv0kMrsaxQCTP1qYOAA_.base = (&NTI_FIkPLrBpEJy6rtwh9bFNTRA_);
NTI_y9c6dv0kMrsaxQCTP1qYOAA_.marker = Marker_tyRef_y9c6dv0kMrsaxQCTP1qYOAA;
NTI_tKCpk3v6uzTPdzngd4khKg_.size = sizeof(tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg);
NTI_tKCpk3v6uzTPdzngd4khKg_.kind = 17;
NTI_tKCpk3v6uzTPdzngd4khKg_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
NTI_tKCpk3v6uzTPdzngd4khKg_.flags = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[8].len = 0; TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[8].kind = 2;
NTI_tKCpk3v6uzTPdzngd4khKg_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[8];
NTI_wxtX2Dn9bLzkwATjviHoHPw_.size = sizeof(tyObject_NoneValuecolonObjectType__tKCpk3v6uzTPdzngd4khKg*);
NTI_wxtX2Dn9bLzkwATjviHoHPw_.kind = 22;
NTI_wxtX2Dn9bLzkwATjviHoHPw_.base = (&NTI_tKCpk3v6uzTPdzngd4khKg_);
NTI_wxtX2Dn9bLzkwATjviHoHPw_.marker = Marker_tyRef_wxtX2Dn9bLzkwATjviHoHPw;
NTI_noD08ztngGqjHZ7t6Rl9aiQ_.size = sizeof(tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ);
NTI_noD08ztngGqjHZ7t6Rl9aiQ_.kind = 17;
NTI_noD08ztngGqjHZ7t6Rl9aiQ_.base = (&NTI_73JSczcdor7tTS06v9cHOZw_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[9].kind = 1;
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[9].offset = offsetof(tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ, values);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[9].typ = (&NTI_49cSLhOXtIXPXzKKaGFU0eQ_);
TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[9].name = "values";
NTI_noD08ztngGqjHZ7t6Rl9aiQ_.node = &TM_9bdoCSGEt0EMj9bAZ9amxNihA_0[9];
NTI_mW8phZov9cHZwUtCe8U2gZw_.size = sizeof(tyObject_ListValuecolonObjectType__noD08ztngGqjHZ7t6Rl9aiQ*);
NTI_mW8phZov9cHZwUtCe8U2gZw_.kind = 22;
NTI_mW8phZov9cHZwUtCe8U2gZw_.base = (&NTI_noD08ztngGqjHZ7t6Rl9aiQ_);
NTI_mW8phZov9cHZwUtCe8U2gZw_.marker = Marker_tyRef_mW8phZov9cHZwUtCe8U2gZw;
}

