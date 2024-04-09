#ifndef _VPSS_MAC_DEFINE_H_
#define _VPSS_MAC_DEFINE_H_


/****************************************************************/
// LAYER NAME USE IN FUNC
/****************************************************************/
typedef enum
{
    VPSS_MAC_RCHN_CF = 0  ,
    VPSS_MAC_RCHN_P1      ,
    VPSS_MAC_RCHN_P2      ,
    VPSS_MAC_RCHN_P3      ,
    VPSS_MAC_RCHN_P3I     ,
    VPSS_MAC_RCHN_NR_RMAD ,
    VPSS_MAC_RCHN_DI_RST  ,
    VPSS_MAC_RCHN_DI_STCNT,
    VPSS_MAC_RCHN_P3MT    ,
    VPSS_MAC_RCHN_P2MV    ,
    VPSS_MAC_RCHN_P3MV    ,
    VPSS_MAC_RCHN_P1RGMV  ,
    VPSS_MAC_RCHN_P2RGMV  ,
    VPSS_MAC_RCHN_RPRJH   ,
    VPSS_MAC_RCHN_RPRJV   ,

    VPSS_MAC_RCHN_BUTT
} VPSS_MAC_RCHN_E;

typedef enum
{
    VPSS_MAC_WCHN_OUT0  = 0,
    VPSS_MAC_WCHN_NR_RFR   ,
    VPSS_MAC_WCHN_DI_RFR   ,
    VPSS_MAC_WCHN_NR_WMAD  ,
    VPSS_MAC_WCHN_DI_WST   ,
    VPSS_MAC_WCHN_DI_STCNT ,
    VPSS_MAC_WCHN_P2MT     ,
    VPSS_MAC_WCHN_CFMV     ,
    VPSS_MAC_WCHN_CFRGMV   ,
    VPSS_MAC_WCHN_WPRJH    ,
    VPSS_MAC_WCHN_WPRJV    ,

    VPSS_MAC_WCHN_BUTT
} VPSS_MAC_WCHN_E;

/****************************************************************/
// LAYER CONT
/****************************************************************/
#define VPSS_RCHN_MAX ((HI_U32)(VPSS_MAC_RCHN_BUTT))
#define VPSS_WCHN_MAX ((HI_U32)(VPSS_MAC_WCHN_BUTT))
#define VPSS_STT_MAX    5
#define VPSS_CHKSUM_MAX 24

extern const HI_U32 gu32VpssRchnAddr[VPSS_RCHN_MAX];
extern const HI_U32 gu32VpssWchnAddr[VPSS_WCHN_MAX];
extern const HI_U32 gu32VpssRchnMaxWth[VPSS_RCHN_MAX];
extern const HI_U32 gu32VpssRchnMaxHgt[VPSS_RCHN_MAX];
extern const HI_U32 gu32VpssWchnMaxWth[VPSS_WCHN_MAX];
extern const HI_U32 gu32VpssWchnMaxHgt[VPSS_WCHN_MAX];

#define VPSS_RCHN_IMG_START_OFFSET  (gu32VpssRchnAddr[VPSS_MAC_RCHN_CF])
#define VPSS_WCHN_IMG_START_OFFSET  (gu32VpssWchnAddr[VPSS_MAC_WCHN_OUT0])
#define VPSS_RCHN_SOLO_START_OFFSET (gu32VpssRchnAddr[VPSS_MAC_RCHN_NR_RMAD])
#define VPSS_WCHN_SOLO_START_OFFSET (gu32VpssWchnAddr[VPSS_MAC_WCHN_NR_WMAD])

//-------------------------------------------------------
// VPSS READ IMG BASE REGISTER
//-------------------------------------------------------
/* Define the union U_VPSS_BASE_RD_IMG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    format               : 4   ; /* [3..0]  */
        unsigned int    type                 : 4   ; /* [7..4]  */
        unsigned int    order                : 4   ; /* [11..8]  */
        unsigned int    bitw                 : 4   ; /* [15..12]  */
        unsigned int    dcmp_mode            : 4   ; /* [19..16]  */
        unsigned int    uv_invert            : 1   ; /* [20]  */
        unsigned int    mirror               : 1   ; /* [21]  */
        unsigned int    flip                 : 1   ; /* [22]  */
        unsigned int    lm_rmode             : 3   ; /* [25..23]  */
        unsigned int    b_bypass             : 1   ; /* [26]  */
        unsigned int    h_bypass             : 1   ; /* [27]  */
        unsigned int    d_bypass             : 1   ; /* [28]  */
        unsigned int    mute_en              : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMG_CTRL;
