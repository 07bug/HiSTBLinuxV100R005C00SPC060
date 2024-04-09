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
 * Create By Cai Zhiying 2015.7.28
 *
******************************************************************************/
#include <hinfc_gen.h>
#include <asm/sizes.h>
#include "hiflash.h"

#define LP_OPTIONS NAND_SAMSUNG_LP_OPTIONS
#define LP_OPTIONS16 (LP_OPTIONS | NAND_BUSWIDTH_16)

/*
 * A helper for defining older NAND chips where the second ID byte fully
 * defined the chip, including the geometry (chip size, eraseblock size, page
 * size). All these chips have 512 bytes NAND page size.
 */
#define LEGACY_ID_NAND(nm, devid, chipsz, erasesz, opts)          \
	{ .name = (nm), {{ .dev_id = (devid) }}, .pagesize = 512, \
	  .chipsize = (chipsz), .erasesize = (erasesz), .options = (opts) }

/*
 * A helper for defining newer chips which report their page size and
 * eraseblock size via the extended ID bytes.
 *
 * The real difference between LEGACY_ID_NAND and EXTENDED_ID_NAND is that with
 * EXTENDED_ID_NAND, manufacturers overloaded the same device ID so that the
 * device ID now only represented a particular total chip size (and voltage,
 * buswidth), and the page size, eraseblock size, and OOB size could vary while
 * using the same device ID.
 */
#define EXTENDED_ID_NAND(nm, devid, chipsz, opts)                      \
	{ .name = (nm), {{ .dev_id = (devid) }}, .chipsize = (chipsz), \
	  .options = (opts) }


/******************************************************************************/

