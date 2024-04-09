/**
 * \file
 * \brief Describes the information about error number module.
 */

#ifndef __HAL_ERRNO_H__
#define __HAL_ERRNO_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
/** \addtogroup      HAL_ERRNO */
/** @{ */  /** <!-- [HAL_ERRNO] */

#define ERROR_NULL_PTR                                          (S32)(0xFF000100)
#define ERROR_NOT_SUPPORTED                                     (S32)(0xFF000101)
#define ERROR_NO_MEMORY                                         (S32)(0xFF000102)
#define ERROR_INVALID_PARAM                                     (S32)(0xFF000103)
#define ERROR_NOT_INITED                                        (S32)(0xFF000104)

#define ERROR_SYSTEM_INIT_FAILED                                (S32)(0xFF000200)
#define ERROR_SYSTEM_DEINIT_FAILED                              (S32)(0xFF000201)
#define ERROR_SYSTEM_STANDBY_FAILED                             (S32)(0xFF000202)

#define ERROR_AOUT_INIT_FAILED                                  (S32)(0xFF000301)
#define ERROR_AOUT_DEINIT_FAILED                                (S32)(0xFF000302)
#define ERROR_AOUT_OP_FAILED                                    (S32)(0xFF000303)
#define ERROR_AOUT_CHANNEL_CLOSE_FAILED                         (S32)(0xFF000304)

#define ERROR_DISPLAY_INIT_FAILED                               (S32)(0xFF000400)
#define ERROR_DISPLAY_DEINIT_FAILED                             (S32)(0xFF000401)
#define ERROR_DISPLAY_CHANNEL_OPEN_FAILED                       (S32)(0xFF000402)
#define ERROR_DISPLAY_CHANNEL_CLOSE_FAILED                      (S32)(0xFF000403)
#define ERROR_DISPLAY_ATTACH_INTF_FAILED                        (S32)(0xFF000404)
#define ERROR_DISPLAY_DETACH_INTF_FAILED                        (S32)(0xFF000405)
#define ERROR_DISPLAY_OP_FAILED                                 (S32)(0xFF000406)
#define ERROR_VO_INIT_FAILED                                    (S32)(0xFF000407)
#define ERROR_VO_NOT_INITED                                     (S32)(0xFF000408)
#define ERROR_VO_PARAMETER_INVALID                              (S32)(0xFF000409)
#define ERROR_VO_NOT_OPENED                                     (S32)(0xFF000410)
#define ERROR_VO_TERM_FAILED                                    (S32)(0xFF000411)
#define ERROR_VO_OP_FAILED                                      (S32)(0xFF000412)
#define ERROR_VO_WIN_NOT_CREATED                                (S32)(0xFF000413)
#define ERROR_VO_DEINIT_FAILED                                  (S32)(0xFF000414)
#define ERROR_VO_WIN_BUFQUE_FULL                                (S32)(0xFF000415)

#define ERROR_AO_INIT_FAILED                                    (S32)(0xFF000501)
#define ERROR_AO_NOT_INITED                                     (S32)(0xFF000502)
#define ERROR_AO_PARAMETER_INVALID                              (S32)(0xFF000503)
#define ERROR_AO_NOT_OPENED                                     (S32)(0xFF000504)
#define ERROR_AO_TERM_FAILED                                    (S32)(0xFF000505)
#define ERROR_AO_OP_FAILED                                      (S32)(0xFF000506)
#define ERROR_AO_TRACK_NOT_CREATED                              (S32)(0xFF000507)

#define ERROR_AV_INIT_FAILED                                    (S32)(0xFF000601)
#define ERROR_AV_DEINIT_FAILED                                  (S32)(0xFF000602)
#define ERROR_AV_TERM_FAILED                                    (S32)(0xFF000603)
#define ERROR_AV_OP_FAILED                                      (S32)(0xFF000604)
#define ERROR_AV_PARAMETER_INVALID                              (S32)(0xFF000605)
#define ERROR_AV_PLAYER_NOT_CREATED                             (S32)(0xFF000606)
#define ERROR_AV_INJECT_NOT_OPENED                              (S32)(0xFF000607)
#define ERROR_AV_INJECT_NOT_DETACH                              (S32)(0xFF000608)
#define ERROR_AV_AUD_START_FAIL                                 (S32)(0xFF000609)
#define ERROR_AV_VID_START_FAIL                                 (S32)(0xFF00060A)
#define ERROR_AV_VID_AND_AUD_START_FAIL                         (S32)(0xFF00060B)

