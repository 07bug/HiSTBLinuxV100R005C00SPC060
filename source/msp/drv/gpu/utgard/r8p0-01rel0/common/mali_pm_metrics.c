/*
 * Copyright (C) 2010-2014, 2016-2017 ARM Limited. All rights reserved.
 * 
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 * 
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "mali_pm_metrics.h"
#include "mali_osk_locks.h"
#include "mali_osk_mali.h"
#include <linux/ktime.h>

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi governor */
#include "platform/dt/mali4xx_dt.h"
#endif

#define MALI_PM_TIME_SHIFT 0
#define MALI_UTILIZATION_MAX_PERIOD 80000000/* ns = 100ms */

_mali_osk_errcode_t mali_pm_metrics_init(struct mali_device *mdev)
{
	int i = 0;

	MALI_DEBUG_ASSERT(mdev != NULL);

	mdev->mali_metrics.time_period_start = ktime_get();
	mdev->mali_metrics.time_period_start_gp = mdev->mali_metrics.time_period_start;
	mdev->mali_metrics.time_period_start_pp = mdev->mali_metrics.time_period_start;

	mdev->mali_metrics.time_busy = 0;
	mdev->mali_metrics.time_idle = 0;
	mdev->mali_metrics.prev_busy = 0;
	mdev->mali_metrics.prev_idle = 0;
	mdev->mali_metrics.num_running_gp_cores = 0;
	mdev->mali_metrics.num_running_pp_cores = 0;
	mdev->mali_metrics.time_busy_gp = 0;
	mdev->mali_metrics.time_idle_gp = 0;

	for (i = 0; i < MALI_MAX_NUMBER_OF_PHYSICAL_PP_GROUPS; i++) {
		mdev->mali_metrics.time_busy_pp[i] = 0;
		mdev->mali_metrics.time_idle_pp[i] = 0;
	}
	mdev->mali_metrics.gpu_active = MALI_FALSE;

	mdev->mali_metrics.lock = _mali_osk_spinlock_irq_init(_MALI_OSK_LOCKFLAG_UNORDERED, _MALI_OSK_LOCK_ORDER_FIRST);
	if (NULL == mdev->mali_metrics.lock) {
		return _MALI_OSK_ERR_NOMEM;
	}

	return _MALI_OSK_ERR_OK;
}

void mali_pm_metrics_term(struct mali_device *mdev)
{
	_mali_osk_spinlock_irq_term(mdev->mali_metrics.lock);
}

