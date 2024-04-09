#ifndef __HI_CIPHER__
#define __HI_CIPHER__
#include "types.h"

#define AUTH_SUCCESS                (0x3CA5965A)
#define AUTH_FAILURE                (0xC35A69A5)

/* spacc error code */
#define HI_CIPHER_ERR_BUSY                 AUTH_FAILURE
#define HI_CIPHER_ERR_TIMEOUT              AUTH_FAILURE

/* spacc macro define */
#define DMA_DECRYPT_CHANNEL                 2
#define HASH_HARD_CHN                       1
#define HASH_HARD_CHN_NUM                   3
#define CIPHER_LOGIC_MAX_CHN                4
#define CIPHER_PKGx1_CHAN                   0
#define CIPHER_PKGxN_CHAN_MIN               1
#define CIPHER_PKGxN_CHAN_MAX               2
#define CIPHER_MAX_DEPTH                    2 /*only use 2 nodes */
#define CIPHER_PAGE_SIZE                    64 /* size of 2 nodes */
#define CIPHER_CHN_MASK                     0x07 /*2.1.0*/
#define CIPHER_TIME_OUT                     50000
#define CIPHER_TIME_OUT_LONG                50000
#define SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE      CIPHER_PAGE_SIZE
#define SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE     CIPHER_PAGE_SIZE
#define SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE    CIPHER_PAGE_SIZE
#define CIPHER_BLOCK_SIZE                   0x40
#define HASH_BLOCK_SIZE                     0x40

#define HI_SYMC_ALG_AES                     0x02
#define HI_SYMC_ALG_SM4                     0x03
#define HI_SYMC_MODE_CBC                    0x01
#define HI_MODE_HASH                        0x00
#define HI_HASH_ALG_SHA256                  0x01
#define HI_HASH_ALG_SM3                     0x02

#define SYMC_DAT_WIDTH128                   0x03
#define DIGEST_ALG_SHA256                   0x02
#define DIGEST_ALG_SM3                      0x05
#define CIPHER_CTRL_NONE                    0x00
#define CIPHER_CTRL_SYMC_IN_FIRST           0x01
#define CIPHER_CTRL_SYMC_IN_LAST            0x02
#define CIPHER_CTRL_SYMC_OUT_LAST           0x02
#define CIPHER_CTRL_HASH_IN_FIRST           0x01
#define CIPHER_CTRL_HASH_IN_LAST            0x02

#define SHA1_LEN                            0x14
#define HASH_RESULT_SIZE                    0x20

#define SHA256_H0                           0x6a09e667UL
#define SHA256_H1                           0xbb67ae85UL
#define SHA256_H2                           0x3c6ef372UL
#define SHA256_H3                           0xa54ff53aUL
#define SHA256_H4                           0x510e527fUL
#define SHA256_H5                           0x9b05688cUL
#define SHA256_H6                           0x1f83d9abUL
#define SHA256_H7                           0x5be0cd19UL

#define SM3_H0                              0x7380166FUL
#define SM3_H1                              0x4914B2B9UL
#define SM3_H2                              0x172442D7UL
#define SM3_H3                              0xDA8A0600UL
#define SM3_H4                              0xA96F30BCUL
#define SM3_H5                              0x163138AAUL
#define SM3_H6                              0xE38DEE4DUL
#define SM3_H7                              0xB0FB0E4EUL

/* spacc struct and union define */
struct HASH_INFO
{
    uint32_t     bIsInit;
    uint32_t     enMode;
    uint32_t     enAlg;
};

struct cipher_symc_in_entry_t
{
    uint32_t     cipher_cmd:2;
    uint32_t     rev1:6;
    uint32_t     sym_ctrl:7;
    uint32_t     rev2:1;
    uint32_t     gcm_iv_len:4;
    uint32_t     rev3:12;
    uint32_t     word1;
    uint32_t     sym_start_addr;
    uint32_t     sym_alg_length;
    uint32_t     IV[4];
};

struct cipher_digest_in_entry_t
{
    uint32_t    cipher_cmd:2;
    uint32_t    rev1:6;
    uint32_t    hash_ctrl:6;
    uint32_t    rev2:18;
    uint32_t    hash_start_addr;
    uint32_t    hash_alg_length;
    uint32_t    word1;
};

struct cipher_symc_out_entry_t
{
    uint32_t    rev1:8;
    uint32_t    aes_ctrl:4;
    uint32_t    rev2:20;
    uint32_t    sym_start_addr;
    uint32_t    sym_alg_length;
    uint32_t    hash_rslt_start_addr;
    uint32_t    tag[4];
};

struct cipher_symc_context
{
    struct cipher_symc_in_entry_t*   entry_symc_in;
    struct cipher_symc_out_entry_t*  entry_symc_out;
    struct cipher_digest_in_entry_t* entry_digest_in;

    uint32_t entry_symc_in_depth;
    uint32_t entry_symc_out_depth;
    uint32_t symc_cur_in_nodes;
    uint32_t symc_cur_out_nodes;
};

