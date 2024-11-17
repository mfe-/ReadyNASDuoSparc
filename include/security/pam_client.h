/*
 * $Id: pam_client.h,v 1.4 2002/09/15 21:30:26 hartmans Exp $
 *
 * Copyright (c) 1999 Andrew G. Morgan <morgan@linux.kernel.org>
 *
 * This header file provides the prototypes for the PAM client API
 */

#ifndef PAM_CLIENT_H
#define PAM_CLIENT_H

#ifdef __cplusplus 
extern "C" { 
#endif /* def __cplusplus */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* opaque agent handling structure */

typedef struct pamc_handle_s *pamc_handle_t;

/* binary prompt structure pointer */
#ifndef __u32
# define __u32  unsigned int
#endif
#ifndef __u8
# define __u8  unsigned char
#endif
typedef struct { __u32 length; __u8 control; } *pamc_bp_t;

/*
 * functions provided by libpamc
 */

/*
 * Initialize the agent abstraction library
 */

pamc_handle_t pamc_start(void);

/*
 * Terminate the authentication process
 */

int pamc_end(pamc_handle_t *pch);

/*
 * force the loading of a specified agent
 */

int pamc_load(pamc_handle_t pch, const char *agent_id);

/*
 * Single conversation interface for binary prompts
 */

int pamc_converse(pamc_handle_t pch, pamc_bp_t *prompt_p);

/*
 * disable an agent
 */

int pamc_disable(pamc_handle_t pch, const char *agent_id);

/*
 * obtain a list of available agents
 */

char **pamc_list_agents(pamc_handle_t pch);

/*
 * PAM_BP_ MACROS for creating, destroying and manipulating binary prompts
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef PAM_BP_ASSERT
# define PAM_BP_ASSERT(x)   do { printf(__FILE__ "(%d): %s\n", \
					__LINE__, x) ; exit(1); } while (0)
#endif /* PAM_BP_ASSERT */

#ifndef PAM_BP_CALLOC
# define PAM_BP_CALLOC      calloc
#endif /* PAM_BP_CALLOC */

#ifndef PAM_BP_FREE
# define PAM_BP_FREE        free
#endif /* PAM_BP_FREE */

#define __PAM_BP_WOCTET(x,y)  (*((y) + (__u8 *)(x)))
#define __PAM_BP_ROCTET(x,y)  (*((y) + (const __u8 *)(x)))

#define PAM_BP_MIN_SIZE       (sizeof(__u32) + sizeof(__u8))
#define PAM_BP_MAX_LENGTH     0x20000                   /* an advisory limit */
#define PAM_BP_WCONTROL(x)    (__PAM_BP_WOCTET(x,4))
#define PAM_BP_RCONTROL(x)    (__PAM_BP_ROCTET(x,4))
#define PAM_BP_SIZE(x)        ((__PAM_BP_ROCTET(x,0)<<24)+      \
			       (__PAM_BP_ROCTET(x,1)<<16)+      \
			       (__PAM_BP_ROCTET(x,2)<< 8)+      \
			       (__PAM_BP_ROCTET(x,3)    ))
#define PAM_BP_LENGTH(x)      (PAM_BP_SIZE(x) - PAM_BP_MIN_SIZE)
#define PAM_BP_WDATA(x)       (PAM_BP_MIN_SIZE + (__u8 *) (x))
#define PAM_BP_RDATA(x)       (PAM_BP_MIN_SIZE + (const __u8 *) (x))

/* Note, this macro always '\0' terminates renewed packets */

#define PAM_BP_RENEW(old_p, cntrl, data_length)                            \
do {                                                                       \
    if (old_p) {                                                           \
	if (*(old_p)) {                                                    \
	    __u32 __size;                                                  \
            __size = PAM_BP_SIZE(*(old_p));                                \
	    memset(*(old_p), 0, __size);                                   \
	    PAM_BP_FREE(*(old_p));                                         \
	}                                                                  \
	if (cntrl) {                                                       \
	    __u32 __size;                                                  \
                                                                           \
	    __size = PAM_BP_MIN_SIZE + data_length;                        \
	    if ((*(old_p) = PAM_BP_CALLOC(1, 1+__size))) {                 \
 		__PAM_BP_WOCTET(*(old_p), 3) =  __size      & 0xFF;        \
		__PAM_BP_WOCTET(*(old_p), 2) = (__size>>=8) & 0xFF;        \
		__PAM_BP_WOCTET(*(old_p), 1) = (__size>>=8) & 0xFF;        \
		__PAM_BP_WOCTET(*(old_p), 0) = (__size>>=8) & 0xFF;        \
		(*(old_p))->control = cntrl;                               \
	    } else {                                                       \
		PAM_BP_ASSERT("out of memory for binary prompt");          \
	    }                                                              \
	} else {                                                           \
	    *old_p = NULL;                                                 \
	}                                                                  \
    } else {                                                               \
	PAM_BP_ASSERT("programming error, invalid binary prompt pointer"); \
    }                                                                      \
} while (0)

#define PAM_BP_FILL(prmpt, offset, length, data)                           \
do {                                                                       \
    size_t bp_length;                                                      \
    __u8 *prompt = (__u8 *) (prmpt);                                       \
    bp_length = PAM_BP_LENGTH(prompt);                                     \
    if (bp_length < ((length)+(offset))) {                                 \
	PAM_BP_ASSERT("attempt to write over end of prompt");              \
    }                                                                      \
    memcpy((offset) + PAM_BP_WDATA(prompt), (data), (length));             \
} while (0)

#define PAM_BP_EXTRACT(prmpt, offset, length, data)                        \
do {                                                                       \
    size_t __bp_length;                                                    \
    const __u8 *__prompt = (const __u8 *) (prmpt);                         \
    __bp_length = PAM_BP_LENGTH(__prompt);                                 \
    if (((offset) < 0) || (__bp_length < ((length)+(offset)))              \
	|| ((length) < 0)) {                                               \
	PAM_BP_ASSERT("invalid extraction from prompt");                   \
    }                                                                      \
    memcpy((data), (offset) + PAM_BP_RDATA(__prompt), (length));           \
} while (0)

#ifdef __cplusplus
}
#endif

/* Control types */

#define PAM_BPC_FALSE   0
#define PAM_BPC_TRUE    1

#define PAM_BPC_OK      0x01   /* continuation packet   */
#define PAM_BPC_SELECT  0x02   /* initialization packet */
#define PAM_BPC_DONE    0x03   /* termination packet    */
#define PAM_BPC_FAIL    0x04   /* unable to execute     */

/* The following control characters are only legal for echanges
   between an agent and a client (it is the responsibility of the
   client to enforce this rule in the face of a rogue server): */

#define PAM_BPC_GETENV  0x41   /* obtain client env.var */
#define PAM_BPC_PUTENV  0x42   /* set client env.var    */
#define PAM_BPC_TEXT    0x43   /* display message       */
#define PAM_BPC_ERROR   0x44   /* display error message */
#define PAM_BPC_PROMPT  0x45   /* echo'd text prompt    */
#define PAM_BPC_PASS    0x46   /* non-echo'd text prompt*/

/* quick check for prompts that are legal for the client (by
   implication the server too) to send to libpamc */

#define PAM_BPC_FOR_CLIENT(/* pamc_bp_t */ prompt)                            \
    (((prompt)->control <= PAM_BPC_FAIL && (prompt)->control >= PAM_BPC_OK)   \
     ? PAM_BPC_TRUE:PAM_BPC_FALSE)

#ifdef __cplusplus
}
#endif /* def __cplusplus */

#endif /* PAM_CLIENT_H */
