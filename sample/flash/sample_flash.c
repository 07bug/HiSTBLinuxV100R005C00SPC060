#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "hi_type.h"
#include "hi_flash.h"

enum hiflash_command
{
	CMD_NONE,
	CMD_READ,
	CMD_WRITE,
	CMD_ERASE,
	CMD_BUTT
};

static char *device;
static HI_FLASH_TYPE_E type = HI_FLASH_TYPE_BUTT;
int type_set;
static char *file;
static int input_file_set;
static int output_file_set;
static unsigned long long offset;
static int offset_set;
static unsigned long len;
static int len_set;
static int withoob;

static enum hiflash_command cmd;

HI_HANDLE handle;


/*
��������Ҫ����hiflash�Բ⡣��
sample����:
����:
sample_flash -E [-D device] -T nand|spi|emmc:�����豸device
sample_flash -E [-D device] -T nand|spi|emmc [-s 0x0] [-l 0x100000]
�����豸device�ϴ�0��ʼ������1M����,emmc ����Ҫ������

��:
sample_flash -R [-D device] -T nand|spi|emmc [-o file] [-s 0] [-l 0x100000] [-O]
���豸device�ϴ�0��ʼ������Ϊ1M�����ݶ�����file��.��ָ��-O����oob���������ǰ����device��nand����

д:
sample_flash -W [-D device] -T nand|spi|emmc [-i file] [-s 0] [-l 0x100000] [-O]
���ļ�fileд�뵽device��0λ�ÿ�ʼ,����Ϊ1M��λ�á����ƶ�-O,��д��oob����

��������:
-E �������
-R �����
-W д���
-D �豸��.ֻ�ڲ���emmcʱ����Ϊ�գ�����flash���ͱ���Ҫ�������������������emmc�Ƚ����⣬���Բ���-D���������ڲ���kernel��boot�ȷ�����
-s ������ƫ�Ƶ�ַ����δָ����Ĭ�ϴӷ���0ƫ�ƴ�������
-l ��Ҫ�����ĳ��ȡ���δָ����Ĭ�ϲ����������������в�����������oob�������ڣ������Զ����㡣�������������顢ҳ�ȶ����������Ҫ�û����ж��롣
-o ����ļ�����δָ����Ĭ�����������.
-i �����ļ�����δ�ƶ���Ĭ�ϴ��ڴ�������������ݡ�
-O �����Ƿ��OOB����

ע:
a. ��[]�������Ĳ������Ǳ���ģ���-E -T�����������������
b. |��ʾ���򣬼�������ѡ��һ������nand|spi|emmc��ʾѡnand����spi����emmc��

!!!!!!!!!!!!!!!! ����ע�����ʹ�ñ���ʱ�����ܲ�������ϵͳ����ʹ�õķ������������ļ�ϵͳ����mount�ķ����ȡ�

��������:
1. ./sample_flash -R -D /dev/mtd3 -T nand -s 0 -l 0x20000 -O
	��/dev/mtd3��0ƫ�ƴ���ʼ�������ݳ���Ϊ0x20000�����ݣ����Ҷ���oob����/dev/mtd3��һ��nand����
2. ./sample_flash -R -D /dev/mtd4 -T nand -s 0 -l 0x10000
	��/dev/mtd4��0ƫ�ƴ���ȡ0x10000�����ݳ��ȣ�������������/dev/mtd4��һ��nand������
3. ./sample_flash  -E -D /dev/mtd5 -T nand
	����/dev/mtd5��������������������һ��nand������
4. ./sample_flash  -W -D /dev/mtd5 -T nand -i rootfs.yaffs -O
	��rootfs.yaffs�Դ�oobд��ķ�ʽ��д�뵽/dev/mtd5����nand �����ϡ�

5. ./sample_flash -W -D /dev/mmcblk0p7  -T emmc -i /mnt/image/rootfs_80M.ext3 -s 0 -l 0x5000000
	��/mnt/image/rootfs_80M.ext3д�뵽/dev/mmcblk0p7��0��ʼ����Ϊ0x5000000��λ�ã�flash����Ϊemmc

6. ./sample_flash -R -D /dev/mmcblk0p7  -T emmc -o /mnt/tmp/read_rootfs_80M.ext3 -s 0 -l 0x5000000
	��/dev/mmcblk0p7��0ƫ�ƴ���ʼ��ȡ0x5000000�������ݵ�/mnt/tmp/read_rootfs_80M.ext3��flash����Ϊemmc

7. ./sample_flash -R -T emmc -s 0x200000 -l 0x300000 -o /mnt/2M3M
	��emmc flash��ƫ��0x200000����ʼ����ȡ0x300000Byte�����ݣ�д��/mnt/2M3M�ļ��

8. ./sample_flash -W -T emmc -s 0x200000 -l 0x2e0000 -i ./hi_kernel.bin
	��./hi_kernel.bin�ļ�д�뵽emmc flash��0x200000Mƫ�ƴ������д0x2e0000Byte���ݡ�

	������-D ����ʱ����ʽ����Ҫ�������д�ķ�ʽ����emmc��������ˣ�����ָ��-s��-l��������hiflash��Ҫ������flash����λ�á�
*/
static void usage(char* base)
{
	printf("%s: sample for flash operation.\n"\
		"\t\t%s -R -D device -T nand|spi|emmc [-o output_file] [-s offset_in_partition] [-l length] [-O]\n"\
		"\t\t%s -W -D device -T nand|spi|emmc [-i input_file] [-s offset_in_partition] [-l length] [-O]\n"\
		"\t\t%s -E -D device -T nand|spi|emmc [-s offset_in_partition] [-l length]\n"\
		"\t\t -E: Erase command.\n"\
		"\t\t -R: Read command.\n"\
		"\t\t -W: Write command.\n"\
		"\t\t -D: Device name.\n"\
		"\t\t -T: Tell me which type of flash the device is.\n"\
		"\t\t -s: Start address in device(partition).Default to offset 0.\n"\
		"\t\t -l: Operation length. defualt to full partition length. and not inlcude oob size if -O set\n"\
		"\t\t -o: Output file. Defualt to print to serial.\n"\
		"\t\t -i: Input file. defualt to random value in memory.\n"\
		"\t\t -O: If you wish to operate the oob area, set -O.defualt no.\n",
		  base, base, base, base);

	exit(-1);
}

