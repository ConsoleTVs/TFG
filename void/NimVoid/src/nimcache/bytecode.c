/* Generated by Nim Compiler v0.18.0 */
/*   (c) 2018 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Linux, amd64, gcc */
/* Command for C compiler:
   gcc -c  -w -O3 -fno-strict-aliasing  -I/home/erik/.choosenim/toolchains/nim-0.18.0/lib -o /home/erik/Code/TFG/void/NimVoid/src/nimcache/bytecode.o /home/erik/Code/TFG/void/NimVoid/src/nimcache/bytecode.c */
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
typedef struct tyTuple_8eO9cDFHNTedYaXAdSjBGjA tyTuple_8eO9cDFHNTedYaXAdSjBGjA;
typedef struct tyTuple_M3y5mHl2OtcVFI81N2j0DQ tyTuple_M3y5mHl2OtcVFI81N2j0DQ;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g;
typedef struct tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w;
typedef struct tyObject_GcHeap_1TRH1TZMaVZTnLNcIHuNFQ tyObject_GcHeap_1TRH1TZMaVZTnLNcIHuNFQ;
typedef struct tyObject_GcStack_7fytPA5bBsob6See21YMRA tyObject_GcStack_7fytPA5bBsob6See21YMRA;
typedef struct tyObject_MemRegion_x81NhDv59b8ercDZ9bi85jyg tyObject_MemRegion_x81NhDv59b8ercDZ9bi85jyg;
typedef struct tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ;
typedef struct tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg;
typedef struct tyObject_LLChunk_XsENErzHIZV9bhvyJx56wGw tyObject_LLChunk_XsENErzHIZV9bhvyJx56wGw;
typedef struct tyObject_IntSet_EZObFrE3NC9bIb3YMkY9crZA tyObject_IntSet_EZObFrE3NC9bIb3YMkY9crZA;
typedef struct tyObject_Trunk_W0r8S0Y3UGke6T9bIUWnnuw tyObject_Trunk_W0r8S0Y3UGke6T9bIUWnnuw;
typedef struct tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw;
typedef struct tyObject_HeapLinks_PDV1HBZ8CQSQJC9aOBFNRSg tyObject_HeapLinks_PDV1HBZ8CQSQJC9aOBFNRSg;
typedef struct tyTuple_ujsjpB2O9cjj3uDHsXbnSzg tyTuple_ujsjpB2O9cjj3uDHsXbnSzg;
typedef struct tyObject_GcStat_0RwLoVBHZPfUAcLczmfQAg tyObject_GcStat_0RwLoVBHZPfUAcLczmfQAg;
typedef struct tyObject_CellSet_jG87P0AI9aZtss9ccTYBIISQ tyObject_CellSet_jG87P0AI9aZtss9ccTYBIISQ;
typedef struct tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tyTuple_p7Uw0BAWm1JV3F8w0mhMOA tyTuple_p7Uw0BAWm1JV3F8w0mhMOA;
typedef struct tySequence_g8wWagWtbBE4jkij9axgDjA tySequence_g8wWagWtbBE4jkij9axgDjA;
typedef struct tySequence_49cSLhOXtIXPXzKKaGFU0eQ tySequence_49cSLhOXtIXPXzKKaGFU0eQ;
typedef struct tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw;
typedef struct tySequence_rl1wTgiGRBZamH1pllm1bA tySequence_rl1wTgiGRBZamH1pllm1bA;
typedef struct tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg;
typedef struct tyObject_Table_zjMaDBasw1LnKbj11akpfw tyObject_Table_zjMaDBasw1LnKbj11akpfw;
typedef struct tySequence_pUxI6Ljo6IKKHXKOZkQ7Og tySequence_pUxI6Ljo6IKKHXKOZkQ7Og;
typedef struct tyObject_BaseChunk_Sdq7WpT6qAH858F5ZEdG3w tyObject_BaseChunk_Sdq7WpT6qAH858F5ZEdG3w;
typedef struct tyObject_FreeCell_u6M5LHprqzkn9axr04yg9bGQ tyObject_FreeCell_u6M5LHprqzkn9axr04yg9bGQ;
typedef struct RootObj RootObj;
typedef struct tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw;
typedef struct tySequence_JAV0yhDlrNFYdAVDw2r39bQ tySequence_JAV0yhDlrNFYdAVDw2r39bQ;
typedef struct tyTuple_sr3s7uVHpu9cEbbDnCSg8yQ tyTuple_sr3s7uVHpu9cEbbDnCSg8yQ;
typedef struct tyTuple_zXBGqNygOt4DlBCAX3NcVQ tyTuple_zXBGqNygOt4DlBCAX3NcVQ;
struct tyTuple_8eO9cDFHNTedYaXAdSjBGjA {
tyTuple_M3y5mHl2OtcVFI81N2j0DQ* Field0;
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
typedef NU8 tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ;
struct TNimNode {
tyEnum_TNimNodeKind_unfNsxrcATrufDZmpBq4HQ kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
struct tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g {
NI refcount;
TNimType* typ;
};
struct tyObject_GcStack_7fytPA5bBsob6See21YMRA {
void* bottom;
};
struct tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w {
NI len;
NI cap;
tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g** d;
};
typedef tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ* tyArray_SiRwrEKZdLgxqz9a9aoVBglg[512];
typedef NU32 tyArray_BHbOSqU1t9b3Gt7K2c6fQig[24];
typedef tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg* tyArray_N1u1nqOgmuJN9cSZrnMHgOQ[32];
typedef tyArray_N1u1nqOgmuJN9cSZrnMHgOQ tyArray_B6durA4ZCi1xjJvRtyYxMg[24];
typedef tyObject_Trunk_W0r8S0Y3UGke6T9bIUWnnuw* tyArray_lh2A89ahMmYg9bCmpVaplLbA[256];
struct tyObject_IntSet_EZObFrE3NC9bIb3YMkY9crZA {
tyArray_lh2A89ahMmYg9bCmpVaplLbA data;
};
typedef tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw* tyArray_0aOLqZchNi8nWtMTi8ND8w[2];
struct tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw {
tyArray_0aOLqZchNi8nWtMTi8ND8w link;
NI key;
NI upperBound;
NI level;
};
struct tyTuple_ujsjpB2O9cjj3uDHsXbnSzg {
tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg* Field0;
NI Field1;
};
typedef tyTuple_ujsjpB2O9cjj3uDHsXbnSzg tyArray_LzOv2eCDGiceMKQstCLmhw[30];
struct tyObject_HeapLinks_PDV1HBZ8CQSQJC9aOBFNRSg {
NI len;
tyArray_LzOv2eCDGiceMKQstCLmhw chunks;
tyObject_HeapLinks_PDV1HBZ8CQSQJC9aOBFNRSg* next;
};
struct tyObject_MemRegion_x81NhDv59b8ercDZ9bi85jyg {
NI minLargeObj;
NI maxLargeObj;
tyArray_SiRwrEKZdLgxqz9a9aoVBglg freeSmallChunks;
NU32 flBitmap;
tyArray_BHbOSqU1t9b3Gt7K2c6fQig slBitmap;
tyArray_B6durA4ZCi1xjJvRtyYxMg matrix;
tyObject_LLChunk_XsENErzHIZV9bhvyJx56wGw* llmem;
NI currMem;
NI maxMem;
NI freeMem;
NI occ;
NI lastSize;
tyObject_IntSet_EZObFrE3NC9bIb3YMkY9crZA chunkStarts;
tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw* root;
tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw* deleted;
tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw* last;
tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw* freeAvlNodes;
NIM_BOOL locked;
NIM_BOOL blockChunkSizeIncrease;
NI nextChunkSize;
tyObject_AvlNode_IaqjtwKhxLEpvDS9bct9blEw bottomData;
tyObject_HeapLinks_PDV1HBZ8CQSQJC9aOBFNRSg heapLinks;
};
struct tyObject_GcStat_0RwLoVBHZPfUAcLczmfQAg {
NI stackScans;
NI cycleCollections;
NI maxThreshold;
NI maxStackSize;
NI maxStackCells;
NI cycleTableSize;
NI64 maxPause;
};
struct tyObject_CellSet_jG87P0AI9aZtss9ccTYBIISQ {
NI counter;
NI max;
tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg* head;
tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg** data;
};
struct tyObject_GcHeap_1TRH1TZMaVZTnLNcIHuNFQ {
tyObject_GcStack_7fytPA5bBsob6See21YMRA stack;
NI cycleThreshold;
tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w zct;
tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w decStack;
tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w tempStack;
NI recGcLock;
tyObject_MemRegion_x81NhDv59b8ercDZ9bi85jyg region;
tyObject_GcStat_0RwLoVBHZPfUAcLczmfQAg stat;
tyObject_CellSet_jG87P0AI9aZtss9ccTYBIISQ marked;
tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w additionalRoots;
NI gcThreadId;
};
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
struct tyObject_Table_zjMaDBasw1LnKbj11akpfw {
tySequence_pUxI6Ljo6IKKHXKOZkQ7Og* data;
NI counter;
};
struct tyTuple_M3y5mHl2OtcVFI81N2j0DQ {
tySequence_g8wWagWtbBE4jkij9axgDjA* Field0;
tySequence_49cSLhOXtIXPXzKKaGFU0eQ* Field1;
tySequence_rl1wTgiGRBZamH1pllm1bA* Field2;
tyObject_Table_zjMaDBasw1LnKbj11akpfw Field3;
NI Field4;
NI Field5;
};
typedef NU8 tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw;
struct tyTuple_p7Uw0BAWm1JV3F8w0mhMOA {
tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw Field0;
tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* Field1;
};
struct tyObject_BaseChunk_Sdq7WpT6qAH858F5ZEdG3w {
NI prevSize;
NI size;
};
struct tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ {
  tyObject_BaseChunk_Sdq7WpT6qAH858F5ZEdG3w Sup;
tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ* next;
tyObject_SmallChunk_tXn60W2f8h3jgAYdEmy5NQ* prev;
tyObject_FreeCell_u6M5LHprqzkn9axr04yg9bGQ* freeList;
NI free;
NI acc;
NF data;
};
struct tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg {
  tyObject_BaseChunk_Sdq7WpT6qAH858F5ZEdG3w Sup;
tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg* next;
tyObject_BigChunk_Rv9c70Uhp2TytkX7eH78qEg* prev;
NF data;
};
struct tyObject_LLChunk_XsENErzHIZV9bhvyJx56wGw {
NI size;
NI acc;
tyObject_LLChunk_XsENErzHIZV9bhvyJx56wGw* next;
};
typedef NI tyArray_9a8QARi5WsUggNU9bom7kzTQ[8];
struct tyObject_Trunk_W0r8S0Y3UGke6T9bIUWnnuw {
tyObject_Trunk_W0r8S0Y3UGke6T9bIUWnnuw* next;
NI key;
tyArray_9a8QARi5WsUggNU9bom7kzTQ bits;
};
struct tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg {
tyObject_PageDesc_fublkgIY4LG3mT51LU2WHg* next;
NI key;
tyArray_9a8QARi5WsUggNU9bom7kzTQ bits;
};
struct RootObj {
TNimType* m_type;
};
struct tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw {
  RootObj Sup;
};
struct tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw {
tySequence_JAV0yhDlrNFYdAVDw2r39bQ* data;
NI counter;
};
struct tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg {
tyObject_Table_upT1OmA0PO9bbHjDDPVn2Uw Field0;
NI Field1;
};
struct tyTuple_sr3s7uVHpu9cEbbDnCSg8yQ {
NI Field0;
NimStringDesc* Field1;
NI Field2;
};
struct tyObject_FreeCell_u6M5LHprqzkn9axr04yg9bGQ {
tyObject_FreeCell_u6M5LHprqzkn9axr04yg9bGQ* next;
NI zeroField;
};
struct tyTuple_zXBGqNygOt4DlBCAX3NcVQ {
NI Field0;
NimStringDesc* Field1;
tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* Field2;
};
struct tySequence_g8wWagWtbBE4jkij9axgDjA {
  TGenericSeq Sup;
  tyTuple_p7Uw0BAWm1JV3F8w0mhMOA* data[SEQ_DECL_SIZE];
};
struct tySequence_49cSLhOXtIXPXzKKaGFU0eQ {
  TGenericSeq Sup;
  tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* data[SEQ_DECL_SIZE];
};
struct tySequence_rl1wTgiGRBZamH1pllm1bA {
  TGenericSeq Sup;
  tyTuple_r4JoVxlxeWnXF9cuRoe3Jtg* data[SEQ_DECL_SIZE];
};
struct tySequence_pUxI6Ljo6IKKHXKOZkQ7Og {
  TGenericSeq Sup;
  tyTuple_sr3s7uVHpu9cEbbDnCSg8yQ data[SEQ_DECL_SIZE];
};
struct tySequence_JAV0yhDlrNFYdAVDw2r39bQ {
  TGenericSeq Sup;
  tyTuple_zXBGqNygOt4DlBCAX3NcVQ data[SEQ_DECL_SIZE];
};
N_NIMCALL(void, nimGCvisit)(void* d, NI op);
static N_NIMCALL(void, Marker_tyRef_I3NKKFmWZOsFHsQBiT19bKw)(void* p, NI op);
N_NIMCALL(void*, newObj)(TNimType* typ, NI size);
static N_INLINE(void, asgnRef)(void** dest, void* src);
static N_INLINE(void, incRef_9cAA5YuQAAC3MVbnGeV86swsystem)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c);
static N_INLINE(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*, usrToCell_yB9aH5WIlwd0xkYrcdPeXrQsystem)(void* usr);
static N_INLINE(void, decRef_MV4BBk6J1qu70IbBxwEn4wsystem)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c);
static N_INLINE(void, rtlAddZCT_MV4BBk6J1qu70IbBxwEn4w_2system)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c);
N_LIB_PRIVATE N_NOINLINE(void, addZCT_fCDI7oO1NNVXXURtxSzsRw)(tyObject_CellSeq_Axo1XVm9aaQueTOldv8le5w* s, tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c);
N_NIMCALL(NimStringDesc*, copyString)(NimStringDesc* src);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, format_9aLJdrhpYXKUhdIoI6dJGPg)(tyTuple_8eO9cDFHNTedYaXAdSjBGjA* b, tyTuple_p7Uw0BAWm1JV3F8w0mhMOA* n);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar__7fo3EMB4ZHVOeNHdcmvmHw)(tyObject_ValuecolonObjectType__73JSczcdor7tTS06v9cHOZw* value);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
static N_INLINE(void, copyMem_E1xtACub5WcDa3vbrIXbwgsystem)(void* dest, void* source, NI size);
N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
static N_INLINE(NIM_BOOL, isObjWithCache)(TNimType* obj, TNimType* subclass, TNimType** cache);
N_LIB_PRIVATE N_NOINLINE(NIM_BOOL, isObjSlowPath_k9bdq9bQE075AR7scLFt5wIg)(TNimType* obj, TNimType* subclass, TNimType** cache);
N_NIMCALL(NimStringDesc*, reprEnum)(NI e, TNimType* typ);
N_NIMCALL(NimStringDesc*, resizeString)(NimStringDesc* dest, NI addlen);
N_LIB_PRIVATE N_NIMCALL(void, writeFile_c1B29b0ZdDRPHc27YaKqwaA)(NimStringDesc* filename, NimStringDesc* content);
TNimType NTI_8eO9cDFHNTedYaXAdSjBGjA_;
extern TNimType NTI_ORWQUtasKGvy7C2tIe1dcg_;
TNimType NTI_I3NKKFmWZOsFHsQBiT19bKw_;
extern tyObject_GcHeap_1TRH1TZMaVZTnLNcIHuNFQ gch_IcYaEuuWivYAS86vFMTS3Q;
extern TNimType NTI_PO9bUMXtlWXaezrslbDbWhQ_;
static TNimType* Nim_OfCheck_CACHE6[2];
extern TNimType NTI_wzzqsNRSFKQWlUMuy1TJiw_;
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_3, "*main:\012", 7);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_4, ":\012", 2);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_6, "\"", 1);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_7, "\"\012", 2);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_8, "\012", 1);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_9, "\011", 1);
STRING_LITERAL(TM_8MLG8czdpLIxlikvWnFQRA_10, " ", 1);
static N_NIMCALL(void, Marker_tyRef_I3NKKFmWZOsFHsQBiT19bKw)(void* p, NI op) {
	tyTuple_8eO9cDFHNTedYaXAdSjBGjA* a;
	a = (tyTuple_8eO9cDFHNTedYaXAdSjBGjA*)p;
	nimGCvisit((void*)(*a).Field0, op);
}

