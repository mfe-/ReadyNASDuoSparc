/*
 * linux/mm/slab.h
 * Written by Mark Hemment, 1996.
 * (markhe@nextd.demon.co.uk)
 */

#ifndef _LINUX_SLAB_H
#define	_LINUX_SLAB_H

#if	defined(__KERNEL__)

typedef struct kmem_cache kmem_cache_t;

#include	<linux/config.h>	/* kmalloc_sizes.h needs CONFIG_ options */
#include	<linux/gfp.h>
#include	<linux/init.h>
#include	<linux/types.h>
#include	<asm/page.h>		/* kmalloc_sizes.h needs PAGE_SIZE */
#include	<asm/cache.h>		/* kmalloc_sizes.h needs L1_CACHE_BYTES */

/* flags for kmem_cache_alloc() */
#define	SLAB_NOFS		GFP_NOFS
#define	SLAB_NOIO		GFP_NOIO
#define	SLAB_ATOMIC		GFP_ATOMIC
#define	SLAB_USER		GFP_USER
#define	SLAB_KERNEL		GFP_KERNEL
#define	SLAB_DMA		GFP_DMA

#define SLAB_LEVEL_MASK		GFP_LEVEL_MASK

#define	SLAB_NO_GROW		__GFP_NO_GROW	/* don't grow a cache */

/* flags to pass to kmem_cache_create().
 * The first 3 are only valid when the allocator as been build
 * SLAB_DEBUG_SUPPORT.
 */
#define	SLAB_DEBUG_FREE		0x00000100UL	/* Peform (expensive) checks on free */
#define	SLAB_DEBUG_INITIAL	0x00000200UL	/* Call constructor (as verifier) */
#define	SLAB_RED_ZONE		0x00000400UL	/* Red zone objs in a cache */
#define	SLAB_POISON		0x00000800UL	/* Poison objects */
#define	SLAB_HWCACHE_ALIGN	0x00002000UL	/* align objs on a h/w cache lines */
#define SLAB_CACHE_DMA		0x00004000UL	/* use GFP_DMA memory */
#define SLAB_MUST_HWCACHE_ALIGN	0x00008000UL	/* force alignment */
#define SLAB_STORE_USER		0x00010000UL	/* store the last owner for bug hunting */
#define SLAB_RECLAIM_ACCOUNT	0x00020000UL	/* track pages allocated to indicate
						   what is reclaimable later*/
#define SLAB_PANIC		0x00040000UL	/* panic if kmem_cache_create() fails */
#define SLAB_DESTROY_BY_RCU	0x00080000UL	/* defer freeing pages to RCU */
#define SLAB_MEM_SPREAD		0x00100000UL	/* Spread some memory over cpuset */

/* flags passed to a constructor func */
#define	SLAB_CTOR_CONSTRUCTOR	0x001UL		/* if not set, then deconstructor */
#define SLAB_CTOR_ATOMIC	0x002UL		/* tell constructor it can't sleep */
#define	SLAB_CTOR_VERIFY	0x004UL		/* tell constructor it's a verify call */

#ifndef CONFIG_SLOB

/* prototypes */
extern void __init kmem_cache_init(void);

extern kmem_cache_t *kmem_cache_create(const char *, size_t, size_t, unsigned long,
				       void (*)(void *, kmem_cache_t *, unsigned long),
				       void (*)(void *, kmem_cache_t *, unsigned long));
extern int kmem_cache_destroy(kmem_cache_t *);
extern int kmem_cache_shrink(kmem_cache_t *);
extern void *kmem_cache_alloc(kmem_cache_t *, gfp_t);
extern void *kmem_cache_zalloc(struct kmem_cache *, gfp_t);
extern void kmem_cache_free(kmem_cache_t *, void *);
extern unsigned int kmem_cache_size(kmem_cache_t *);
extern const char *kmem_cache_name(kmem_cache_t *);
extern kmem_cache_t *kmem_find_general_cachep(size_t size, gfp_t gfpflags);

/* Size description struct for general caches. */
struct cache_sizes {
	size_t		 cs_size;
	kmem_cache_t	*cs_cachep;
	kmem_cache_t	*cs_dmacachep;
};
extern struct cache_sizes malloc_sizes[];

extern void *__kmalloc(size_t, gfp_t);
#ifndef CONFIG_DEBUG_SLAB
#define ____kmalloc(size, flags) __kmalloc(size, flags)
#else
extern void *__kmalloc_track_caller(size_t, gfp_t, void*);
#define ____kmalloc(size, flags) \
    __kmalloc_track_caller(size, flags, __builtin_return_address(0))
