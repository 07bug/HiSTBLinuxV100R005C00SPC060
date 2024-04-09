#ifndef COMMON_H
#define COMMON_H

#include <limits.h>
#include <stdbool.h>


/* True if the real type T is signed.  */
#define TYPE_SIGNED(t) (! ((t) 0 < (t) -1))
#define TYPE_WIDTH(t) (sizeof (t) * CHAR_BIT)
#define TYPE_MINIMUM(t) ((t) ~ TYPE_MAXIMUM (t))
#define TYPE_MAXIMUM(t)                                                 \
   ((t) (! TYPE_SIGNED (t)                                               \
         ? (t) -1                                                        \
         : ((((t) 1 << (sizeof (t) * CHAR_BIT - 2)) - 1) * 2 + 1)))

#define _GL_SIGNED_TYPE_OR_EXPR(t) TYPE_SIGNED (__typeof__ (t))
#define INT_BITS_STRLEN_BOUND(b) (((b) * 146 + 484) / 485)
#define INT_STRLEN_BOUND(t)                                     \
  (INT_BITS_STRLEN_BOUND (TYPE_WIDTH (t) - _GL_SIGNED_TYPE_OR_EXPR (t)) \
   + _GL_SIGNED_TYPE_OR_EXPR (t))

/* Bound on buffer size needed to represent an integer type or expression T,
   including the terminating null.  */
#define INT_BUFSIZE_BOUND(t) (INT_STRLEN_BOUND (t) + 1)

#ifndef __strtol
# define __strtol strtol
# define __strtol_t unsigned long int
# define __xstrtol xstrtol
# define STRTOL_T_MINIMUM LONG_MIN
# define STRTOL_T_MAXIMUM LONG_MAX
#endif

#define STREQ(a, b) (strcmp (a, b) == 0)
#define xalloc_oversized(n, s) __xalloc_oversized (n, s)
#define __xalloc_oversized(n, s) \
  ((size_t) (PTRDIFF_MAX < SIZE_MAX ? PTRDIFF_MAX : SIZE_MAX - 1) / (s) < (n))
#if 0
# define X2NREALLOC(P, PN) ((void) verify_true (sizeof *(P) != 1), \
                           x2nrealloc (P, PN, sizeof *(P)))
#else
# define X2NREALLOC(P, PN)  x2nrealloc (P, PN, sizeof *(P))
#endif

#define xalloc_oversized(n, s) __xalloc_oversized (n, s)
#define __xalloc_oversized(n, s) \
  ((size_t) (PTRDIFF_MAX < SIZE_MAX ? PTRDIFF_MAX : SIZE_MAX - 1) / (s) < (n))

#define umaxtostr anytostr


static inline unsigned char to_uchar (char ch) { return ch; }
 
extern const char *ProName;

typedef enum strtol_error
{
	LONGINT_OK = 0,
	/* These two values can be ORed together, to indicate that both
		errors occurred.  */
	LONGINT_OVERFLOW = 1,
	LONGINT_INVALID_SUFFIX_CHAR = 2,
	LONGINT_INVALID_SUFFIX_CHAR_WITH_OVERFLOW = (LONGINT_INVALID_SUFFIX_CHAR
													| LONGINT_OVERFLOW),
	LONGINT_INVALID = 4
} strtol_error;

enum
{
	EXIT_TIMEDOUT = 124, /* Time expired before child completed.  */
	EXIT_CANCELED = 125, /* Internal error prior to exec attempt.  */
	EXIT_CANNOT_INVOKE = 126, /* Program located, but not usable.  */
	EXIT_ENOENT = 127 /* Could not find program to exec.  */
};

enum
{
	GROUPS = UCHAR_MAX + 1,
	USERSPEC,
	GETOPT_HELP_CHAR = (CHAR_MIN - 2)
};

extern unsigned int error_message_count;

int is_root (const char* dir);
void set_pro_name(const char *argv0);
void alloc_exit (void);
void *xmemdup (void const *p, size_t s);
char *xstrdup (char const *string);
void *x2nrealloc (void *p, size_t *pn, size_t s);
strtol_error xstrtoul (const char *s, char **ptr, int strtol_base,
			__strtol_t *val, const char *valid_suffixes);
void error (int status, int errnum, const char *message, ...);
void print_errno_message (int errnum);
char * __attribute_warn_unused_result__ anytostr (int i, char *buf);



#endif