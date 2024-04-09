
#ifndef __VDP_DM_MODCTRL_H__
#define __VDP_DM_MODCTRL_H__


#define DM_VER_CTRL             3
#define DM_VER_CTRL_MINOR       1




#define DM_VER_IS(mj_, mn_)   (DM_VER_CTRL == mj_ && DM_VER_CTRL_MINOR == mn_)





#define DM_STB 1

#define DM_DTV 0



#define REDUCED_COMPLEXITY      1


#define K_FLOAT_MATCH_FIXED     1




#define ENABLE_DBG_BUF          0

#define EN_CHK_POINT         1
#define SIMPLE_CP_FILE_NAMING    0


#define DM_EXTERNAL_CCM         (1 && DM_FULL_SRC_SPEC)


#define EN_KS_DM_IN             1


#define DmCfg_t       DmCfgFxp_t
#define HDmCfg_t      HDmCfgFxp_t
typedef struct DmCfgFxp_t_ *HDmCfgFxp_t;

#define SrcSigEnv_t   SrcSigEnvFxp_t
#define TgtSigEnv_t   TgtSigEnvFxp_t
#define GrcSigEnv_t   GrcSigEnvFxp_t

#define DmCtrl_t      DmCtrlFxp_t
#define TmCtrl_t      TmCtrlFxp_t
#define MsCtrl_t      MsCtrlFxp_t
#define GdCtrl_t      GdCtrlFxp_t

#define Dm_t          DmCtxtFxp_t
#define HDm_t         HDmFxp_t
#define DmCtxt_t      DmCtxtFxp_t
typedef struct DmCtxtFxp_t_ *HDmFxp_t;

#define DmKs_t        DmKsFxp_t
#define HDmKs_t       HDmKsFxp_t
typedef struct DmKsFxp_t_  *HDmKsFxp_t;


#define BIN_MD_BE                   1

#define DM_FULL_SRC_SPEC            1

#define EN_GLOBAL_DIMMING           (1 && DM_DTV)
#define EN_AOI                      0

#define DM_SEC_INPUT                DM_STB
#define DM_SIMPLE_SEC_INPUT         (0 && DM_STB)
#define EN_GENERAL_SEC_INPUT        (DM_SEC_INPUT)
#define MAP_2_INPUT_IPT             (1 && DM_VER_CTRL == 3)
#define EN_UP_DOWN_SAMPLE_OPTION    1
#define EN_420_OUTPUT               (0 && EN_UP_DOWN_SAMPLE_OPTION)
#define EN_MS_OPTION                (DM_DTV || (DM_VER_CTRL == 2))
#define EN_EDGE_SIMPLE              (DM_VER_CTRL_MINOR == 0)
#define EN_MS_FILTER_CFG            1
#define EN_NEW_IPT_RANGE            (0 && (DM_VER_CTRL >= 3) && !DM_STB)
#define EN_IPT_PQ_ONLY_OPTION       (0 && !DM_SEC_INPUT && (DM_VER_CTRL == 3))
#define EN_IPT_PQ_OUTPUT_SHORT_CUT  ((0 || EN_IPT_PQ_ONLY_OPTION) && (DM_VER_CTRL == 3))
#define EN_IPT_PQ_INPUT_SHORT_CUT   ((0 || EN_IPT_PQ_ONLY_OPTION) && (DM_VER_CTRL == 3))
#define EN_SKIP_TMAP_MS             1
#define EN_BYPASS_DM                1

#define MS_VERT_FILTER_FIRST        REDUCED_COMPLEXITY
#define REDUCED_TC_LUT              0
#if 1

#define _USE_2_TAP_CHROMA_VERT_FILTER_

#endif



#if EN_GLOBAL_DIMMING && !K_FLOAT_MATCH_FIXED
#undef USE_12BITS_IN_3D_LUT
#undef USE_12BITS_MSB_IN_3D_LUT
#endif

#if DM_VER_IS(3, 1) && !K_FLOAT_MATCH_FIXED
#undef _USE_2_TAP_CHROMA_VERT_FILTER_
#endif


#ifndef __CUDA_ARCH__
#define CONST_MODIFIER const
#else
#define CONST_MODIFIER __constant__
#endif



#define DM_FRAME_SIZE_1080P       0
#define DM_FRAME_SIZE_2K          1
#define DM_FRAME_SIZE_4K          2

#define DM_FRAME_SIZE_SUPPORT      DM_FRAME_SIZE_4K

#define DM_ROW_NUM_4K    2160
#define DM_COL_NUM_4K    4096

#define DM_ROW_NUM_2K    1080
#define DM_COL_NUM_2K    2048

#define DM_ROW_NUM_1080P  1080
#define DM_COL_NUM_1080P  1920


#if (DM_FRAME_SIZE_SUPPORT == DM_FRAME_SIZE_4K)
#define DM_MAX_ROW_NUM    DM_ROW_NUM_4K
#define DM_MAX_COL_NUM    DM_COL_NUM_4K
#elif (DM_FRAME_SIZE_SUPPORT == DM_FRAME_SIZE_2K)
#define DM_MAX_ROW_NUM    DM_ROW_NUM_2K
#define DM_MAX_COL_NUM    DM_COL_NUM_2K
#else
#define DM_MAX_ROW_NUM    DM_ROW_NUM_1080P
#define DM_MAX_COL_NUM    DM_COL_NUM_1080P
#endif

#define DM_MAX_IMG_SIZE  (DM_MAX_ROW_NUM * DM_MAX_COL_NUM)


#define DM_DEF_ROW_NUM    DM_ROW_NUM_1080P
#define DM_DEF_COL_NUM    DM_COL_NUM_1080P
#define DM_DEF_IMG_SIZE (DM_DEF_ROW_NUM * DM_DEF_COL_NUM)



#define TM1_LUT_MAX_SIZE     512

#if !DM_SIMPLE_SEC_INPUT
#define TM2_LUT_MAX_SIZE      512
#else
#define TM2_LUT_MAX_SIZE      256
#endif


#define TM_LUT_MAX_SIZE  ((TM1_LUT_MAX_SIZE >= TM2_LUT_MAX_SIZE) ? TM1_LUT_MAX_SIZE : TM2_LUT_MAX_SIZE)


#endif
