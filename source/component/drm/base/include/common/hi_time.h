/******************************************************************************
Copyright (C), 2015-2025, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     : hi_time.h
Version       : Initial draft
Author        : HiSilicon DTV stack software group
Created Date  : 2015-08-24
Last Modified by: T00219055
Description   : Application programming interfaces (APIs) of Time module.
Function List :
Change History:
******************************************************************************/

#ifndef __HI_TIME_H__
#define __HI_TIME_H__

#include <stdio.h>
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      time */
/** @{ */  /** <!--[time]*/

/** Decode time BCD. */
#define HI_TIME_BCD_DEC(val) ((val>>4)*10 + (val&0xF))
/** Encode time BCD. */
#define HI_TIME_BCD_ENC(val) (((val/10)<<4) + (val%10))

/** Definition of week day index. */
/** CNcomment:����һ�������� */
typedef enum hiTIME_WEEK_DAY_E
{
    HI_TIME_WEEK_DAY_SUN = 0x0,
    HI_TIME_WEEK_DAY_MON,
    HI_TIME_WEEK_DAY_TUE,
    HI_TIME_WEEK_DAY_WED,
    HI_TIME_WEEK_DAY_THU,
    HI_TIME_WEEK_DAY_FRI,
    HI_TIME_WEEK_DAY_SAT,
    HI_TIME_WEEK_DAY_BUTT
} HI_TIME_WEEK_DAY_E;

/** Definition of time infomation struct. */
/** CNcomment:ʱ���ʽ�ṹ�� */
typedef struct hiTIME_INFO_S {
    HI_S32 s32Sec;  /**<The  number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.*/
    HI_S32 s32Min;  /**<The number of minutes after the hour, in the range 0 to 59.*/
    HI_S32 s32Hour; /**<The number of hours past midnight, in the range 0 to 23.*/
    HI_S32 s32Mday; /**<The day of the month, in the range 1 to 31.*/
    HI_S32 s32Mon;  /**<The number of months since January, in the range 1 to 12.*/
    HI_S32 s32Year; /**<The number of years since A.D. 0.,eg.2009*/
    HI_S32 s32Wday; /**<The number of days since Sunday, in the range 0 to 6.*/
    HI_S32 s32Yday; /**<The number of days since January 1, in the range 1 to 366.*/
} HI_TIME_INFO_S;

/** Definition of MJD and UTC format time. */
/** CNcomment:MJD��UTCʱ�� */
typedef struct hiTIME_MJDUTC_S
{
    HI_U16 u16MJD;  /**<UTC time of year/month/day in TOT table.*//**<CNcomment:TOT����UTCʱ���16bit����/��/�� */
    HI_U32 u32UTC;  /**<UTC time of hour/minute/second in TOT table.*//**<CNcomment:TOT����UTCʱ���24bit��ʱ/��/�� */
} HI_TIME_MJDUTC_S;

/** Definition of MJD and UTC and duration format time. */
/** CNcomment:MJD��UTCʱ�䣬�ټ��ϳ���ʱ�� */
typedef struct hiTIME_MJDUTC_DURATION_S
{
    HI_TIME_MJDUTC_S             stTime;
    HI_U32                         u32Duration:24;
} HI_TIME_MJDUTC_DURATION_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      time */
/** @{ */  /** <!--[time]*/