extern char *optarg;
extern int optind, opterr, optopt;

static void process_option(int argc, char *argv[])
{
	int op;
	opterr = 0;

	while ((op = getopt(argc, argv, "RWED:T:s:l:o:i:O")) != -1) {
		switch (op) {
			case 'R' :
				cmd = CMD_READ;
				printf("command read, ");
				break;
			case 'W' :
				cmd = CMD_WRITE;
				printf("command write, ");
				break;
			case 'E':
				cmd = CMD_ERASE;
				printf("command erase, ");
				break;
			case 'D':
				device = optarg;
				printf("device:%s, ", device);
				break;
			case 'T':
				printf("flash :");
				if (optarg[0] == 'N' || optarg[0] == 'n') {
					type = HI_FLASH_TYPE_NAND_0;
					printf("nand, ");
				} else if (optarg[0] == 'S' || optarg[0] == 's') {
					type = HI_FLASH_TYPE_SPI_0;
					printf("spi, ");
				} else if (optarg[0] == 'E' || optarg[0] == 'e') {
					type = HI_FLASH_TYPE_EMMC_0;
					printf("emmc, ");
				} else {
					type_set = 0;
					break;
				}
				type_set = 1;
				break;
			case 's':
				offset_set = 1;
				offset = strtoull(optarg, 0, 16);
				printf("offset: 0x%llx, ",offset);
				break;
			case 'l':
				len_set = 1;
				len = strtoul(optarg, 0, 16);
				printf("len: 0x%lx, ",len);
				break;
			case 'o':
				output_file_set = 1;
				file = optarg;
				printf("output file: %s, ",file);
				break;
			case 'i':
				input_file_set = 1;
				file = optarg;
				printf("input file: %s, ",file);
				break;
			case 'O':
				withoob = 1;
				printf("with oob, ");
				break;
			case 'h':
			case 'H':
			default:
				usage(argv[0]);
				exit(0);
		}
	}
	printf("\r\n");
}
static int check_param(void)
{
	if (cmd != CMD_ERASE && cmd != CMD_WRITE && cmd != CMD_READ) {
		printf("command %d not right!\n",cmd);
		return -1;
	}
	if (type >= HI_FLASH_TYPE_BUTT || !type_set) {
		printf("flash %d type not right!\n", type);
		return -1;
	}

	if (cmd == CMD_ERASE && (output_file_set || input_file_set)) {
		printf("cmd is erase, but file set!\n");
		return -1;
	}

	if (cmd == CMD_WRITE && output_file_set) {
		printf("cmd is write but output file set!\n");
		return -1;
	}

	if (cmd == CMD_READ && input_file_set) {
		printf("cmd is read but input file set\n");
		return -1;
	}

	if (input_file_set && output_file_set) {
		printf("input file and output file set both!\n");
		return -1;
	}

	if (type != HI_FLASH_TYPE_EMMC_0 && (!device || !device[0])) {
		printf("this program require device param if flash is nand or spi!\n");
		return -1;
	}
	if (type == HI_FLASH_TYPE_EMMC_0 && !offset_set && (!device || !device[0])) {
		printf("emmc require device or offset at least!\n");
		return -1;
	}

	if (withoob && type != HI_FLASH_TYPE_NAND_0) {
		printf("operate oob but flash is not nand!\n");
		return -1;
	}

	return 0;

}
static int print_sn = 0;
static void print_data(unsigned char *bf, int len)
{
	int i;
	for (i = 0; i < len/4; i+=4)
	{
		if (i%16 == 0) {
			printf("%08x: ", i);
		}
		printf("%08x ", *(unsigned int*)(bf + i));

		if (((print_sn + 1) % 4) == 0)
			printf("\n");

		print_sn++;
	}
}
#define BUF_SZ 0x10000UL /* 64KB buffer */
static int flash_sample_read(void)
{
	int fd = -1;
	unsigned char tmp[BUF_SZ];
	int ret, read= 0;
	HI_Flash_InterInfo_S info;
	int step, sz;
	int cnt;
	print_sn = 0;

	if (output_file_set) {
		fd = open(file,O_RDWR|O_CREAT|O_LARGEFILE);
		if (fd < 0) {
			printf("Fail to open %s\n", file);
			perror("Error:");
			exit(-1);
		}
	}

	ret = HI_Flash_GetInfo(handle, &info);
	if (ret) {
		printf("Fail to get info, ret: 0x%x\n",ret);
		exit(-1);
	}

	if (!offset_set)
		offset = 0;
	if (!len_set)
		len = info.PartSize;

	if (info.PageSize)
		cnt = step = info.PageSize;
	else if (info.BlockSize) {
		if (BUF_SZ >= info.BlockSize)
			cnt = step = info.BlockSize;
		else
			cnt = step = BUF_SZ;
	} else {
		printf("Both of pagesize and block size is 0!\n");
		exit(-1);
	}

	if (withoob) {

		if (offset % info.PageSize) {
			printf("Offset must page(%d) aliagn!\n", info.PageSize);
			exit(-1);
		}

		cnt = info.PageSize + info.OobSize;
	}

	if (type != HI_FLASH_TYPE_EMMC_0) {
		/* find max step */
		for (sz = 0; ; sz ++) {
			if (withoob) {
				if (step + info.OobSize +info.PageSize > BUF_SZ && cnt + info.PageSize + info.OobSize > BUF_SZ) {
					break;
				}
				step += info.PageSize;
				cnt += info.PageSize + info.OobSize;
			}
			else {
				if (step + info.PageSize > BUF_SZ && cnt + info.PageSize > BUF_SZ) {
					break;
				}
				step += info.PageSize;
				cnt += info.PageSize;
			}
		}
	}
	printf("Read info: read cnt: %d(may include oob, lie on -O, step :%d(not include oob), len:0x%lx\n", cnt, step, len);
	/* Fix emmc read no-ext partitions. the -s param will be use to open the desired start address .
	 * The -l param will be used to set the desired partition size.
	 * The purpose of command like : ./sample_flash -R -T emmc -s 0x200000 -l 0x200
	 * is want to open partition from 0x200000 and len is 0x200, then read  this partiton whole out.
	 * Notes: In this command, no extended partition specified.
	 */
	if (type == HI_FLASH_TYPE_EMMC_0 && (!device || !device[0])) {
		offset = 0;
	}
	for (;len >= BUF_SZ;) {
		ret = HI_Flash_Read(handle, offset, tmp, cnt,
				withoob ? HI_FLASH_RW_FLAG_WITH_OOB : HI_FLASH_RW_FLAG_RAW);
		if (ret <= 0 || ret != cnt) {
			printf("\nFail to read,ret:0x%x, offset:0x%llx, len:0x%lx, %s, already read:0x%x\n",
				ret, offset, len, withoob?"with oob":"no oob", read);
			if (output_file_set)
				close(fd);
			exit(-1);
		}

		if (output_file_set)
			write(fd, tmp, ret);
		else
			print_data(tmp, ret);

		len -=step;
		read += cnt;
		offset += step;
	}

	if (len < BUF_SZ && len > 0) {

		if (withoob)
			len += (len / info.PageSize) * info.OobSize;

		ret = HI_Flash_Read(handle, offset, tmp, len,
				withoob ? HI_FLASH_RW_FLAG_WITH_OOB : HI_FLASH_RW_FLAG_RAW);
		if (ret < 0 || ret != len) {
			printf("\nFail to read 2, ret:0x%x, offset:0x%llx, len:0x%lx, %s, already read 0x%x\n",
				ret, offset, len, withoob?"with oob":"no oob", read);
			if (output_file_set)
				close(fd);
			exit(-1);
		}

		if (output_file_set)
			write(fd, tmp, ret);
		else
			print_data(tmp, ret);

		read += ret;
		offset += BUF_SZ;
	}

	printf("\ntotal read 0x%x Bytes.\n",read);

	if (output_file_set)
		close(fd);

	return 0;
}
static int flash_sample_write(void)
{
	int fd = -1;
	unsigned char data[BUF_SZ];
	int ret;
	HI_Flash_InterInfo_S info;
	int written = 0;
	int cnt;
	int step;
	int eof = 0;
	int sz ;

	if (input_file_set) {
		fd = open(file, O_RDONLY);
		if (fd < 0) {
			printf("Fail to open %s!\n", file);
			perror("Error:");
			exit(-1);
		}
	}


	ret = HI_Flash_GetInfo(handle, &info);
	if (ret) {
		printf("Failt to getinfo, ret 0x%x\n",ret);
		exit(-1);
	}

	if (!offset_set)
		offset = 0;
	if (!len_set)
		len = info.PartSize;


	if (info.PageSize)
		cnt = step = info.PageSize;
	else if (info.BlockSize) {
		if (BUF_SZ >= info.BlockSize)
			cnt = step = info.BlockSize;
		else
			cnt = step = BUF_SZ;
	} else {
		printf("Both of pagesize and block size is 0!\n");
		exit(-1);
	}

	if (withoob)
	{
		cnt = info.OobSize +info.PageSize;
		if (cnt > BUF_SZ) {
			printf("BUF_SZ too small. Enlarge it and re-compile this program!\n");
			exit(-1);
		}
		step = info.PageSize;
	}

	if (type != HI_FLASH_TYPE_EMMC_0) {

		/* find max step */
		for (sz = 0; ; sz ++) {
			if (withoob) {
				if (step + info.PageSize > BUF_SZ || cnt + info.OobSize +info.PageSize > BUF_SZ) {
					break;
				}
				step += info.PageSize;
				cnt += info.OobSize +info.PageSize;
			}
			else {
				if (step + info.PageSize > BUF_SZ || cnt +info.PageSize > BUF_SZ) {
					break;
				}
				step += info.PageSize;
				cnt += info.PageSize;
			}
		}
	}

	if (info.PageSize)
		printf("Write info: per pages:%d, write step(not include oob) :%d, read count(may include oob, lie on -O) :%d\n",
				step / info.PageSize, step, cnt);
	else
		printf("Write info: Write step(not include oob) :%d, read count(may include oob, lie on -O) :%d\n",
				 step, cnt);

	ret = HI_Flash_Erase(handle, offset, len);
	if (type != HI_FLASH_TYPE_EMMC_0 &&ret != len) {
		printf("Fail to erase offset 0x%llx, len 0x%lx, ret:0x%x\n",offset, len,ret);
		exit(-1);
	}
	else if (type == HI_FLASH_TYPE_EMMC_0 && ret) {
		printf("Fail to erase offset 0x%llx, len 0x%lx, ret:0x%x\n",offset, len,ret);
		exit(-1);
	}
	printf("Erase from 0x%08llx size 0x%lx done!\n",offset, len);

	/* Fix emmc read no-ext partitions. the -s param will be use to open the desired start address .
	 * The -l param will be used to set the desired partition size.
	 * The purpose of command like : ./sample_flash -R -T emmc -s 0x200000 -l 0x200
	 * is want to open partition from 0x200000 and len is 0x200, then read  this partiton whole out.
	 * Notes: In this command, no extended partition specified.
	 */
	if (type == HI_FLASH_TYPE_EMMC_0 && (!device || !device[0])) {
		offset = 0;
	}
	while (len >= step && !eof) {
		if (input_file_set)
			ret = read(fd, data, cnt);
		if (ret < cnt && ret > 0) {
			cnt = ret;
			eof = 1;
		}

		ret = HI_Flash_Write(handle, offset, data, cnt,
				(withoob ? HI_FLASH_RW_FLAG_WITH_OOB : HI_FLASH_RW_FLAG_RAW));
		if (ret < 0 || cnt != ret) {
			printf("Fail to write, ret:0x%x, offset:0x%llx, cnt:%d\n",
				ret, offset,cnt);
			exit(-1);
		}
		written += cnt;
		len -= step;
		offset += step;
	}

	if (len < BUF_SZ && len > 0 && !eof) {

		if (withoob)
			len += (len / info.PageSize) * info.OobSize;

		if (input_file_set)
			ret = read(fd, data, len);
		if (ret < len && ret > 0) {
			len = ret;
			eof = 1;
		}

		ret = HI_Flash_Write(handle, offset, data, len,
				withoob ? HI_FLASH_RW_FLAG_WITH_OOB : HI_FLASH_RW_FLAG_RAW);
		if (ret < 0 || len != ret) {
			printf("Fail to write, ret:0x%x, offset:0x%llx, cnt:%d\n",
				ret, offset,cnt);
			exit(-1);
		}
		written += len;
		len -= len;
		offset += len;
	}

	printf("Written 0x%x Bytes!\n",written);
	if (input_file_set)
		close(fd);

	return 0;

}
static int flash_sample_erase(void)
{
	int ret;
	HI_Flash_InterInfo_S info;

	ret = HI_Flash_GetInfo(handle, &info);
	if (ret) {
		printf("Fail to get info, ret:x0%x\n", ret);
		exit(-1);
	}

	if (!offset_set)
		offset = 0;
	if (!len_set)
		len = info.PartSize;

	ret = HI_Flash_Erase(handle, offset, len);
	if (ret < 0 || ret != len) {
		printf("Fail to erase offset:0x%llx, len:0x%lx, ret:0x%x\n", offset, len, ret);
		exit(-1);
	}

	return 0;
}
int main(int argc, char *argv[])
{
	process_option(argc, argv);

	if (check_param())
		usage(argv[0]);

	handle = HI_Flash_Open(type, device, offset,len);
	if (INVALID_FD == handle) {
		printf("Fail to open %s\n",device);
		exit(-1);
	}

	if (cmd == CMD_READ)
		flash_sample_read();
	else if (cmd == CMD_WRITE)
		flash_sample_write();
	else if (cmd == CMD_ERASE)
		flash_sample_erase();
	else
		usage(argv[0]);

	HI_Flash_Close(handle);
	exit(0);
}
