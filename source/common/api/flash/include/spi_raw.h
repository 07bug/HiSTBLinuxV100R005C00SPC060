#ifndef SPI_RAWH
#define SPI_RAWH
/******************************************************************************/

#include "nand.h"

HI_S32 spi_raw_init(HI_VOID);

HI_S32 spi_raw_destroy(HI_VOID);

HI_S32 spi_raw_dump_partition(HI_VOID);

HI_S32 spi_raw_read(HI_S32 fd, HI_U64 *startaddr, HI_U8 *buffer,
    HI_ULONG length, HI_U64 openaddr, HI_U64 limit_leng, HI_S32 read_oob, HI_S32 skip_badblock);

HI_S32 spi_raw_write(HI_S32 fd, HI_U64 *startaddr, HI_U8 *buffer,
    HI_ULONG length, HI_U64 openaddr, HI_U64 limit_leng, HI_S32 write_oob);

HI_S64 spi_raw_erase(HI_S32 fd, HI_U64 startaddr,
   HI_U64 length, HI_U64 openaddr, HI_U64 limit_leng);

HI_U64 spi_raw_get_start_addr(const HI_CHAR *dev_name, HI_ULONG blocksize, HI_S32 *value_valid);

HI_VOID spi_raw_get_info(HI_U64 *totalsize, HI_U32 *pagesize, HI_U32 *blocksize,
    HI_U32 *oobsize, HI_U32 *blockshift);

/******************************************************************************/
#endif /* SPI_RAWH */