struct cipher_digest_context
{
    unsigned int     digest_len;

    struct cipher_digest_in_entry_t* entry_digest_in;
    unsigned int entry_digest_in_depth;
    unsigned int digest_cur_in_nodes;
};

typedef union
{
    struct
    {
        unsigned int    cipher_sec_chn_cfg    : 8   ; /* [7..0]  */
        unsigned int    cipher_sec_chn_cfg_lock : 1   ; /* [8]  */
        unsigned int    reserved_0            : 7   ; /* [15..9]  */
        unsigned int    hash_sec_chn_cfg      : 8   ; /* [23..16]  */
        unsigned int    hash_sec_chn_cfg_lock : 1   ; /* [24]  */
        unsigned int    reserved_1            : 7   ; /* [31..25]  */
    } bits;
    unsigned int    u32;
} U_SEC_CHN_CFG;

typedef union
{
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    cipher_chn_ibuf_raw   : 7   ; /* [7..1]  */
        unsigned int    cipher_chn_obuf_raw   : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;
    unsigned int    u32;
} U_CIPHER_INT_RAW;

typedef union
{
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    sym_chn_alg_mode      : 3   ; /* [3..1]  */
        unsigned int    sym_chn_alg_sel       : 3   ; /* [6..4]  */
        unsigned int    sym_chn_decrypt       : 1   ; /* [7]  */
        unsigned int    sym_chn_dat_width     : 2   ; /* [9..8]  */
        unsigned int    sym_chn_key_length    : 2   ; /* [11..10]  */
        unsigned int    reserved_1            : 2   ; /* [13..12]  */
        unsigned int    sym_chn_key_sel       : 1   ; /* [14]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    sym_chn_dout_byte_swap_en : 1   ; /* [16]  */
        unsigned int    sym_chn_din_byte_swap_en : 1   ; /* [17]  */
        unsigned int    sym_chn_sm1_round_num : 2   ; /* [19..18]  */
        unsigned int    reserved_3            : 2   ; /* [21..20]  */
        unsigned int    weight                : 10  ; /* [31..22]  */
    } bits;
    unsigned int    u32;
} U_CHANN_CIPHER_CTRL;

typedef union
{
    struct
    {
        unsigned int    cipher_in_node_mpackage_int_level : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    cipher_in_node_rptr   : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    cipher_in_node_wptr   : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    cipher_in_node_total_num : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;
    unsigned int    u32;
} U_CHANN_CIPHER_IN_NODE_CFG;

typedef union
{
    struct
    {
        unsigned int    cipher_out_node_mpackage_int_level : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    cipher_out_node_rptr  : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    cipher_out_node_wptr  : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    cipher_out_node_total_num : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;
    unsigned int    u32;
} U_CHANN_CIPHER_OUT_NODE_CFG;

typedef union
{
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    hash_chn_oram_raw     : 8   ; /* [25..18]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;
    unsigned int    u32;
} U_HASH_INT_RAW;

typedef union
{
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    hash_chn_agl_sel      : 3   ; /* [3..1]  */
        unsigned int    reserved_1            : 1   ; /* [4]  */
        unsigned int    hash_chn_mode         : 1   ; /* [5]  */
        unsigned int    hash_chn_key_sel      : 1   ; /* [6]  */
        unsigned int    hash_chn_dat_in_byte_swap_en : 1   ; /* [7]  */
        unsigned int    hash_chn_dat_in_bit_swap_en : 1   ; /* [8]  */
        unsigned int    hash_chn_auto_padding_en : 1   ; /* [9]  */
        unsigned int    hash_chn_hmac_key_addr : 3   ; /* [12..10]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;
    unsigned int    u32;
} U_CHANN_HASH_CTRL;

typedef union
{
    struct
    {
        unsigned int    hash_in_node_mpackage_int_level : 8   ; /* [7..0]  */
        unsigned int    hash_in_node_rptr     : 8   ; /* [15..8]  */
        unsigned int    hash_in_node_wptr     : 8   ; /* [23..16]  */
        unsigned int    hash_in_node_total_num : 8   ; /* [31..24]  */
    } bits;
    unsigned int    u32;
} U_CHANN_HASH_IN_NODE_CFG;

/* api declaration */
void HI_CIPHER_Init(void);
void HI_CIPHER_DeInit(void);
uint32_t HI_CIPHER_decrypt(const uint32_t u32SrcPhyAddr, uint32_t decrypt_type, const uint32_t u32Length, const uint32_t checksum);
uint32_t HI_HASH_Init(uint32_t hash_type);
uint32_t HI_HASH_Update(const uint32_t u32DataAddr, const uint32_t u32DataLen);
uint32_t HI_HASH_Final(const uint32_t u32DataAddr, const uint32_t u32DataLen, uint8_t *pu8OutputHash);
uint32_t HI_HASH_Padding(uint8_t *pu8Msg, uint32_t u32CurLen, uint32_t u32TotalLen);
#endif
