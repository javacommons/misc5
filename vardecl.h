﻿#ifndef _TLSDECL_H_
#define _TLSDECL_H_

#if __cplusplus >= 201103L
#define TLS_VARIABLE_DECL thread_local
#else
#ifdef __GNUC__
#define TLS_VARIABLE_DECL __thread
#else
#define TLS_VARIABLE_DECL __declspec(thread)
#endif
#endif

#ifdef __GNUC__
#define TLS_CALLBACK_DECL(SECTION,VAR,FUN) PIMAGE_TLS_CALLBACK VAR __attribute__ ((section(SECTION))) = FUN;
#else
#ifdef _WIN64
#define TLS_CALLBACK_DECL(SECTION,VAR,FUN) __pragma(const_seg(SECTION)) extern const PIMAGE_TLS_CALLBACK VAR; const PIMAGE_TLS_CALLBACK VAR = FUN; __pragma(const_seg())
#else
#define TLS_CALLBACK_DECL(SECTION,VAR,FUN) __pragma(data_seg(SECTION)) PIMAGE_TLS_CALLBACK VAR = FUN; __pragma(data_seg())
#endif
#endif

#ifdef __GNUC__
#define ALIGNED_ARRAY_DECL(TYPE, VAR, SIZE, ALIGN) TYPE VAR[SIZE] __attribute__ ((__aligned__(ALIGN)))
#else
#define ALIGNED_ARRAY_DECL(TYPE, VAR, SIZE, ALIGN) __declspec(align(ALIGN)) TYPE VAR[SIZE]
#endif

#define UNUSED_VARIABLE(P) (void)P

#endif /* _TLSDECL_H_ */
