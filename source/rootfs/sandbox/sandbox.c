#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#include "common.h"
#include "userspec.h"

static inline bool uid_unset (uid_t uid) {return uid == (uid_t)(-1);}
static inline bool gid_unset (gid_t gid) {return gid == (gid_t)(-1);}
#define uid_set(a) (!uid_unset(a))
#define gid_set(a) (!gid_unset(a))

#define echo_help_message() \
	do \
	{ \
		fprintf (stderr, "Try '%s --help' for more information.\n", \
				ProName); \
		} \
	while (0)

int volatile exit_failure = EXIT_FAILURE;


static struct option const long_opts[] =
{
	{"groups",   required_argument, NULL, GROUPS},
	{"userspec", required_argument, NULL, USERSPEC},
	{"help",     no_argument,       NULL, GETOPT_HELP_CHAR},
	{NULL, 0, NULL, 0}
};


void usage (int status)
{
      printf ("\
Usage: %s [OPTION] NEWROOT [COMMAND [ARG]...]\n\
  or:  %s OPTION\n\
",ProName, ProName);

      fputs ("\
Run COMMAND with root directory set to NEWROOT.\n\
\n\
", stdout);

      fputs ("\
  --userspec=USER:GROUP  specify user and group (ID or name) to use\n\
  --groups=G_LIST        specify supplementary groups as g1,g2,..,gN\n\
", stdout);

      fputs ("\
\n\
If no command is given, run '${SHELL} -i' (default: '/bin/sh -i').\n\
", stdout);

}

int main(int argc, char* argv[])
{
	int ch;
	
	/* Input user and groups spec.*/
	char *userspec = NULL;
	char const *username = NULL;
	char const *groups = NULL;
	
	/* Parsed user and groups IDS. */
	uid_t uid = -1;
	gid_t gid = -1;
	gid_t *out_gids = NULL;
	size_t n_gids = 0;
	size_t userlen = 0;
	char const *err = NULL;
	
	set_pro_name (argv[0]);
	
	while((ch = getopt_long (argc, argv, "+", long_opts, NULL)) != -1)
	{
		switch(ch)
		{
		case USERSPEC:
		{
			userspec = optarg;
			userlen = strlen (userspec);
			if(userlen&&userspec[userlen-1] == ':')
				userspec[userlen - 1] = '\0';
			break;
		}
		case GROUPS:
			groups = optarg;
			break;

		case GETOPT_HELP_CHAR:
			usage (EXIT_SUCCESS);
			break;

		default:
			usage(EXIT_CANCELED);
            break;
		}
	}

	if (argc <= optind)
	{
		error (0, 0, "missing operand");
		usage(EXIT_CANCELED);
	}

	if (!is_root(argv[optind]))
	{
		if(userspec)
			(void)parse_user_spec(userspec, &uid, &gid, NULL, NULL);
		/* If no git is supplied or look up, do so now.
		also lookup the usename for use with getgroups. */
		if(uid_set(uid) && (!groups || gid_unset(gid)))
		{ 
			const struct passwd *pwd;
			if((pwd = getpwuid(uid)))
			{
				if(gid_unset(gid))
					gid = pwd->pw_gid;
				username = pwd->pw_name;
			}	
		}
		
		if(groups && *groups) 
			(void)parse_additional_groups (groups, &out_gids, &n_gids, false);
		else if (!groups && gid_set(gid) && username)
		{
			int ngroups = xgetgroups (username, gid, &out_gids);
			if (0 < ngroups)
			n_gids = ngroups;
		}
		
		if (chroot (argv[optind]) != 0)
			error (EXIT_CANCELED, errno, "cannot change root directory to %s",
					argv[optind]);

		if (chdir ("/"))
			error (EXIT_CANCELED, errno, "cannot chdir to root directory");
	}
	
	if(argc == optind + 1)
	{
		/* No conmmand. Run an interactive shell. */
		char *shell = getenv("SHELL");
		if(shell == NULL)
			shell = (char *)"/bin/sh";
		argv[0] = shell;
		argv[1] = (char *)"-i";
		argv[2] = NULL;
	} else {
		/* The following arguments give the command.  */
			argv += optind + 1;
	}
	/* Attempt to set all three: supplementary groups, group ID, user ID.
	  Diagnose any failures.  If any have failed, exit before execvp.  */
	if(userspec)
	{
		err = parse_user_spec(userspec, &uid, &gid, NULL, NULL);
		if(err && uid_unset(uid) && gid_unset(gid))
		error (EXIT_CANCELED, errno, "%s", err);
	}
	/* If no gid is supplied or looked up, do so now.
	  Also lookup the username for use with getgroups.  */
	if(uid_set (uid) && (! groups || gid_unset (gid)))
	{
		const struct passwd *pwd;
		if ((pwd = getpwuid (uid)))
		{
			if (gid_unset (gid))
			gid = pwd->pw_gid;
			username = pwd->pw_name;
		}
		else if (gid_unset (gid))
		{
			error (EXIT_CANCELED, errno,
			"no group specified for unknown uid: %d", (int) uid);
		}
	}

	gid_t *gids = out_gids;
	gid_t *in_gids = NULL;
	if (groups && *groups)
	{
		if (parse_additional_groups(groups, &in_gids, &n_gids, !n_gids) != 0)
		{
			if (!n_gids)
			exit (EXIT_CANCELED);
		/* else look-up outside the chroot worked, then go with those.  */
		}
		else
			gids = in_gids;
	}
	else if (!groups && gid_set (gid) && username)
	{
		int ngroups = xgetgroups (username, gid, &in_gids);
		if (ngroups <= 0)
		{
			if(!n_gids)
			error(EXIT_CANCELED, errno,
				"failed to get supplemental groups");
		/* else look-up outside the chroot worked, then go with those.  */
		}
		else
		{
			n_gids = ngroups;
			gids = in_gids;
		}
	}

	if((uid_set (uid) || groups) && setgroups (n_gids, gids) != 0)
	error (EXIT_CANCELED, errno, "failed to %s supplemental groups",
			gids ? "set" : "clear");

	free(in_gids);
	free(out_gids);

	if(gid_set(gid) && setgid (gid))
	error (EXIT_CANCELED, errno, "failed to set group-ID");

	if(uid_set (uid) && setuid (uid))
	error (EXIT_CANCELED, errno, "failed to set user-ID");

	/* Execute the given command.  */
	execvp (argv[0], argv);

	{
		int exit_status = (errno == ENOENT ? EXIT_ENOENT : EXIT_CANNOT_INVOKE);
		error (0, errno, "failed to run command %s", argv[0]);
		exit (exit_status);
	}
	
}