struct nand_flash_special_dev nand_flash_ids_hisi[] = {
	{
		.name      = "TC58NVG5D2 32G 3.3V 8-bit",
		.id        = {0x98, 0xD7, 0x94, 0x32, 0x76, 0x56, 0x09, 0x00},
		.id_len    = 8,
		.pagesize  = SZ_8K,
		.chipsize  = SZ_4K,
		.erasesize = SZ_1M,
		.oobsize   = 640,
		.options   = 0,
	}, {
		.name      = "S34ML04G2 3.3V 8-bit",
		.id        = {0x01, 0xdc, 0x90, 0x95, 0x56, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.pagesize  = SZ_2K,
		.chipsize  = SZ_512,
		.erasesize = SZ_128K,
		.oobsize   = 128,
		.options   = 0,
	}, {
		.name      = "S34ML02G2",
		.id        = {0x01, 0xda, 0x90, 0x95, 0x46, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.pagesize  = SZ_2K,
		.chipsize  = SZ_256,
		.erasesize = SZ_128K,
		.oobsize   = 128,
		.options   = 0,
	}, {
		.name      = "TC58NVG6D2 64G 3.3V 8-bit",
		.id        = {0x98, 0xDE, 0x94, 0x82, 0x76, 0x56, 0x04, 0x20},
		.id_len    = 8,
		.pagesize  = SZ_8K,
		.chipsize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 640,
		.options   = 0,
	}, {
		.name      = "SDTNRGAMA 64G 3.3V 8-bit",
		.id        = {0x45, 0xDE, 0x94, 0x93, 0x76, 0x50},
		.id_len    = 6,
		.pagesize  = SZ_16K,
		.chipsize  = SZ_8K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
	}, {
		.name      = "H27UCG8T2ATR-BC 64G 3.3V 8-bit",
		.id        = {0xAD, 0xDE, 0x94, 0xDA, 0x74, 0xC4},
		.id_len    = 6,
		.pagesize  = SZ_8K,
		.chipsize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 640,
		.options   = 0,
		.read_retry_type = NAND_RR_HYNIX_CG_ADIE,
	}, {
		.name      = "TC58NVG3S0F 8G 3.3V 8-bit",
		.id        = {0x98, 0xD3, 0x90, 0x26, 0x76, 0x15, 0x02, 0x08},
		.id_len    = 8,
		.pagesize  = SZ_4K,
		.chipsize  = SZ_1K,
		.erasesize = SZ_256K,
		.oobsize   = 232,
		.options   = 0,
	}, {
		.name      = "TC58NVG2S0F 4G 3.3V 8-bit",
		.id        = {0x98, 0xDC, 0x90, 0x26, 0x76, 0x15, 0x01, 0x08},
		.id_len    = 8,
		.pagesize  = SZ_4K,
		.chipsize  = SZ_512,
		.erasesize = SZ_256K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "TC58NVG2S0HBAI4",
		.id        = {0x98, 0xDC, 0x90, 0x26, 0x76, 0x16, 0x08, 0x00},
		.id_len    = 8,
		.pagesize  = SZ_4K,
		.chipsize  = SZ_512,
		.erasesize = SZ_256K,
		.oobsize   = 256,
		.options   = 0,
	}, {
		.name      = "MT29F32G08CBADA",
		.id        = {0x2C, 0x44, 0x44, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 744,
		.options   = 0,
		.read_retry_type = NAND_RR_MICRON,
	}, {
		.name      = "MT29F8G08ABxBA",
		.id        = {0x2C, 0x38, 0x00, 0x26, 0x85, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_1K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_512K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F16G08CBABx",
		.id        = {0x2C, 0x48, 0x04, 0x46, 0x85, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_1M,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F16G08CBACA",
		.id        = {0x2C, 0x48, 0x04, 0x4A, 0xA5, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_1M,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F32G08CBACA",
		.id        = {0x2C, 0x68, 0x04, 0x4A, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_1M,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F64G08CxxAA",
		.id        = {0x2C, 0x88, 0x04, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_8K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 448,
		.options   = 0,
	}, {
		.name      = "MT29F256G08CJAAA",
		.id        = {0x2C, 0xA8, 0x05, 0xCB, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_16K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 448,
		.options   = 0,
	}, {
		.name      = "MT29F64G08CBAAB",
		.id        = {0x2C, 0x64, 0x44, 0x4B, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_8K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 744,
		.options   = 0,
		.read_retry_type = NAND_RR_MICRON,
		.flags     = NAND_MODE_SYNC_ONFI23,
	}, {
		.name      = "MT29F8G08ABACA",
		.id        = {0x2C, 0xD3, 0x90, 0xA6, 0x64, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_1K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_256K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F4G08ABAEA",
		.id        = {0x2C, 0xDC, 0x90, 0xA6, 0x54, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_512,
		.pagesize  = SZ_4K,
		.erasesize = SZ_256K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F2G08ABAFA",
		.id        = {0x2C, 0xDA, 0x90, 0x95, 0x04, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_256,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "MT29F16G08ABACA",
		.id        = {0x2C, 0x48, 0x00, 0x26, 0xA9, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_512K,
		.oobsize   = 224,
		.options   = 0,
	}, {
		.name      = "TC58NVG4D2FTA00",
		.id        = {0x98, 0xD5, 0x94, 0x32, 0x76, 0x55, 0x00, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 448,
		.options   = 0,
	}, {
		.name      = "TH58NVG6D2FTA20",
		.id        = {0x98, 0xD7, 0x94, 0x32, 0x76, 0x55, 0x00, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 448,
		.options   = 0,
	}, {
		.name      = "TC58NVG5D2HTA00",
		.id        = {0x98, 0xD7, 0x94, 0x32, 0x76, 0x56, 0x08, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 640,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2012,
	}, {
		.name      = "TC58NVG6D2GTA00",
		.id        = {0x98, 0xDE, 0x94, 0x82, 0x76, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_8K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 640,
		.options   = 0,
	}, {
		.name      = "TC58NVG6DCJTA00",
		.id        = {0x98, 0xDE, 0x84, 0x93, 0x72, 0x57, 0x08, 0x04},
		.id_len    = 8,
		.chipsize  = SZ_8K,
		.pagesize  = SZ_16K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2012,
	}, {
		.name      = "TC58TEG5DCJTA00",
		.id        = {0x98, 0xD7, 0x84, 0x93, 0x72, 0x57, 0x08, 0x04},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_16K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2012,
	}, {
		.name      = "TC58NVG0S3HTA00",
		.id        = {0x98, 0xF1, 0x80, 0x15, 0x72, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_128,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 128,
		.options   = 0,
	}, {
		.name      = "TC58NVG1S3HTA00/QSV256M3THE",
		.id        = {0x98, 0xDA, 0x90, 0x15, 0x76, 0x16, 0x08, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_256,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 128,
		.options   = 0,
	}, {
		.name      = "TC58NVG1S3ETA00",
		.id        = {0x98, 0xDA, 0x90, 0x15, 0x76, 0x14, 0x03, 0x00},
		.id_len    = 8,
		.chipsize  = SZ_256,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 64,
		.options   = 0,
	}, {
		.name      = "TC58NVG5T2JTA00",
		.id        = {0x98, 0xD7, 0x98, 0x92, 0x72, 0x57, 0x08, 0x10},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_4M,
		.oobsize   = 1024,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2012,
	}, {
		.name      = "TC58TEG5DCKTAx0",
		.id        = {0x98, 0xD7, 0x84, 0x93, 0x72, 0x50, 0x08, 0x04},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_16K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2013,
	}, {
		.name      = "Tx58TEGxDDKTAx0",
		.id        = {0x98, 0xDE, 0x94, 0x93, 0x76, 0x50},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_16K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2013,
		.flags     = NAND_MODE_SYNC_TOGGLE10,
	},{
		.name      = "TC58TEG5DClTA0C",
		.id        = {0x98, 0xD7, 0x84, 0x93, 0x72, 0x51, 0x08, 0x04},
		.id_len    = 8,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_16K,
		.erasesize = SZ_4M,
		.oobsize   = 1280,
		.options   = 0,
		.read_retry_type = NAND_RR_TOSHIBA_V2013,
		.flags     = NAND_MODE_SYNC_TOGGLE10,
	}, {
		.name      = "K9GAG08U0F",
		.id        = {0xEC, 0xD5, 0x94, 0x76, 0x54, 0x43, 0x00, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 512,
		.options   = 0,
	}, {
		.name      = "K9LBG08U0M",
		.id        = {0xEC, 0xD7, 0x55, 0xB6, 0x78, 0x00, 0x00, 0x00},
		.id_len    = 5,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_512K,
		.oobsize   = 128,
		.options   = 0,
	}, {
		.name      = "K9GBG08U0A",
		.id        = {0xEC, 0xD7, 0x94, 0x7A, 0x54, 0x43, 0x00, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 640,
		.options   = 0,
		.read_retry_type = NAND_RR_SAMSUNG,
	}, {
		.name      = "K9GBG08U0B",
		.id        = {0xEC, 0xD7, 0x94, 0x7E, 0x64, 0x44, 0x00, 0x00},
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_1M,
		.oobsize   = 1024,
		.options   = 0,
		.read_retry_type = NAND_RR_SAMSUNG,
	}, {
		.name      = "H27UBG8T2C",
		.id        = {0xAD, 0xD7, 0x94, 0x91, 0x60, 0x44, },
		.id_len    = 6,
		.chipsize  = SZ_4K,
		.pagesize  = SZ_8K,
		.erasesize = SZ_2M,
		.oobsize   = 640,
		.options   = 0,
		.read_retry_type = NAND_RR_HYNIX_BG_CDIE,
	}, {
		.name      = "P1UAGA30AT-GCA",
		.id        = {0xC8, 0xD5, 0x14, 0x29, 0x34, 0x01, },
		.id_len    = 6,
		.chipsize  = SZ_2K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_512K,
		.oobsize   = 218,
		.options   = 0,
	}, {   
		.name      = "PSU8GA30AT-GIA/ASU8GA30IT-G30CA",
		.id        = {0xC8, 0xD3, 0x90, 0x19, 0x34, 0x01, },
		.id_len    = 6,
		.chipsize  = SZ_1K,
		.pagesize  = SZ_4K,
		.erasesize = SZ_256K,
		.oobsize   = 218,
		.options   = 0,
	}, {        /* SLC 1bit/512 */
		.name      = "PSU2GA30AT",
		.id        = {0x7F, 0x7F, 0x7F, 0x7F, 0xC8, 0xDA, 0x00, 0x15, },
		.id_len    = 8,
		.chipsize  = SZ_256,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 64,
		.options   = 0,
	}, {        /* SLC 4bit/512 */
		.name      = "PMND1G08U3B",
		.id        = {0xF8, 0xF1, 0x80, 0x91, },
		.id_len    = 4,
		.chipsize  = SZ_128,
		.pagesize  = SZ_2K,
		.erasesize = SZ_128K,
		.oobsize   = 64,
		.options   = 0,
	},

	LEGACY_ID_NAND("NAND 4MiB 5V 8-bit",   0x6B, 4, SZ_8K, 0),
	LEGACY_ID_NAND("NAND 4MiB 3,3V 8-bit", 0xE3, 4, SZ_8K, 0),
	LEGACY_ID_NAND("NAND 4MiB 3,3V 8-bit", 0xE5, 4, SZ_8K, 0),
	LEGACY_ID_NAND("NAND 8MiB 3,3V 8-bit", 0xD6, 8, SZ_8K, 0),
	LEGACY_ID_NAND("NAND 8MiB 3,3V 8-bit", 0xE6, 8, SZ_8K, 0),

	LEGACY_ID_NAND("NAND 16MiB 1,8V 8-bit",  0x33, 16, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 16MiB 3,3V 8-bit",  0x73, 16, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 16MiB 1,8V 16-bit", 0x43, 16, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 16MiB 3,3V 16-bit", 0x53, 16, SZ_16K, NAND_BUSWIDTH_16),

	LEGACY_ID_NAND("NAND 32MiB 1,8V 8-bit",  0x35, 32, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 32MiB 3,3V 8-bit",  0x75, 32, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 32MiB 1,8V 16-bit", 0x45, 32, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 32MiB 3,3V 16-bit", 0x55, 32, SZ_16K, NAND_BUSWIDTH_16),

	LEGACY_ID_NAND("NAND 64MiB 1,8V 8-bit",  0x36, 64, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 64MiB 3,3V 8-bit",  0x76, 64, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 64MiB 1,8V 16-bit", 0x46, 64, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 64MiB 3,3V 16-bit", 0x56, 64, SZ_16K, NAND_BUSWIDTH_16),

	LEGACY_ID_NAND("NAND 128MiB 1,8V 8-bit",  0x78, 128, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 128MiB 1,8V 8-bit",  0x39, 128, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 128MiB 3,3V 8-bit",  0x79, 128, SZ_16K, 0),
	LEGACY_ID_NAND("NAND 128MiB 1,8V 16-bit", 0x72, 128, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 128MiB 1,8V 16-bit", 0x49, 128, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 128MiB 3,3V 16-bit", 0x74, 128, SZ_16K, NAND_BUSWIDTH_16),
	LEGACY_ID_NAND("NAND 128MiB 3,3V 16-bit", 0x59, 128, SZ_16K, NAND_BUSWIDTH_16),

	LEGACY_ID_NAND("NAND 256MiB 3,3V 8-bit", 0x71, 256, SZ_16K, 0),

	/*
	 * These are the new chips with large page size. Their page size and
	 * eraseblock size are determined from the extended ID bytes.
	 */

	/* 512 Megabit */
	EXTENDED_ID_NAND("NAND 64MiB 1,8V 8-bit",  0xA2,  64, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64MiB 1,8V 8-bit",  0xA0,  64, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64MiB 3,3V 8-bit",  0xF2,  64, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64MiB 3,3V 8-bit",  0xD0,  64, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64MiB 3,3V 8-bit",  0xF0,  64, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64MiB 1,8V 16-bit", 0xB2,  64, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 64MiB 1,8V 16-bit", 0xB0,  64, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 64MiB 3,3V 16-bit", 0xC2,  64, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 64MiB 3,3V 16-bit", 0xC0,  64, LP_OPTIONS16),

	/* 1 Gigabit */
	EXTENDED_ID_NAND("NAND 128MiB 1,8V 8-bit",  0xA1, 128, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 128MiB 3,3V 8-bit",  0xF1, 128, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 128MiB 3,3V 8-bit",  0xD1, 128, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 128MiB 1,8V 16-bit", 0xB1, 128, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 128MiB 3,3V 16-bit", 0xC1, 128, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 128MiB 1,8V 16-bit", 0xAD, 128, LP_OPTIONS16),

	/* 2 Gigabit */
	EXTENDED_ID_NAND("NAND 256MiB 1,8V 8-bit",  0xAA, 256, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 256MiB 3,3V 8-bit",  0xDA, 256, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 256MiB 1,8V 16-bit", 0xBA, 256, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 256MiB 3,3V 16-bit", 0xCA, 256, LP_OPTIONS16),

	/* 4 Gigabit */
	EXTENDED_ID_NAND("NAND 512MiB 1,8V 8-bit",  0xAC, 512, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 512MiB 3,3V 8-bit",  0xDC, 512, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 512MiB 1,8V 16-bit", 0xBC, 512, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 512MiB 3,3V 16-bit", 0xCC, 512, LP_OPTIONS16),

	/* 8 Gigabit */
	EXTENDED_ID_NAND("NAND 1GiB 1,8V 8-bit",  0xA3, 1024, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 1GiB 3,3V 8-bit",  0xD3, 1024, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 1GiB 1,8V 16-bit", 0xB3, 1024, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 1GiB 3,3V 16-bit", 0xC3, 1024, LP_OPTIONS16),

	/* 16 Gigabit */
	EXTENDED_ID_NAND("NAND 2GiB 1,8V 8-bit",  0xA5, 2048, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 2GiB 3,3V 8-bit",  0xD5, 2048, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 2GiB 1,8V 16-bit", 0xB5, 2048, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 2GiB 3,3V 16-bit", 0xC5, 2048, LP_OPTIONS16),

	/* 32 Gigabit */
	EXTENDED_ID_NAND("NAND 4GiB 1,8V 8-bit",  0xA7, 4096, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 4GiB 3,3V 8-bit",  0xD7, 4096, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 4GiB 1,8V 16-bit", 0xB7, 4096, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 4GiB 3,3V 16-bit", 0xC7, 4096, LP_OPTIONS16),

	/* 64 Gigabit */
	EXTENDED_ID_NAND("NAND 8GiB 1,8V 8-bit",  0xAE, 8192, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 8GiB 3,3V 8-bit",  0xDE, 8192, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 8GiB 1,8V 16-bit", 0xBE, 8192, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 8GiB 3,3V 16-bit", 0xCE, 8192, LP_OPTIONS16),

	/* 128 Gigabit */
	EXTENDED_ID_NAND("NAND 16GiB 1,8V 8-bit",  0x1A, 16384, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 16GiB 3,3V 8-bit",  0x3A, 16384, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 16GiB 1,8V 16-bit", 0x2A, 16384, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 16GiB 3,3V 16-bit", 0x4A, 16384, LP_OPTIONS16),

	/* 256 Gigabit */
	EXTENDED_ID_NAND("NAND 32GiB 1,8V 8-bit",  0x1C, 32768, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 32GiB 3,3V 8-bit",  0x3C, 32768, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 32GiB 1,8V 16-bit", 0x2C, 32768, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 32GiB 3,3V 16-bit", 0x4C, 32768, LP_OPTIONS16),

	/* 512 Gigabit */
	EXTENDED_ID_NAND("NAND 64GiB 1,8V 8-bit",  0x1E, 65536, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64GiB 3,3V 8-bit",  0x3E, 65536, LP_OPTIONS),
	EXTENDED_ID_NAND("NAND 64GiB 1,8V 16-bit", 0x2E, 65536, LP_OPTIONS16),
	EXTENDED_ID_NAND("NAND 64GiB 3,3V 16-bit", 0x4E, 65536, LP_OPTIONS16),

	{NULL}
};
