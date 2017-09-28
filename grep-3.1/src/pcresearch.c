/* pcresearch.c - searching subroutines using PCRE for grep.
   Copyright 2000, 2007, 2009-2017 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* Written August 1992 by Mike Haertel. */

#include <config.h>
#include "search.h"
#include "die.h"

#if HAVE_LIBPCRE
# include <pcre.h>

/* This must be at least 2; everything after that is for performance
   in pcre_exec.  */
enum { NSUB = 300 };

# ifndef PCRE_STUDY_JIT_COMPILE
#  define PCRE_STUDY_JIT_COMPILE 0
# endif

struct pcre_comp
{
  /* Compiled internal form of a Perl regular expression.  */
  pcre *cre;

  /* Additional information about the pattern.  */
  pcre_extra *extra;

# if PCRE_STUDY_JIT_COMPILE
  /* The JIT stack and its maximum size.  */
  pcre_jit_stack *jit_stack;
  int jit_stack_size;
# endif

  /* Table, indexed by ! (flag & PCRE_NOTBOL), of whether the empty
     string matches when that flag is used.  */
  int empty_match[2];
};


/* Match the already-compiled PCRE pattern against the data in SUBJECT,
   of size SEARCH_BYTES and starting with offset SEARCH_OFFSET, with
   options OPTIONS, and storing resulting matches into SUB.  Return
   the (nonnegative) match location or a (negative) error number.  */
static int
jit_exec (struct pcre_comp *pc, char const *subject, int search_bytes,
          int search_offset, int options, int *sub)
{
  while (true)
    {
      int e = pcre_exec (pc->cre, pc->extra, subject, search_bytes,
                         search_offset, options, sub, NSUB);

# if PCRE_STUDY_JIT_COMPILE
      if (e == PCRE_ERROR_JIT_STACKLIMIT
          && 0 < pc->jit_stack_size && pc->jit_stack_size <= INT_MAX / 2)
        {
          int old_size = pc->jit_stack_size;
          int new_size = pc->jit_stack_size = old_size * 2;
          if (pc->jit_stack)
            pcre_jit_stack_free (pc->jit_stack);
          pc->jit_stack = pcre_jit_stack_alloc (old_size, new_size);
          if (!pc->jit_stack)
            die (EXIT_TROUBLE, 0,
                 _("failed to allocate memory for the PCRE JIT stack"));
          pcre_assign_jit_stack (pc->extra, NULL, pc->jit_stack);
          continue;
        }
# endif

      return e;
    }
}

#endif

void *
Pcompile (char *pattern, size_t size, reg_syntax_t ignored)
{
#if !HAVE_LIBPCRE
  die (EXIT_TROUBLE, 0,
       _("support for the -P option is not compiled into "
         "this --disable-perl-regexp binary"));
#else
  int e;
  char const *ep;
  static char const wprefix[] = "(?<!\\w)(?:";
  static char const wsuffix[] = ")(?!\\w)";
  static char const xprefix[] = "^(?:";
  static char const xsuffix[] = ")$";
  int fix_len_max = MAX (sizeof wprefix - 1 + sizeof wsuffix - 1,
                         sizeof xprefix - 1 + sizeof xsuffix - 1);
  char *re = xnmalloc (4, size + (fix_len_max + 4 - 1) / 4);
  int flags = PCRE_DOLLAR_ENDONLY | (match_icase ? PCRE_CASELESS : 0);
  char const *patlim = pattern + size;
  char *n = re;
  char const *p;
  char const *pnul;
  struct pcre_comp *pc = xcalloc (1, sizeof (*pc));

  if (localeinfo.multibyte)
    {
      if (! localeinfo.using_utf8)
        die (EXIT_TROUBLE, 0, _("-P supports only unibyte and UTF-8 locales"));
      flags |= PCRE_UTF8;
    }

  /* FIXME: Remove this restriction.  */
  if (memchr (pattern, '\n', size))
    die (EXIT_TROUBLE, 0, _("the -P option only supports a single pattern"));

  *n = '\0';
  if (match_words)
    strcpy (n, wprefix);
  if (match_lines)
    strcpy (n, xprefix);
  n += strlen (n);

  /* The PCRE interface doesn't allow NUL bytes in the pattern, so
     replace each NUL byte in the pattern with the four characters
     "\000", removing a preceding backslash if there are an odd
     number of backslashes before the NUL.  */
  for (p = pattern; (pnul = memchr (p, '\0', patlim - p)); p = pnul + 1)
    {
      memcpy (n, p, pnul - p);
      n += pnul - p;
      for (p = pnul; pattern < p && p[-1] == '\\'; p--)
        continue;
      n -= (pnul - p) & 1;
      strcpy (n, "\\000");
      n += 4;
    }

  memcpy (n, p, patlim - p);
  n += patlim - p;
  *n = '\0';
  if (match_words)
    strcpy (n, wsuffix);
  if (match_lines)
    strcpy (n, xsuffix);

  pc->cre = pcre_compile (re, flags, &ep, &e, pcre_maketables ());
  if (!pc->cre)
    die (EXIT_TROUBLE, 0, "%s", ep);

  pc->extra = pcre_study (pc->cre, PCRE_STUDY_JIT_COMPILE, &ep);
  if (ep)
    die (EXIT_TROUBLE, 0, "%s", ep);

# if PCRE_STUDY_JIT_COMPILE
  if (pcre_fullinfo (pc->cre, pc->extra, PCRE_INFO_JIT, &e))
    die (EXIT_TROUBLE, 0, _("internal error (should never happen)"));

  /* The PCRE documentation says that a 32 KiB stack is the default.  */
  if (e)
    pc->jit_stack_size = 32 << 10;
# endif

  free (re);

  int sub[NSUB];
  pc->empty_match[false] = pcre_exec (pc->cre, pc->extra, "", 0, 0,
                                      PCRE_NOTBOL, sub, NSUB);
  pc->empty_match[true] = pcre_exec (pc->cre, pc->extra, "", 0, 0, 0, sub,
                                     NSUB);

  return pc;
#endif /* HAVE_LIBPCRE */
}