/*caller needs to hold mdev->mali_metrics.lock before calling this function*/
void mali_pm_record_job_status(struct mali_device *mdev)
{
	ktime_t now;
	ktime_t diff;
	u64 ns_time;

	MALI_DEBUG_ASSERT(mdev != NULL);

	now = ktime_get();
	diff = ktime_sub(now, mdev->mali_metrics.time_period_start);

	ns_time = (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
	mdev->mali_metrics.time_busy += ns_time;
	mdev->mali_metrics.time_period_start = now;
}

void mali_pm_record_gpu_idle(mali_bool is_gp)
{
	ktime_t now;
	ktime_t diff;
	u64 ns_time;
	struct mali_device *mdev = dev_get_drvdata(&mali_platform_device->dev);

	MALI_DEBUG_ASSERT(mdev != NULL);

	_mali_osk_spinlock_irq_lock(mdev->mali_metrics.lock);
	now = ktime_get();

	if (MALI_TRUE == is_gp) {
		--mdev->mali_metrics.num_running_gp_cores;
		if (0 == mdev->mali_metrics.num_running_gp_cores) {
			diff = ktime_sub(now, mdev->mali_metrics.time_period_start_gp);
			ns_time = (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
			mdev->mali_metrics.time_busy_gp += ns_time;
			mdev->mali_metrics.time_period_start_gp = now;

			if (0 == mdev->mali_metrics.num_running_pp_cores) {
				MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_TRUE);
				diff = ktime_sub(now, mdev->mali_metrics.time_period_start);
				ns_time = (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
				mdev->mali_metrics.time_busy += ns_time;
				mdev->mali_metrics.time_period_start = now;
				mdev->mali_metrics.gpu_active = MALI_FALSE;
			}
		}
	} else {
		--mdev->mali_metrics.num_running_pp_cores;
		if (0 == mdev->mali_metrics.num_running_pp_cores) {
			diff = ktime_sub(now, mdev->mali_metrics.time_period_start_pp);
			ns_time = (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
			mdev->mali_metrics.time_busy_pp[0] += ns_time;
			mdev->mali_metrics.time_period_start_pp = now;

			if (0 == mdev->mali_metrics.num_running_gp_cores) {
				MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_TRUE);
				diff = ktime_sub(now, mdev->mali_metrics.time_period_start);
				ns_time = (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
				mdev->mali_metrics.time_busy += ns_time;
				mdev->mali_metrics.time_period_start = now;
				mdev->mali_metrics.gpu_active = MALI_FALSE;
			}
		}
	}

	_mali_osk_spinlock_irq_unlock(mdev->mali_metrics.lock);
}

void mali_pm_record_gpu_active(mali_bool is_gp)
{
	ktime_t now;
	ktime_t diff;
	struct mali_device *mdev = dev_get_drvdata(&mali_platform_device->dev);

	MALI_DEBUG_ASSERT(mdev != NULL);

	_mali_osk_spinlock_irq_lock(mdev->mali_metrics.lock);
	now = ktime_get();

	if (MALI_TRUE == is_gp) {
		mdev->mali_metrics.num_running_gp_cores++;
		if (1 == mdev->mali_metrics.num_running_gp_cores) {
			diff = ktime_sub(now, mdev->mali_metrics.time_period_start_gp);
			mdev->mali_metrics.time_idle_gp += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
			mdev->mali_metrics.time_period_start_gp = now;
			if (0 == mdev->mali_metrics.num_running_pp_cores) {
				MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_FALSE);
				diff = ktime_sub(now, mdev->mali_metrics.time_period_start);
				mdev->mali_metrics.time_idle += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
				mdev->mali_metrics.time_period_start = now;
				mdev->mali_metrics.gpu_active = MALI_TRUE;
			}
		} else {
			MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_TRUE);
		}
	} else {
		mdev->mali_metrics.num_running_pp_cores++;
		if (1 == mdev->mali_metrics.num_running_pp_cores) {
			diff = ktime_sub(now, mdev->mali_metrics.time_period_start_pp);
			mdev->mali_metrics.time_idle_pp[0] += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
			mdev->mali_metrics.time_period_start_pp = now;
			if (0 == mdev->mali_metrics.num_running_gp_cores) {
				MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_FALSE);
				diff = ktime_sub(now, mdev->mali_metrics.time_period_start);
				mdev->mali_metrics.time_idle += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);
				mdev->mali_metrics.time_period_start = now;
				mdev->mali_metrics.gpu_active = MALI_TRUE;
			}
		} else {
			MALI_DEBUG_ASSERT(mdev->mali_metrics.gpu_active == MALI_TRUE);
		}
	}

	_mali_osk_spinlock_irq_unlock(mdev->mali_metrics.lock);
}


/*caller needs to hold mdev->mali_metrics.lock before calling this function*/
static void mali_pm_get_dvfs_utilisation_calc(struct mali_device *mdev, ktime_t now)
{
	ktime_t diff;
#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	ktime_t diff_gp, diff_pp;
#endif

	MALI_DEBUG_ASSERT(mdev != NULL);

	diff = ktime_sub(now, mdev->mali_metrics.time_period_start);

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	diff_gp = ktime_sub(now, mdev->mali_metrics.time_period_start_gp);
	diff_pp = ktime_sub(now, mdev->mali_metrics.time_period_start_pp);
#endif

	if (mdev->mali_metrics.gpu_active) {
		mdev->mali_metrics.time_busy += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	if(1 == mdev->mali_metrics.num_running_gp_cores)
	{
		mdev->mali_metrics.time_busy_gp += (u64)(ktime_to_ns(diff_gp) >> MALI_PM_TIME_SHIFT);
	}
	else
	{
		mdev->mali_metrics.time_busy_pp[0] += (u64)(ktime_to_ns(diff_pp) >> MALI_PM_TIME_SHIFT);
	}
#endif
	} else {
		mdev->mali_metrics.time_idle += (u64)(ktime_to_ns(diff) >> MALI_PM_TIME_SHIFT);

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	if(1 == mdev->mali_metrics.num_running_gp_cores)
	{
		mdev->mali_metrics.time_idle_gp += (u64)(ktime_to_ns(diff_gp) >> MALI_PM_TIME_SHIFT);
	}
	else
	{
		mdev->mali_metrics.time_idle_pp[0] += (u64)(ktime_to_ns(diff_pp) >> MALI_PM_TIME_SHIFT);
	}
#endif
	}
}

