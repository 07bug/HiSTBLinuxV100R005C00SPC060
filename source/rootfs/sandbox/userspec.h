#ifndef USERSPEC_H
#define USERSPEC_H

#include <grp.h>
#include <sys/types.h>
#include <stdbool.h>


int parse_additional_groups(char const *groups, gid_t **pgids,
							size_t *pn_gids, bool show_errors);
char const* parse_user_spec(char const *spec, uid_t *uid, gid_t *gid,
								char **username, char **groupname);

int mgetgroups (const char *username, gid_t gid, gid_t **groups);
int xgetgroups (const char *username, gid_t gid, gid_t **groups);
char * __attribute_warn_unused_result__ anytostr (int i, char *buf);


#endif