size_t
Pexecute (void *vcp, char const *buf, size_t size, size_t *match_size,
          char const *start_ptr)
{
#if !HAVE_LIBPCRE
  /* We can't get here, because Pcompile would have been called earlier.  */
  die (EXIT_TROUBLE, 0, _("internal error"));
#else
  int sub[NSUB];
  char const *p = start_ptr ? start_ptr : buf;
  bool bol = p[-1] == eolbyte;
  char const *line_start = buf;
  int e = PCRE_ERROR_NOMATCH;
  char const *line_end;
  struct pcre_comp *pc = vcp;

  /* The search address to pass to pcre_exec.  This is the start of
     the buffer, or just past the most-recently discovered encoding
     error or line end.  */
  char const *subject = buf;

  do
    {
      /* Search line by line.  Although this code formerly used
         PCRE_MULTILINE for performance, the performance wasn't always
         better and the correctness issues were too puzzling.  See
         Bug#22655.  */
      line_end = memchr (p, eolbyte, buf + size - p);
      if (INT_MAX < line_end - p)
        die (EXIT_TROUBLE, 0, _("exceeded PCRE's line length limit"));

      for (;;)
        {
          /* Skip past bytes that are easily determined to be encoding
             errors, treating them as data that cannot match.  This is
             faster than having pcre_exec check them.  */
          while (localeinfo.sbclen[to_uchar (*p)] == -1)
            {
              p++;
              subject = p;
              bol = false;
            }

          int search_offset = p - subject;

          /* Check for an empty match; this is faster than letting
             pcre_exec do it.  */
          if (p == line_end)
            {
              sub[0] = sub[1] = search_offset;
              e = pc->empty_match[bol];
              break;
            }

          int options = 0;
          if (!bol)
            options |= PCRE_NOTBOL;

          e = jit_exec (pc, subject, line_end - subject, search_offset,
                        options, sub);
          if (e != PCRE_ERROR_BADUTF8)
            break;
          int valid_bytes = sub[0];

          if (search_offset <= valid_bytes)
            {
              /* Try to match the string before the encoding error.  */
              if (valid_bytes == 0)
                {
                  /* Handle the empty-match case specially, for speed.
                     This optimization is valid if VALID_BYTES is zero,
                     which means SEARCH_OFFSET is also zero.  */
                  sub[1] = 0;
                  e = pc->empty_match[bol];
                }
              else
                e = jit_exec (pc, subject, valid_bytes, search_offset,
                              options | PCRE_NO_UTF8_CHECK | PCRE_NOTEOL, sub);

              if (e != PCRE_ERROR_NOMATCH)
                break;

              /* Treat the encoding error as data that cannot match.  */
              p = subject + valid_bytes + 1;
              bol = false;
            }

          subject += valid_bytes + 1;
        }

      if (e != PCRE_ERROR_NOMATCH)
        break;
      bol = true;
      p = subject = line_start = line_end + 1;
    }
  while (p < buf + size);

  if (e <= 0)
    {
      switch (e)
        {
        case PCRE_ERROR_NOMATCH:
          break;

        case PCRE_ERROR_NOMEMORY:
          die (EXIT_TROUBLE, 0, _("memory exhausted"));

# if PCRE_STUDY_JIT_COMPILE
        case PCRE_ERROR_JIT_STACKLIMIT:
          die (EXIT_TROUBLE, 0, _("exhausted PCRE JIT stack"));
# endif

        case PCRE_ERROR_MATCHLIMIT:
          die (EXIT_TROUBLE, 0, _("exceeded PCRE's backtracking limit"));

        default:
          /* For now, we lump all remaining PCRE failures into this basket.
             If anyone cares to provide sample grep usage that can trigger
             particular PCRE errors, we can add to the list (above) of more
             detailed diagnostics.  */
          die (EXIT_TROUBLE, 0, _("internal PCRE error: %d"), e);
        }

      return -1;
    }
  else
    {
      char const *matchbeg = subject + sub[0];
      char const *matchend = subject + sub[1];
      char const *beg;
      char const *end;
      if (start_ptr)
        {
          beg = matchbeg;
          end = matchend;
        }
      else
        {
          beg = line_start;
          end = line_end + 1;
        }
      *match_size = end - beg;
      return beg - buf;
    }
#endif
}
