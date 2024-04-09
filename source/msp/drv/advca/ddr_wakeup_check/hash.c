#include "lib.h"
#include "hash.h"

#define UART_PRINT_OUT 0xf8b00000


void HEX2STR(char buf[2], u8 val)
{
    u8 high, low;
    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;
    if(high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }
    if(low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }
}
void printu32(unsigned int *size)
{
    char buf[2];
    unsigned int i;
    HEX2STR(buf,(u8)((*size) >> 24));
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[0]);
#endif
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[1]);
#endif
    HEX2STR(buf,(u8)((*size) >> 16));
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[0]);
#endif
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[1]);
#endif
    HEX2STR(buf,(u8)((*size) >> 8));
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[0]);
#endif
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[1]);
#endif
    HEX2STR(buf,(u8)*size);
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[0]);
#endif
#ifndef HI_ADVCA_FUNCTION_RELEASE
    i = 0;while(i++ < 0x1fff);
    reg_set(UART_PRINT_OUT, buf[1]);
#endif
}
#define wait_minute_2(x,y) do{ \
    unsigned char  i, j; \
    for(i = 0; i < x; i++) {\
        for(j = 0; j < y; j++); \
    }\
}while(0);
#define trace_char(ch) do{ \
    reg_set(UART_PRINT_OUT, ch);\
    }while(0)
void printf_str(char *string)
{
    char *p = string;
    for(; *p!='\0'; p++)
    {
        printf_char(*p);
    }
    printf_char('\n');printf_char('\r');
    return;
}
void printf_char(unsigned char ch)
{
    int regValue = 0;
    while(1)
    {
        regValue = reg_get(UART_PRINT_OUT + 0x18);
        if((regValue & 0x20) == 0)
        {
            break;
        }
        wait_minute_2(20,20);
    }
    wait_minute_2(20,20);
    trace_char(ch);
}
void Hex2Str(unsigned int u32Hex, char *pu8Str)
{
    unsigned int i;
    unsigned char u8Tmp;
    for(i = 0; i < 8; i++)
    {
        u8Tmp = (u32Hex >> (28 - (i * 4))) & 0x0F;
        if(u8Tmp >= 0 && u8Tmp <= 9)
        {
            pu8Str[i] = (u8Tmp + 0x30);
        }
        else if(u8Tmp >= 10 && u8Tmp <= 15)
        {
            pu8Str[i] = (u8Tmp + 0x37);
        }
    }
    pu8Str[i] = '\0';
}
void printf_hex(unsigned int u32Hex)
{
    char u8Str[32];
    Hex2Str(u32Hex, u8Str);
    printf_char('0');
    printf_char('x');
    printf_str((char *)u8Str);
    printf_char('\n');
    printf_char('\r');
}

int hash_cfg_len(HASH_TYPE_E enType, u32 *size, u32 *pad_size)
{
    u32 total_len;
    u32 last_size;
    u32 val;
    u32 i;
    u32 count = 0;
    u32 timeout = 0;            //10s

    if ((size == NULL) || (pad_size == NULL))
    {
        return;
    }
    /*
    PERI_CRG49 ΪSHA ��ص�ʱ�Ӽ���λ���ƼĴ�����
    [4] RW sha_srst_req
    sha ��λ����
    0������λ��
    1����λ��
    [3:1] RW reserved ������
    [0] RW sha_cken
    sha ʱ���ſء�
    0���ضϣ�
    1���򿪡�
    */
    //reset
    val = 0x10;
    reg_set(HASH_REG_CRG, val);
    for(i=0; i<10000; i++)
    {
        count ++;//just for delay
    }

    //work
    val = 0x01;
    reg_set(HASH_REG_CRG, val);
    for(i=0; i<10000; i++)
    {
        count ++;//just for delay
    }


    *size &= ~3; /* align word */
    total_len = (*size + 9 + 63) & (~63);
    last_size = *size % 64;
    *pad_size = (last_size < 56) ? (55 - last_size) : (119 - last_size);
    /* Actually, pad_size at least is 3. When last_size equal 52, pad_size is 3. It's impossible less than 3.*/

    /* wait hash_rdy to be 1 */
    timeout = 0;
    do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_HASH_RDY));

    /* total len */
    reg_set(HASH_REG_TOTAL_LEN1, total_len);
    reg_set(HASH_REG_TOTAL_LEN2, 0);

    /* sha control */
    val = reg_get(HASH_REG_SHA_CTRL);
    val &= ~(3<<1);
    reg_set(HASH_REG_SHA_CTRL, val | (enType << 1));

    /* sha start */
    reg_set(HASH_REG_SHA_START, 1);
    return AUTH_SUCCESS;
}

