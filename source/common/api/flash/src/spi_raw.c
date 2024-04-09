#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "hi_flash.h"
#include "nand.h"
#include "spi_raw.h"
#include "hi_debug.h"
#include "hi_type.h"

static struct nand_raw_ctrl * spiraw_ctrl = NULL;

/*****************************************************************************/

HI_S32 spi_raw_init(HI_VOID)
{
    HI_S32 ix;
    HI_S32 dev;
    HI_S32 readonly;
    HI_S32 max_partition;
    //struct stat status;
    struct mtd_partition *ptn;
    struct mtd_info_user mtdinfo;

    // HI_CHAR buf[sizeof(DEV_MTDBASE) + 5] = DEV_MTDBASE;
    // HI_CHAR *ptr = buf + sizeof(DEV_MTDBASE) - 1;
    HI_CHAR buf[PATH_MAX];

    if (spiraw_ctrl)
        return 0;

    if (0 == (max_partition = get_max_partition()))
    {
#ifdef SPI_RAW_DBG
        HI_PRINT("Can't find mtd device at /dev/mtdx.\n");
#endif
        return -1;
    }

    if (++max_partition >= MAX_MTD_PARTITION)
    {
        HI_PRINT("partition maybe more than %d, please increase MAX_MTD_PARTITION.\n", MAX_MTD_PARTITION);
    }

    if(0 != (flash_partition_info_init()))
    {
        DBG_OUT("Initial partition information failure.\n");
        return -1;
    }
    spiraw_ctrl = (struct nand_raw_ctrl *)malloc(sizeof(struct nand_raw_ctrl)
        + (HI_U32)max_partition * sizeof(struct mtd_partition));

    if (!spiraw_ctrl)
    {
        HI_PRINT("Not enough memory.\n");
        return -ENOMEM;
    }
    memset(spiraw_ctrl, 0, sizeof(struct nand_raw_ctrl)
        + (HI_U32)max_partition * sizeof(struct mtd_partition));

    spiraw_ctrl->num_partition = 0;
    spiraw_ctrl->size = 0;
    ptn = spiraw_ctrl->partition;

    for (ix = 0; ix < max_partition; ix++)
    {
        readonly = 0;
        ptn->fd = INVALID_FD;
        (HI_VOID)snprintf(buf, PATH_MAX, DEV_MTDBASE"%d", ix);
        dev = open(buf, O_RDWR);
        if (-1 == dev)
        {
            dev = open(buf, O_RDONLY);
            if (-1 == dev)
            {
                //HI_PRINT("Can't open \"%s\"\n", buf);
                ptn->perm =  ACCESS_NONE;
                continue;
            }
            ptn->perm = ACCESS_RD;
            readonly = 1;
        } else {
            ptn->perm = ACCESS_RDWR;
        }

        if (ioctl(dev, MEMGETINFO, &mtdinfo))
        {
            HI_PRINT("Can't get \"%s\" information.\n", buf);
            close(dev);
            continue;
        }

        if (mtdinfo.type != MTD_SPIFLASH)
        {
            close(dev);
            continue;
        }

        if ((mtdinfo.type == MTD_NANDFLASH) || (mtdinfo.type == MTD_MLCNANDFLASH))
        {
            close(dev);
            break;
        }
        HI_Flash_PartInfo_S *pstPartInfo = NULL;
        HI_CHAR devname[32];
        memset(devname, 0, sizeof(devname));
        (HI_VOID)snprintf(devname, sizeof(devname), "mtd%d", ix);
        pstPartInfo = get_flash_partition_info(HI_FLASH_TYPE_SPI_0, devname);
        if(NULL == pstPartInfo)
        {
            DBG_OUT("Can't get \"%s\" partition information.\n", devname);
            close(dev);
            continue;
        }

        strncpy(ptn->mtddev, buf, sizeof(ptn->mtddev));
        ptn->mtddev[sizeof(ptn->mtddev) - 1] = '\0';
        ptn->fd = dev;
        ptn->readonly = readonly;
  #if 0
        ptn->start = spiraw_ctrl->size;
        spiraw_ctrl->size += mtdinfo.size;
        ptn->end   = spiraw_ctrl->size - 1;
  #else
        ptn->start = pstPartInfo->StartAddr;
        ptn->end   = pstPartInfo->StartAddr + mtdinfo.size -1;
  #endif
        spiraw_ctrl->num_partition++;

        ptn++;

        if (spiraw_ctrl->num_partition == 1)
        {
            spiraw_ctrl->pagesize  = mtdinfo.writesize;
            spiraw_ctrl->blocksize = mtdinfo.erasesize;
            spiraw_ctrl->pagemask  = (mtdinfo.writesize - 1);
            spiraw_ctrl->blockmask = (mtdinfo.erasesize - 1);
            spiraw_ctrl->oobsize   = mtdinfo.oobsize;

            spiraw_ctrl->pageshift  = (HI_U32)offshift(mtdinfo.writesize);
            spiraw_ctrl->blockshift = (HI_U32)offshift(mtdinfo.erasesize);
        }
    }

    if (!spiraw_ctrl->num_partition)
    {
        free(spiraw_ctrl);
        spiraw_ctrl = NULL;
        return 0;
    }
    spiraw_ctrl->size = get_flash_total_size(HI_FLASH_TYPE_SPI_0);

    return 0;
}

