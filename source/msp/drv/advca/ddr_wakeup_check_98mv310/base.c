#include "lib.h"
#include "base.h"

#define UART_PRINT_OUT 0xf8b00000

#define trace_char(ch) do{ \
    reg_set(UART_PRINT_OUT, ch);\
    }while(0)

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

void printf_str(char *string)
{
    char *p = string;
    for(; *p!='\0'; p++)
    {
        printf_char(*p);
    }
    //printf_char('\n');printf_char('\r');
    return;
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
    printf_char(' ');
    //printf_char('\r');
}

void memset(void *s, int c, unsigned int count)
{
    char *__s = (char *)s;

    while (count--)
        *__s++ = (char)c;

    return;
}

void memcpy(void * dst, const void * src, unsigned int count)
{
    char *__dst = (char *)dst;
    char *__src = (char *)src;

    while (count--)
        *__dst++ = *__src++;

    return;
}

void u82u32(unsigned int * u32_data, unsigned char * u8_data, unsigned int byte_size)
{
    int i = 0;

    for (i = 0; i < (byte_size / 4); i++)
    {
        u32_data[i] = u8_data[4 * i] | (u8_data[4 * i + 1] << 8) | (u8_data[4 * i + 2] << 16) |
                        (u8_data[4 * i + 3] << 24);
    }
}

void u322u8(unsigned char * u8_data, unsigned int * u32_data, unsigned int byte_size)
{
    int i = 0;

    for (i = 0; i < (byte_size / 4); i++)
    {
        *(u8_data + 4 * i) = (*(u32_data + i)) & 0xFF;
        *(u8_data + 4 * i + 1) = (*(u32_data + i) >> 8) & 0xFF;
        *(u8_data + 4 * i + 2) = (*(u32_data + i) >> 16) & 0xFF;
        *(u8_data + 4 * i + 3) = (*(u32_data + i) >> 24) & 0xFF;
    }
}

