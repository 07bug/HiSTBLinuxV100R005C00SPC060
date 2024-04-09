#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/semaphore.h>
#include <linux/semaphore.h>
#include <asm/cacheflush.h>

#include <linux/hisilicon/tee_smmu.h>
#include "drv_mmz.h"
#include "drv_tzsmmu.h"
#include "drv_media_mem.h"
#include "hi_debug.h"

#define HI_ZERO 0

#define MAX_MEMBLOCK_NUM (1024*1024)

extern int mmz_print_level ;

static int _hi_tee_smmumem_into_ta(TEE_MEM_BUFFER_S *teebuf, u32 addr,
				   int iommu)
{
	int ret = 0;

	ret = hisi_tee_smmumem_into_ta(teebuf, addr, iommu);

	return ret;
}

static void _hi_tee_smmumem_outfrom_ta(u32 buf_phys)
{
	hisi_tee_smmumem_outfrom_ta(buf_phys);
}

/*
 * addr: no-sec address,cma or smmu
 * iommu:indicate the addr type:phys_addr or iommu
 */
u32 hi_tee_smmumem_into_ta(u32 addr, int iommu)
{
	int buf_phys = 0;
	TEE_MEM_BUFFER_S teebuf;
	u32 u32size;
	u32 base_addr;

	memset(&teebuf, 0x0, sizeof(TEE_MEM_BUFFER_S));

	teebuf.table = get_meminfo(addr, iommu, &u32size, &base_addr);
	if (!teebuf.table) {
		HI_MMZ_WARN("%s :Cannot get meminfo and check parameter!\n",__func__);
		return 0;
	}
	teebuf.u32Size = PAGE_ALIGN(u32size);
	buf_phys = _hi_tee_smmumem_into_ta(&teebuf, base_addr, iommu);
	if (!buf_phys)
		HI_MMZ_WARN("%s :_hi_tee_smmumem_into_ta failed!\n", __func__);

	return buf_phys;
}

void hi_tee_smmumem_outfrom_ta(u32 buf_phys)
{
	_hi_tee_smmumem_outfrom_ta(buf_phys);
}

/* func: set secure flag and create sec smmu map
 * input no-secure mem info(smmu addr or phys addr,indicated by iommu),
 * and return secure address( sec smmu addr or phys addr)
 */
u32 secmem_alloc(mmb_addr_t phyaddr, unsigned int iommu)
{
	TEE_MEM_BUFFER_S teebuf;
	u32 u32size;
	int ret;
	HI_U32 sec_smmu = 0;
	u32 base_addr = 0;

	memset(&teebuf, 0x0, sizeof(TEE_MEM_BUFFER_S));

	teebuf.table = get_meminfo(phyaddr, iommu, &u32size, &base_addr);
	if (!teebuf.table) {
		HI_MMZ_WARN("%s :Cannot get meminfo and check parameter!\n",__func__);
		goto out;
	}
	teebuf.u32Size = PAGE_ALIGN(u32size);

	ret = hisi_secmem_alloc(&teebuf, base_addr, iommu, &sec_smmu);
	if (ret) {
		HI_MMZ_WARN("%s: hisi_secmem_alloc failed!\n", __func__);
		goto out;
	}

	/* set mmb flag to indicate that the mem is secure  */
	set_sec_mmb_flag(phyaddr, iommu);
	sec_mmb_get(phyaddr, iommu, sec_smmu);

	return iommu? sec_smmu : phyaddr;

out:
	return MMB_ADDR_INVALID;
}

/* func: clear secure flag and unmap the sec smmu
 * input sec mem info (sec smmu addr or phys addr, indicated by iommu),
 * and output non-sec info (smmu addr or phys addr)
 */