static N_INLINE(void, incRef_9cAA5YuQAAC3MVbnGeV86swsystem)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c) {
	(*c).refcount = (NI)((NU64)((*c).refcount) + (NU64)(((NI) 8)));
}

static N_INLINE(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*, usrToCell_yB9aH5WIlwd0xkYrcdPeXrQsystem)(void* usr) {
	tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* result;
	result = (tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*)0;
	result = ((tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*) ((NI)((NU64)(((NI) (ptrdiff_t) (usr))) - (NU64)(((NI)sizeof(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g))))));
	return result;
}

static N_INLINE(void, rtlAddZCT_MV4BBk6J1qu70IbBxwEn4w_2system)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c) {
	addZCT_fCDI7oO1NNVXXURtxSzsRw((&gch_IcYaEuuWivYAS86vFMTS3Q.zct), c);
}

static N_INLINE(void, decRef_MV4BBk6J1qu70IbBxwEn4wsystem)(tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* c) {
	{
		(*c).refcount -= ((NI) 8);
		if (!((NU64)((*c).refcount) < (NU64)(((NI) 8)))) goto LA3_;
		rtlAddZCT_MV4BBk6J1qu70IbBxwEn4w_2system(c);
	}
	LA3_: ;
}

static N_INLINE(void, asgnRef)(void** dest, void* src) {
	{
		tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* T5_;
		if (!!((src == NIM_NIL))) goto LA3_;
		T5_ = (tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*)0;
		T5_ = usrToCell_yB9aH5WIlwd0xkYrcdPeXrQsystem(src);
		incRef_9cAA5YuQAAC3MVbnGeV86swsystem(T5_);
	}
	LA3_: ;
	{
		tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g* T10_;
		if (!!(((*dest) == NIM_NIL))) goto LA8_;
		T10_ = (tyObject_Cell_1zcF9cV8XIAtbN8h5HRUB8g*)0;
		T10_ = usrToCell_yB9aH5WIlwd0xkYrcdPeXrQsystem((*dest));
		decRef_MV4BBk6J1qu70IbBxwEn4wsystem(T10_);
	}
	LA8_: ;
	(*dest) = src;
}