/* Define the union U_VPSS_BASE_RD_IMG_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    width              : 16  ; /* [15..0]  */
        unsigned int    height             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMG_SIZE;
/* Define the union U_VPSS_BASE_RD_IMG_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_offset         : 16  ; /* [15..0]  */
        unsigned int    ver_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMG_OFFSET;
/* Define the union U_VPSS_BASE_RD_IMGY_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_addr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGY_ADDR_HIGH;
/* Define the union U_VPSS_BASE_RD_IMGY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_addr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGY_ADDR_LOW;
/* Define the union U_VPSS_BASE_RD_IMGC_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_addr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGC_ADDR_HIGH;
/* Define the union U_VPSS_BASE_RD_IMGC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_addr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGC_ADDR_LOW;
/* Define the union U_VPSS_BASE_RD_IMGCR_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cr_addr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGCR_ADDR_HIGH;
/* Define the union U_VPSS_BASE_RD_IMGCR_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cr_addr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMGCR_ADDR_LOW;
/* Define the union U_VPSS_BASE_RD_IMG_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_stride            : 16  ; /* [15..0]  */
        unsigned int    c_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMG_STRIDE;

/* Define the union U_VPSS_BASE_RD_IMG_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_mute_val          : 10  ; /* [9..0]  */
        unsigned int    c_mute_val          : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_IMG_MUTE_VAL;


//-------------------------------------------------------
// VPSS READ SOLO BASE REGISTER
//-------------------------------------------------------
/* Define the union U_VPSS_BASE_RD_SOLO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0           : 21  ; /* [20..0]  */
        unsigned int    mirror               : 1   ; /* [21]  */
        unsigned int    flip                 : 1   ; /* [22]  */
        unsigned int    reserved_1           : 4   ; /* [26..23]  */
        unsigned int    en1                  : 1   ; /* [27]  */
        unsigned int    d_bypass             : 1   ; /* [28]  */
        unsigned int    mute_en              : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_CTRL;
/* Define the union U_VPSS_BASE_RD_SOLO_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    width        : 16  ; /* [15..0]  */
        unsigned int    height       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_SIZE;
/* Define the union U_VPSS_BASE_RD_SOLO_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int addr_h        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_ADDR_HIGH;
/* Define the union U_VPSS_BASE_RD_SOLO_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int addr_l        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_ADDR_LOW;
/* Define the union U_VPSS_BASE_RD_SOLO_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stride       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_STRIDE;
/* Define the union U_VPSS_BASE_RD_SOLO_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mute_val0     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_MUTE_VAL0;
/* Define the union U_VPSS_BASE_RD_SOLO_MUTE_VAL1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mute_val1     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_RD_SOLO_MUTE_VAL1;

//-------------------------------------------------------
// VPSS WRITE IMG BASE REGISTER
//-------------------------------------------------------
/* Define the union U_VPSS_BASE_WR_IMG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    format               : 4   ; /* [3..0]  */
        unsigned int    type                 : 4   ; /* [7..4]  */
        unsigned int    bitw                 : 4   ; /* [11..8]  */
        unsigned int    cmp_mode             : 4   ; /* [15..12]  */
        unsigned int    uv_invert            : 1   ; /* [16]  */
        unsigned int    mirror               : 1   ; /* [17]  */
        unsigned int    flip                 : 1   ; /* [18]  */
        unsigned int    dither_en            : 1   ; /* [19]  */
        unsigned int    dither_mode          : 1   ; /* [20]  */
        unsigned int    reserved_1           : 2   ; /* [22..21]  */
        unsigned int    lm_rmode             : 3   ; /* [25..23]  */
        unsigned int    reserved_2           : 2   ; /* [27..26]  */
        unsigned int    h_bypass             : 1   ; /* [28]  */
        unsigned int    d_bypass             : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_CTRL;