u32 secmem_free(mmb_addr_t sec_addr, unsigned int iommu)
{
	int ret;
	u32 addr;
	int sec_smmu_ref = 0;
	TEE_MEM_BUFFER_S teebuf;
	u32 size = 0;
	u32 base_addr = 0;
	u32 offset = 0;
	u32 sec_base_addr = 0;

	if (iommu)
		addr = (u32)get_nonsecsmmu_by_secsmmu(sec_addr);
	else
		addr = (u32)sec_addr;

	teebuf.table = get_meminfo(addr, iommu, &size, &base_addr);
	if (!teebuf.table) {
		HI_MMZ_WARN("%s:Cannot get meminfo and check parameter!\n", __func__);
		goto exit;
	}
	offset = addr - base_addr;
	sec_base_addr = sec_addr - offset;

	sec_smmu_ref = sec_mmb_put(base_addr, iommu);
	if (sec_smmu_ref) {
		/*
		 * free later. warning: map sec-smmu many times
		 */
		goto exit;
	}

	ret = hisi_secmem_free(sec_base_addr, iommu);
	if (ret) {
		HI_MMZ_WARN("%s: hisi_secmem_free failed!\n", __func__);
		goto out;
	}

	clr_sec_mmb_flag(base_addr, iommu);

	return base_addr;

out:
	sec_mmb_get(addr, iommu, sec_base_addr);
exit:
	return MMB_ADDR_INVALID;
}

/* func: map to sec smmu
 * addr:input, smmu or phy address in normal world
 * iommu: address type
 * sec smmu address is returned when exec success
 * MMB_ADDR_INVALID is returned when exec failed
 */
u32 secmem_map_to_secsmmu(HI_U32 phyaddr, int iommu)
{
	TEE_MEM_BUFFER_S teebuf;
	u32 u32size;
	HI_U32 sec_smmu = 0;
	int ret;
	u32 base_addr = 0;
	u32 offset = 0;

	if (iommu)
		sec_smmu = get_sec_smmu_by_nosmmu(phyaddr);
	else
		sec_smmu = get_sec_smmu_by_phys(phyaddr);
	if (MMB_ADDR_INVALID != sec_smmu) {
		/*
		 * map to sec smmu before,and give the previous value
		 */
		goto out;
	}

	/*
	 * the first time to map to sec smmu
	 */
	memset(&teebuf, 0x0, sizeof(TEE_MEM_BUFFER_S));

	teebuf.table = get_meminfo(phyaddr, iommu, &u32size, &base_addr);
	if (!teebuf.table) {
		HI_MMZ_WARN("%s :Cannot get meminfo and check parameter!\n",__func__);
		goto exit;
	}
	teebuf.u32Size = PAGE_ALIGN(u32size);

	ret = hisi_secmem_mapto_secsmmu(&teebuf, base_addr, iommu, &sec_smmu);
	if (ret) {
		HI_MMZ_WARN("%s: hisi_secmem_mapto_secsmmu failed!\n", __func__);
		goto exit;
	}
	offset =  phyaddr - base_addr;
out:
	sec_mmb_get(phyaddr, iommu, sec_smmu);

	return (sec_smmu + offset);

exit:
	return MMB_ADDR_INVALID;
}

/* func: unmap from sec smmu
 * secsmmu:input, smmu address in sec world
 * iommu: memtype indicate the mem attr(mmz or system)
 * 0 is returned when exec success
 * non-zero is returned when exec failed
 */