HI_VOID spi_raw_get_info
(
    HI_U64 *totalsize,
    HI_U32 *pagesize,
    HI_U32 *blocksize,
    HI_U32 *oobsize,
    HI_U32 *blockshift)
{
    *totalsize  = spiraw_ctrl->size;
    *pagesize   = spiraw_ctrl->pagesize;
    *blocksize  = spiraw_ctrl->blocksize;
    *oobsize    = spiraw_ctrl->oobsize;
    *blockshift = spiraw_ctrl->blockshift;
}

/*****************************************************************************/
/*
 * warning:
 *    1. if open SPI/NOR FLASH, return 0
      2. if dev_name cannot match spiraw_ctrl, return error_valid;
 */
HI_U64 spi_raw_get_start_addr(const HI_CHAR *dev_name, HI_ULONG blocksize, HI_S32 *value_valid)
{
    struct mtd_partition *ptn;
    HI_S32 max_partition;
    HI_S32 ix;

    ptn = spiraw_ctrl->partition;

    if (0 == (max_partition = get_max_partition()))
    {
        //HI_PRINT("Can't find mtd device at /dev/mtdx.\n");
        return 0;
    }

    if (spiraw_ctrl->blocksize != blocksize)
    {
        *value_valid = 1;
        return 0;
    }

    for (ix = 0; ix <= max_partition; ix++)
    {
        if (!strncmp(ptn->mtddev, dev_name,
            strlen(ptn->mtddev) > strlen(dev_name) ?
                strlen(ptn->mtddev) : strlen(dev_name)))
        {
            break;
        }
        ptn++;
    }

    if (max_partition < ix)
    {
        *value_valid = 0;
        return 0;
    }
    else
    {
        *value_valid = 1;
        /*lint -e661*/
        return ptn->start;
        /*lint +e661*/
    }
}
/*****************************************************************************/
/*
 * warning:
 *    1. startaddr should be alignment with pagesize
 */

