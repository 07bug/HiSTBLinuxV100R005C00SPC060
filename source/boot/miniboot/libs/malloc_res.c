/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <errno.h>
#include <malloc.h>
#include <module.h>
#include <hush.h>
#include <env_set.h>
#include <boot.h>
#include <string.h>

//#define MODULE_DEBUG
#include <debug.h>

#include "memlib.h"

struct alloc_t {
	const char *file;
	int line;
	void *ptr;
	uint32 bytes;
};

struct memdbg_t {
	uint32 nr_malloc;
	uint32 nr_free;

	uint32 sz_malloc;
	uint32 sz_free;

	struct hush_t *hush;
};

static struct memctrl_t *memctrl = NULL;
static struct memdbg_t *memdbg = NULL;

/*****************************************************************************/

static int memdbg_insert(struct memdbg_t *memdbg, const char *file, int line,
			 void *ptr, uint32 bytes)
{
	struct alloc_t *mem;

	mem = (struct alloc_t *)hush_add(memdbg->hush, (uint32)ptr,
		sizeof(struct alloc_t));
	if (!mem) {
		pr_error("Out of memory.\n");
		return -ENOMEM;
	}

	mem->file = file;
	mem->line = line;
	mem->ptr = ptr;
	mem->bytes = bytes;

	memdbg->nr_malloc++;
	memdbg->sz_malloc += bytes;

	return 0;
}
/*****************************************************************************/

void do_remove_alloc(void *args, uint32 tag, char *data)
{
	struct alloc_t *mem;
	struct memdbg_t *memdbg = (struct memdbg_t *)args;

	if (!data) {
		pr_error("free an invalid pointer.\n");
		return;
	}

	mem = (struct alloc_t *)data;
	memdbg->nr_free++;
	memdbg->sz_free += mem->bytes;
}
/*****************************************************************************/

static int memdbg_remove(struct memdbg_t *memdbg, void *ptr)
{
	return hush_remove(memdbg->hush, (uint32)ptr, memdbg, do_remove_alloc);
}
/*****************************************************************************/

void resmalloc_init(uint32 start, uint32 len)
{
	if (!memctrl)
		memctrl = memlib_init(start, len);

	memdbg = (struct memdbg_t *)zmalloc(sizeof(struct memdbg_t) +
		sizeof(struct hush_t));
	if (!memdbg) {
		pr_error("Out of memory.\n");
		return;
	}

	memdbg->hush = (struct hush_t *)&memdbg[1];

	hush_init(memdbg->hush, 40);
}
/*****************************************************************************/

void *__resmalloc(uint32 bytes, char *file, int line)
{
	void *ptr;

	if (!memctrl) {
		pr_debug("malloc module uninitializtion.\n");
		return NULL;
	}

	ptr = memlib_malloc(memctrl, bytes);
	if (ptr)
		memdbg_insert(memdbg, file, line, ptr, bytes);

	dbgout(_YELLOW "%s(%d): resmalloc:0x%x\n" _NONE, file, line, bytes);

	return ptr;
}
/*****************************************************************************/

void resfree(void *mem)
{
	if (!memctrl) {
		pr_debug("malloc module uninitializtion.\n");
		return;
	}

	dbgout(_YELLOW "%s(%d): resfree\n" _NONE, file, line);

	if (mem)
		memdbg_remove(memdbg, mem);

	memlib_free(memctrl, mem);
}
/*****************************************************************************/

void *__resmemalign(uint32 alignment, uint32 bytes, char *file, int line)
{
	void *ptr;

	if (!memctrl) {
		pr_debug("malloc module uninitializtion.\n");
		return NULL;
	}

	dbgout(_YELLOW "%s(%d): resmemalign:0x%x\n" _NONE, file, line, bytes);

	ptr = memlib_memalign(memctrl, alignment, bytes);
	if (ptr)
		memdbg_insert(memdbg, file, line, ptr, bytes);

	return ptr;
}
/*****************************************************************************/

int get_res_end(uint32 *end)
{
	char *bootargs = NULL;
	char *tmp = NULL;
	uint32 mem_val = 0;
	char args_merge_name[32];
	unsigned int ddrsize = get_ddr_size();

	if (NULL == end)
		goto error_out;

	bootargs = env_get("bootargs");
	if (!bootargs)
		goto error_out;

	tmp = strstr(bootargs, "mem=");
	if (!tmp) {
		snprintf(args_merge_name, sizeof(args_merge_name), "bootargs_%s",
		 	ultohstr((unsigned long long)ddrsize));
		bootargs = env_get(args_merge_name);
		if (!bootargs)
			goto error_out;
	}

	tmp = strstr(bootargs, "mem=");
	if (!tmp) {
		pr_error("%s %d: Invalid bootargs, mem is needed!\n", __func__, __LINE__);
		goto error_out;
	}

	tmp += sizeof("mem=") - 1;
	if (!isdigit(*tmp)) {
		pr_error("%s %d: Invalid mem args: %s!\n", __func__, __LINE__, tmp);
		goto error_out;
	}

	mem_val = memparse(tmp, NULL);
	*end = MEM_BASE_DDR + mem_val;
	return 0;
error_out:
	return -1;
}
/*****************************************************************************/

void resmem_dump(int verbose)
{
	struct alloc_t *mem;

	printf("\nReserve memory:\n");
	printf("    Start Address:  0x%08X\n", memctrl->start);
	printf("    End Address:    0x%08X\n", memctrl->end);
	printf("----------------------------------------\n");
	printf("Address     Size\n");

	hush_find_init(memdbg->hush);
	do {
		mem = (struct alloc_t *)hush_find_next(memdbg->hush, NULL);
		if (mem) {
			printf("0x%08X  0x%08X  ", (uint32)mem->ptr,
			       mem->bytes);
			if (verbose)
				printf("%s(%d)", mem->file, mem->line);
			printf("\n");
		}
	} while (mem);

	if (verbose) {
		printf("malloc:      %d\n", memdbg->nr_malloc);
		printf("free:        %d\n", memdbg->nr_free);
		printf("malloc size: 0x%08x\n", memdbg->sz_malloc);
		printf("free size:   0x%08x\n", memdbg->sz_free);
		printf("inused:      0x%08x\n",
		       (memdbg->sz_malloc - memdbg->sz_free));
	}

	printf("\n");
}

/*****************************************************************************/

static void resmem_init(void *ptr)
{
	u32 start = 0;
	u32 size = 0;

#if defined(CONFIG_FIXED_RSV_MEM_START) && defined(CONFIG_FIXED_RSV_MEM_SIZE)
	start = CONFIG_FIXED_RSV_MEM_START;
	size = CONFIG_FIXED_RSV_MEM_SIZE;
#else
	u32 ddrsize = 0;
	u32 ddrend;
	int32 ret;

	start = MEM_BASE_DDR;
	ret = get_res_end(&ddrsize);
	if (ret)
		ddrend =start + get_ddr_size();
	else
		ddrend = start + ddrsize;

	if (ddrsize >= _2G) {
		start = ddrend - _512M;
		size = _512M;
	} else if (ddrsize >= _1G) {
		start = ddrend - _256M;
		size = _256M;
	} else if (ddrsize >= _512M) {
		start = ddrend - _64M;
		size = _64M;
	} else if (ddrsize >= _256M) {
		start = ddrend - _32M;
		size = _32M;
	} else {
		start = ddrend - _32M;
		size = _32M;
	}
#endif
	resmalloc_init(start, size);

}
/*****************************************************************************/

static struct module_t module_resmem_set = {
	.priority = MODULE_PRI_DEF,
	.init = resmem_init,
};
MODULE(module_resmem_set);

