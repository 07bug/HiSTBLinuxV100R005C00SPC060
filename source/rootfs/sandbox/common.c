#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>

#include "common.h"
#include "userspec.h"


#ifdef NDEBUG
# define assure(E) ((void) (0 && (E)))
#else
# define assure(E) assert (E)
#endif

#define MAXGID TYPE_MAXIMUM(gid_t)



const char *ProName = NULL;
unsigned int error_message_count;


/* Only do chroot specific actions if actually changing root.
  The main difference here is that we don't change working dir.*/
int is_root (const char* dir)
{
	int ret = 0;
	struct stat root, arg;

	ret = lstat ("/", &root);
	if(ret)
		error (EXIT_CANCELED, errno, "failed to get attributes of %s",
				"/");

	ret = lstat (dir, &arg);
	if(ret)
		error (EXIT_CANCELED, errno, "failed to get attributes of %s",
				dir);

	ret = root.st_ino == arg.st_ino &&
		  root.st_dev == root.st_dev;

  return ret;
}

void set_pro_name(const char *argv0)
{

	const char *slash;
	const char *base;

	if (argv0 == NULL)
		abort ();

	slash = strrchr (argv0, '/');
	base = (slash != NULL ? slash + 1 : argv0);

	if (base - argv0 >= 7 && strncmp (base - 7, "/.libs/", 7) == 0)
	{
		argv0 = base;
		if (strncmp (base, "lt-", 3) == 0)
		{
			argv0 = base + 3;
		}
	}

	ProName = argv0;
}

void *xmalloc (size_t n)
{
	void *p = malloc (n);
	if (!p && n != 0)
		alloc_exit ();
	return p;
}

void *xmemdup (void const *p, size_t s)
{
	return memcpy (xmalloc (s), p, s);
}

char *xstrdup (char const *string)
{
	return xmemdup (string, strlen (string) + 1);
}

static strtol_error bkm_scale(__strtol_t *x, int scale_factor)
{
	if(TYPE_SIGNED (__strtol_t) && *x < LONG_MIN / scale_factor)
	{
		*x = LONG_MIN;
		return LONGINT_OVERFLOW;
	}
	if(LONG_MAX / scale_factor < *x)
	{
		*x = LONG_MAX;
		return LONGINT_OVERFLOW;
	}
	*x *= scale_factor;
	return LONGINT_OK;
}

static strtol_error bkm_scale_by_power(__strtol_t *x, int base, int power)
{
	strtol_error err = LONGINT_OK;
	while(power--)
	err |= bkm_scale (x, base);
	return err;
}

