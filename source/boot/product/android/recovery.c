#ifdef HI_MINIBOOT_SUPPORT
#include <app.h>
#else
#include <uboot.h>
#include <linux/string.h>
#include <malloc.h>
#include <spiflash_logif.h>
#include <nand_logif.h>
#include <emmc_logif.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <asm/arch/platform.h>
#include <net.h>
#include <linux/mtd/mtd.h>
#include "hi_common.h"
#include "exports.h"
#endif

#include "hi_drv_gpio.h"
#include "hi_type.h"
#include "hi_flash.h"
#include "recovery.h"
#ifdef HI_BUILD_WITH_KEYLED
#include "hi_keyled.h"
#endif
#ifdef HI_REMOTE_RECOVERY_SUPPORT
#include "hi_unf_ir.h"
#define REMOTE_BTN_RECOVER 0x629dff00
#define VOLUME_BTN_RECOVER 0x7e81ff00
int gpio_recovery = 0 ;
#endif

extern int kern_load(const char *addr);
extern HI_S32 HI_Android_Auth_Recovery(HI_VOID);


#define KEY_PRESS             (0x0)	/* press */
#define KEY_HOLD              (0x01)	/* hold */
#define KEY_RELEASE           (0x02)	/* release */

#define FASTBOOT_RECOVERY_NAME "recovery"
#define FASTBOOT_RECOVERY_OFFSET 0

#define FASTBOOT_MISC_NAME "misc"
#define FASTBOOT_MISC_OFFSET 0

#define KERNEL_LOAD_ADDR 0x1000000
int check_gpio_recovery(void)
{
	int count = 2;
	HI_U32 value;
	while ((HI_DRV_GPIO_ReadBit(HI_RECOVERY_GPIO,&value) == 0) &&(value == 0)&& (count > 0)) {
		udelay(1000 * 1000);
		count--;
	}

	printf("count=%x\n", count);
	if (count > 0)
		return HI_FAILURE;
	else
		return HI_SUCCESS;
}

