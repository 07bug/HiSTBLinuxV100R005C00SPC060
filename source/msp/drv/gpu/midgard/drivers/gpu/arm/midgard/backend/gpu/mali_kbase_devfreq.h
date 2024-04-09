/*
 *
 * (C) COPYRIGHT 2014 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */
#ifndef MIDGARD_HISILICON_PLUGIN
#define MIDGARD_HISILICON_PLUGIN
#endif

#ifndef _BASE_DEVFREQ_H_
#define _BASE_DEVFREQ_H_

int kbase_devfreq_init(struct kbase_device *kbdev);
void kbase_devfreq_term(struct kbase_device *kbdev);

#ifdef MIDGARD_HISILICON_PLUGIN
int kbase_devfreq_downscale(struct kbase_device *kbdev);
int kbase_devfreq_restore(struct kbase_device *kbdev);
#endif

#endif /* _BASE_DEVFREQ_H_ */