strtol_error xstrtoul (const char *s, char **ptr, int strtol_base,
			__strtol_t *val, const char *valid_suffixes)
{
	char *t_ptr;
	char **p;
	__strtol_t tmp;
	strtol_error err = LONGINT_OK;

	assure (0 <= strtol_base && strtol_base <= 36);

	p = (ptr ? ptr : &t_ptr);

	errno = 0;

	if(!TYPE_SIGNED(__strtol_t))
	{
		const char *q = s;
		unsigned char ch = *q;
		while (isspace (ch))
			ch = *++q;
		if(ch == '-')
		return LONGINT_INVALID;
	}

	tmp = strtol(s, p, strtol_base);

	if(*p == s)
	{
		/* If there is no number but there is a valid suffix, assume the
		  number is 1.  The string is invalid otherwise.  */
		if(valid_suffixes && **p && strchr (valid_suffixes, **p))
			tmp = 1;
		else
			return LONGINT_INVALID;
	}
	else if (errno != 0)
	{
		if(errno != ERANGE)
			return LONGINT_INVALID;
		err = LONGINT_OVERFLOW;
		}

	/* Let valid_suffixes == NULL mean "allow any suffix".  */
	/* FIXME: update all callers except the ones that allow suffixes
	  after the number, changing last parameter NULL to "".  */
	if(!valid_suffixes)
	{
		*val = tmp;
		return err;
	}

	if(**p != '\0')
	{
		int base = 1024;
		int suffixes = 1;
		strtol_error overflow;

		if(!strchr (valid_suffixes, **p))
		{
			*val = tmp;
			return err | LONGINT_INVALID_SUFFIX_CHAR;
		}

		switch (**p)
		{
		case 'E': case 'G': case 'g': case 'k': case 'K': case 'M': case 'm':
		case 'P': case 'T': case 't': case 'Y': case 'Z':

			/* The "valid suffix" '0' is a special flag meaning that
			  an optional second suffix is allowed, which can change
			  the base.  A suffix "B" (e.g. "100MB") stands for a power
			  of 1000, whereas a suffix "iB" (e.g. "100MiB") stands for
			  a power of 1024.  If no suffix (e.g. "100M"), assume
			  power-of-1024.  */

			if (strchr (valid_suffixes, '0'))
				switch (p[0][1])
				{
				case 'i':
					if (p[0][2] == 'B')
						suffixes += 2;
					break;

				case 'B':
				case 'D': /* 'D' is obsolescent */
					base = 1000;
					suffixes++;
					break;
				}
		}

		switch (**p)
		{
		case 'b':
			overflow = bkm_scale (&tmp, 512);
			break;

		case 'B':
			/* This obsolescent first suffix is distinct from the 'B'
			  second suffix above.  E.g., 'tar -L 1000B' means change
			  the tape after writing 1000 KiB of data.  */
			overflow = bkm_scale (&tmp, 1024);
			break;

		case 'c':
			overflow = LONGINT_OK;
			break;

		case 'E': /* exa or exbi */
			overflow = bkm_scale_by_power (&tmp, base, 6);
			break;

		case 'G': /* giga or gibi */
		case 'g': /* 'g' is undocumented; for compatibility only */
			overflow = bkm_scale_by_power (&tmp, base, 3);
			break;

		case 'k': /* kilo */
		case 'K': /* kibi */
			overflow = bkm_scale_by_power (&tmp, base, 1);
			break;

		case 'M': /* mega or mebi */
		case 'm': /* 'm' is undocumented; for compatibility only */
			overflow = bkm_scale_by_power (&tmp, base, 2);
			break;

		case 'P': /* peta or pebi */
			overflow = bkm_scale_by_power (&tmp, base, 5);
			break;

		case 'T': /* tera or tebi */
		case 't': /* 't' is undocumented; for compatibility only */
			overflow = bkm_scale_by_power (&tmp, base, 4);
			break;

		case 'w':
			overflow = bkm_scale (&tmp, 2);
			break;

		case 'Y': /* yotta or 2**80 */
			overflow = bkm_scale_by_power (&tmp, base, 8);
			break;

		case 'Z': /* zetta or 2**70 */
			overflow = bkm_scale_by_power (&tmp, base, 7);
			break;

		default:
			*val = tmp;
			return err | LONGINT_INVALID_SUFFIX_CHAR;
		}

		err |= overflow;
		*p += suffixes;
		if (**p)
			err |= LONGINT_INVALID_SUFFIX_CHAR;
	}

	*val = tmp;
	return err;
}

void alloc_exit (void)
{
	error (EXIT_FAILURE, 0, "%s", "memory exhausted");
	abort ();
}

void *xrealloc (void *p, size_t n)
{
	if(!n && p)
	{
		free (p);
		return NULL;
	}

	p = realloc (p, n);
	if(!p && n)
		alloc_exit ();
	return p;
}

void *x2nrealloc (void *p, size_t *pn, size_t s)
{
	size_t n = *pn;

	if (!p)
	{
		if(!n)
		{
			enum { DEFAULT_MXFAST = 64 * sizeof (size_t) / 4 };

			n = DEFAULT_MXFAST / s;
			n += !n;
		}
	} else {
		if((PTRDIFF_MAX < SIZE_MAX ? PTRDIFF_MAX : SIZE_MAX) / 3 * 2 / s <= n)
			alloc_exit ();
		n += n / 2 + 1;
	}

	*pn = n;
	return xrealloc (p, n * s);
}

void error (int status, int errnum, const char *message, ...)
{
	va_list args;

	fflush (stdout);

	fprintf (stderr, "%s: ", ProName);

	va_start (args, message);
	vfprintf (stderr, message, args);
	va_end (args);

	++error_message_count;
	if (errnum)
		print_errno_message(errnum);

	putc ('\n', stderr);

	fflush (stderr);
	if(status)
		exit(status);
}

void print_errno_message (int errnum)
{
	char const *s;

	char errbuf[1024];

	if(strerror_r (errnum, errbuf, sizeof errbuf) == 0)
		s = errbuf;
	else
		s = 0;

	if(!s)
		s = "Unknown system error";

	fprintf (stderr, ": %s", s);

}

char * __attribute_warn_unused_result__
anytostr (int i, char *buf)
{
	char *p = buf + INT_STRLEN_BOUND (int);
	*p = 0;

	if (i < 0)
	{
		do
			*--p = '0' - i % 10;
		while ((i /= 10) != 0);

		*--p = '-';
	}
	else
	{
		do
			*--p = '0' + i % 10;
		while ((i /= 10) != 0);
	}

  return p;
}













