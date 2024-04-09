/*
* Copyright (c) 2011-2012 Qualcomm Atheros Inc. All Rights Reserved.
* Qualcomm Atheros Proprietary and Confidential.
*/

#include "libtcmd.h"
#include  "os.h"

int tcmd_set_timer(struct tcmd_cfg *cfg)
{
	struct itimerspec exp_time;
	int err;

	A_DBG("setting timer\n");
	bzero(&exp_time, sizeof(exp_time));
	exp_time.it_value.tv_sec = TCMD_TIMEOUT;
	err = timer_settime(cfg->timer, 0, &exp_time, NULL);
	cfg->timeout = false;
	if (err < 0)
		return errno;
	return 0;
}

int tcmd_reset_timer(struct tcmd_cfg *cfg)
{
	struct itimerspec curr_time;
	int err;

	err = timer_gettime(cfg->timer, &curr_time);
	if (err < 0)
		return errno;

	if (!curr_time.it_value.tv_sec && !curr_time.it_value.tv_nsec)
		return -ETIMEDOUT;

	A_DBG("resetting timer\n");
	bzero(&curr_time, sizeof(curr_time));
	err = timer_settime(cfg->timer, 0, &curr_time, NULL);
	if (err < 0)
		return errno;
	return 0;
}
