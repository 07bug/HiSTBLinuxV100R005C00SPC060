#ifndef __SEC_MMZ_COMMON_H
#define __SEC_MMZ_COMMON_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef enum {
	HI_MMZ_NEW = 0x1000,
	HI_MMZ_DEL,
	HI_MMZ_CP_CA2TA,
	HI_MMZ_CP_TA2CA,
	HI_MMZ_CP_TA2TA,
	HI_MMZ_TEST,
	HI_MMZ_DEBUG
} hi_mmz_cmd;

#define SEC_MMZ_UUID 0xd93d4688, 0xbde7, 0x11e6, \
	{ 0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xc3, 0x01 }

#define SUCCESS 0
#define ERR_IN_SEC_OS -1
#define NO_SEC_OS -2

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __SEC_MMZ_COMMON_H */
