#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "common.h"
#include "userspec.h"


static char const *parse_with_separator (char const *spec, char const *separator,
						uid_t *uid, gid_t *gid, char **username, char **groupname)
{
	static const char *E_invalid_user = "invalid user";
	static const char *E_invalid_group = "invalid group";
	static const char *E_bad_spec = "invalid spec";

	const char *error_msg;
	struct passwd *pwd;
	struct group *grp;
	char *u;
	char const *g;
	char *gname = NULL;
	uid_t unum = *uid;
	gid_t gnum = gid ? *gid : -1;

	error_msg = NULL;
	if(username)
		*username = NULL;
	if(groupname)
		*groupname = NULL;

	/* Set U and G to nonzero length strings corresponding to user and
	  group specifiers or to NULL.  If U is not NULL, it is a newly
	  allocated string.  */

	u = NULL;
	if (separator == NULL)
	{
		if(*spec)
			u = xstrdup (spec);
		} else {
			size_t ulen = separator - spec;
			if (ulen != 0)
		{
			u = xmemdup (spec, ulen + 1);
			u[ulen] = '\0';
		}
	}

	g = (separator == NULL || *(separator + 1) == '\0'
		? NULL
		: separator + 1);

	if (u != NULL)
	{
		/* If it starts with "+", skip the look-up.  */
		pwd = (*u == '+' ? NULL : getpwnam (u));
		if(pwd == NULL)
		{
			bool use_login_group = (separator != NULL && g == NULL);
			if(use_login_group)
			{
				/* If there is no group,
				then there may not be a trailing ":", either.  */
				error_msg = E_bad_spec;
			}
			else
			{
				unsigned long int tmp;
				if(xstrtoul (u, NULL, 10, &tmp, "") == LONGINT_OK
					&& tmp <= TYPE_MAXIMUM(uid_t) && (uid_t) tmp != (uid_t) -1)
					unum = tmp;
				else
					error_msg = E_invalid_user;
			}
		} else {
			unum = pwd->pw_uid;
			if(g == NULL && separator != NULL)
			{
				/* A separator was given, but a group was not specified,
					so get the login group.  */
				char buf[INT_BUFSIZE_BOUND (uintmax_t)];
				gnum = pwd->pw_gid;
				grp = getgrgid(gnum);
				gname = xstrdup(grp ? grp->gr_name : umaxtostr (gnum, buf));
				endgrent();
			}
		}
		endpwent ();
	}

	if(g != NULL && error_msg == NULL)
	{
		/* Explicit group.  */
		/* If it starts with "+", skip the look-up.  */
		grp = (*g == '+' ? NULL : getgrnam (g));
		if(grp == NULL)
		{
			unsigned long int tmp;
			if(xstrtoul (g, NULL, 10, &tmp, "") == LONGINT_OK
				&& tmp <= TYPE_MAXIMUM(gid_t) && (gid_t) tmp != (gid_t) -1)
				gnum = tmp;
			else
				error_msg = E_invalid_group;
		}
		else
			gnum = grp->gr_gid;
		endgrent ();              /* Save a file descriptor.  */
		gname = xstrdup (g);
	}

	if(error_msg == NULL)
	{
		*uid = unum;
		if(gid)
			*gid = gnum;
		if(username)
		{
			*username = u;
			u = NULL;
		}
		if(groupname)
		{
			*groupname = gname;
			gname = NULL;
		}
	}

	free (u);
	free (gname);
	return error_msg ? error_msg : NULL;
}

char const *parse_user_spec (char const *spec, uid_t *uid, gid_t *gid,
							char **username, char **groupname)
{
	char const *colon = gid ? strchr (spec, ':') : NULL;
	char const *error_msg =
	parse_with_separator (spec, colon, uid, gid, username, groupname);

	if(gid && !colon && error_msg)
	{
		char const *dot = strchr (spec, '.');
		if(dot
		&& !parse_with_separator(spec, dot, uid, gid, username, groupname))
		error_msg = NULL;
	}

	return error_msg;
}


int parse_additional_groups (char const *groups, gid_t **pgids,
							size_t *pn_gids, bool show_errors)
{
	gid_t *gids = NULL;
	size_t n_gids_allocated = 0;
	size_t n_gids = 0;
	char *buffer = xstrdup (groups);
	char const *tmp;
	int ret = 0;

	for (tmp = strtok (buffer, ","); tmp; tmp = strtok (NULL, ","))
	{
		struct group *g;
		unsigned long int value;

		if (xstrtoul (tmp, NULL, 10, &value, "") == LONGINT_OK && value <= TYPE_MAXIMUM(gid_t))
		{
			while (isspace (to_uchar (*tmp)))
				tmp++;
			if (*tmp != '+')
			{
				/* Handle the case where the name is numeric.  */
				g = getgrnam (tmp);
				if (g != NULL)
					value = g->gr_gid;
			}
			/* Flag that we've got a group from the number.  */
			g = (struct group *) (intptr_t) ! NULL;
		} else {
			g = getgrnam (tmp);
			if (g != NULL)
				value = g->gr_gid;
		}

		if (g == NULL)
		{
			ret = -1;

			if (show_errors)
			{
				 error (0, errno, "invalid group %s", tmp);
				continue;
			}

			break;
		}

		if (n_gids == n_gids_allocated)
			gids = X2NREALLOC (gids, &n_gids_allocated);
		gids[n_gids++] = value;
	}

	if (ret == 0 && n_gids == 0)
	{
		if (show_errors)
			error (0, 0, "invalid group list %s", groups);
		ret = -1;
	}

	*pgids = gids;

	if (ret == 0)
		*pn_gids = n_gids;

	free (buffer);
	return ret;
}