int secmem_unmap_from_secsmmu(HI_U32 sec_addr, int iommu)
{
	int ret;
	int sec_smmu_ref = 0;
	int addr;
	TEE_MEM_BUFFER_S teebuf;
	u32 size = 0;
	u32 base_addr = 0;
	u32 sec_addr_base = 0;

	if (iommu) {
		/*
		 * the mem is system mem
		 */
		addr = get_nonsecsmmu_by_secsmmu(sec_addr);
	} else {
		/*
		 * the mem is system mem
		 */
		addr = get_phys_by_secsmmu(sec_addr);
	}
	teebuf.table = get_meminfo(addr, iommu, &size, &base_addr);
	if (!teebuf.table) {
		HI_MMZ_WARN("%s:Cannot get meminfo and check parameter!\n", __func__);
		goto err;
	}

	sec_addr_base = sec_addr - (addr - base_addr);
	sec_smmu_ref = sec_mmb_put(base_addr, iommu);
	if (sec_smmu_ref) {
		/*
		 *free later. warning: map sec-smmu many times
		 */
		goto out;
	}

	if (is_sec_mem(base_addr, iommu)) {
		/*
		 * mem is secure mem, and should be clear sec flag and unmap
		 * sec smmu.
		 */
		ret = hisi_secmem_free(sec_addr_base, 1);
		if (0 != ret) {
			HI_MMZ_WARN("%s: hisi_secmem_free failed!\n", __func__);
			goto exit;
		}
		clr_sec_mmb_flag(base_addr, iommu);
	} else {
		/*
		 * mem is normal mem, and just should be unmap sec smmu.
		 */
		ret = hisi_secmem_unmap_from_secsmmu(sec_addr_base);
		if (ret) {
			HI_MMZ_WARN("%s: hisi_secmem_unmap_from_secsmmu failed!\n",
								__func__);
			goto exit;
		}
	}

	/*
	 * the mem may not be free here, but it is just a repair the mistake for
	 * the exceptional calling order like:
	 * 1 secmem_alloc   ---  secmem_map_to_secsmmu  ------ secmem_free ------
	 * secmem_unmap_from_secsmmu
	 * 2 nomal alloc -- secmem_map_to_secsmmu --- normal free --
	 * secmem_unmap_from_secsmmu
	 */
	sec_delay_release_for_mem(base_addr, iommu);
out:
	return 0;
exit:
	sec_mmb_get(base_addr, iommu, sec_addr_base);
err:
	return -1;

}

int hi_tee_agent_end(void)
{
	return hisi_secmem_agent_end();
}

int sec_mem_get(HI_U32 sec_addr, int iommu)
{
	HI_U32 addr = MMB_ADDR_INVALID;

	if (iommu)
		addr = get_nonsecsmmu_by_secsmmu(sec_addr);
	else
		addr = sec_addr;

	if (addr == MMB_ADDR_INVALID) {
		HI_MMZ_WARN("%s, err args:addr:0x%x iommu:%d!\n", __func__,
							sec_addr, iommu);
		return HI_FAILURE;
	}

	if (!is_sec_mem(addr, iommu)) {
		HI_MMZ_WARN("%s:The mem should be sec!\n", __func__);
		return HI_FAILURE;
	}

	/* mem sec_smmu_ref is not 0, ignore sec_addr    */
	return sec_mmb_get(addr, iommu, sec_addr);
}

int sec_mem_put(HI_U32 sec_addr, int iommu)
{
	HI_U32 addr = MMB_ADDR_INVALID;
	int ret;

	if (iommu)
		addr = get_nonsecsmmu_by_secsmmu(sec_addr);
	else
		addr = sec_addr;

	if (addr == MMB_ADDR_INVALID) {
		HI_MMZ_WARN("%s, err args:addr:0x%x iommu:%d!\n", __func__,
							sec_addr, iommu);
		return HI_FAILURE;
	}

	if (!is_sec_mem(addr, iommu)) {
		HI_MMZ_WARN("%s:The mem should be sec!\n", __func__);
		return HI_FAILURE;
	}

	ret = sec_mmb_put(addr, iommu);
	if (ret < 0) {
		HI_MMZ_WARN("%s:call wrong times, the sec ref is %d.\n",
						__func__, ret);
		return HI_FAILURE;
	} else if(ret > 0) {
		/* just decrement the ref     */
		return HI_SUCCESS;
	} else {
		ret = hisi_secmem_free(sec_addr, iommu);
		if (ret) {
			HI_MMZ_WARN("%s: hisi_secmem_free failed!\n", __func__);
			return HI_FAILURE;
		}

		clr_sec_mmb_flag(addr, iommu);

		delete_mmb(addr, iommu);
	}

	return HI_SUCCESS;
}

EXPORT_SYMBOL(hi_tee_smmumem_into_ta);
EXPORT_SYMBOL(hi_tee_smmumem_outfrom_ta);
EXPORT_SYMBOL(secmem_alloc);
EXPORT_SYMBOL(secmem_free);
EXPORT_SYMBOL(secmem_map_to_secsmmu);
EXPORT_SYMBOL(secmem_unmap_from_secsmmu);
EXPORT_SYMBOL(hi_tee_agent_end);
EXPORT_SYMBOL(sec_mem_get);
EXPORT_SYMBOL(sec_mem_put);

