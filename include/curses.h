/****************************************************************************
 * Copyright (c) 1998-2003,2004 Free Software Foundation, Inc.              *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 *     and: Thomas E. Dickey 1996-on                                        *
 ****************************************************************************/

/* $Id: curses.h.in,v 1.148 2004/01/14 23:50:12 tom Exp $ */

#ifndef __NCURSES_H
#define __NCURSES_H

#define CURSES 1
#define CURSES_H 1

/* This should be defined for the enhanced functionality to be visible.
 * However, some of the wide-character (enhanced) functionality is missing.
 * So we do not define it (yet).
#define _XOPEN_CURSES 1
 */

/* These are defined only in curses.h, and are used for conditional compiles */
#define NCURSES_VERSION_MAJOR 5
#define NCURSES_VERSION_MINOR 4
#define NCURSES_VERSION_PATCH 20040208

/* This is defined in more than one ncurses header, for identification */
#undef  NCURSES_VERSION
#define NCURSES_VERSION "5.4"

#include <ncurses_dll.h>

/*
 * NCURSES_ATTR_T is used to quiet compiler warnings when building ncurses
 * configured using --disable-macros.
 */
#ifdef NCURSES_NOMACROS
#define NCURSES_ATTR_T attr_t
#endif

#ifndef NCURSES_ATTR_T
#define NCURSES_ATTR_T int
#endif

/*
 * Expands to 'const' if ncurses is configured using --enable-const.  Note that
 * doing so makes it incompatible with other implementations of X/Open Curses.
 */
#undef  NCURSES_CONST
#define NCURSES_CONST const

/*
 * The internal type used for color values
 */
#undef	NCURSES_COLOR_T
#define	NCURSES_COLOR_T short

/*
 * The internal type used for window dimensions.
 */
#undef	NCURSES_SIZE_T
#define	NCURSES_SIZE_T short

/*
 * NCURSES_CH_T is used in building the library, but not used otherwise in
 * this header file, since that would make the normal/wide-character versions
 * of the header incompatible.
 */
#undef	NCURSES_CH_T
#define NCURSES_CH_T chtype

typedef unsigned long chtype;

#include <stdio.h>
#include <unctrl.h>
#include <stdarg.h>	/* we need va_list */
#ifdef _XOPEN_SOURCE_EXTENDED
#include <stddef.h>	/* we want wchar_t */
#endif /* _XOPEN_SOURCE_EXTENDED */

/* XSI and SVr4 specify that curses implements 'bool'.  However, C++ may also
 * implement it.  If so, we must use the C++ compiler's type to avoid conflict
 * with other interfaces.
 *
 * A further complication is that <stdbool.h> may declare 'bool' to be a
 * different type, such as an enum which is not necessarily compatible with
 * C++.  If we have <stdbool.h>, make 'bool' a macro, so users may #undef it.
 * Otherwise, let it remain a typedef to avoid conflicts with other #define's.
 * In either case, make a typedef for NCURSES_BOOL which can be used if needed
 * from either C or C++.
 */

#undef TRUE
#define TRUE    1

#undef FALSE
#define FALSE   0

typedef unsigned char NCURSES_BOOL;

#if defined(__cplusplus)	/* __cplusplus, etc. */

/* use the C++ compiler's bool type */
#define NCURSES_BOOL bool

#else			/* c89, c99, etc. */

#if 1
#include <stdbool.h>
/* use whatever the C compiler decides bool really is */
#define NCURSES_BOOL bool
#else
/* there is no predefined bool - use our own */
#undef bool
#define bool NCURSES_BOOL
#endif

#endif /* !__cplusplus, etc. */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * XSI attributes.  In the ncurses implementation, they are identical to the
 * A_ attributes.
 */
#define WA_ATTRIBUTES	A_ATTRIBUTES
#define WA_NORMAL	A_NORMAL
#define WA_STANDOUT	A_STANDOUT
#define WA_UNDERLINE	A_UNDERLINE
#define WA_REVERSE	A_REVERSE
#define WA_BLINK	A_BLINK
#define WA_DIM		A_DIM
#define WA_BOLD		A_BOLD
#define WA_ALTCHARSET	A_ALTCHARSET
#define WA_INVIS	A_INVIS
#define WA_PROTECT	A_PROTECT
#define WA_HORIZONTAL	A_HORIZONTAL
#define WA_LEFT		A_LEFT
#define WA_LOW		A_LOW
#define WA_RIGHT	A_RIGHT
#define WA_TOP		A_TOP
#define WA_VERTICAL	A_VERTICAL

/* colors */
extern NCURSES_EXPORT_VAR(int) COLORS;
extern NCURSES_EXPORT_VAR(int) COLOR_PAIRS;

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/* line graphics */

#if 0
extern NCURSES_EXPORT_VAR(chtype*) _nc_acs_map(void);
#define acs_map (_nc_acs_map())
#else
extern NCURSES_EXPORT_VAR(chtype) acs_map[];
#endif

#define NCURSES_ACS(c)	(acs_map[(unsigned char)c])

/* VT100 symbols begin here */
#define ACS_ULCORNER	NCURSES_ACS('l') /* upper left corner */
#define ACS_LLCORNER	NCURSES_ACS('m') /* lower left corner */
#define ACS_URCORNER	NCURSES_ACS('k') /* upper right corner */
#define ACS_LRCORNER	NCURSES_ACS('j') /* lower right corner */
#define ACS_LTEE	NCURSES_ACS('t') /* tee pointing right */
#define ACS_RTEE	NCURSES_ACS('u') /* tee pointing left */
#define ACS_BTEE	NCURSES_ACS('v') /* tee pointing up */
#define ACS_TTEE	NCURSES_ACS('w') /* tee pointing down */
#define ACS_HLINE	NCURSES_ACS('q') /* horizontal line */
#define ACS_VLINE	NCURSES_ACS('x') /* vertical line */
#define ACS_PLUS	NCURSES_ACS('n') /* large plus or crossover */
#define ACS_S1		NCURSES_ACS('o') /* scan line 1 */
#define ACS_S9		NCURSES_ACS('s') /* scan line 9 */
#define ACS_DIAMOND	NCURSES_ACS('`') /* diamond */
#define ACS_CKBOARD	NCURSES_ACS('a') /* checker board (stipple) */
#define ACS_DEGREE	NCURSES_ACS('f') /* degree symbol */
#define ACS_PLMINUS	NCURSES_ACS('g') /* plus/minus */
#define ACS_BULLET	NCURSES_ACS('~') /* bullet */
/* Teletype 5410v1 symbols begin here */
#define ACS_LARROW	NCURSES_ACS(',') /* arrow pointing left */
#define ACS_RARROW	NCURSES_ACS('+') /* arrow pointing right */
#define ACS_DARROW	NCURSES_ACS('.') /* arrow pointing down */
#define ACS_UARROW	NCURSES_ACS('-') /* arrow pointing up */
#define ACS_BOARD	NCURSES_ACS('h') /* board of squares */
#define ACS_LANTERN	NCURSES_ACS('i') /* lantern symbol */
#define ACS_BLOCK	NCURSES_ACS('0') /* solid square block */
/*
 * These aren't documented, but a lot of System Vs have them anyway
 * (you can spot pprryyzz{{||}} in a lot of AT&T terminfo strings).
 * The ACS_names may not match AT&T's, our source didn't know them.
 */
#define ACS_S3		NCURSES_ACS('p') /* scan line 3 */
#define ACS_S7		NCURSES_ACS('r') /* scan line 7 */
#define ACS_LEQUAL	NCURSES_ACS('y') /* less/equal */
#define ACS_GEQUAL	NCURSES_ACS('z') /* greater/equal */
#define ACS_PI		NCURSES_ACS('{') /* Pi */
#define ACS_NEQUAL	NCURSES_ACS('|') /* not equal */
#define ACS_STERLING	NCURSES_ACS('}') /* UK pound sign */

/*
 * Line drawing ACS names are of the form ACS_trbl, where t is the top, r
 * is the right, b is the bottom, and l is the left.  t, r, b, and l might
 * be B (blank), S (single), D (double), or T (thick).  The subset defined
 * here only uses B and S.
 */
