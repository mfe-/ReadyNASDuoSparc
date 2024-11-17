/* 
 * Copyright (c) 1991-1994 by Xerox Corporation.  All rights reserved.
 * Copyright (c) 1996-1999 by Silicon Graphics.  All rights reserved.
 * Copyright (c) 1999-2003 by Hewlett-Packard Company. All rights reserved.
 *
 *
 * THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
 * OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission is hereby granted to use or copy this program
 * for any purpose,  provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 * Some of the machine specific code was borrowed from our GC distribution.
 */

/* The following really assume we have a 486 or better.  Unfortunately	*/
/* gcc doesn't define a suitable feature test macro based on command 	*/
/* line options.							*/
/* We should perhaps test dynamically.					*/

#include "../aligned_atomic_load_store.h"

/* Real X86 implementations, except for some old WinChips, appear	*/
/* to enforce ordering between memory operations, EXCEPT that a later	*/
/* read can pass earlier writes, presumably due to the visible		*/
/* presence of store buffers.						*/
/* We ignore both the WinChips, and the fact that the official specs	*/
/* seem to be much weaker (and arguably too weak to be usable).		*/

#include "../ordered_except_wr.h"

#if defined(AO_USE_PENTIUM4_INSTRS)
AO_INLINE void
AO_nop_full()
{
  __asm__ __volatile__("mfence" : : : "memory");
}

#define AO_HAVE_NOP_FULL

#else

/* We could use the cpuid instruction.  But that seems to be slower 	*/
/* than the default implementation based on test_and_set_full.  Thus	*/
/* we omit that bit of misinformation here.				*/

#endif

/* As far as we can tell, the lfence and sfence instructions are not	*/
/* currently needed or useful for cached memory accesses.		*/

/* Really only works for 486 and later */
AO_INLINE AO_t
AO_fetch_and_add_full (volatile AO_t *p, long incr)
{
  AO_t result = incr;

  __asm__ __volatile__ ("lock; xaddq %0, %1" :
			"+r" (result), "+m" (*p) : : "memory");
  return result;
}

#define AO_HAVE_fetch_and_add_full

/* Really only works for 486 and later */
AO_INLINE void
AO_or_full (volatile AO_t *p, AO_t incr)
{
  __asm__ __volatile__ ("lock; orq %1, %0" :
			"+m" (*p) : "r" (incr) : "memory");
}

#define AO_HAVE_or_full

AO_INLINE AO_TS_t
AO_test_and_set_full(volatile AO_t *addr)
{
  AO_t oldval;
  /* Note: the "xchg" instruction does not need a "lock" prefix */
  __asm__ __volatile__("xchgq %0, %1"
		: "=r"(oldval), "+m"(*(addr))
		: "0"(1) : "memory");
  return oldval;
}

#define AO_HAVE_test_and_set_full

/* Returns nonzero if the comparison succeeded. */
AO_INLINE int
AO_compare_and_swap_full(volatile AO_t *addr,
		  	     AO_t old, AO_t new_val) 
{
  char result;
  __asm__ __volatile__("lock; cmpxchgq %2, %0; setz %1"
	    	       : "+m"(*(addr)), "=q"(result)
		       : "r" (new_val), "a"(old) : "memory");
  return (int) result;
}

#define AO_HAVE_compare_and_swap_full
