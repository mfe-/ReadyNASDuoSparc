/*
 * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307,
 * USA.
 * 
 * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 * Mountain View, CA  94043, or:
 * 
 * http://www.sgi.com 
 * 
 * For further information regarding this notice, see: 
 * 
 * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/
 */
#ifndef __XATTR_H__
#define __XATTR_H__

#include <features.h>

#include <errno.h>
#ifndef ENOATTR
# define ENOATTR ENODATA        /* No such attribute */
#endif

#define XATTR_CREATE  0x1       /* set value, fail if attr already exists */
#define XATTR_REPLACE 0x2       /* set value, fail if attr does not exist */


__BEGIN_DECLS

extern int setxattr (const char *__path, const char *__name,
		      const void *__value, size_t __size, int __flags) __THROW;
extern int lsetxattr (const char *__path, const char *__name,
		      const void *__value, size_t __size, int __flags) __THROW;
extern int fsetxattr (int __filedes, const char *__name,
		      const void *__value, size_t __size, int __flags) __THROW;

extern ssize_t getxattr (const char *__path, const char *__name,
				void *__value, size_t __size) __THROW;
extern ssize_t lgetxattr (const char *__path, const char *__name,
				void *__value, size_t __size) __THROW;
extern ssize_t fgetxattr (int __filedes, const char *__name,
				void *__value, size_t __size) __THROW;

extern ssize_t listxattr (const char *__path, char *__list,
				size_t __size) __THROW;
extern ssize_t llistxattr (const char *__path, char *__list,
				size_t __size) __THROW;
extern ssize_t flistxattr (int __filedes, char *__list,
				size_t __size) __THROW;

extern int removexattr (const char *__path, const char *__name) __THROW;
extern int lremovexattr (const char *__path, const char *__name) __THROW;
extern int fremovexattr (int __filedes,   const char *__name) __THROW;

__END_DECLS

#endif	/* __XATTR_H__ */
