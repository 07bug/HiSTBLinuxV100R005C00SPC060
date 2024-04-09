/******************************************************************************
 *  Copyright (C) 2015 Cai Zhiyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiying 2015.7.27
 *
******************************************************************************/

#ifndef NAND_SYNC_H
#define NAND_SYNC_H

#include <hinfc_gen.h>

#define DEFAULT_SYNCMODE_TIMING              0xaaaaaaa  //default syncmode timing
#define DEFAULT_SYNCMODE_CLOCK               75         //default syncmode clock.

#define NAND_IO_VOL_3_3V                     0
#define NAND_IO_VOL_1_8V                     1

/**************** sync nand only **********************************************/

extern struct nand_sync_t nand_sync_toggle_v10;
extern struct nand_sync_t nand_sync_toggle_v20;
extern struct nand_sync_t nand_sync_onfi_v23;
extern struct nand_sync_t nand_sync_onfi_v30;

/******************************************************************************/
struct nand_sync_timing {
	const char *name;
	u8 id[FLASH_ID_LEN];
	int id_len;

	u8 syncmode;

	unsigned int timing;
	unsigned int clock;
};

struct nand_sync_t {
	u8 type;
	int (*enable)(struct flash_regop *regop);
	int (*disable)(struct flash_regop *regop);
};

struct nand_sync_timing *nand_get_sync_timing(struct nand_sync_timing *nand_sync_timing,
					      u8 *id, int id_len);

struct nand_sync_t *nand_get_sync(char nand_sync_type);

#endif /* NAND_SYNC_H*/