N_LIB_PRIVATE N_NIMCALL(tyTuple_8eO9cDFHNTedYaXAdSjBGjA*, newBytecode_zrLPEi2Nr0xqwx15uw4sxw)(tyTuple_M3y5mHl2OtcVFI81N2j0DQ* vm) {
	tyTuple_8eO9cDFHNTedYaXAdSjBGjA* result;
	result = (tyTuple_8eO9cDFHNTedYaXAdSjBGjA*)0;
	result = (tyTuple_8eO9cDFHNTedYaXAdSjBGjA*) newObj((&NTI_I3NKKFmWZOsFHsQBiT19bKw_), sizeof(tyTuple_8eO9cDFHNTedYaXAdSjBGjA));
	asgnRef((void**) (&(*result).Field0), vm);
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

static N_INLINE(NIM_BOOL, isObjWithCache)(TNimType* obj, TNimType* subclass, TNimType** cache) {
	NIM_BOOL result;
{	result = (NIM_BOOL)0;
	{
		if (!(obj == subclass)) goto LA3_;
		result = NIM_TRUE;
		goto BeforeRet_;
	}
	LA3_: ;
	{
		if (!((*obj).base == subclass)) goto LA7_;
		result = NIM_TRUE;
		goto BeforeRet_;
	}
	LA7_: ;
	{
		if (!(cache[(((NI) 0))- 0] == obj)) goto LA11_;
		result = NIM_FALSE;
		goto BeforeRet_;
	}
	LA11_: ;
	{
		if (!(cache[(((NI) 1))- 0] == obj)) goto LA15_;
		result = NIM_TRUE;
		goto BeforeRet_;
	}
	LA15_: ;
	result = isObjSlowPath_k9bdq9bQE075AR7scLFt5wIg(obj, subclass, cache);
	goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, format_9aLJdrhpYXKUhdIoI6dJGPg)(tyTuple_8eO9cDFHNTedYaXAdSjBGjA* b, tyTuple_p7Uw0BAWm1JV3F8w0mhMOA* n) {
	NimStringDesc* result;
{	result = (NimStringDesc*)0;
	switch ((*n).Field0) {
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 4):
	{
		NimStringDesc* T2_;
		NimStringDesc* T3_;
		T2_ = (NimStringDesc*)0;
		T3_ = (NimStringDesc*)0;
		T3_ = dollar__7fo3EMB4ZHVOeNHdcmvmHw((*n).Field1);
		T2_ = rawNewString(T3_->Sup.len + 2);
appendString(T2_, T3_);
appendString(T2_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_4));
		result = T2_;
		goto BeforeRet_;
	}
	break;
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 6):
	{
		{
			NimStringDesc* T9_;
			NimStringDesc* T10_;
			if (!(((*n).Field1) && (isObjWithCache((*(*n).Field1).Sup.m_type, (&NTI_PO9bUMXtlWXaezrslbDbWhQ_), Nim_OfCheck_CACHE6)))) goto LA7_;
			T9_ = (NimStringDesc*)0;
			T10_ = (NimStringDesc*)0;
			T10_ = dollar__7fo3EMB4ZHVOeNHdcmvmHw((*n).Field1);
			T9_ = rawNewString(T10_->Sup.len + 3);
appendString(T9_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_6));
appendString(T9_, T10_);
appendString(T9_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_7));
			result = T9_;
			goto BeforeRet_;
		}
		goto LA5_;
		LA7_: ;
		{
			NimStringDesc* T12_;
			NimStringDesc* T13_;
			T12_ = (NimStringDesc*)0;
			T13_ = (NimStringDesc*)0;
			T13_ = dollar__7fo3EMB4ZHVOeNHdcmvmHw((*n).Field1);
			T12_ = rawNewString(T13_->Sup.len + 1);
appendString(T12_, T13_);
appendString(T12_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_8));
			result = T12_;
			goto BeforeRet_;
		}
		LA5_: ;
	}
	break;
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 24):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 25):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 1):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 22):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 23):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 26):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 27):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 32):
	case ((tyEnum_InstructionKind_wzzqsNRSFKQWlUMuy1TJiw) 35):
	{
		NimStringDesc* T15_;
		T15_ = (NimStringDesc*)0;
		T15_ = rawNewString(reprEnum((NI)(*n).Field0, (&NTI_wzzqsNRSFKQWlUMuy1TJiw_))->Sup.len + 2);
appendString(T15_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_9));
appendString(T15_, reprEnum((NI)(*n).Field0, (&NTI_wzzqsNRSFKQWlUMuy1TJiw_)));
appendString(T15_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_10));
		result = T15_;
		goto BeforeRet_;
	}
	break;
	default:
	{
		NimStringDesc* T17_;
		T17_ = (NimStringDesc*)0;
		T17_ = rawNewString(reprEnum((NI)(*n).Field0, (&NTI_wzzqsNRSFKQWlUMuy1TJiw_))->Sup.len + 2);
appendString(T17_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_9));
appendString(T17_, reprEnum((NI)(*n).Field0, (&NTI_wzzqsNRSFKQWlUMuy1TJiw_)));
appendString(T17_, ((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_8));
		result = T17_;
		goto BeforeRet_;
	}
	break;
	}
	}BeforeRet_: ;
	return result;
}