#endif

static inline void *kmalloc(size_t size, gfp_t flags)
{
	if (__builtin_constant_p(size)) {
		int i = 0;
#define CACHE(x) \
		if (size <= x) \
			goto found; \
		else \
			i++;
#include "kmalloc_sizes.h"
#undef CACHE
		{
			extern void __you_cannot_kmalloc_that_much(void);
			__you_cannot_kmalloc_that_much();
		}
found:
		return kmem_cache_alloc((flags & GFP_DMA) ?
			malloc_sizes[i].cs_dmacachep :
			malloc_sizes[i].cs_cachep, flags);
	}
	return __kmalloc(size, flags);
}

extern void *__kzalloc(size_t, gfp_t);

static inline void *kzalloc(size_t size, gfp_t flags)
{
	if (__builtin_constant_p(size)) {
		int i = 0;
#define CACHE(x) \
		if (size <= x) \
			goto found; \
		else \
			i++;
#include "kmalloc_sizes.h"
#undef CACHE
		{
			extern void __you_cannot_kzalloc_that_much(void);
			__you_cannot_kzalloc_that_much();
		}
found:
		return kmem_cache_zalloc((flags & GFP_DMA) ?
			malloc_sizes[i].cs_dmacachep :
			malloc_sizes[i].cs_cachep, flags);
	}
	return __kzalloc(size, flags);
}

/**
 * kcalloc - allocate memory for an array. The memory is set to zero.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate.
 */
static inline void *kcalloc(size_t n, size_t size, gfp_t flags)
{
	if (n != 0 && size > ULONG_MAX / n)
		return NULL;
	return kzalloc(n * size, flags);
}

extern void kfree(const void *);
extern unsigned int ksize(const void *);
extern int slab_is_available(void);

#ifdef CONFIG_NUMA
extern void *kmem_cache_alloc_node(kmem_cache_t *, gfp_t flags, int node);
extern void *kmalloc_node(size_t size, gfp_t flags, int node);
#else
static inline void *kmem_cache_alloc_node(kmem_cache_t *cachep, gfp_t flags, int node)
{
	return kmem_cache_alloc(cachep, flags);
}
static inline void *kmalloc_node(size_t size, gfp_t flags, int node)
{
	return kmalloc(size, flags);
}
#endif

extern int FASTCALL(kmem_cache_reap(int));
extern int FASTCALL(kmem_ptr_validate(kmem_cache_t *cachep, void *ptr));

#else /* CONFIG_SLOB */

/* SLOB allocator routines */

void kmem_cache_init(void);
struct kmem_cache *kmem_find_general_cachep(size_t, gfp_t gfpflags);
struct kmem_cache *kmem_cache_create(const char *c, size_t, size_t,
	unsigned long,
	void (*)(void *, struct kmem_cache *, unsigned long),
	void (*)(void *, struct kmem_cache *, unsigned long));
int kmem_cache_destroy(struct kmem_cache *c);
void *kmem_cache_alloc(struct kmem_cache *c, gfp_t flags);
void *kmem_cache_zalloc(struct kmem_cache *, gfp_t);
void kmem_cache_free(struct kmem_cache *c, void *b);
const char *kmem_cache_name(struct kmem_cache *);
void *kmalloc(size_t size, gfp_t flags);
void *__kzalloc(size_t size, gfp_t flags);
void kfree(const void *m);
unsigned int ksize(const void *m);
unsigned int kmem_cache_size(struct kmem_cache *c);

static inline void *kcalloc(size_t n, size_t size, gfp_t flags)
{
	return __kzalloc(n * size, flags);
}

#define kmem_cache_shrink(d) (0)
#define kmem_cache_reap(a)
#define kmem_ptr_validate(a, b) (0)
#define kmem_cache_alloc_node(c, f, n) kmem_cache_alloc(c, f)
#define kmalloc_node(s, f, n) kmalloc(s, f)
#define kzalloc(s, f) __kzalloc(s, f)
#define ____kmalloc kmalloc

#endif /* CONFIG_SLOB */

/* System wide caches */
extern kmem_cache_t	*vm_area_cachep;
extern kmem_cache_t	*names_cachep;
extern kmem_cache_t	*files_cachep;
extern kmem_cache_t	*filp_cachep;
extern kmem_cache_t	*fs_cachep;
extern kmem_cache_t	*sighand_cachep;
extern kmem_cache_t	*bio_cachep;

extern atomic_t slab_reclaim_pages;

#endif	/* __KERNEL__ */

#endif	/* _LINUX_SLAB_H */