/* Define the union U_VPSS_BASE_WR_IMG_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_offset       : 16  ; /* [15..0]  */
        unsigned int    ver_offset       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_OFFSET;
/* Define the union U_VPSS_BASE_WR_IMGY_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_addr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMGY_ADDR_HIGH;
/* Define the union U_VPSS_BASE_WR_IMGY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_addr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMGY_ADDR_LOW;
/* Define the union U_VPSS_BASE_WR_IMGC_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_addr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMGC_ADDR_HIGH;
/* Define the union U_VPSS_BASE_WR_IMGC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_addr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMGC_ADDR_LOW;
/* Define the union U_VPSS_BASE_WR_IMG_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_stride          : 16  ; /* [15..0]  */
        unsigned int    c_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_STRIDE;
/* Define the union U_VPSS_BASE_WR_IMG_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    width            : 16  ; /* [15..0]  */
        unsigned int    height           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_SIZE;
/* Define the union U_VPSS_BASE_WR_IMG_FINFO_HIGN */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int finfo_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_FINFO_HIGN;
/* Define the union U_VPSS_BASE_WR_IMG_FINFO_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int finfo_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_IMG_FINFO_LOW;

//-------------------------------------------------------
// VPSS WRITE SOLO BASE REGISTER
//-------------------------------------------------------
/* Define the union U_VPSS_BASE_WR_SOLO_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0           : 17  ; /* [16..0]  */
        unsigned int    mirror               : 1   ; /* [17]  */
        unsigned int    flip                 : 1   ; /* [18]  */
        unsigned int    reserved_1           : 10  ; /* [28..19]  */
        unsigned int    d_bypass             : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_SOLO_CTRL;
/* Define the union U_VPSS_BASE_WR_SOLO_ADDR_HIGH */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int addr_h        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_SOLO_ADDR_HIGH;
/* Define the union U_VPSS_BASE_WR_SOLO_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int addr_l        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_SOLO_ADDR_LOW;
/* Define the union U_VPSS_BASE_WR_SOLO_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stride       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_SOLO_STRIDE;
/* Define the union U_VPSS_BASE_WR_SOLO_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    width        : 16  ; /* [15..0]  */
        unsigned int    height       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_BASE_WR_SOLO_SIZE;


typedef enum
{
    VPSS_MASTER_SEL_0 = 0,
    VPSS_MASTER_SEL_BUTT
} VPSS_MASTER_SEL_E;

typedef enum
{
    VPSS_MAC_ADDR_CTRL_WR_STT   ,
    VPSS_MAC_ADDR_CTRL_RD_TUNL  ,
    VPSS_MAC_ADDR_CTRL_WR_TUNL  ,
    VPSS_MAC_ADDR_CTRL_BUTT
} VPSS_MAC_CTRL_ADDR_E;

typedef enum
{
    VPSS_PATTERN_MODE_DEGREE_30,
    VPSS_PATTERN_MODE_DEGREE_60,
    VPSS_PATTERN_MODE_BUTT
} VPSS_PATTERN_MODE_E;

typedef struct
{
    HI_BOOL                 bEn ;
    VPSS_PATTERN_MODE_E     enAngleMode ;
    HI_U32                  u32LineWidth;
    XDP_BKG_S               stBkgColor ;
} VPSS_PATTERN_CFG_S;

/****************************************************************/
// Function
/****************************************************************/
HI_VOID VpssGetRchnLayerName (VPSS_MAC_RCHN_E enLayer, HI_CHAR *cChnName);
HI_VOID VpssGetWchnLayerName (VPSS_MAC_WCHN_E enLayer, HI_CHAR *cChnName);
HI_BOOL VpssGetRchnClassType (VPSS_MAC_RCHN_E enLayer);
HI_BOOL VpssGetWchnClassType (VPSS_MAC_WCHN_E enLayer);
HI_U32  VpssGetRchnDataWidth (VPSS_MAC_RCHN_E enLayer);
HI_U32  VpssGetWchnDataWidth (VPSS_MAC_WCHN_E enLayer);

#endif