N_LIB_PRIVATE N_NIMCALL(void, save_9cfEfE2eKoZxOmsVVRZQiDQ)(tyTuple_8eO9cDFHNTedYaXAdSjBGjA* b, NimStringDesc* file) {
	NimStringDesc* contents;
	contents = copyString(((NimStringDesc*) &TM_8MLG8czdpLIxlikvWnFQRA_3));
	{
		tyTuple_p7Uw0BAWm1JV3F8w0mhMOA* i;
		tySequence_g8wWagWtbBE4jkij9axgDjA* colontmp_;
		NI i_2;
		NI L;
		NI T2_;
		i = (tyTuple_p7Uw0BAWm1JV3F8w0mhMOA*)0;
		colontmp_ = (tySequence_g8wWagWtbBE4jkij9axgDjA*)0;
		colontmp_ = (*(*b).Field0).Field0;
		i_2 = ((NI) 0);
		T2_ = (colontmp_ ? colontmp_->Sup.len : 0);
		L = T2_;
		{
			while (1) {
				NimStringDesc* T5_;
				if (!(i_2 < L)) goto LA4;
				i = colontmp_->data[i_2];
				T5_ = (NimStringDesc*)0;
				T5_ = format_9aLJdrhpYXKUhdIoI6dJGPg(b, i);
				contents = resizeString(contents, T5_->Sup.len + 0);
appendString(contents, T5_);
				i_2 += ((NI) 1);
			} LA4: ;
		}
	}
	writeFile_c1B29b0ZdDRPHc27YaKqwaA(file, contents);
}
NIM_EXTERNC N_NOINLINE(void, unknown_bytecodeInit000)(void) {
}

