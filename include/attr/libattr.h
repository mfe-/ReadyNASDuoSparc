#ifndef __LIBATTR_H
#define __LIBATTR_H

#ifdef __cplusplus
extern "C" {
#endif

struct error_context;

extern int attr_copy_file (const char *, const char *,
			   int (*) (const char *, struct error_context *),
			   struct error_context *);
extern int attr_copy_fd (const char *, int, const char *, int,
			 int (*) (const char *, struct error_context *),
			 struct error_context *);

/* The default check function used by attr_copy_{fd,file}. */
extern int attr_copy_check_permissions(const char *, struct error_context *);

#ifdef __cplusplus
}
#endif

#endif
