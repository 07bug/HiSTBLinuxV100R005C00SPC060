/******************************************************************************
 *  Copyright (C) 2016 Hisilicon Technologies CO.,LTD.
 *
 * Create By Hisilicon 2017.4.15
 *
 ******************************************************************************/

#include "mailbox.h"
#include <asm/io.h>
#include <stdio.h>

/******************************************************************************/

#define tole(x) (x)

extern void udelay(unsigned int usec);
extern void *memcpy(void *dest, const void *src, unsigned int n);

/* ========================================================================
 * Table of CRC-32's of all single-byte values (made by make_crc_table)
 */

static int crc_table_empty;
static unsigned int crc_table[256];

static void make_crc_table(void)
{
	unsigned int c;
	unsigned int n, k;
	unsigned int poly;       /* polynomial exclusive-or pattern */
	/* terms of polynomial defining this crc (except x^32): */
	static const unsigned char p[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26};

	/* make exclusive-or pattern from polynomial (0xedb88320L) */
	poly = 0L;
	for (n = 0; n < sizeof(p)/sizeof(unsigned char); n++)
	      poly |= 1L << (31 - p[n]);

	for (n = 0; n < 256; n++) {
		c = (unsigned int)n;
		for (k = 0; k < 8; k++)
		      c = c & 1 ? poly ^ (c >> 1) : c >> 1;
		crc_table[n] = tole(c);
	}
	crc_table_empty = 0;
}

/* ========================================================================= */
#  define DO_CRC(x) crc = tab[(crc ^ (x)) & 255] ^ (crc >> 8)

/* ========================================================================= */

unsigned int crc32_unit(unsigned int crc, const unsigned int *buf, unsigned int len)
{
	const unsigned int *tab = crc_table;
	const unsigned int *b = buf;
	unsigned int rem_len;

	if (crc_table_empty)
	      make_crc_table();

	/* Align it */
	if (((long)b) & 3 && len) {
		unsigned char *p = (unsigned char *)b;
		do {
			DO_CRC(*p++);
		} while ((--len) && ((long)p)&3);
		b = (unsigned int *)p;
	}

	rem_len = len & 3;
	len = len >> 2;
	for (--b; len; --len) {
		/* load data 32 bits wide, xor data 32 bits wide. */
		crc ^= *++b; /* use pre increment for speed */
		DO_CRC(0);
		DO_CRC(0);
		DO_CRC(0);
		DO_CRC(0);
	}
	len = rem_len;
	/* And the last few bytes */
	if (len) {
		unsigned char *p = (unsigned char *)(b + 1) - 1;
		do {
			DO_CRC(*++p); /* use pre increment for speed */
		} while (--len);
	}

	return crc;
}
#undef DO_CRC

unsigned int crc32_priv (unsigned int crc, const unsigned int *p, unsigned int len)
{
	return crc32_unit(crc ^ 0xffffffffL, p, len) ^ 0xffffffffL;
}

int mailbox_get(unsigned int *command, unsigned int *argv, unsigned int wait_us)
{
	ACPU_INTR_STATUS_U un_mbx_intr;
	unsigned int wait_time = 0;
	unsigned int crc_value = 0;
	unsigned int loop = 0;
	unsigned int temp[8] = {0};

	if (wait_us == 0)
		wait_time = 0xFFFFFFFF;
	else
		wait_time = wait_us;

	/* wait until there are data in mailbox */
	loop = 0;
	do {
		un_mbx_intr.u32 = readl(ACPU_INTR_STATUS);

		if(un_mbx_intr.bits.acpu_intr)
			break;

		udelay(1);

		loop++;
	} while(loop < wait_time);

	if (loop >= wait_time || !un_mbx_intr.bits.acpu_intr) {
		printf("Mailbox timeout!\n");
		return -1;
	}

	writel(un_mbx_intr.u32, ACPU_INTR_STATUS);

	*command = readl(CMD_SCPU_TO_ACPU(0));
	crc_table_empty = 1;
	memcpy(temp, command, 4);

	crc_value = crc32_priv(crc_value, temp, 4);

	switch (*command) {
		case MBX_TYPE_CMD_PROCESS_OK :
		case MBX_TYPE_CMD_PROCESS_FAILURE :
			*argv = readl(CMD_SCPU_TO_ACPU(1));
			memcpy(temp, argv, 4);
			crc_value = crc32_priv(crc_value, temp, 4);
			*(argv + 1) = readl(CMD_SCPU_TO_ACPU(2));

			if (*argv != 0x0) {
				printf("Mailbox command format error!\n");
				return -1;
			}

			if (crc_value != *(argv + 1)) {
				printf("Mailbox command crc check error!\n");
				return -1;
			}
			break;
		default:
			printf("Unknown mailbox command type!\n");
			return -1;
	}

	return 0;
}
/******************************************************************************/

int mailbox_set(unsigned int *command, unsigned int *argv, unsigned int argc, unsigned int wait_us)
{
	CMD_SEND_ACPU_TO_SCPU_U un_mbx_send;
	SCPU_INTR_FROM_ACPU_STATUS_U un_mbx_intr;
	unsigned int wait_time = 0;
	unsigned int crc_value = 0;
	unsigned int i = 0;
	unsigned int temp[8] = {0};

	if (wait_us == 0)
		wait_time = 0xFFFFFFFF;
	else
		wait_time = wait_us;

	/* wait until there are no data in mailbox */
	i = 0;
	do {
		un_mbx_intr.u32 = readl(SCPU_INTR_FROM_ACPU_STATUS);

		if(!un_mbx_intr.bits.scpu_intr_from_acpu)
			break;

		udelay(1);
		i++;
	} while(i < wait_time);

	if (i >= wait_time || un_mbx_intr.bits.scpu_intr_from_acpu) {
		printf("Wait mailbox empty timeout!\n");
		return -1;
	}

	writel(*command, CMD_ACPU_TO_SCPU(0));
	crc_table_empty = 1;
	memcpy(temp, command, 4);
	crc_value = crc32_priv(crc_value, temp, 4);

	writel(argc, CMD_ACPU_TO_SCPU(1));

	for ( i = 0 ; i < argc ; i++ ) {
		writel(argv[i], CMD_ACPU_TO_SCPU(2 + i));
	}

	*temp = argc;
	memcpy(temp + 1, argv, argc * 4);
	crc_value = crc32_priv(crc_value, temp, (argc + 1) * 4);
	writel(crc_value, CMD_ACPU_TO_SCPU(2 + i));

	un_mbx_send.u32 = readl(CMD_SEND_ACPU_TO_SCPU);
	un_mbx_send.bits.cmd_send_acpu2scpu = 1;
	writel(un_mbx_send.u32, CMD_SEND_ACPU_TO_SCPU);

	/* wait until there are data in mailbox */
	i = 0;
	do {
		un_mbx_intr.u32 = readl(SCPU_INTR_FROM_ACPU_STATUS);
		if (!un_mbx_intr.bits.scpu_intr_from_acpu)
			break;
		udelay(1);
		i++;
	} while(i < wait_time);

	if (i >= wait_time || un_mbx_intr.bits.scpu_intr_from_acpu) {
		printf("Send to mailbox timeout!\n");
		return -1;
	}

	return 0;
}
/******************************************************************************/