static gid_t *realloc_groupbuf (gid_t *g, size_t num)
{
	if(xalloc_oversized (num, sizeof *g))
	{
		errno = ENOMEM;
		return NULL;
	}

	return realloc (g, num * sizeof *g);
}

int getugroups (int maxcount, gid_t *grouplist, char const *username,
				gid_t gid)
{
	int count = 0;

	if(gid != (gid_t) -1)
	{
		if(maxcount != 0)
			grouplist[count] = gid;
		++count;
	}

	setgrent ();
	while(1)
	{
		char **cp;
		struct group *grp;

		errno = 0;
		grp = getgrent ();
		if(grp == NULL)
			break;

		for(cp = grp->gr_mem; *cp; ++cp)
		{
			int n;

			if( !STREQ (username, *cp))
				continue;

			/* See if this group number is already on the list.  */
			for(n = 0; n < count; ++n)
			if (grouplist && grouplist[n] == grp->gr_gid)
				break;

			/* If it's a new group number, then try to add it to the list.  */
			if(n == count)
			{
				if(maxcount != 0)
				{
					if(count >= maxcount)
						goto done;
					grouplist[count] = grp->gr_gid;
				}
				if(count == INT_MAX)
				{
					errno = EOVERFLOW;
					goto done;
				}
				count++;
			}
		}
	}

	if(errno != 0)
		count = -1;

 done:
	{
		int saved_errno = errno;
		endgrent ();
		errno = saved_errno;
	}

	return count;
}

int mgetgroups (char const *username, gid_t gid, gid_t **groups)
{
	int max_n_groups;
	int ng;
	gid_t *g;


	if (username)
	{
		enum { N_GROUPS_INIT = 10 };
		max_n_groups = N_GROUPS_INIT;

		g = realloc_groupbuf (NULL, max_n_groups);
		if (g == NULL)
			return -1;

		while (1)
		{
			gid_t *h;
			int last_n_groups = max_n_groups;

			/* getgrouplist updates max_n_groups to num required.  */
			ng = getgrouplist (username, gid, g, &max_n_groups);

			/* Some systems (like Darwin) have a bug where they
			 never increase max_n_groups.  */
			if (ng < 0 && last_n_groups == max_n_groups)
				max_n_groups *= 2;

		  if ((h = realloc_groupbuf (g, max_n_groups)) == NULL)
			{
				int saved_errno = errno;
				free (g);
				errno = saved_errno;
				return -1;
			}
			g = h;

			if (0 <= ng)
			{
				*groups = g;
				/* On success some systems just return 0 from getgrouplist,
				 so return max_n_groups rather than ng.  */
				return max_n_groups;
			}
		}
	}
  /* else no username, so fall through and use getgroups. */

  max_n_groups = (username
				  ? getugroups (0, NULL, username, gid)
				  : getgroups (0, NULL));

  /* If we failed to count groups because there is no supplemental
	 group support, then return an array containing just GID.
	 Otherwise, we fail for the same reason.  */
	if (max_n_groups < 0)
	{
	  if (errno == ENOSYS && (g = realloc_groupbuf (NULL, 1)))
		{
			*groups = g;
			*g = gid;
			return gid != (gid_t) -1;
		}
	  return -1;
	}

	if (max_n_groups == 0 || (!username && gid != (gid_t) -1))
	max_n_groups++;
	g = realloc_groupbuf (NULL, max_n_groups);
	if (g == NULL)
	return -1;

	ng = (username
		? getugroups (max_n_groups, g, username, gid)
		: getgroups (max_n_groups - (gid != (gid_t) -1),
								g + (gid != (gid_t) -1)));

	if (ng < 0)
	{
		/* Failure is unexpected, but handle it anyway.  */
		int saved_errno = errno;
		free (g);
		errno = saved_errno;
		return -1;
	}

	if (!username && gid != (gid_t) -1)
	{
		*g = gid;
		ng++;
	}
	*groups = g;

  if (1 < ng)
	{
		gid_t first = *g;
		gid_t *next;
		gid_t *groups_end = g + ng;

		for (next = g + 1; next < groups_end; next++)
		{
			if (*next == first || *next == *g)
				ng--;
			else
				*++g = *next;
		}
	}

  return ng;
}


int xgetgroups (char const *name, gid_t gid, gid_t **grp)
{
	int result = mgetgroups (name, gid, grp);
	if (result == -1 && errno == ENOMEM)
		alloc_exit ();
	return result;
}





