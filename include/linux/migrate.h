#ifndef _LINUX_MIGRATE_H
#define _LINUX_MIGRATE_H

#include <linux/config.h>
#include <linux/mm.h>

#ifdef CONFIG_MIGRATION
extern int isolate_lru_page(struct page *p, struct list_head *pagelist);
extern int putback_lru_pages(struct list_head *l);
extern int migrate_page(struct page *, struct page *);
extern void migrate_page_copy(struct page *, struct page *);
extern int migrate_page_remove_references(struct page *, struct page *, int);
extern int migrate_pages(struct list_head *l, struct list_head *t,
		struct list_head *moved, struct list_head *failed);
extern int migrate_pages_to(struct list_head *pagelist,
			struct vm_area_struct *vma, int dest);
extern int fail_migrate_page(struct page *, struct page *);

extern int migrate_prep(void);

#else

static inline int isolate_lru_page(struct page *p, struct list_head *list)
					{ return -ENOSYS; }
static inline int putback_lru_pages(struct list_head *l) { return 0; }
static inline int migrate_pages(struct list_head *l, struct list_head *t,
	struct list_head *moved, struct list_head *failed) { return -ENOSYS; }

static inline int migrate_pages_to(struct list_head *pagelist,
			struct vm_area_struct *vma, int dest) { return 0; }

static inline int migrate_prep(void) { return -ENOSYS; }

/* Possible settings for the migrate_page() method in address_operations */
#define migrate_page NULL
#define fail_migrate_page NULL

#endif /* CONFIG_MIGRATION */
#endif /* _LINUX_MIGRATE_H */