HI_S32 spi_raw_read
(
    HI_S32 fd,
    HI_U64 *startaddr, /* this address maybe change when meet bad block */
    HI_U8      *buffer,
    HI_ULONG       length,    /* if HI_FLASH_RW_FLAG_WITH_OOB, include oob*/
    HI_U64  openaddr,
    HI_U64  limit_leng,
    HI_S32                 read_oob,
    HI_S32                skip_badblock)
{
    HI_S32 ix;
    HI_S32 totalread = 0;
    HI_ULONG num_read  = 0;
    struct mtd_partition *ptn;
    HI_U64 offset = *startaddr;

    HI_UNUSED(openaddr);
    HI_UNUSED(skip_badblock);
    HI_UNUSED(fd);
    HI_UNUSED(limit_leng);
    HI_UNUSED(read_oob);

    if (!spiraw_ctrl)
    {
        HI_PRINT("Please initialize before use this function.\n");
        return -1;
    }
    if(NULL==buffer)
        return -1;

    if (offset >= spiraw_ctrl->size || !length)
    {
        return -1;
    }

    for (ix = 0; ix < spiraw_ctrl->num_partition && length; ix++)
    {
        ptn = &spiraw_ctrl->partition[ix];
        /*lint -save -e655 */
        if ((ptn->start <= offset) && (offset < ptn->end) && length && (ptn->perm & ACCESS_RD) && (ptn->fd != INVALID_FD))
        {
            if (offset + length > ptn->end)
            {
                num_read = (HI_ULONG)((ptn->end - offset) + 1);
            }
            else
            {
                num_read = length;
            }
            DBG_OUT(">ptn->fd=%d, length=%#lx, *startaddr=%#llx, offset=%#llx\n", ptn->fd, num_read, *startaddr, offset);

            if (lseek(ptn->fd, (long)(offset - ptn->start), SEEK_SET) != -1
                && read(ptn->fd, buffer, (size_t)num_read) != (ssize_t)num_read)
            {
                HI_PRINT("read \"%s\" fail. error(%d)\n", ptn->mtddev, errno);
                return HI_FAILURE;
            }

            buffer    += num_read;
            length    -= num_read;
            totalread += num_read;

            offset += (HI_ULONG)num_read;
        }
    }
    *startaddr = offset;

    return totalread;
}
/*****************************************************************************/
/*
 * warning:
 *    1. offset and length should be alignment with blocksize
 */