/* Caller needs to hold mdev->mali_metrics.lock before calling this function. */
static void mali_pm_reset_dvfs_utilisation_unlocked(struct mali_device *mdev, ktime_t now)
{
	/* Store previous value */
	mdev->mali_metrics.prev_idle = mdev->mali_metrics.time_idle;
	mdev->mali_metrics.prev_busy = mdev->mali_metrics.time_busy;

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	mdev->mali_metrics.prev_idle_gp = mdev->mali_metrics.time_idle_gp;
	mdev->mali_metrics.prev_busy_gp = mdev->mali_metrics.time_busy_gp;
	mdev->mali_metrics.prev_idle_pp[0] = mdev->mali_metrics.time_idle_pp[0];
	mdev->mali_metrics.prev_busy_pp[0] = mdev->mali_metrics.time_busy_pp[0];
#endif

	/* Reset current values */
	mdev->mali_metrics.time_period_start = now;
	mdev->mali_metrics.time_period_start_gp = now;
	mdev->mali_metrics.time_period_start_pp = now;
	mdev->mali_metrics.time_idle = 0;
	mdev->mali_metrics.time_busy = 0;

	mdev->mali_metrics.time_busy_gp = 0;
	mdev->mali_metrics.time_idle_gp = 0;
	mdev->mali_metrics.time_busy_pp[0] = 0;
	mdev->mali_metrics.time_idle_pp[0] = 0;
}

void mali_pm_reset_dvfs_utilisation(struct mali_device *mdev)
{
	_mali_osk_spinlock_irq_lock(mdev->mali_metrics.lock);
	mali_pm_reset_dvfs_utilisation_unlocked(mdev, ktime_get());
	_mali_osk_spinlock_irq_unlock(mdev->mali_metrics.lock);
}

void mali_pm_get_dvfs_utilisation(struct mali_device *mdev,
				  unsigned long *total_out, unsigned long *busy_out)
{
	ktime_t now = ktime_get();
	u64 busy = 0;
	u64 total = 0;

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	u64 busy_gp = 0, total_gp = 0;
	u64 busy_pp = 0, total_pp = 0;

	struct mali_config *mali_valuable;
#endif

	_mali_osk_spinlock_irq_lock(mdev->mali_metrics.lock);

	mali_pm_get_dvfs_utilisation_calc(mdev, now);

	busy = mdev->mali_metrics.time_busy;
	total = busy + mdev->mali_metrics.time_idle;

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	busy_gp = mdev->mali_metrics.time_busy_gp;
	total_gp = busy_gp + mdev->mali_metrics.time_idle_gp;
	busy_pp = mdev->mali_metrics.time_busy_pp[0];
	total_pp = busy_pp + mdev->mali_metrics.time_idle_pp[0];
#endif

	/* Reset stats if older than MALI_UTILIZATION_MAX_PERIOD (default
	 * 100ms) */
	if (total >= MALI_UTILIZATION_MAX_PERIOD) {
		mali_pm_reset_dvfs_utilisation_unlocked(mdev, now);
	} else if (total < (MALI_UTILIZATION_MAX_PERIOD / 2)) {
		total += mdev->mali_metrics.prev_idle +
			 mdev->mali_metrics.prev_busy;
		busy += mdev->mali_metrics.prev_busy;

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
		total_gp += mdev->mali_metrics.prev_idle_gp +
             mdev->mali_metrics.prev_busy_gp;
		busy_gp += mdev->mali_metrics.prev_busy_gp;
		total_pp += mdev->mali_metrics.prev_idle_pp[0] +
             mdev->mali_metrics.prev_busy_pp[0];
		busy_pp += mdev->mali_metrics.prev_busy_pp[0];
#endif
	}

	*total_out = (unsigned long)total;
	*busy_out = (unsigned long)busy;

#if defined(UTGARD_HISILICON_PLUGIN) /* Hisi Governor */
	mali_valuable = (struct mali_config*)mali_adp_get_configuration(mdev);

	mali_valuable->time_busy_gp = (unsigned long)busy_gp;
	mali_valuable->time_total_gp = (unsigned long)total_gp;

	mali_valuable->time_busy_pp = (unsigned long)busy_pp;
	mali_valuable->time_total_pp = (unsigned long)total_pp;
#endif

	_mali_osk_spinlock_irq_unlock(mdev->mali_metrics.lock);
}

void mali_pm_metrics_spin_lock(void)
{
	struct mali_device *mdev = dev_get_drvdata(&mali_platform_device->dev);
	_mali_osk_spinlock_irq_lock(mdev->mali_metrics.lock);
}

void mali_pm_metrics_spin_unlock(void)
{
	struct mali_device *mdev = dev_get_drvdata(&mali_platform_device->dev);
	_mali_osk_spinlock_irq_unlock(mdev->mali_metrics.lock);
}
