/* tools/mkbootimg/bootimg.h
**
** Copyright 2007, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef _BOOT_IMAGE_H_
#define _BOOT_IMAGE_H_

#include <linux/types.h>

typedef struct boot_img_hdr boot_img_hdr;

#define BOOT_MAGIC              "ANDROID!"
#define BOOT_MAGIC_SIZE         8
#define BOOT_NAME_SIZE          16
#define BOOT_ARGS_SIZE          512
#define HI_ADVCA_MAGIC          "Hisilicon_ADVCA_ImgHead_MagicNum"
#define HI_ADVCA_MAGIC_SIZE     32
#define HI_ADVCA_HEADER_SIZE    0x2000
#define HI_TEE_ATF_SIZE         0x200000

struct boot_img_hdr {
	unsigned char magic[BOOT_MAGIC_SIZE];

	__u32 kernel_size; /* kernel size in bytes */
	__u32 kernel_addr; /* physical load addr */

	__u32 ramdisk_size; /* ramdisk size in bytes */
	__u32 ramdisk_addr; /* physical load addr */

	__u32 second_size; /* size in bytes */
	__u32 second_addr; /* physical load addr */

	__u32 tags_addr; /* physical addr for kernel tags */
	__u32 page_size; /* flash page size we assume */
	__u32 unused[2]; /* future expansion: should be 0 */

	unsigned char name[BOOT_NAME_SIZE]; /* asciiz product name */

	unsigned char cmdline[BOOT_ARGS_SIZE];

	__u32 id[8]; /* timestamp / checksum / sha1 / etc */
};

/*
** +-----------------+ 
** | boot header     | 1 page
** +-----------------+
** | kernel          | n pages  
** +-----------------+
** | ramdisk         | m pages  
** +-----------------+
** | second stage    | o pages
** +-----------------+
**
** n = (kernel_size + page_size - 1) / page_size
** m = (ramdisk_size + page_size - 1) / page_size
** o = (second_size + page_size - 1) / page_size
**
** 0. all entities are page_size aligned in flash
** 1. kernel and ramdisk are required (size != 0)
** 2. second is optional (second_size == 0 -> no second)
** 3. load each element (kernel, ramdisk, second) at
**    the specified physical address (kernel_addr, etc)
** 4. prepare tags at tag_addr.  kernel_args[] is
**    appended to the kernel commandline in the tags.
** 5. r0 = 0, r1 = MACHINE_TYPE, r2 = tags_addr
** 6. if second_size != 0: jump to second_addr
**    else: jump to kernel_addr
*/

int check_bootimg(char *buf, unsigned int len);

int bootimg_get_kernel(char *buf, unsigned int len, unsigned int *entry);

int bootimg_get_ramfs(char *buf, unsigned int len, unsigned int *initrd_start,
		      unsigned int *initrd_size);

#endif