#define ACS_BSSB	ACS_ULCORNER
#define ACS_SSBB	ACS_LLCORNER
#define ACS_BBSS	ACS_URCORNER
#define ACS_SBBS	ACS_LRCORNER
#define ACS_SBSS	ACS_RTEE
#define ACS_SSSB	ACS_LTEE
#define ACS_SSBS	ACS_BTEE
#define ACS_BSSS	ACS_TTEE
#define ACS_BSBS	ACS_HLINE
#define ACS_SBSB	ACS_VLINE
#define ACS_SSSS	ACS_PLUS

#undef	ERR
#define ERR     (-1)

#undef	OK
#define OK      (0)

/* values for the _flags member */
#define _SUBWIN         0x01	/* is this a sub-window? */
#define _ENDLINE        0x02	/* is the window flush right? */
#define _FULLWIN        0x04	/* is the window full-screen? */
#define _SCROLLWIN      0x08	/* bottom edge is at screen bottom? */
#define _ISPAD	        0x10	/* is this window a pad? */
#define _HASMOVED       0x20	/* has cursor moved since last refresh? */
#define _WRAPPED        0x40	/* cursor was just wrappped */

/*
 * this value is used in the firstchar and lastchar fields to mark
 * unchanged lines
 */
#define _NOCHANGE       -1

/*
 * this value is used in the oldindex field to mark lines created by insertions
 * and scrolls.
 */
#define _NEWINDEX	-1

typedef struct screen  SCREEN;
typedef struct _win_st WINDOW;

typedef	chtype	attr_t;		/* ...must be at least as wide as chtype */

#ifdef _XOPEN_SOURCE_EXTENDED

#if 0
#ifdef mblen			/* libutf8.h defines it w/o undefining first */
#undef mblen
#endif
#include <libutf8.h>
#endif

#if 0
#include <wchar.h>		/* ...to get mbstate_t, etc. */
#endif

#if 0
typedef unsigned short wchar_t;
#endif

#if 0
typedef unsigned int wint_t;
#endif

#define CCHARW_MAX	5
typedef struct
{
    attr_t	attr;
    wchar_t	chars[CCHARW_MAX];
}
cchar_t;

#endif /* _XOPEN_SOURCE_EXTENDED */

struct ldat;

struct _win_st
{
	NCURSES_SIZE_T _cury, _curx; /* current cursor position */

	/* window location and size */
	NCURSES_SIZE_T _maxy, _maxx; /* maximums of x and y, NOT window size */
	NCURSES_SIZE_T _begy, _begx; /* screen coords of upper-left-hand corner */

	short   _flags;		/* window state flags */

	/* attribute tracking */
	attr_t  _attrs;		/* current attribute for non-space character */
	chtype  _bkgd;		/* current background char/attribute pair */

	/* option values set by user */
	bool	_notimeout;	/* no time out on function-key entry? */
	bool	_clear;		/* consider all data in the window invalid? */
	bool	_leaveok;	/* OK to not reset cursor on exit? */
	bool	_scroll;	/* OK to scroll this window? */
	bool	_idlok;		/* OK to use insert/delete line? */
	bool	_idcok;		/* OK to use insert/delete char? */
	bool	_immed;		/* window in immed mode? (not yet used) */
	bool	_sync;		/* window in sync mode? */
	bool	_use_keypad;	/* process function keys into KEY_ symbols? */
	int	_delay;		/* 0 = nodelay, <0 = blocking, >0 = delay */

	struct ldat *_line;	/* the actual line data */

	/* global screen state */
	NCURSES_SIZE_T _regtop;	/* top line of scrolling region */
	NCURSES_SIZE_T _regbottom; /* bottom line of scrolling region */

	/* these are used only if this is a sub-window */
	int	_parx;		/* x coordinate of this window in parent */
	int	_pary;		/* y coordinate of this window in parent */
	WINDOW	*_parent;	/* pointer to parent if a sub-window */

	/* these are used only if this is a pad */
	struct pdat
	{
	    NCURSES_SIZE_T _pad_y,      _pad_x;
	    NCURSES_SIZE_T _pad_top,    _pad_left;
	    NCURSES_SIZE_T _pad_bottom, _pad_right;
	} _pad;

	NCURSES_SIZE_T _yoffset; /* real begy is _begy + _yoffset */

#ifdef _XOPEN_SOURCE_EXTENDED
	cchar_t  _bkgrnd;	/* current background char/attribute pair */
#endif
};

extern NCURSES_EXPORT_VAR(WINDOW *)   stdscr;
extern NCURSES_EXPORT_VAR(WINDOW *)   curscr;
extern NCURSES_EXPORT_VAR(WINDOW *)   newscr;

extern NCURSES_EXPORT_VAR(int)	LINES;
extern NCURSES_EXPORT_VAR(int)	COLS;
extern NCURSES_EXPORT_VAR(int)	TABSIZE;

/*
 * This global was an undocumented feature under AIX curses.
 */
extern NCURSES_EXPORT_VAR(int) ESCDELAY;	/* ESC expire time in milliseconds */

extern NCURSES_EXPORT_VAR(char) ttytype[];	/* needed for backward compatibility */

/*
 * These functions are extensions - not in XSI Curses.
 */
#if 1
extern NCURSES_EXPORT(bool) is_term_resized (int, int);
extern NCURSES_EXPORT(char *) keybound (int, int);
extern NCURSES_EXPORT(const char *) curses_version (void);
extern NCURSES_EXPORT(int) assume_default_colors (int, int);
extern NCURSES_EXPORT(int) define_key (const char *, int);
extern NCURSES_EXPORT(int) key_defined (const char *);
extern NCURSES_EXPORT(int) keyok (int, bool);
extern NCURSES_EXPORT(int) resize_term (int, int);
extern NCURSES_EXPORT(int) resizeterm (int, int);
extern NCURSES_EXPORT(int) use_default_colors (void);
extern NCURSES_EXPORT(int) use_extended_names (bool);
extern NCURSES_EXPORT(int) wresize (WINDOW *, int, int);
#else
#define curses_version() NCURSES_VERSION
#endif

/*
 * This is an extension to support events...
 */
#if 1
#ifdef NCURSES_WGETCH_EVENTS
#if !defined(__BEOS__)		/* Fix _nc_timed_wait() on BEOS... */
#  define NCURSES_EVENT_VERSION	1
#endif	/* !defined(__BEOS__) */

/*
 * Bits to set in _nc_event.data.flags
 */
#  define _NC_EVENT_TIMEOUT_MSEC	1
#  define _NC_EVENT_FILE		2
#  define _NC_EVENT_FILE_READABLE	2
#  if 0					/* Not supported yet... */
#    define _NC_EVENT_FILE_WRITABLE	4
#    define _NC_EVENT_FILE_EXCEPTION	8
#  endif

typedef struct
{
    int type;
    union
    {
	long timeout_msec;	/* _NC_EVENT_TIMEOUT_MSEC */
	struct
	{
	    unsigned int flags;
	    int fd;
	    unsigned int result;
	} fev;				/* _NC_EVENT_FILE */
    } data;
} _nc_event;

typedef struct
{
    int count;
    int result_flags;	/* _NC_EVENT_TIMEOUT_MSEC or _NC_EVENT_FILE_READABLE */
    _nc_event *events[1];
} _nc_eventlist;

extern NCURSES_EXPORT(int) wgetch_events(WINDOW *, _nc_eventlist *);	/* experimental */
extern NCURSES_EXPORT(int) wgetnstr_events(WINDOW *,char *,int,_nc_eventlist *);/* experimental */

#endif /* NCURSES_WGETCH_EVENTS */
#endif /* NCURSES_EXT_FUNCS */

/*
 * GCC (and some other compilers) define '__attribute__'; we're using this
 * macro to alert the compiler to flag inconsistencies in printf/scanf-like
 * function calls.  Just in case '__attribute__' isn't defined, make a dummy.
 * Old versions of G++ do not accept it anyway, at least not consistently with
 * GCC.
 */
#if !(defined(__GNUC__) || defined(__GNUG__) || defined(__attribute__))
#define __attribute__(p) /* nothing */
#endif