int hash_cfg_dma(u8 *buf, u32 size, u32 *hash_dma_rcv_len)
{
    volatile u32 timeout = 0;
    u32 total_len = 0;

    /* sha control, select dma */
    reg_set(HASH_REG_SHA_CTRL, reg_get(HASH_REG_SHA_CTRL) & (~1));

    /* wait rec_rdy to be 1 */
    do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

    /* dma start addr, len */
    reg_set(HASH_REG_DMA_START_ADDR, (u32)buf);
    reg_set(HASH_REG_DMA_LEN, size);

    /* fix dma bug, wait for dma rev len == configed len */
    total_len = *hash_dma_rcv_len + size;

    timeout = 0;
    do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
        timeout++;
    } while(hash_dma_rcv_len != (reg_get(HASH_REG_REC_LEN1)));

    *hash_dma_rcv_len = total_len;
    return AUTH_SUCCESS;
}

void hash_cfg_cpu(u8 *buf, u32 size)
{
    u32 i;
    u32 data;
    u32 *ptr = (u32*)buf;

    if (buf == NULL)
    {
        return;
    }

    /* sha control, select cpu */
    reg_set(HASH_REG_SHA_CTRL, reg_get(HASH_REG_SHA_CTRL) | 1);

    size >>= 2;     /* size / 4 */
    for(i = 0; i < size; i++)
    {
        data = ptr[i];
        /* wait rec_rdy to be 1 */
        while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

        reg_set(HASH_REG_DATA_IN, data);
    }
}

int hash_cfg_pad(u32 size, u32 pad_size)
{
    u32 i;
    u32 data;
    u8 len[8]={0};
    u32 timeout = 0;

    /* wait rec_rdy to be 1 */
     do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

    /* sha control */
    reg_set(HASH_REG_SHA_CTRL, reg_get(HASH_REG_SHA_CTRL) | 1);

    /* cal len */
    for (i = 0; i < 8; i++)
    {
        len[i] = ((size * 8) >> ((7 - i) * 8)) & 0xff;
    }

    /* wait rec_rdy to be 1 */
    timeout = 0;
     do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

    /* first word */
    data = 0x80;
    reg_set(HASH_REG_DATA_IN, data);

    /* middle word */
    for(i = 3; i < pad_size; i+=4)
    {
        /* wait rec_rdy to be 1 */
        timeout = 0;
        do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
        } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

        reg_set(HASH_REG_DATA_IN, 0);
    }

    /* wait rec_rdy to be 1 */
    timeout = 0;
    do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));

    /* the last 2 word */
    data = (len[3]<<24) | (len[2]<<16) | (len[1]<<8) | len[0];
    reg_set(HASH_REG_DATA_IN, data);

    timeout = 0;
    do {
        if (timeout++ > CIPHER_TIME_OUT)
        {
            return AUTH_FAILURE;
        }
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_REC_RDY));
    data = (len[7]<<24) | (len[6]<<16) | (len[5]<<8) | len[4];
    reg_set(HASH_REG_DATA_IN, data);
    return AUTH_SUCCESS;
}

int hash_get_result(HASH_TYPE_E enType, u8 *out)
{
    u32 data, i;
    u32 len = (enType == MOD_HASH1) ? 20 : 32;
    u32 timeout = 0;            //10s

    timeout = 0;
    do {
        if (timeout++ > CIPHER_TIME_OUT)
    {
            return AUTH_FAILURE;
    }

    /* wait hash_rdy to be 1 */
    } while(!(reg_get(HASH_REG_SHA_STATUS) & SHA_STATUS_BIT_HASH_RDY));

    if((reg_get(HASH_REG_SHA_STATUS) & 0xf0) != 0)
    {
        out[0] = 0xee; /* error */
        return AUTH_FAILURE;
    }

    for(i = 0; i < len; i += 4)
    {
        data = reg_get(HASH_REG_SHA_OUT1 + i);
        out[i] = data & 0xff;
        out[i+1] = (data >> 8) & 0xff;
        out[i+2] = (data >> 16) & 0xff;
        out[i+3] = (data >> 24) & 0xff;
    }

    return AUTH_SUCCESS;
}