NIM_EXTERNC N_NOINLINE(void, unknown_bytecodeDatInit000)(void) {
static TNimNode* TM_8MLG8czdpLIxlikvWnFQRA_2[1];
static TNimNode TM_8MLG8czdpLIxlikvWnFQRA_0[2];
NTI_8eO9cDFHNTedYaXAdSjBGjA_.size = sizeof(tyTuple_8eO9cDFHNTedYaXAdSjBGjA);
NTI_8eO9cDFHNTedYaXAdSjBGjA_.kind = 18;
NTI_8eO9cDFHNTedYaXAdSjBGjA_.base = 0;
TM_8MLG8czdpLIxlikvWnFQRA_2[0] = &TM_8MLG8czdpLIxlikvWnFQRA_0[1];
TM_8MLG8czdpLIxlikvWnFQRA_0[1].kind = 1;
TM_8MLG8czdpLIxlikvWnFQRA_0[1].offset = offsetof(tyTuple_8eO9cDFHNTedYaXAdSjBGjA, Field0);
TM_8MLG8czdpLIxlikvWnFQRA_0[1].typ = (&NTI_ORWQUtasKGvy7C2tIe1dcg_);
TM_8MLG8czdpLIxlikvWnFQRA_0[1].name = "Field0";
TM_8MLG8czdpLIxlikvWnFQRA_0[0].len = 1; TM_8MLG8czdpLIxlikvWnFQRA_0[0].kind = 2; TM_8MLG8czdpLIxlikvWnFQRA_0[0].sons = &TM_8MLG8czdpLIxlikvWnFQRA_2[0];
NTI_8eO9cDFHNTedYaXAdSjBGjA_.node = &TM_8MLG8czdpLIxlikvWnFQRA_0[0];
NTI_I3NKKFmWZOsFHsQBiT19bKw_.size = sizeof(tyTuple_8eO9cDFHNTedYaXAdSjBGjA*);
NTI_I3NKKFmWZOsFHsQBiT19bKw_.kind = 22;
NTI_I3NKKFmWZOsFHsQBiT19bKw_.base = (&NTI_8eO9cDFHNTedYaXAdSjBGjA_);
NTI_I3NKKFmWZOsFHsQBiT19bKw_.marker = Marker_tyRef_I3NKKFmWZOsFHsQBiT19bKw;
}