/*
 * We cannot define these in ncurses_cfg.h, since they require parameters to be
 * passed (that's non-portable).
 */
#ifndef GCC_PRINTFLIKE
#if defined(GCC_PRINTF) && !defined(printf)
#define GCC_PRINTFLIKE(fmt,var) __attribute__((format(printf,fmt,var)))
#else
#define GCC_PRINTFLIKE(fmt,var) /*nothing*/
#endif
#endif

#ifndef GCC_SCANFLIKE
#if defined(GCC_SCANF) && !defined(scanf)
#define GCC_SCANFLIKE(fmt,var)  __attribute__((format(scanf,fmt,var)))
#else
#define GCC_SCANFLIKE(fmt,var)  /*nothing*/
#endif
#endif

#ifndef	GCC_NORETURN
#define	GCC_NORETURN /* nothing */
#endif

#ifndef	GCC_UNUSED
#define	GCC_UNUSED /* nothing */
#endif

/*
 * Function prototypes.  This is the complete XSI Curses list of required
 * functions.  Those marked `generated' will have sources generated from the
 * macro definitions later in this file, in order to satisfy XPG4.2
 * requirements.
 */

extern NCURSES_EXPORT(int) addch (const chtype);			/* generated */
extern NCURSES_EXPORT(int) addchnstr (const chtype *, int);		/* generated */
extern NCURSES_EXPORT(int) addchstr (const chtype *);			/* generated */
extern NCURSES_EXPORT(int) addnstr (const char *, int);			/* generated */
extern NCURSES_EXPORT(int) addstr (const char *);			/* generated */
extern NCURSES_EXPORT(int) attroff (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attron (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attrset (NCURSES_ATTR_T);			/* generated */
extern NCURSES_EXPORT(int) attr_get (attr_t *, short *, void *);	/* generated */
extern NCURSES_EXPORT(int) attr_off (attr_t, void *);			/* generated */
extern NCURSES_EXPORT(int) attr_on (attr_t, void *);			/* generated */
extern NCURSES_EXPORT(int) attr_set (attr_t, short, void *);		/* generated */
extern NCURSES_EXPORT(int) baudrate (void);				/* implemented */
extern NCURSES_EXPORT(int) beep  (void);				/* implemented */
extern NCURSES_EXPORT(int) bkgd (chtype);				/* generated */
extern NCURSES_EXPORT(void) bkgdset (chtype);				/* generated */
extern NCURSES_EXPORT(int) border (chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);	/* generated */
extern NCURSES_EXPORT(int) box (WINDOW *, chtype, chtype);		/* generated */
extern NCURSES_EXPORT(bool) can_change_color (void);			/* implemented */
extern NCURSES_EXPORT(int) cbreak (void);				/* implemented */
extern NCURSES_EXPORT(int) chgat (int, attr_t, short, const void *);	/* generated */
extern NCURSES_EXPORT(int) clear (void);				/* generated */
extern NCURSES_EXPORT(int) clearok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) clrtobot (void);				/* generated */
extern NCURSES_EXPORT(int) clrtoeol (void);				/* generated */
extern NCURSES_EXPORT(int) color_content (short,short*,short*,short*);	/* implemented */
extern NCURSES_EXPORT(int) color_set (short,void*);			/* generated */
extern NCURSES_EXPORT(int) COLOR_PAIR (int);				/* generated */
extern NCURSES_EXPORT(int) copywin (const WINDOW*,WINDOW*,int,int,int,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) curs_set (int);				/* implemented */
extern NCURSES_EXPORT(int) def_prog_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) def_shell_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) delay_output (int);				/* implemented */
extern NCURSES_EXPORT(int) delch (void);				/* generated */
extern NCURSES_EXPORT(void) delscreen (SCREEN *);			/* implemented */
extern NCURSES_EXPORT(int) delwin (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) deleteln (void);				/* generated */
extern NCURSES_EXPORT(WINDOW *) derwin (WINDOW *,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) doupdate (void);				/* implemented */
extern NCURSES_EXPORT(WINDOW *) dupwin (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) echo (void);					/* implemented */
extern NCURSES_EXPORT(int) echochar (const chtype);			/* generated */
extern NCURSES_EXPORT(int) erase (void);				/* generated */
extern NCURSES_EXPORT(int) endwin (void);				/* implemented */
extern NCURSES_EXPORT(char) erasechar (void);				/* implemented */
extern NCURSES_EXPORT(void) filter (void);				/* implemented */
extern NCURSES_EXPORT(int) flash (void);				/* implemented */
extern NCURSES_EXPORT(int) flushinp (void);				/* implemented */
extern NCURSES_EXPORT(chtype) getbkgd (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) getch (void);				/* generated */
extern NCURSES_EXPORT(int) getnstr (char *, int);			/* generated */
extern NCURSES_EXPORT(int) getstr (char *);				/* generated */
extern NCURSES_EXPORT(WINDOW *) getwin (FILE *);			/* implemented */
extern NCURSES_EXPORT(int) halfdelay (int);				/* implemented */
extern NCURSES_EXPORT(bool) has_colors (void);				/* implemented */
extern NCURSES_EXPORT(bool) has_ic (void);				/* implemented */
extern NCURSES_EXPORT(bool) has_il (void);				/* implemented */
extern NCURSES_EXPORT(int) hline (chtype, int);				/* generated */
extern NCURSES_EXPORT(void) idcok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(int) idlok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(void) immedok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(chtype) inch (void);				/* generated */
extern NCURSES_EXPORT(int) inchnstr (chtype *, int);			/* generated */
extern NCURSES_EXPORT(int) inchstr (chtype *);				/* generated */
extern NCURSES_EXPORT(WINDOW *) initscr (void);				/* implemented */
extern NCURSES_EXPORT(int) init_color (short,short,short,short);	/* implemented */
extern NCURSES_EXPORT(int) init_pair (short,short,short);		/* implemented */
extern NCURSES_EXPORT(int) innstr (char *, int);			/* generated */
extern NCURSES_EXPORT(int) insch (chtype);				/* generated */
extern NCURSES_EXPORT(int) insdelln (int);				/* generated */
extern NCURSES_EXPORT(int) insertln (void);				/* generated */
extern NCURSES_EXPORT(int) insnstr (const char *, int);			/* generated */
extern NCURSES_EXPORT(int) insstr (const char *);			/* generated */
extern NCURSES_EXPORT(int) instr (char *);				/* generated */
extern NCURSES_EXPORT(int) intrflush (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(bool) isendwin (void);				/* implemented */
extern NCURSES_EXPORT(bool) is_linetouched (WINDOW *,int);		/* implemented */
extern NCURSES_EXPORT(bool) is_wintouched (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(NCURSES_CONST char *) keyname (int);		/* implemented */
extern NCURSES_EXPORT(int) keypad (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(char) killchar (void);				/* implemented */
extern NCURSES_EXPORT(int) leaveok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(char *) longname (void);				/* implemented */
extern NCURSES_EXPORT(int) meta (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) move (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvaddch (int, int, const chtype);		/* generated */
extern NCURSES_EXPORT(int) mvaddchnstr (int, int, const chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvaddchstr (int, int, const chtype *);	/* generated */
extern NCURSES_EXPORT(int) mvaddnstr (int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvaddstr (int, int, const char *);		/* generated */
extern NCURSES_EXPORT(int) mvchgat (int, int, int, attr_t, short, const void *);	/* generated */
extern NCURSES_EXPORT(int) mvcur (int,int,int,int);			/* implemented */
extern NCURSES_EXPORT(int) mvdelch (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvderwin (WINDOW *, int, int);		/* implemented */
extern NCURSES_EXPORT(int) mvgetch (int, int);				/* generated */
extern NCURSES_EXPORT(int) mvgetnstr (int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvgetstr (int, int, char *);			/* generated */
extern NCURSES_EXPORT(int) mvhline (int, int, chtype, int);		/* generated */
extern NCURSES_EXPORT(chtype) mvinch (int, int);			/* generated */
extern NCURSES_EXPORT(int) mvinchnstr (int, int, chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvinchstr (int, int, chtype *);		/* generated */
extern NCURSES_EXPORT(int) mvinnstr (int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvinsch (int, int, chtype);			/* generated */
extern NCURSES_EXPORT(int) mvinsnstr (int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvinsstr (int, int, const char *);		/* generated */
extern NCURSES_EXPORT(int) mvinstr (int, int, char *);			/* generated */
extern NCURSES_EXPORT(int) mvprintw (int,int, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(3,4);
extern NCURSES_EXPORT(int) mvscanw (int,int, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(3,4);
extern NCURSES_EXPORT(int) mvvline (int, int, chtype, int);		/* generated */
extern NCURSES_EXPORT(int) mvwaddch (WINDOW *, int, int, const chtype);	/* generated */
extern NCURSES_EXPORT(int) mvwaddchnstr (WINDOW *, int, int, const chtype *, int);/* generated */
extern NCURSES_EXPORT(int) mvwaddchstr (WINDOW *, int, int, const chtype *);	/* generated */
extern NCURSES_EXPORT(int) mvwaddnstr (WINDOW *, int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwaddstr (WINDOW *, int, int, const char *);	/* generated */
extern NCURSES_EXPORT(int) mvwchgat (WINDOW *, int, int, int, attr_t, short, const void *);/* generated */
extern NCURSES_EXPORT(int) mvwdelch (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) mvwgetch (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) mvwgetnstr (WINDOW *, int, int, char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwgetstr (WINDOW *, int, int, char *);	/* generated */
extern NCURSES_EXPORT(int) mvwhline (WINDOW *, int, int, chtype, int);	/* generated */
extern NCURSES_EXPORT(int) mvwin (WINDOW *,int,int);			/* implemented */
extern NCURSES_EXPORT(chtype) mvwinch (WINDOW *, int, int);			/* generated */
extern NCURSES_EXPORT(int) mvwinchnstr (WINDOW *, int, int, chtype *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwinchstr (WINDOW *, int, int, chtype *);		/* generated */
extern NCURSES_EXPORT(int) mvwinnstr (WINDOW *, int, int, char *, int);		/* generated */
extern NCURSES_EXPORT(int) mvwinsch (WINDOW *, int, int, chtype);		/* generated */
extern NCURSES_EXPORT(int) mvwinsnstr (WINDOW *, int, int, const char *, int);	/* generated */
extern NCURSES_EXPORT(int) mvwinsstr (WINDOW *, int, int, const char *);		/* generated */
extern NCURSES_EXPORT(int) mvwinstr (WINDOW *, int, int, char *);		/* generated */
extern NCURSES_EXPORT(int) mvwprintw (WINDOW*,int,int, const char *,...)	/* implemented */
		GCC_PRINTFLIKE(4,5);
extern NCURSES_EXPORT(int) mvwscanw (WINDOW *,int,int, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(4,5);
extern NCURSES_EXPORT(int) mvwvline (WINDOW *,int, int, chtype, int);	/* generated */
extern NCURSES_EXPORT(int) napms (int);					/* implemented */
extern NCURSES_EXPORT(WINDOW *) newpad (int,int);				/* implemented */
extern NCURSES_EXPORT(SCREEN *) newterm (NCURSES_CONST char *,FILE *,FILE *);	/* implemented */
extern NCURSES_EXPORT(WINDOW *) newwin (int,int,int,int);			/* implemented */
extern NCURSES_EXPORT(int) nl (void);					/* implemented */
extern NCURSES_EXPORT(int) nocbreak (void);				/* implemented */
extern NCURSES_EXPORT(int) nodelay (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) noecho (void);				/* implemented */
extern NCURSES_EXPORT(int) nonl (void);					/* implemented */
extern NCURSES_EXPORT(void) noqiflush (void);				/* implemented */
extern NCURSES_EXPORT(int) noraw (void);				/* implemented */
extern NCURSES_EXPORT(int) notimeout (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) overlay (const WINDOW*,WINDOW *);		/* implemented */
extern NCURSES_EXPORT(int) overwrite (const WINDOW*,WINDOW *);		/* implemented */
extern NCURSES_EXPORT(int) pair_content (short,short*,short*);		/* implemented */
extern NCURSES_EXPORT(int) PAIR_NUMBER (int);				/* generated */
extern NCURSES_EXPORT(int) pechochar (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) pnoutrefresh (WINDOW*,int,int,int,int,int,int);/* implemented */
extern NCURSES_EXPORT(int) prefresh (WINDOW *,int,int,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) printw (const char *,...)			/* implemented */
		GCC_PRINTFLIKE(1,2);
extern NCURSES_EXPORT(int) putp (const char *);				/* implemented */
extern NCURSES_EXPORT(int) putwin (WINDOW *, FILE *);			/* implemented */
extern NCURSES_EXPORT(void) qiflush (void);				/* implemented */
extern NCURSES_EXPORT(int) raw (void);					/* implemented */
extern NCURSES_EXPORT(int) redrawwin (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) refresh (void);				/* generated */
extern NCURSES_EXPORT(int) resetty (void);				/* implemented */
extern NCURSES_EXPORT(int) reset_prog_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) reset_shell_mode (void);			/* implemented */
extern NCURSES_EXPORT(int) ripoffline (int, int (*)(WINDOW *, int));	/* implemented */
extern NCURSES_EXPORT(int) savetty (void);				/* implemented */
extern NCURSES_EXPORT(int) scanw (NCURSES_CONST char *,...)		/* implemented */
		GCC_SCANFLIKE(1,2);
extern NCURSES_EXPORT(int) scr_dump (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scr_init (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scrl (int);					/* generated */
extern NCURSES_EXPORT(int) scroll (WINDOW *);				/* generated */
extern NCURSES_EXPORT(int) scrollok (WINDOW *,bool);			/* implemented */
extern NCURSES_EXPORT(int) scr_restore (const char *);			/* implemented */
extern NCURSES_EXPORT(int) scr_set (const char *);			/* implemented */
extern NCURSES_EXPORT(int) setscrreg (int,int);				/* generated */
extern NCURSES_EXPORT(SCREEN *) set_term (SCREEN *);			/* implemented */
extern NCURSES_EXPORT(int) slk_attroff (const chtype);			/* implemented */
extern NCURSES_EXPORT(int) slk_attr_off (const attr_t, void *);		/* generated:WIDEC */
extern NCURSES_EXPORT(int) slk_attron (const chtype);			/* implemented */
extern NCURSES_EXPORT(int) slk_attr_on (attr_t,void*);			/* generated:WIDEC */
extern NCURSES_EXPORT(int) slk_attrset (const chtype);			/* implemented */
extern NCURSES_EXPORT(attr_t) slk_attr (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_attr_set (const attr_t,short,void*);	/* implemented */
extern NCURSES_EXPORT(int) slk_clear (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_color (short);				/* implemented */
extern NCURSES_EXPORT(int) slk_init (int);				/* implemented */
extern NCURSES_EXPORT(char *) slk_label (int);				/* implemented */
extern NCURSES_EXPORT(int) slk_noutrefresh (void);			/* implemented */
extern NCURSES_EXPORT(int) slk_refresh (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_restore (void);				/* implemented */
extern NCURSES_EXPORT(int) slk_set (int,const char *,int);		/* implemented */
extern NCURSES_EXPORT(int) slk_touch (void);				/* implemented */
extern NCURSES_EXPORT(int) standout (void);				/* generated */
extern NCURSES_EXPORT(int) standend (void);				/* generated */
extern NCURSES_EXPORT(int) start_color (void);				/* implemented */
extern NCURSES_EXPORT(WINDOW *) subpad (WINDOW *, int, int, int, int);	/* implemented */
extern NCURSES_EXPORT(WINDOW *) subwin (WINDOW *,int,int,int,int);	/* implemented */
extern NCURSES_EXPORT(int) syncok (WINDOW *, bool);			/* implemented */
extern NCURSES_EXPORT(chtype) termattrs (void);				/* implemented */
extern NCURSES_EXPORT(char *) termname (void);				/* implemented */
extern NCURSES_EXPORT(int) tigetflag (NCURSES_CONST char *);		/* implemented */
extern NCURSES_EXPORT(int) tigetnum (NCURSES_CONST char *);		/* implemented */
extern NCURSES_EXPORT(char *) tigetstr (NCURSES_CONST char *);		/* implemented */
extern NCURSES_EXPORT(void) timeout (int);				/* generated */
extern NCURSES_EXPORT(int) touchline (WINDOW *, int, int);		/* generated */
extern NCURSES_EXPORT(int) touchwin (WINDOW *);				/* generated */
extern NCURSES_EXPORT(char *) tparm (NCURSES_CONST char *, ...);	/* implemented */
extern NCURSES_EXPORT(int) typeahead (int);				/* implemented */
extern NCURSES_EXPORT(int) ungetch (int);				/* implemented */
extern NCURSES_EXPORT(int) untouchwin (WINDOW *);			/* generated */
extern NCURSES_EXPORT(void) use_env (bool);				/* implemented */
extern NCURSES_EXPORT(int) vidattr (chtype);				/* implemented */
extern NCURSES_EXPORT(int) vidputs (chtype, int (*)(int));		/* implemented */
extern NCURSES_EXPORT(int) vline (chtype, int);				/* generated */
extern NCURSES_EXPORT(int) vwprintw (WINDOW *, const char *,va_list);	/* implemented */
extern NCURSES_EXPORT(int) vw_printw (WINDOW *, const char *,va_list);	/* generated */
extern NCURSES_EXPORT(int) vwscanw (WINDOW *, NCURSES_CONST char *,va_list);	/* implemented */
extern NCURSES_EXPORT(int) vw_scanw (WINDOW *, NCURSES_CONST char *,va_list);	/* generated */
extern NCURSES_EXPORT(int) waddch (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) waddchnstr (WINDOW *,const chtype *,int);	/* implemented */
extern NCURSES_EXPORT(int) waddchstr (WINDOW *,const chtype *);		/* generated */
extern NCURSES_EXPORT(int) waddnstr (WINDOW *,const char *,int);	/* implemented */
extern NCURSES_EXPORT(int) waddstr (WINDOW *,const char *);		/* generated */
extern NCURSES_EXPORT(int) wattron (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattroff (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattrset (WINDOW *, int);			/* generated */
extern NCURSES_EXPORT(int) wattr_get (WINDOW *, attr_t *, short *, void *);	/* generated */
extern NCURSES_EXPORT(int) wattr_on (WINDOW *, attr_t, void *);		/* implemented */
extern NCURSES_EXPORT(int) wattr_off (WINDOW *, attr_t, void *);	/* implemented */
extern NCURSES_EXPORT(int) wattr_set (WINDOW *, attr_t, short, void *);	/* generated */
extern NCURSES_EXPORT(int) wbkgd (WINDOW *, chtype);			/* implemented */
extern NCURSES_EXPORT(void) wbkgdset (WINDOW *,chtype);			/* implemented */
extern NCURSES_EXPORT(int) wborder (WINDOW *,chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);	/* implemented */
extern NCURSES_EXPORT(int) wchgat (WINDOW *, int, attr_t, short, const void *);/* implemented */
extern NCURSES_EXPORT(int) wclear (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wclrtobot (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wclrtoeol (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wcolor_set (WINDOW*,short,void*);		/* implemented */
extern NCURSES_EXPORT(void) wcursyncup (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wdelch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wdeleteln (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) wechochar (WINDOW *, const chtype);		/* implemented */
extern NCURSES_EXPORT(int) werase (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wgetch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wgetnstr (WINDOW *,char *,int);		/* implemented */
extern NCURSES_EXPORT(int) wgetstr (WINDOW *, char *);			/* generated */
extern NCURSES_EXPORT(int) whline (WINDOW *, chtype, int);		/* implemented */
extern NCURSES_EXPORT(chtype) winch (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) winchnstr (WINDOW *, chtype *, int);		/* implemented */
extern NCURSES_EXPORT(int) winchstr (WINDOW *, chtype *);		/* generated */
extern NCURSES_EXPORT(int) winnstr (WINDOW *, char *, int);		/* implemented */
extern NCURSES_EXPORT(int) winsch (WINDOW *, chtype);			/* implemented */
extern NCURSES_EXPORT(int) winsdelln (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) winsertln (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) winsnstr (WINDOW *, const char *,int);	/* implemented */
extern NCURSES_EXPORT(int) winsstr (WINDOW *, const char *);		/* generated */
extern NCURSES_EXPORT(int) winstr (WINDOW *, char *);			/* generated */
extern NCURSES_EXPORT(int) wmove (WINDOW *,int,int);			/* implemented */
extern NCURSES_EXPORT(int) wnoutrefresh (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(int) wprintw (WINDOW *, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(2,3);
extern NCURSES_EXPORT(int) wredrawln (WINDOW *,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wrefresh (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(int) wscanw (WINDOW *, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(2,3);
extern NCURSES_EXPORT(int) wscrl (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) wsetscrreg (WINDOW *,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wstandout (WINDOW *);			/* generated */
extern NCURSES_EXPORT(int) wstandend (WINDOW *);			/* generated */
extern NCURSES_EXPORT(void) wsyncdown (WINDOW *);			/* implemented */
extern NCURSES_EXPORT(void) wsyncup (WINDOW *);				/* implemented */
extern NCURSES_EXPORT(void) wtimeout (WINDOW *,int);			/* implemented */
extern NCURSES_EXPORT(int) wtouchln (WINDOW *,int,int,int);		/* implemented */
extern NCURSES_EXPORT(int) wvline (WINDOW *,chtype,int);		/* implemented */

/*
 * vid_attr() was implemented originally based on the draft of XSI curses.
 */
#ifndef _XOPEN_SOURCE_EXTENDED
#define vid_attr(a,pair,opts) vidattr(a)
#endif

/* attributes */

#define NCURSES_ATTR_SHIFT       8
#define NCURSES_BITS(mask,shift) ((mask) << ((shift) + NCURSES_ATTR_SHIFT))

#define A_NORMAL	0L
#define A_ATTRIBUTES	NCURSES_BITS(~(1UL - 1UL),0)
#define A_CHARTEXT	(NCURSES_BITS(1UL,0) - 1UL)
#define A_COLOR		NCURSES_BITS(((1UL) << 8) - 1UL,0)
#define A_STANDOUT	NCURSES_BITS(1UL,8)
#define A_UNDERLINE	NCURSES_BITS(1UL,9)
#define A_REVERSE	NCURSES_BITS(1UL,10)
#define A_BLINK		NCURSES_BITS(1UL,11)
#define A_DIM		NCURSES_BITS(1UL,12)
#define A_BOLD		NCURSES_BITS(1UL,13)
#define A_ALTCHARSET	NCURSES_BITS(1UL,14)
#define A_INVIS		NCURSES_BITS(1UL,15)
#define A_PROTECT	NCURSES_BITS(1UL,16)
#define A_HORIZONTAL	NCURSES_BITS(1UL,17)
#define A_LEFT		NCURSES_BITS(1UL,18)
#define A_LOW		NCURSES_BITS(1UL,19)
#define A_RIGHT		NCURSES_BITS(1UL,20)
#define A_TOP		NCURSES_BITS(1UL,21)
#define A_VERTICAL	NCURSES_BITS(1UL,22)

#define COLOR_PAIR(n)	NCURSES_BITS(n, 0)
#define PAIR_NUMBER(a)	((int)(((a) & A_COLOR) >> NCURSES_ATTR_SHIFT))

/*
 * pseudo functions
 */
#define wgetstr(w, s)		wgetnstr(w, s, -1)
#define getnstr(s, n)		wgetnstr(stdscr, s, n)

#define setterm(term)		setupterm(term, 1, (int *)0)

#define fixterm()		reset_prog_mode()
#define resetterm()		reset_shell_mode()
#define saveterm()		def_prog_mode()
#define crmode()		cbreak()
#define nocrmode()		nocbreak()
#define gettmode()

#define getyx(win,y,x)   	(y = getcury(win), x = getcurx(win))
#define getbegyx(win,y,x)	(y = getbegy(win), x = getbegx(win))
#define getmaxyx(win,y,x)	(y = getmaxy(win), x = getmaxx(win))
#define getparyx(win,y,x)	(y = getpary(win), x = getparx(win))

#define getsyx(y,x) do { if(newscr->_leaveok) (y)=(x)=-1; \
			 else getyx(newscr,(y),(x)); \
		    } while(0)
#define setsyx(y,x) do { if((y)==-1 && (x)==-1) newscr->_leaveok=TRUE; \
			 else {newscr->_leaveok=FALSE;wmove(newscr,(y),(x));} \
		    } while(0)

/* It seems older SYSV curses versions define these */
#define getattrs(win)		((win)?(win)->_attrs:A_NORMAL)
#define getcurx(win)		((win)?(win)->_curx:ERR)
#define getcury(win)		((win)?(win)->_cury:ERR)
#define getbegx(win)		((win)?(win)->_begx:ERR)
#define getbegy(win)		((win)?(win)->_begy:ERR)
#define getmaxx(win)		((win)?((win)->_maxx + 1):ERR)
#define getmaxy(win)		((win)?((win)->_maxy + 1):ERR)
#define getparx(win)		((win)?(win)->_parx:ERR)
#define getpary(win)		((win)?(win)->_pary:ERR)

#define wstandout(win)      	(wattrset(win,A_STANDOUT))
#define wstandend(win)      	(wattrset(win,A_NORMAL))
#define wattr_set(win,a,p,opts) ((win)->_attrs = (((a) & ~A_COLOR) | COLOR_PAIR(p)), OK)

#define wattron(win,at)		wattr_on(win, (attr_t) at, (void *)0)
#define wattroff(win,at)	wattr_off(win, (attr_t) at, (void *)0)
#define wattrset(win,at)	((win)->_attrs = (at))

#define scroll(win)		wscrl(win,1)

#define touchwin(win)		wtouchln((win), 0, getmaxy(win), 1)
#define touchline(win, s, c)	wtouchln((win), s, c, 1)
#define untouchwin(win)		wtouchln((win), 0, getmaxy(win), 0)

#define box(win, v, h)		wborder(win, v, v, h, h, 0, 0, 0, 0)
#define border(ls, rs, ts, bs, tl, tr, bl, br)	wborder(stdscr, ls, rs, ts, bs, tl, tr, bl, br)
#define hline(ch, n)		whline(stdscr, ch, n)
#define vline(ch, n)		wvline(stdscr, ch, n)

#define winstr(w, s)		winnstr(w, s, -1)
#define winchstr(w, s)		winchnstr(w, s, -1)
#define winsstr(w, s)		winsnstr(w, s, -1)

#define redrawwin(win)		wredrawln(win, 0, (win)->_maxy+1)
#define waddstr(win,str)	waddnstr(win,str,-1)
#define waddchstr(win,str)	waddchnstr(win,str,-1)

/*
 * pseudo functions for standard screen
 */

#define addch(ch)		waddch(stdscr,ch)
#define addchnstr(str,n)	waddchnstr(stdscr,str,n)
#define addchstr(str)		waddchstr(stdscr,str)
#define addnstr(str,n)		waddnstr(stdscr,str,n)
#define addstr(str)		waddnstr(stdscr,str,-1)
#define attroff(at)		wattroff(stdscr,at)
#define attron(at)		wattron(stdscr,at)
#define attrset(at)		wattrset(stdscr,at)
#define attr_get(ap,cp,o)	wattr_get(stdscr,ap,cp,o)
#define attr_off(a,o)		wattr_off(stdscr,a,o)
#define attr_on(a,o)		wattr_on(stdscr,a,o)
#define attr_set(a,c,o)		wattr_set(stdscr,a,c,o)
#define bkgd(ch)		wbkgd(stdscr,ch)
#define bkgdset(ch)		wbkgdset(stdscr,ch)
#define chgat(n,a,c,o)		wchgat(stdscr,n,a,c,o)
#define clear()			wclear(stdscr)
#define clrtobot()		wclrtobot(stdscr)
#define clrtoeol()		wclrtoeol(stdscr)
#define color_set(c,o)		wcolor_set(stdscr,c,o)
#define delch()			wdelch(stdscr)
#define deleteln()		winsdelln(stdscr,-1)
#define echochar(c)		wechochar(stdscr,c)
#define erase()			werase(stdscr)
#define getch()			wgetch(stdscr)
#define getstr(str)		wgetstr(stdscr,str)
#define inch()			winch(stdscr)
#define inchnstr(s,n)		winchnstr(stdscr,s,n)
#define inchstr(s)		winchstr(stdscr,s)
#define innstr(s,n)		winnstr(stdscr,s,n)
#define insch(c)		winsch(stdscr,c)
#define insdelln(n)		winsdelln(stdscr,n)
#define insertln()		winsdelln(stdscr,1)
#define insnstr(s,n)		winsnstr(stdscr,s,n)
#define insstr(s)		winsstr(stdscr,s)
#define instr(s)		winstr(stdscr,s)
#define move(y,x)		wmove(stdscr,y,x)
#define refresh()		wrefresh(stdscr)
#define scrl(n)			wscrl(stdscr,n)
#define setscrreg(t,b)		wsetscrreg(stdscr,t,b)
#define standend()		wstandend(stdscr)
#define standout()		wstandout(stdscr)
#define timeout(delay)		wtimeout(stdscr,delay)
#define wdeleteln(win)		winsdelln(win,-1)
#define winsertln(win)		winsdelln(win,1)

/*
 * mv functions
 */

#define mvwaddch(win,y,x,ch)		(wmove(win,y,x) == ERR ? ERR : waddch(win,ch))
#define mvwaddchnstr(win,y,x,str,n)	(wmove(win,y,x) == ERR ? ERR : waddchnstr(win,str,n))
#define mvwaddchstr(win,y,x,str)	(wmove(win,y,x) == ERR ? ERR : waddchnstr(win,str,-1))
#define mvwaddnstr(win,y,x,str,n)	(wmove(win,y,x) == ERR ? ERR : waddnstr(win,str,n))
#define mvwaddstr(win,y,x,str)		(wmove(win,y,x) == ERR ? ERR : waddnstr(win,str,-1))
#define mvwdelch(win,y,x)		(wmove(win,y,x) == ERR ? ERR : wdelch(win))
#define mvwchgat(win,y,x,n,a,c,o)	(wmove(win,y,x) == ERR ? ERR : wchgat(win,n,a,c,o))
#define mvwgetch(win,y,x)		(wmove(win,y,x) == ERR ? ERR : wgetch(win))
#define mvwgetnstr(win,y,x,str,n)	(wmove(win,y,x) == ERR ? ERR : wgetnstr(win,str,n))
#define mvwgetstr(win,y,x,str)		(wmove(win,y,x) == ERR ? ERR : wgetstr(win,str))
#define mvwhline(win,y,x,c,n)		(wmove(win,y,x) == ERR ? ERR : whline(win,c,n))
#define mvwinch(win,y,x)		(wmove(win,y,x) == ERR ? (chtype)ERR : winch(win))
#define mvwinchnstr(win,y,x,s,n)	(wmove(win,y,x) == ERR ? ERR : winchnstr(win,s,n))
#define mvwinchstr(win,y,x,s)		(wmove(win,y,x) == ERR ? ERR : winchstr(win,s))
#define mvwinnstr(win,y,x,s,n)		(wmove(win,y,x) == ERR ? ERR : winnstr(win,s,n))
#define mvwinsch(win,y,x,c)		(wmove(win,y,x) == ERR ? ERR : winsch(win,c))
#define mvwinsnstr(win,y,x,s,n)		(wmove(win,y,x) == ERR ? ERR : winsnstr(win,s,n))
#define mvwinsstr(win,y,x,s)		(wmove(win,y,x) == ERR ? ERR : winsstr(win,s))
#define mvwinstr(win,y,x,s)		(wmove(win,y,x) == ERR ? ERR : winstr(win,s))
#define mvwvline(win,y,x,c,n)		(wmove(win,y,x) == ERR ? ERR : wvline(win,c,n))

#define mvaddch(y,x,ch)			mvwaddch(stdscr,y,x,ch)
#define mvaddchnstr(y,x,str,n)		mvwaddchnstr(stdscr,y,x,str,n)
#define mvaddchstr(y,x,str)		mvwaddchstr(stdscr,y,x,str)
#define mvaddnstr(y,x,str,n)		mvwaddnstr(stdscr,y,x,str,n)
#define mvaddstr(y,x,str)		mvwaddstr(stdscr,y,x,str)
#define mvchgat(y,x,n,a,c,o)		mvwchgat(stdscr,y,x,n,a,c,o)
#define mvdelch(y,x)			mvwdelch(stdscr,y,x)
#define mvgetch(y,x)			mvwgetch(stdscr,y,x)
#define mvgetnstr(y,x,str,n)		mvwgetnstr(stdscr,y,x,str,n)
#define mvgetstr(y,x,str)		mvwgetstr(stdscr,y,x,str)
#define mvhline(y,x,c,n)		mvwhline(stdscr,y,x,c,n)
#define mvinch(y,x)			mvwinch(stdscr,y,x)
#define mvinchnstr(y,x,s,n)		mvwinchnstr(stdscr,y,x,s,n)
#define mvinchstr(y,x,s)		mvwinchstr(stdscr,y,x,s)
#define mvinnstr(y,x,s,n)		mvwinnstr(stdscr,y,x,s,n)
#define mvinsch(y,x,c)			mvwinsch(stdscr,y,x,c)
#define mvinsnstr(y,x,s,n)		mvwinsnstr(stdscr,y,x,s,n)
#define mvinsstr(y,x,s)			mvwinsstr(stdscr,y,x,s)
#define mvinstr(y,x,s)			mvwinstr(stdscr,y,x,s)
#define mvvline(y,x,c,n)		mvwvline(stdscr,y,x,c,n)

/*
 * Some wide-character functions do not depend on the extensions.
 */
#define getbkgd(win)                    ((win)->_bkgd)

#define slk_attr_off(a,v)		((v) ? ERR : slk_attroff(a))
#define slk_attr_on(a,v)		((v) ? ERR : slk_attron(a))

#define wattr_get(win,a,p,opts)		((void)((a) != 0 && (*(a) = (win)->_attrs)), \
					 (void)((p) != 0 && (*(p) = PAIR_NUMBER((win)->_attrs))), \
					 OK)

/*
 * XSI curses deprecates SVr4 vwprintw/vwscanw, which are supposed to use
 * varargs.h.  It adds new calls vw_printw/vw_scanw, which are supposed to
 * use POSIX stdarg.h.  The ncurses versions of vwprintw/vwscanw already
 * use stdarg.h, so...
 */
#define vw_printw		vwprintw
#define vw_scanw		vwscanw

/*
 * Export fallback function for use in C++ binding.
 */
#if !1
#define vsscanf(a,b,c) _nc_vsscanf(a,b,c)
NCURSES_EXPORT(int) vsscanf(const char *, const char *, va_list);
#endif

/*
 * Pseudo-character tokens outside ASCII range.  The curses wgetch() function
 * will return any given one of these only if the corresponding k- capability
 * is defined in your terminal's terminfo entry.
 *
 * Some keys (KEY_A1, etc) are arranged like this:
 *	a1     up    a3
 *	left   b2    right
 *	c1     down  c3
 *
 * A few key codes do not depend upon the terminfo entry.
 */
#define KEY_CODE_YES	0400		/* A wchar_t contains a key code */
#define KEY_MIN		0401		/* Minimum curses key */
#define KEY_BREAK	0401		/* Break key (unreliable) */
#define KEY_SRESET	0530		/* Soft (partial) reset (unreliable) */
#define KEY_RESET	0531		/* Reset or hard reset (unreliable) */
/*
 * These definitions were generated by /build/buildd/ncurses-5.4/include/MKkey_defs.sh /build/buildd/ncurses-5.4/include/Caps
 */
#define KEY_DOWN	0402		/* down-arrow key */
#define KEY_UP		0403		/* up-arrow key */
#define KEY_LEFT	0404		/* left-arrow key */
#define KEY_RIGHT	0405		/* right-arrow key */
#define KEY_HOME	0406		/* home key */
#define KEY_BACKSPACE	0407		/* backspace key */
#define KEY_F0		0410		/* Function keys.  Space for 64 */
#define KEY_F(n)	(KEY_F0+(n))	/* Value of function key n */
#define KEY_DL		0510		/* delete-line key */
#define KEY_IL		0511		/* insert-line key */
#define KEY_DC		0512		/* delete-character key */
#define KEY_IC		0513		/* insert-character key */
#define KEY_EIC		0514		/* sent by rmir or smir in insert mode */
#define KEY_CLEAR	0515		/* clear-screen or erase key */
#define KEY_EOS		0516		/* clear-to-end-of-screen key */
#define KEY_EOL		0517		/* clear-to-end-of-line key */
#define KEY_SF		0520		/* scroll-forward key */
#define KEY_SR		0521		/* scroll-backward key */
#define KEY_NPAGE	0522		/* next-page key */
#define KEY_PPAGE	0523		/* previous-page key */
#define KEY_STAB	0524		/* set-tab key */
#define KEY_CTAB	0525		/* clear-tab key */
#define KEY_CATAB	0526		/* clear-all-tabs key */
#define KEY_ENTER	0527		/* enter/send key */
#define KEY_PRINT	0532		/* print key */
#define KEY_LL		0533		/* lower-left key (home down) */
#define KEY_A1		0534		/* upper left of keypad */
#define KEY_A3		0535		/* upper right of keypad */
#define KEY_B2		0536		/* center of keypad */
#define KEY_C1		0537		/* lower left of keypad */
#define KEY_C3		0540		/* lower right of keypad */
#define KEY_BTAB	0541		/* back-tab key */
#define KEY_BEG		0542		/* begin key */
#define KEY_CANCEL	0543		/* cancel key */
#define KEY_CLOSE	0544		/* close key */
#define KEY_COMMAND	0545		/* command key */
#define KEY_COPY	0546		/* copy key */
#define KEY_CREATE	0547		/* create key */
#define KEY_END		0550		/* end key */
#define KEY_EXIT	0551		/* exit key */
#define KEY_FIND	0552		/* find key */
#define KEY_HELP	0553		/* help key */
#define KEY_MARK	0554		/* mark key */
#define KEY_MESSAGE	0555		/* message key */
#define KEY_MOVE	0556		/* move key */
#define KEY_NEXT	0557		/* next key */
#define KEY_OPEN	0560		/* open key */
#define KEY_OPTIONS	0561		/* options key */
#define KEY_PREVIOUS	0562		/* previous key */
#define KEY_REDO	0563		/* redo key */
#define KEY_REFERENCE	0564		/* reference key */
#define KEY_REFRESH	0565		/* refresh key */
#define KEY_REPLACE	0566		/* replace key */
#define KEY_RESTART	0567		/* restart key */
#define KEY_RESUME	0570		/* resume key */
#define KEY_SAVE	0571		/* save key */
#define KEY_SBEG	0572		/* shifted begin key */
#define KEY_SCANCEL	0573		/* shifted cancel key */
#define KEY_SCOMMAND	0574		/* shifted command key */
#define KEY_SCOPY	0575		/* shifted copy key */
#define KEY_SCREATE	0576		/* shifted create key */
#define KEY_SDC		0577		/* shifted delete-character key */
#define KEY_SDL		0600		/* shifted delete-line key */
#define KEY_SELECT	0601		/* select key */
#define KEY_SEND	0602		/* shifted end key */
#define KEY_SEOL	0603		/* shifted clear-to-end-of-line key */
#define KEY_SEXIT	0604		/* shifted exit key */
#define KEY_SFIND	0605		/* shifted find key */
#define KEY_SHELP	0606		/* shifted help key */
#define KEY_SHOME	0607		/* shifted home key */
#define KEY_SIC		0610		/* shifted insert-character key */
#define KEY_SLEFT	0611		/* shifted left-arrow key */
#define KEY_SMESSAGE	0612		/* shifted message key */
#define KEY_SMOVE	0613		/* shifted move key */
#define KEY_SNEXT	0614		/* shifted next key */
#define KEY_SOPTIONS	0615		/* shifted options key */
#define KEY_SPREVIOUS	0616		/* shifted previous key */
#define KEY_SPRINT	0617		/* shifted print key */
#define KEY_SREDO	0620		/* shifted redo key */
#define KEY_SREPLACE	0621		/* shifted replace key */
#define KEY_SRIGHT	0622		/* shifted right-arrow key */
#define KEY_SRSUME	0623		/* shifted resume key */
#define KEY_SSAVE	0624		/* shifted save key */
#define KEY_SSUSPEND	0625		/* shifted suspend key */
#define KEY_SUNDO	0626		/* shifted undo key */
#define KEY_SUSPEND	0627		/* suspend key */
#define KEY_UNDO	0630		/* undo key */
#define KEY_MOUSE	0631		/* Mouse event has occurred */
#define KEY_RESIZE	0632		/* Terminal resize event */
#define KEY_EVENT	0633		/* We were interrupted by an event */

#define KEY_MAX		0777		/* Maximum key value is 0633 */
/* $Id: curses.tail,v 1.8 2002/11/02 20:26:26 tom Exp $ */

/* mouse interface */
#define NCURSES_MOUSE_VERSION	1

/* event masks */
#define	BUTTON1_RELEASED	000000000001L
#define	BUTTON1_PRESSED		000000000002L
#define	BUTTON1_CLICKED		000000000004L
#define	BUTTON1_DOUBLE_CLICKED	000000000010L
#define	BUTTON1_TRIPLE_CLICKED	000000000020L
#define BUTTON1_RESERVED_EVENT	000000000040L
#define	BUTTON2_RELEASED	000000000100L
#define	BUTTON2_PRESSED		000000000200L
#define	BUTTON2_CLICKED		000000000400L
#define	BUTTON2_DOUBLE_CLICKED	000000001000L
#define	BUTTON2_TRIPLE_CLICKED	000000002000L
#define BUTTON2_RESERVED_EVENT	000000004000L
#define	BUTTON3_RELEASED	000000010000L
#define	BUTTON3_PRESSED		000000020000L
#define	BUTTON3_CLICKED		000000040000L
#define	BUTTON3_DOUBLE_CLICKED	000000100000L
#define	BUTTON3_TRIPLE_CLICKED	000000200000L
#define BUTTON3_RESERVED_EVENT	000000400000L
#define	BUTTON4_RELEASED	000001000000L
#define	BUTTON4_PRESSED		000002000000L
#define	BUTTON4_CLICKED		000004000000L
#define	BUTTON4_DOUBLE_CLICKED	000010000000L
#define	BUTTON4_TRIPLE_CLICKED	000020000000L
#define BUTTON4_RESERVED_EVENT	000040000000L
#define BUTTON_CTRL		000100000000L
#define BUTTON_SHIFT		000200000000L
#define BUTTON_ALT		000400000000L
#define	ALL_MOUSE_EVENTS	000777777777L
#define	REPORT_MOUSE_POSITION	001000000000L

/* macros to extract single event-bits from masks */
#define	BUTTON_RELEASE(e, x)		((e) & (001 << (6 * ((x) - 1))))
#define	BUTTON_PRESS(e, x)		((e) & (002 << (6 * ((x) - 1))))
#define	BUTTON_CLICK(e, x)		((e) & (004 << (6 * ((x) - 1))))
#define	BUTTON_DOUBLE_CLICK(e, x)	((e) & (010 << (6 * ((x) - 1))))
#define	BUTTON_TRIPLE_CLICK(e, x)	((e) & (020 << (6 * ((x) - 1))))
#define	BUTTON_RESERVED_EVENT(e, x)	((e) & (040 << (6 * ((x) - 1))))

typedef unsigned long mmask_t;

typedef struct
{
    short id;		/* ID to distinguish multiple devices */
    int x, y, z;	/* event coordinates (character-cell) */
    mmask_t bstate;	/* button state bits */
}
MEVENT;

extern NCURSES_EXPORT(int) getmouse (MEVENT *);
extern NCURSES_EXPORT(int) ungetmouse (MEVENT *);
extern NCURSES_EXPORT(mmask_t) mousemask (mmask_t, mmask_t *);
extern NCURSES_EXPORT(bool) wenclose (const WINDOW *, int, int);
extern NCURSES_EXPORT(int) mouseinterval (int);
extern NCURSES_EXPORT(bool) wmouse_trafo (const WINDOW* win,int* y, int* x, bool to_screen);
extern NCURSES_EXPORT(bool) mouse_trafo (int*, int*, bool);              /* generated */

#define mouse_trafo(y,x,to_screen) wmouse_trafo(stdscr,y,x,to_screen)

/* other non-XSI functions */

extern NCURSES_EXPORT(int) mcprint (char *, int);	/* direct data to printer */
extern NCURSES_EXPORT(int) has_key (int);		/* do we have given key? */

/* Debugging : use with libncurses_g.a */

extern NCURSES_EXPORT(void) _tracef (const char *, ...) GCC_PRINTFLIKE(1,2);
extern NCURSES_EXPORT(void) _tracedump (const char *, WINDOW *);
extern NCURSES_EXPORT(char *) _traceattr (attr_t);
extern NCURSES_EXPORT(char *) _traceattr2 (int, chtype);
extern NCURSES_EXPORT(char *) _nc_tracebits (void);
extern NCURSES_EXPORT(char *) _tracechar (int);
extern NCURSES_EXPORT(char *) _tracechtype (chtype);
extern NCURSES_EXPORT(char *) _tracechtype2 (int, chtype);
#ifdef _XOPEN_SOURCE_EXTENDED
#define _tracech_t		_tracecchar_t
extern NCURSES_EXPORT(char *) _tracecchar_t (const cchar_t *);
#define _tracech_t2		_tracecchar_t2
extern NCURSES_EXPORT(char *) _tracecchar_t2 (int, const cchar_t *);
#else
#define _tracech_t		_tracechtype
#define _tracech_t2		_tracechtype2
#endif
extern NCURSES_EXPORT(char *) _tracemouse (const MEVENT *);
extern NCURSES_EXPORT(void) trace (const unsigned int);

/* trace masks */
#define TRACE_DISABLE	0x0000	/* turn off tracing */
#define TRACE_TIMES	0x0001	/* trace user and system times of updates */
#define TRACE_TPUTS	0x0002	/* trace tputs calls */
#define TRACE_UPDATE	0x0004	/* trace update actions, old & new screens */
#define TRACE_MOVE	0x0008	/* trace cursor moves and scrolls */
#define TRACE_CHARPUT	0x0010	/* trace all character outputs */
#define TRACE_ORDINARY	0x001F	/* trace all update actions */
#define TRACE_CALLS	0x0020	/* trace all curses calls */
#define TRACE_VIRTPUT	0x0040	/* trace virtual character puts */
#define TRACE_IEVENT	0x0080	/* trace low-level input processing */
#define TRACE_BITS	0x0100	/* trace state of TTY control bits */
#define TRACE_ICALLS	0x0200	/* trace internal/nested calls */
#define TRACE_CCALLS	0x0400	/* trace per-character calls */
#define TRACE_DATABASE	0x0800	/* trace read/write of terminfo/termcap data */
#define TRACE_ATTRS	0x1000	/* trace attribute updates */

#define TRACE_SHIFT	13	/* number of bits in the trace masks */
#define TRACE_MAXIMUM	((1 << TRACE_SHIFT) - 1) /* maximum trace level */

#if defined(TRACE) || defined(NCURSES_TEST)
extern NCURSES_EXPORT_VAR(int) _nc_optimize_enable;		/* enable optimizations */
#ifdef _XOPEN_SOURCE_EXTENDED
extern NCURSES_EXPORT(const char *) _nc_viswbuf(const wchar_t *);
#endif
extern NCURSES_EXPORT(const char *) _nc_visbuf (const char *);
#define OPTIMIZE_MVCUR		0x01	/* cursor movement optimization */
#define OPTIMIZE_HASHMAP	0x02	/* diff hashing to detect scrolls */
#define OPTIMIZE_SCROLL		0x04	/* scroll optimization */
#define OPTIMIZE_ALL		0xff	/* enable all optimizations (dflt) */
#endif

#ifdef __cplusplus

/* these names conflict with STL */
#undef box
#undef clear
#undef erase
#undef move
#undef refresh

}
#endif

#endif /* __NCURSES_H */