HI_S64 spi_raw_erase
(
    HI_S32 fd,
    HI_U64 startaddr,
    HI_U64 length,
    HI_U64 openaddr,
    HI_U64 limit_leng)
{
    HI_S32 ix;
    HI_S64 totalerase = 0;
    HI_U64 offset = startaddr;
    struct mtd_partition *ptn;

    HI_UNUSED(openaddr);
    HI_UNUSED(fd);
    HI_UNUSED(limit_leng);


    if (!spiraw_ctrl)
    {
        HI_PRINT("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= spiraw_ctrl->size || !length)
    {
        return -1;
    }

    if (((HI_ULONG)offset & spiraw_ctrl->blockmask)
        || ((HI_ULONG)length & spiraw_ctrl->blockmask))
    {
        HI_PRINT("offset or length should be alignment with blocksize(0x%X)\n",
            (HI_U32)spiraw_ctrl->blocksize);
        return -1;
    }

    if (offset + length > spiraw_ctrl->size)
        length = spiraw_ctrl->size - offset;

    for (ix = 0; ix < spiraw_ctrl->num_partition && length; ix++)
    {
        ptn = &spiraw_ctrl->partition[ix];

        if (ptn->readonly)
        {
            HI_PRINT("erase a read only partition \"%s\".\n", ptn->mtddev);
            return -1;
        }

        if ((ptn->start <= offset) && (offset < ptn->end) && length && (ptn->perm & ACCESS_WR) && ptn->fd != INVALID_FD)
        {
            struct erase_info_user64 eraseinfo;

            eraseinfo.start  = (HI_U64)(offset - ptn->start);
            if (offset + length > ptn->end)
            {
                eraseinfo.length = (HI_U64)((ptn->end - offset) + 1);
            }
            else
            {
                eraseinfo.length = (HI_U64)length;
            }

            DBG_OUT(">ptn->fd=%d, length=%#llx, *startaddr=%#llx, offset=%#llx\n", ptn->fd, eraseinfo.length, startaddr, offset);

            /* don't deal with */
            if (ioctl(ptn->fd, MEMERASE64, &eraseinfo))
            {
                HI_PRINT("Erase 0x%llx failed!\n", offset);
            }

            length -= eraseinfo.length;
            offset += eraseinfo.length;
            totalerase += (HI_S64)eraseinfo.length;
        }
    }
    return totalerase;
}


/*****************************************************************************/
/*
 * warning:
 *    1. startaddr should be alignment with pagesize
 */
HI_S32 spi_raw_write
(
    HI_S32 fd,
    HI_U64 *startaddr,
    HI_U8 *buffer,
    HI_ULONG length,
    HI_U64 openaddr,
    HI_U64 limit_leng,
    HI_S32 write_oob)
{
    HI_S32 ix;
    HI_S32 totalwrite = 0;
    HI_S32 num_write = 0;
    struct mtd_partition *ptn;
    HI_U64 offset = *startaddr;

    HI_UNUSED(openaddr);
    HI_UNUSED(write_oob);
    HI_UNUSED(fd);
    HI_UNUSED(limit_leng);

    if (!spiraw_ctrl)
    {
        HI_PRINT("Please initialize before use this function.\n");
        return -1;
    }

    if (offset >= spiraw_ctrl->size || !length)
    {
        return -1;
    }

    for (ix = 0; ix < spiraw_ctrl->num_partition && length; ix++)
    {
        ptn = &spiraw_ctrl->partition[ix];
        if (ptn->readonly)
        {
            HI_PRINT("Write a read only partition \"%s\".\n", ptn->mtddev);
            return -1;
        }

        if ((ptn->start <= offset) && (offset < ptn->end) && length && (ptn->perm & ACCESS_WR) && ptn->fd != INVALID_FD)
        {
            if (offset + length > ptn->end)
            {
                num_write = (HI_S32)((ptn->end - offset) + 1);
            }
            else
            {
                num_write = (HI_S32)length;
            }
            DBG_OUT(">ptn->fd=%d, length=%#x, *startaddr=%#llx, offset=%#llx\n", ptn->fd, num_write, *startaddr, offset);

            if (lseek(ptn->fd, (off_t)(offset - ptn->start), SEEK_SET) != -1
                && write(ptn->fd, buffer, (size_t)num_write) != (ssize_t)num_write)
            {
                HI_PRINT("write \"%s\" fail. error(%d)\n", ptn->mtddev, errno);
                return HI_FAILURE;
            }

            buffer     += num_write;
            length     -= (HI_U32)num_write;
            totalwrite += num_write;

            offset += (HI_ULONG)num_write;
        }
    }

    *startaddr = offset;

    return totalwrite;
}


/*****************************************************************************/

HI_S32 spi_raw_dump_partition(HI_VOID)
{
    HI_S32 ix;
    struct mtd_partition *ptn;

    if (!spiraw_ctrl)
    {
        HI_PRINT("Please initialize before use this function.\n");
        return -1;
    }

    HI_PRINT("-------------------------\n");
    HI_PRINT("mtd device   start length mode\n");
    for (ix = 0; ix < spiraw_ctrl->num_partition; ix++)
    {
        ptn = &spiraw_ctrl->partition[ix];
        if ((ptn->perm & ACCESS_RD) == ACCESS_RD) {
            HI_PRINT("%-12s ", ptn->mtddev);
            HI_PRINT("%5s ", int_to_size(ptn->start));
            HI_PRINT("%6s ", int_to_size(ptn->end + 1 - ptn->start));
            HI_PRINT("%2s ", ptn->readonly ? "r" : "rw");
            HI_PRINT("\n");
        }
    }

    return 0;
}
/*****************************************************************************/

HI_S32 spi_raw_destroy(HI_VOID)
{
    HI_S32 ix;

    if (!spiraw_ctrl)
        return 0;

    for (ix = 0; ix < spiraw_ctrl->num_partition; ix++)
    {
        if( INVALID_FD != spiraw_ctrl->partition[ix].fd)
        {
            close(spiraw_ctrl->partition[ix].fd);
        }
    }

    if( NULL != spiraw_ctrl )
    {
        free(spiraw_ctrl);
    }
    spiraw_ctrl = NULL;
    //DBG_OUT("\n");

    return 0;
}

