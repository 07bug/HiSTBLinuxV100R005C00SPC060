/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 *
 * (C) Copyright 2008 Atmel Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <environment.h>
#include <malloc.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>

#ifndef CONFIG_ENV_SPI_BUS
# define CONFIG_ENV_SPI_BUS	0
#endif
#ifndef CONFIG_ENV_SPI_CS
# define CONFIG_ENV_SPI_CS		0
#endif
#ifndef CONFIG_ENV_SPI_MAX_HZ
# define CONFIG_ENV_SPI_MAX_HZ	1000000
#endif
#ifndef CONFIG_ENV_SPI_MODE
# define CONFIG_ENV_SPI_MODE	SPI_MODE_3
#endif

DECLARE_GLOBAL_DATA_PTR;

/* references to names in env_common.c */
extern uchar default_environment[];

extern env_t *env_ptr;

static struct spi_flash *env_flash;

static uchar sf_env_get_char_spec(int index)
{
	return *((uchar *)(gd->env_addr + index));
}

static int sf_saveenv(void)
{
	u32 saved_size, saved_offset;
	char *saved_buffer = NULL;
	u32 sector = 1;
	int ret;
	u_int32_t erase_length;
	struct mtd_info_ex *spiflash_info = get_spiflash_info();

	env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
			CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);

	if (!env_flash) {
		puts("Environment SPI flash not initialized\n");
		return 1;
	}

	/* Is the sector larger than the env (i.e. embedded) */
	if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
		saved_size = CONFIG_ENV_SECT_SIZE - CONFIG_ENV_SIZE;
		saved_offset = CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE;
		saved_buffer = malloc(saved_size);
		if (!saved_buffer) {
			ret = 1;
			goto done;
		}
		ret = spi_flash_read(env_flash, saved_offset, saved_size, saved_buffer);
		if (ret)
			goto done;
	}

	if (CONFIG_ENV_SIZE > CONFIG_ENV_SECT_SIZE) {
		sector = CONFIG_ENV_SIZE / CONFIG_ENV_SECT_SIZE;
		if (CONFIG_ENV_SIZE % CONFIG_ENV_SECT_SIZE)
			sector++;
	}

	erase_length = (sector * CONFIG_ENV_SECT_SIZE);
	if (erase_length < spiflash_info->erasesize)
	{
		printf("Warning: Erase size 0x%08x smaller than one "	\
			"erase block 0x%08x\n", erase_length, spiflash_info->erasesize);
		printf("         Erasing 0x%08x instead\n", spiflash_info->erasesize);
		erase_length = spiflash_info->erasesize;
	}
	printf("Erasing SPI flash, offset 0x%08x size %s ...",
		CONFIG_ENV_OFFSET, ultohstr(erase_length));
	ret = spi_flash_erase(env_flash, CONFIG_ENV_OFFSET, erase_length);
	if (ret)
		goto done;

	printf("done\nWriting to SPI flash, offset 0x%08x size %s ...",
		CONFIG_ENV_OFFSET, ultohstr(CONFIG_ENV_SIZE));
	ret = spi_flash_write(env_flash, CONFIG_ENV_OFFSET, CONFIG_ENV_SIZE, env_ptr);
	if (ret)
		goto done;

	if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) {
		ret = spi_flash_write(env_flash, saved_offset, saved_size, saved_buffer);
		if (ret)
			goto done;
	}

	ret = 0;
	puts("done\n");

 done:
	if (saved_buffer)
		free(saved_buffer);
	return ret;
}

static int sf_env_relocate_spec(unsigned int offset)
{
	int ret;

	env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS,
			CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
	if (!env_flash)
		goto err_probe;

	ret = spi_flash_read(env_flash, offset, CONFIG_ENV_SIZE, env_ptr);
	if (ret)
		goto err_read;

	if (crc32(0, env_ptr->data, ENV_SIZE) != env_ptr->crc)
		goto err_crc;

	gd->env_valid = 1;

	return 0;

err_read:
	spi_flash_free(env_flash);
	env_flash = NULL;
err_probe:
err_crc:
	return 1;
}

static int sf_env_init(void)
{
	/* SPI flash isn't usable before relocation */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}

struct env_common_func_t sf_env_cmn_func = {
	.env_init = sf_env_init,
	.env_get_char_spec = sf_env_get_char_spec,
	.saveenv = sf_saveenv,
	.env_relocate_spec = sf_env_relocate_spec,
	.env_name_spec = "SPI Flash",
	.env_media = BOOT_MEDIA_SPIFLASH,
};