#define ERROR_DMX_INIT_FAILED                                   (S32)(0xFF000701)
#define ERROR_DMX_DEINIT_FAILED                                 (S32)(0xFF000702)
#define ERROR_DMX_OP_FAILED                                     (S32)(0xFF000703)
#define ERROR_DMX_GETBUF_TIMEOUT                                (S32)(0xFF000704)
#define ERROR_DMX_NOATTACH_SOURCE                               (S32)(0xFF000705)
#define ERROR_DMX_INVALID_DMX_ID                                (S32)(0xFF000706)
#define ERROR_DMX_UNMATCH_CHAN                                  (S32)(0xFF000707)
#define ERROR_DMX_NOAVAILABLE_DATA                              (S32)(0xFF000708)
#define ERROR_DMX_TIMEOUT                                       (S32)(0xFF000709)
#define ERROR_DMX_NOFREE_CHAN                                   (S32)(0xFF00070A)
#define ERROR_DMX_NOFREE_FILTER                                 (S32)(0xFF00070B)

#define ERROR_FRONTEND_INIT_FAILED                              (S32)(0xFF000901)
#define ERROR_FRONTEND_DEINIT_FAILED                            (S32)(0xFF000902)
#define ERROR_FRONTEND_OP_FAILED                                (S32)(0xFF000903)
#define ERROR_FRONTEND_NOT_INIT                                 (S32)(0xFF000904)
#define ERROR_FRONTEND_OPEN_FAILED                              (S32)(0xFF000905)
#define ERROR_FRONTEND_NOT_OPEN                                 (S32)(0xFF000906)
#define ERROR_FRONTEND_CLOSE_FAILED                             (S32)(0xFF000907)
#define ERROR_FRONTEND_ALREADY_OPEN                             (S32)(0xFF000908)

#define ERROR_ENC_INIT_FAILED                                   (S32)(0xFF000A01)
#define ERROR_ENC_DEINIT_FAILED                                 (S32)(0xFF000A02)
#define ERROR_ENC_OPEN_FAILED                                   (S32)(0xFF000A03)
#define ERROR_ENC_CLOSE_FAILED                                  (S32)(0xFF000A04)
#define ERROR_ENC_OP_FAILED                                     (S32)(0xFF000A05)
#define ERROR_ENC_BUF_LENGTH_NOT_ENOUGH                         (S32)(0xFF000A06)
#define ERROR_ENC_TIMEOUT                                       (S32)(0xFF000A07)
#define ERROR_ENC_NO_FREE_RESOURCE                              (S32)(0xFF000A08)
#define ERROR_ENC_NO_SUCH_HANDLE                                (S32)(0xFF000A09)
#define ERROR_ENC_NO_AENC_LIBS                                  (S32)(0xFF000A0A)

#define ERROR_SOURCE_INIT_FAILED                                (S32)(0xFF000B01)
#define ERROR_SOURCE_DEINIT_FAILED                              (S32)(0xFF000B02)
#define ERROR_SOURCE_OP_FAILED                                  (S32)(0xFF000B03)

#define ERROR_CAPTION_INIT_FAILED                               (S32)(0xFF000C01)
#define ERROR_CAPTION_DEINIT_FAILED                             (S32)(0xFF000C02)
#define ERROR_CAPTION_OP_FAILED                                 (S32)(0xFF000C03)

/* hisiliocn extension begin */
#define ERROR_NETWORK_INIT_FAILED                               (S32)(0xFF000D01)
#define ERROR_NETWORK_DEINIT_FAILED                             (S32)(0xFF000D02)
#define ERROR_NETWORK_OPEN_FAILED                               (S32)(0xFF000D03)
#define ERROR_NETWORK_CLOSE_FAILED                              (S32)(0xFF000D04)
#define ERROR_NETWORK_INVALID_ADDRESS                           (S32)(0xFF000D05)
#define ERROR_NETWORK_IP_GATEWAY_NOCOMPATIBLE                   (S32)(0xFF000D06)
#define ERROR_NETWORK_INVALID_MAC                               (S32)(0xFF000D07)
#define ERROR_NETWORK_SET_MAC_FAILED                            (S32)(0xFF000D08)
#define ERROR_NETWORK_GET_MAC_FAILED                            (S32)(0xFF000D09)
#define ERROR_NETWORK_ADDRESS_MATCH_FAILED                      (S32)(0xFF000D0a)

#define ERROR_WLAN_FAILED                                       (S32)(0xFF000E01)
#define ERROR_WLAN_INVALID_PARAMETER                            (S32)(0xFF000E02)
#define ERROR_WLAN_DEVICE_NOT_FOUND                             (S32)(0xFF000E03)
#define ERROR_WLAN_LOAD_DRIVER_FAIL                             (S32)(0xFF000E04)
#define ERROR_WLAN_START_SUPPLICANT_FAIL                        (S32)(0xFF000E05)
#define ERROR_WLAN_CONNECT_TO_SUPPLICANT_FAIL                   (S32)(0xFF000E06)
#define ERROR_WLAN_SEND_COMMAND_FAIL                            (S32)(0xFF000E07)
#define ERROR_WLAN_START_HOSTAPD_FAIL                           (S32)(0xFF000E08)
#define ERROR_WLAN_SET_CALLBACK_FAIL                            (S32)(0xFF000E09)