#ifdef HI_BUILD_WITH_KEYLED
static int check_buttom_recovery(HI_S32 *keyvalue)
{
	HI_S32 Ret = -1;
	HI_U32 u32PressStatus = KEY_RELEASE;
	HI_U32 u32KeyValue = 0;
	HI_S32 s32Cnt = 0;

	Ret = HI_UNF_KEYLED_Init();
	if (HI_SUCCESS != Ret) {
		printf("init failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_SelectType(0);

	Ret |= HI_UNF_LED_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsKeyUp(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsRepKey(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_SetBlockTime(200);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEYLED_Init();
	if (HI_SUCCESS != Ret) {
		printf("init failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_SelectType(0);

	Ret |= HI_UNF_LED_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsKeyUp(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsRepKey(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_LED_Display(0xffffffff);
	if (HI_SUCCESS != Ret) {
		printf("display failed\n");
		return Ret;
	}

	printf("press the key!!\n");

	udelay(50000);

	Ret = HI_UNF_KEY_GetValue(&u32PressStatus, &u32KeyValue);
	printf("get key %d %d\n", u32KeyValue, u32PressStatus);

	while (u32KeyValue == RECOVERY_KEY && u32PressStatus == KEY_PRESS) {

		udelay(1000);
		*keyvalue = u32KeyValue;
		Ret = HI_UNF_KEY_GetValue(&u32PressStatus, &u32KeyValue);
		if (s32Cnt >= MAX_KEY_PRESS_COUNT)
			break;
		else if (u32PressStatus == KEY_RELEASE) {
			*keyvalue = -1;
			u32KeyValue = 0;
			s32Cnt = 0;
			break;
		} else {
			s32Cnt++;
		}
	}

	Ret = HI_UNF_LED_Close();
	if (HI_SUCCESS != Ret) {
		printf("LED close failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEY_Close();
	if (HI_SUCCESS != Ret) {
		printf("key close failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_DeInit();
	if (HI_SUCCESS != Ret) {
		printf("DeInit close failed\n");
		return Ret;
	}

	return HI_SUCCESS;

}
#endif
#ifdef HI_REMOTE_RECOVERY_SUPPORT
#define MAX_KEY_COUNT 30
int check_remote_recovery(void)
{
    HI_S32 ret = HI_FAILURE;
	HI_U64 remote_recovery = 0;
    enum KEY_STATUS PressStatus = KEY_STAT_BUTT;
    HI_U64 KeyId = 0;

    printf("check remote recovery button begin\n");

    ret = HI_UNF_IR_Init();
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_IR_Init failed\n");
        return ret;
    }

    ret = HI_UNF_IR_Enable(HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_IR_Enable failed\n");
        ret = HI_FAILURE;
        goto OUT;
    }

    while(HI_SUCCESS == HI_UNF_IR_GetValue(&PressStatus, &KeyId, 400)
            && ((KeyId  == REMOTE_BTN_RECOVER)||(KeyId  == VOLUME_BTN_RECOVER))){
        if(((KeyId  == REMOTE_BTN_RECOVER)||(KeyId  == VOLUME_BTN_RECOVER))
                && (remote_recovery == 0)){
            remote_recovery = KeyId;
        }
        if(remote_recovery
                && (KeyId  == ((REMOTE_BTN_RECOVER==remote_recovery)?VOLUME_BTN_RECOVER:REMOTE_BTN_RECOVER))){
			ret = HI_SUCCESS;
			goto OUT;
        }
		    udelay(2000);
    }
    ret = HI_FAILURE;
OUT:

    if (HI_SUCCESS != HI_UNF_IR_DeInit())
    {
        printf("HI_UNF_IR_DeInit failed\n");
    }

    return ret;
}
#endif

const char *boot_select(void)
{
	int ret;
	//int count = 0;
	unsigned int len = 0;
	unsigned int len_erase = 0;
	unsigned char *buf;
	unsigned char *buf1;
#ifdef HI_BUILD_WITH_KEYLED
	int keycode = -1;
#endif

	HI_HANDLE flashhandle;

	HI_Flash_InterInfo_S pFlashInfo;

	unsigned int pagesize;
	unsigned int erasesize;
#ifdef HI_REMOTE_RECOVERY_SUPPORT
	if(HI_SUCCESS == check_remote_recovery())
	{
		printf("enter the remote button recovery\n");
		gpio_recovery = 1;
	}
#endif
	flashhandle = HI_Flash_OpenByName(FASTBOOT_MISC_NAME);
	if ((0 == flashhandle) || (HI_INVALID_HANDLE == flashhandle)) {
		printf("HI_Flash_Open partion %s error\n", FASTBOOT_MISC_NAME);
	} else {
		ret = HI_Flash_GetInfo(flashhandle, &pFlashInfo);
		if (ret) {
			printf("HI_Flash_GetInfo %s error\n",
			       FASTBOOT_MISC_NAME);
		}
		switch (pFlashInfo.FlashType) {
		case HI_FLASH_TYPE_SPI_0:
			printf("misc partition can not in spi ERROR!\n");
			HI_Flash_Close(flashhandle);
			break;
		case HI_FLASH_TYPE_NAND_0:
			pagesize = pFlashInfo.PageSize;
			erasesize = pFlashInfo.BlockSize;
			len = MISC_PAGES * pagesize;
			len_erase = (len == erasesize) ? len :(len/erasesize +1)*erasesize;
			buf =
			    (unsigned char *)malloc(len *
						    sizeof(unsigned char));
			if (buf == NULL) {
				printf("malloc buf failed\n");
				HI_Flash_Close(flashhandle);
				break;
			}

			buf1 =
			    (unsigned char *)malloc(len_erase *
						    sizeof(unsigned char));
			if (buf1 == NULL) {
				printf("malloc buf1 failed\n");
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

			ret =
			    HI_Flash_Read(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}
			ret =
			    HI_Flash_Read(flashhandle, erasesize, buf1, len,
					  HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}
			/*check magic number */
			len = MISC_COMMAND_PAGE * pagesize;
			if ((0 == (memcmp(&buf[len], "boot-recovery", 13))) ||
			    (0 == (memcmp(&buf1[len], "boot-setlable", 13)))) {
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				return "recovery";
			}
#ifdef HI_REMOTE_RECOVERY_SUPPORT
			else if (gpio_recovery){
                memcpy(&buf[len], "boot-recovery", 14);
				memcpy(&buf[len+64],"recovery\n--send_intent=update_ui\n",33);
				ret = HI_Flash_Erase(flashhandle,FASTBOOT_MISC_OFFSET, len_erase);
			    if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				ret = HI_Flash_Write(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len*2, HI_FLASH_RW_FLAG_RAW);
		        if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				return "recovery";
			}
#endif
			else{
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}
		case HI_FLASH_TYPE_EMMC_0:
			len = 6 * SZ_1KB;
			buf =
			    (unsigned char *)malloc(len *
						    sizeof(unsigned char));
			if (!buf) {
				printf("malloc buf failed\n");
				HI_Flash_Close(flashhandle);
				break;
			}

			ret =
			    HI_Flash_Read(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

			int len1 = MISC_EMMC_COMMAND_PAGE * SZ_1KB;
			int len2 = MISC_EMMC_WRITE_LABEL_COMMAND_PAGE * SZ_1KB;
			if (0 == (memcmp(&buf[len1], "boot-recovery", 13)) ||
			    0 == (memcmp(&buf[len2], "boot-setlable", 13))) {
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				return "recovery";
			}
#ifdef HI_REMOTE_RECOVERY_SUPPORT
			else if (gpio_recovery){
                memcpy(&buf[len1], "boot-recovery", 14);
				memcpy(&buf[len1+64],"recovery\n--send_intent=update_ui\n",33);
				ret = HI_Flash_Erase(flashhandle,FASTBOOT_MISC_OFFSET,len);
			    if (ret == HI_FAILURE) {
				    free(buf);
				    buf = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				ret = HI_Flash_Write(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
		        if (ret == HI_FAILURE) {
				    free(buf);
				    buf = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				printf("bigfish __recovery__ok");
				return "recovery";
			}
#endif
			 else {
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

		default:
			HI_Flash_Close(flashhandle);
			break;
		}
	}
#ifdef HI_BUILD_WITH_KEYLED
	ret = check_buttom_recovery(&keycode);
	if (keycode == RECOVERY_KEY && ret == HI_SUCCESS) {
		printf("enter the keypress revocery,keycode=%d\n", keycode);
		return "recovery";
	}
#endif
#ifdef HI_GPIO_RECOVERY_SUPPORT
	if (check_gpio_recovery() == HI_SUCCESS) {
		printf("enter the gpio press revocery\n");
		return "recovery";
	}
#endif
	return "kernel";
}

int load_recovery_image(void)
{
	int ret;
	//size_t cnt;
	const HI_CHAR *addr = (HI_CHAR *)KERNEL_LOAD_ADDR;
	HI_HANDLE flashhandle;
	HI_Flash_InterInfo_S pFlashInfo;

	flashhandle = HI_Flash_OpenByName(FASTBOOT_RECOVERY_NAME);
	if ((0 == flashhandle) || (HI_INVALID_HANDLE == flashhandle)) {
		printf("HI_Flash_Open partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		return HI_FAILURE;
	}

	ret = HI_Flash_GetInfo(flashhandle, &pFlashInfo);
	if (ret == HI_FAILURE) {
		printf("HI_Flash_GetInfo partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		HI_Flash_Close(flashhandle);
		return HI_FAILURE;
	}
	ret =
	    HI_Flash_Read(flashhandle, FASTBOOT_RECOVERY_OFFSET, (HI_U8*)addr,
			  pFlashInfo.PartSize, HI_FLASH_RW_FLAG_RAW);
	if (ret == HI_FAILURE) {
		printf("HI_Flash_Read partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		HI_Flash_Close(flashhandle);
		return HI_FAILURE;
	}
	HI_Flash_Close(flashhandle);

	printf("Automatic boot of image at addr 0x%p ...\n", addr);
	ret = kern_load(addr);
	if (ret < 0) {
		printf("recovery bootm failed!\n");
		return -1;
	}

	return 0;
}

void load_recovery(void)
{
	if (!strcmp(boot_select(), "kernel"))
		return;
	char recovery_boot_args[2048] = {0};
	char boot_args[2048] = {0};
#ifdef HI_ADVCA_SUPPORT
#ifndef HI_MINIBOOT_SUPPORT
#ifdef HI_ADVCA_TYPE_OTHER
	if (-1 == HI_Android_Auth_Recovery())
	{
		run_command("reset", 0);
	}
#endif
#endif
#endif
	char mmz[256] = {0};
	char selinux_flag[256] = {0};
	strncpy(mmz," mmz=ddr,0,0,256M",strlen(" mmz=ddr,0,0,256M"));
	strncpy(selinux_flag, "androidboot.selinux=", strlen("androidboot.selinux="));
	printf("selinux_flag is %s\n",selinux_flag);
	long long chipid;
	chipid = get_chipid();

	printf("bootargs:%s\n", getenv("bootargs"));

	if (getenv("recoverybootargs")) {
		strncpy(recovery_boot_args, getenv("recoverybootargs"), strlen(getenv("recoverybootargs")));
		setenv("bootargs", recovery_boot_args);
	}

	strncpy(boot_args, getenv("bootargs"), strlen(getenv("bootargs")));
	if(chipid == _HI3798M_V100) {
		snprintf(boot_args, sizeof(boot_args), "%s %s", boot_args, mmz);
	}
#ifndef HI_ADVCA_SUPPORT
	if (strstr(boot_args, selinux_flag)) {
		if (strncmp(boot_args + strlen(selinux_flag), "enforcing", 9) == 0) {
			char tmp[2048] = {0};
			strncpy(tmp,selinux_flag,strlen(selinux_flag));
			strcat(tmp, "permissive");
			strcat(tmp, boot_args + strlen(selinux_flag) + 9);
			strcat(tmp, "\0");
			memset(boot_args, 0, strlen(boot_args));
			strncpy(boot_args, tmp, strlen(tmp));
		}
	}
#endif
	setenv("bootargs",boot_args);
        if(chipid == _HI3796M_V200_21X21 ||
		chipid == _HI3796M_V200_15X15){
		setenv("notee","y");
	}

	printf("==Enter recovery!\n");
	printf("recoverybootargs:%s\n", getenv("bootargs"));

	if (load_recovery_image() != 0) {
		printf("enter recovery fail!!\n");
		setenv("bootargs", boot_args);
	}
}
