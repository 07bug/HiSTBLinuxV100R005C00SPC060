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

#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <asm/io.h>

#include "hinfc504.h"

/*****************************************************************************/

static int hinfc504_samsung_set_rr_reg(struct hinfc_host *host,int param)
{
#define SAMSUNG_RR_CMD     0xA1

	unsigned char samsung_rr_params[15][4] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x05, 0x0A, 0x00, 0x00},
		{0x28, 0x00, 0xEC, 0xD8},
		{0xED, 0xF5, 0xED, 0xE6},
		{0x0A, 0x0F, 0x05, 0x00},
		{0x0F, 0x0A, 0xFB, 0xEC},
		{0xE8, 0xEF, 0xE8, 0xDC},
		{0xF1, 0xFB, 0xFE, 0xF0},
		{0x0A, 0x00, 0xFB, 0xEC},
		{0xD0, 0xE2, 0xD0, 0xC2},
		{0x14, 0x0F, 0xFB, 0xEC},
		{0xE8, 0xFB, 0xE8, 0xDC},
		{0x1E, 0x14, 0xFB, 0xEC},
		{0xFB, 0xFF, 0xFB, 0xF8},
		{0x07, 0x0C, 0x02, 0x00}
	};

	if (param >= 15)
		param = (param % 15);

	host->set_ecc_randomizer(host, DISABLE, DISABLE);

	hinfc_write(host, 1, HINFC504_DATA_NUM);

	writel(samsung_rr_params[param][0], host->iobase);
	hinfc_write(host, 0xA700, HINFC504_ADDRL);
	hinfc_write(host, SAMSUNG_RR_CMD, HINFC504_CMD);
	hinfc_write(host, HINFC504_WRITE_1CMD_2ADD_DATA, HINFC504_OP);
	WAIT_CONTROLLER_FINISH();

	writel(samsung_rr_params[param][1], host->iobase);
	hinfc_write(host, 0xA400, HINFC504_ADDRL);
	hinfc_write(host, SAMSUNG_RR_CMD, HINFC504_CMD);
	hinfc_write(host, HINFC504_WRITE_1CMD_2ADD_DATA, HINFC504_OP);
	WAIT_CONTROLLER_FINISH();

	writel(samsung_rr_params[param][2], host->iobase);
	hinfc_write(host, 0xA500, HINFC504_ADDRL);
	hinfc_write(host, SAMSUNG_RR_CMD, HINFC504_CMD);
	hinfc_write(host, HINFC504_WRITE_1CMD_2ADD_DATA, HINFC504_OP);
	WAIT_CONTROLLER_FINISH();

	writel(samsung_rr_params[param][3], host->iobase);
	hinfc_write(host, 0xA600, HINFC504_ADDRL);
	hinfc_write(host, SAMSUNG_RR_CMD, HINFC504_CMD);
	hinfc_write(host, HINFC504_WRITE_1CMD_2ADD_DATA, HINFC504_OP);
	WAIT_CONTROLLER_FINISH();

	host->set_ecc_randomizer(host, ENABLE, ENABLE);

	return 0;

#undef SAMSUNG_RR_CMD
}
/*****************************************************************************/

static int hinfc504_samsung_set_rr_param(struct hinfc_host *host,int param)
{
	return hinfc504_samsung_set_rr_reg(host, param);
}
/*****************************************************************************/

struct read_retry_t hinfc504_samsung_read_retry = {
	.type = NAND_RR_SAMSUNG,
	.count = 15,
	.set_rr_param = hinfc504_samsung_set_rr_param,
	.get_rr_param = NULL,
	.enable_enhanced_slc = NULL,
};