#define ERROR_PVR_BASE                                          (S32)(0xFF000F01)
#define ERROR_PVR_INVALID_CHN                                   (S32)(ERROR_PVR_BASE + 1)
#define ERROR_PVR_ALREADY                                       (S32)(ERROR_PVR_BASE + 2)
#define ERROR_PVR_NO_CHN_LEFT                                   (S32)(ERROR_PVR_BASE + 3)
#define ERROR_PVR_NO_MEM                                        (S32)(ERROR_PVR_BASE + 4)
#define ERROR_PVR_MODULE_BUSY                                   (S32)(ERROR_PVR_BASE + 5)
#define ERROR_PVR_CHANNEL_BUSY                                  (S32)(ERROR_PVR_BASE + 6)
#define ERROR_PVR_NOT_SUPPORT                                   (S32)(ERROR_PVR_BASE + 7)
#define ERROR_PVR_RETRY                                         (S32)(ERROR_PVR_BASE + 8)
#define ERROR_PVR_FILE_EXIST                                    (S32)(ERROR_PVR_BASE + 9)
#define ERROR_PVR_FILE_NO_EXIST                                 (S32)(ERROR_PVR_BASE + 10)
#define ERROR_PVR_FILE_CANT_OPEN                                (S32)(ERROR_PVR_BASE + 11)
#define ERROR_PVR_FILE_CANT_CLOSE                               (S32)(ERROR_PVR_BASE + 12)
#define ERROR_PVR_FILE_CANT_SEEK                                (S32)(ERROR_PVR_BASE + 13)
#define ERROR_PVR_FILE_CANT_WRITE                               (S32)(ERROR_PVR_BASE + 14)
#define ERROR_PVR_FILE_CANT_READ                                (S32)(ERROR_PVR_BASE + 15)
#define ERROR_PVR_FILE_INVALID_FNAME                            (S32)(ERROR_PVR_BASE + 16)
#define ERROR_PVR_FILE_TILL_START                               (S32)(ERROR_PVR_BASE + 17)
#define ERROR_PVR_FILE_TILL_END                                 (S32)(ERROR_PVR_BASE + 18)
#define ERROR_PVR_FILE_DISK_FULL                                (S32)(ERROR_PVR_BASE + 19)
#define ERROR_PVR_REC_INVALID_STATE                             (S32)(ERROR_PVR_BASE + 20)
#define ERROR_PVR_REC_INVALID_DMXID                             (S32)(ERROR_PVR_BASE + 21)
#define ERROR_PVR_REC_INVALID_FSIZE                             (S32)(ERROR_PVR_BASE + 22)
#define ERROR_PVR_REC_INVALID_UDSIZE                            (S32)(ERROR_PVR_BASE + 23)
#define ERROR_PVR_PLAY_INVALID_STATE                            (S32)(ERROR_PVR_BASE + 24)
#define ERROR_PVR_PLAY_INVALID_DMXID                            (S32)(ERROR_PVR_BASE + 25)
#define ERROR_PVR_PLAY_INVALID_TSBUFFER                         (S32)(ERROR_PVR_BASE + 26)
#define ERROR_PVR_PLAY_INVALID_PACKETBUFFER                     (S32)(ERROR_PVR_BASE + 27)
#define ERROR_PVR_PLAY_INDEX_BEYOND_TS                          (S32)(ERROR_PVR_BASE + 28)
#define ERROR_PVR_INDEX_CANT_MKIDX                              (S32)(ERROR_PVR_BASE + 29)
#define ERROR_PVR_INDEX_FORMAT_ERR                              (S32)(ERROR_PVR_BASE + 30)
#define ERROR_PVR_INDEX_DATA_ERR                                (S32)(ERROR_PVR_BASE + 31)
#define ERROR_PVR_INDEX_INVALID_ENTRY                           (S32)(ERROR_PVR_BASE + 32)
#define ERROR_PVR_INTF_EVENT_INVAL                              (S32)(ERROR_PVR_BASE + 33)
#define ERROR_PVR_INTF_EVENT_NOREG                              (S32)(ERROR_PVR_BASE + 34)

/* hisilicon extension end */
/** @} */  /*! <!-- Macro Definition End */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_ERRNO_H__ */