/**
\brief time module init. CNcomment:��ʼ��ʱ��ģ�� CNend
\attention \n
N/A
\param[in] pVoid reserved. CNcomment:Ԥ����չ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_Init(const HI_VOID *pVoid);

/**
\brief EPG module deinit. CNcomment:ȥ��ʼ��ģ�� CNend
\attention \n
N/A
\param[in] pVoid reserved. CNcomment:Ԥ����չ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DeInit(const HI_VOID *pVoid);

/**
\brief Get time zone. CNcomment:��ȡʱ�� CNend
\attention \n
N/A
\param[out] ps32TimeZoneSeconds Time zone, unit is second. CNcomment:ʱ��ʱ��,��λ:�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetTimeZone(HI_S32 *ps32TimeZoneSeconds);

/**
\brief Set time zone. CNcomment:����ʱ�� CNend
\attention \n
N/A
\param[in] s32TimeZoneSeconds Time zone, unit is second. CNcomment:ʱ��ʱ��,��λ:�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeZone(HI_S32 s32TimeZoneSeconds);

/**
\brief Set daylight saving time. CNcomment:��������ʱ CNend
\attention \n
N/A
\param[in] bEnable If turn on daylight saving time. CNcomment:�Ƿ���������ʱ, TRUE(+1Сʱ) FALSE(+0Сʱ) CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetDaylight(HI_BOOL bEnable);

/**
\brief Get offset of system time. CNcomment:��ȡƫ��ʱ��(ʱ�� + ����ʱ) CNend
\attention \n
N/A
\param[out] ps32OffsetSeconds Offset = timezone + daylight. CNcomment:ƫ��ʱ��(��) CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetOffset(HI_S32 *ps32OffsetSeconds);

/**
\brief Get system time. CNcomment:��ȡϵͳʱ��(��) CNend
\attention \n
N/A
\param[out] ps32Seconds Seconds of time format. CNcomment:ϵͳʱ�� CNend
\param[in] bWithOffset If include offset time. CNcomment:�����Ƿ����ƫ��ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetSeconds(HI_S32 *ps32Seconds, HI_BOOL bWithOffset);

/**
\brief Get date and time. CNcomment:��ȡϵͳ����ʱ��(������ʱ������ʽ) CNend
\attention \n
N/A
\param[out] pstTimeInfo Time. CNcomment:ϵͳʱ�� CNend
\param[in] bWithOffset If include offset time. CNcomment:�����Ƿ����ƫ��ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetDateTime(HI_TIME_INFO_S *pstTimeInfo, HI_BOOL bWithOffset);

/**
\brief Set date and time. CNcomment:����ϵͳ����ʱ��(������ʱ������ʽ) CNend
\attention \n
N/A
\param[in] pstTimeInfo Time. CNcomment:ϵͳʱ�� CNend
\param[in] bWithOffset If include offset time. CNcomment:�����Ƿ����ƫ��ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetDateTime(const HI_TIME_INFO_S *pstTimeInfo, HI_BOOL bWithOffset);

/**
\brief Set data time to operate system. CNcomment:ͨ��HI_TIME_SetDateTime����DTVʱ��ʱ�Ƿ�ͬʱ��ʱ�����õ�����ϵͳʱ��ȥ CNend
\attention \n
N/A
\param[in] bEnable If set to system. CNcomment:�Ƿ�����, ��ģ���и�ֵĬ��ΪTRUE CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeToSystem(HI_BOOL bEnable);

/**
\brief Set data time to operate system. CNcomment:ͨ��HI_TIME_SetDateTime����DTVʱ��ʱ�Ƿ�ͬʱ��ʱ�����õ�����ϵͳʱ��ȥ CNend
\attention \n
N/A
\param[in] bEnable If set to system. CNcomment:�Ƿ�����, ��ģ���и�ֵĬ��ΪTRUE CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SetTimeZoneToSystem(HI_BOOL bEnable);

/**
\brief Get date and time. CNcomment:��ȡϵͳ����ʱ��(MJD+UTC��ʽ) CNend
\attention \n
N/A
\param[out] pstMjdUtcTime Time. CNcomment:ʱ�� CNend
\param[in] bWithOffset If include offset time. CNcomment:�����Ƿ����ƫ��ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_GetMJDUTCTime(HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_BOOL bWithOffset);

/**
\brief Compare two time structs. CNcomment:����ʱ��Ƚ� CNend
\attention \n
N/A
\param[in] pstTimeInfo1 The first time struct. CNcomment:ʱ��1 CNend
\param[in] pstTimeInfo2 The second time struct. CNcomment:ʱ��2 CNend
\param[out] ps32Result Result, 0 is equal, positive is more than, negative is less than. CNcomment:�ȽϽ��,0,���;>0,ʱ��1>ʱ��2������;<0,ʱ��1<ʱ��2������ CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_CompareDateTime(const HI_TIME_INFO_S *pstTimeInfo1, const HI_TIME_INFO_S *pstTimeInfo2, HI_S32 *ps32Result);

/**
\brief Compare two time structs. CNcomment:����ʱ��Ƚ�(MJD+UTC��ʽ) CNend
\attention \n
N/A
\param[in] pstTimeInfo1 The first time struct. CNcomment:ʱ��1 CNend
\param[in] pstTimeInfo2 The second time struct. CNcomment:ʱ��2 CNend
\param[out] ps32Result Result, 0 is equal, positive is more than, negative is less than. CNcomment:�ȽϽ��,0,���;>0,ʱ��1>ʱ��2������;<0,ʱ��1<ʱ��2������ CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_CompareMJDUTCTime(const HI_TIME_MJDUTC_S *pstTimeInfo1, const HI_TIME_MJDUTC_S *pstTimeInfo2, HI_S32 *ps32Result);

/**
\brief Transform date time format to second format. CNcomment:��ʱ��ת��Ϊ����(from 1970) CNend
\attention \n
N/A
\param[in] pstTimeInfo Date and time. CNcomment:��ת����ʱ�� CNend
\param[out] ps32Seconds Seconds, from 1970.1.1 CNcomment:��������1970��Ϊ0��ʼ���� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DateTimeToSeconds(const HI_TIME_INFO_S *pstTimeInfo, HI_S32 *ps32Seconds);

/**
\brief Transform second format to date time format. CNcomment:������(from 1970)ת��Ϊ������ʱ������ʽ��ʱ�� CNend
\attention \n
N/A
\param[in] s32Seconds Seconds, from 1970.1.1 CNcomment:��������1970Ϊ0��ʼ���� CNend
\param[out] pstTimeInfo Date and time. CNcomment:���������ʱ������ʽ��ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToDateTime(HI_S32 s32Seconds, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform Y/M/D H/M/S format to MJD+BCD UTC format. CNcomment:��ϵͳʱ��ת��ΪMJD/UTCʱ�� CNend
\attention \n
N/A
\param[in] pstTimeInfo Y/M/D H/M/S format time. CNcomment:������ʱ������ʽ������ʱ�� CNend
\param[out] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC��ʽ������ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_DateTimeToMJDUTC(const HI_TIME_INFO_S *pstTimeInfo, HI_TIME_MJDUTC_S *pstMjdUtcTime);

/**
\brief Transform MJD+BCD UTC format to Y/M/D H/M/S format. CNcomment:MJD+BCDUTC��ʽʱ��ת����������ʱ������ʽ������ʱ�� CNend
\attention \n
N/A
\param[in] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC��ʽ��ʱ�� CNend
\param[out] pstTimeInfo Y/M/D H/M/S format time. CNcomment:������ʱ������ʽ������ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDUTCToDateTime(const HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to second format. CNcomment:BCD UTCʱ��ת������(�����00:00:00) CNend
\attention \n
N/A
\param[in] u32UTC BCD UTC format time. CNcomment:BCD��ʽ��UTCʱ�� CNend
\param[out] ps32Seconds Seconds. CNcomment:���� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_BCDUTCToSeconds(HI_U32 u32UTC, HI_S32 *ps32Seconds);

/**
\brief Transform second format to BCD UTC format. CNcomment:��ת����BCD UTCʱ��(�����00:00:00) CNend
\attention \n
N/A
\param[in] s32Seconds Seconds. CNcomment:���� CNend
\param[out] pu32UTC BCD UTC format time. CNcomment:BCD��ʽ��UTCʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToBCDUTC(HI_S32 s32Seconds, HI_U32 *pu32UTC);

/**
\brief Transform MJD+BCD UTC format to second format. CNcomment:MJD+BCD UTC��ʽʱ��ת������ CNend
\attention \n
N/A
\param[in] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC��ʽ��ʱ�� CNend
\param[out] ps32Seconds Seconds. CNcomment:�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDUTCToSeconds(const HI_TIME_MJDUTC_S *pstMjdUtcTime, HI_S32 *ps32Seconds);

/**
\brief Transform second format to MJD/UTC format. CNcomment:����ת��ΪMJD/UTCʱ�� CNend
\attention \n
N/A
\param[in] s32Seconds Seconds. CNcomment:�� CNend
\param[out] pstMjdUtcTime MJD+BCD UTC format time. CNcomment:MJD+BCD UTC��ʽ������ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_SecondsToMJDUTC(HI_S32 s32Seconds, HI_TIME_MJDUTC_S *pstMjdUtcTime);

/**
\brief Transform MJD date format to Y/M/D format. CNcomment:MJD����ת������������ʽ������ CNend
\attention \n
N/A
\param[in] u32MJD MJD date format. CNcomment:MJD��ʽ�������� CNend
\param[out] pstTimeInfo Y/M/D date format. CNcomment:������ʱ������ʽ������ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_MJDToYMD(HI_U32 u32MJD, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to H/M/S format. CNcomment:UTCʱ��ת����ʱ���� CNend
\attention \n
N/A
\param[in] u32UTC BCD UTC format time. CNcomment:BCD��ʽ��UTCʱ�� CNend
\param[out] pstTimeInfo H/M/S format. CNcomment:ʱ������Ϣ CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_BCDUTCToHMS(HI_U32 u32UTC, HI_TIME_INFO_S *pstTimeInfo);

/**
\brief Transform BCD UTC format time to H/M/S format. CNcomment:ʱ����ת����UTCʱ�� CNend
\attention \n
N/A
\param[in] pstTimeInfo H/M/S format. CNcomment:ʱ������Ϣ CNend
\param[out] pu32UTC BCD UTC format time. CNcomment:BCD��ʽ��UTCʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_HMSToBCDUTC(const HI_TIME_INFO_S *pstTimeInfo, HI_U32 *pu32UTC);

/**
\brief Add time with seconds. CNcomment:��ָ��ʱ��ƫ��n�� CNend
\attention \n
N/A
\param[in] pstTimeInfo Source date time. CNcomment:ԭʼ����ʱ�� CNend
\param[in] s32Seconds Offset seconds. CNcomment:ƫ������ CNend
\param[out] pstTimeInfo Target date time. CNcomment:ƫ�ƺ������ʱ�� CNend
\retval ::HI_SUCCESS success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE fail    CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_TIME_AddSeconds(HI_TIME_INFO_S *pstTimeInfo, HI_S32 s32Seconds);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
 }
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_TIME_H__ */
