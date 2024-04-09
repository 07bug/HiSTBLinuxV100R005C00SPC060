#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <time.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/sockios.h>
#include <linux/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "hi_type.h"
#ifndef __GLIBC__
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#endif

#define RELEASE "1.0 version"

/* network interface ioctl's for MII commands */
#ifndef SIOCGMIIPHY
#warning "SIOCGMIIPHY is not defined by your kernel source"
#define SIOCGMIIPHY (SIOCDEVPRIVATE)	/* Read from current PHY */
#define SIOCGMIIREG (SIOCDEVPRIVATE+1) 	/* Read any PHY register */
#define SIOCSMIIREG (SIOCDEVPRIVATE+2) 	/* Write any PHY register */
#define SIOCGPARAMS (SIOCDEVPRIVATE+3) 	/* Read operational parameters */
#define SIOCSPARAMS (SIOCDEVPRIVATE+4) 	/* Set operational parameters */
#endif


/* This data structure is used for all the MII ioctl's */
struct mii_data
{
	__u16	phy_id;
	__u16	reg_num;		//寄存器的号数
	__u16	val_in;			//输入寄存器的值
	__u16	val_out;		//输出寄存器的值
};

/* Basic Mode Control Register */
#define MII_BMCR		0x00		//控制寄存器的操作
#define  MII_BMCR_RESET		0x8000  //复位功能  设置1复位，复位后自动清0
#define  MII_BMCR_LOOPBACK	0x4000	//通过Loopback功能可以检查MII/GMII以及PHY接口部分是否工作正常
#define  MII_BMCR_100MBIT	0x2000	//设置速率，必须要自动协商功能关闭，而且必须复位才生效
#define  MII_BMCR_AN_ENA	0x1000  //自动协商功能，设置1生效，端口工作模式和链接对端进行自动协商
#define  MII_BMCR_PW_DOWN   0X0800	//端口开关，设置为1位power down,设置为0为normal operation
#define  MII_BMCR_ISOLATE	0x0400	//隔离状态开关
#define  MII_BMCR_RESTART	0x0200	//重新启动自动协商开关，自动协商功能开启才可用
#define  MII_BMCR_DUPLEX	0x0100	//双工模式，设置为1为双工，设置为0为半双工，必须在自动协商功能关闭才有效，设置之后需要端口复位
#define  MII_BMCR_COLTEST	0x0080	//冲突信号设置


/* Basic Mode Status Register */
#define MII_BMSR		0x01			//状态寄存器的设置
#define  MII_BMSR_CAP_MASK	0xf800
#define  MII_BMSR_100BASET4	0x8000
#define  MII_BMSR_100BASETX_FD	0x4000
#define  MII_BMSR_100BASETX_HD	0x2000
#define  MII_BMSR_10BASET_FD	0x1000
#define  MII_BMSR_10BASET_HD	0x0800
#define  MII_BMSR_NO_PREAMBLE	0x0040
#define  MII_BMSR_AN_COMPLETE	0x0020
#define  MII_BMSR_REMOTE_FAULT	0x0010
#define  MII_BMSR_AN_ABLE	0x0008
#define  MII_BMSR_LINK_VALID	0x0004  //link状态指示位，bit2=1表示端口link up,bit2=0表示端口link down;通过轮询PHY的这个寄存器值来判断端口的Link状态的


#define  MII_BMSR_JABBER	0x0002
#define  MII_BMSR_EXT_CAP	0x0001


#define MII_PHY_ID1		0x02	//
#define MII_PHY_ID2		0x03	//这两个寄存器是只读寄存器，存放芯片资料，识别型号和版本


/* Auto-Negotiation Advertisement Register */
#define MII_ANAR		0x04   //寄存器4是自动协商的能力通告寄存器，在AN Enable的前提下（见寄存器0），端口根据该寄存器的相关配置将自动协商信息进行通告；



/* Auto-Negotiation Link Partner Ability Register */
#define MII_ANLPAR		0x05   //本端PHY接收到的对端PHY所通告的端口能力

#define  MII_AN_NEXT_PAGE	0x8000
#define  MII_AN_ACK		0x4000
#define  MII_AN_REMOTE_FAULT	0x2000
#define  MII_AN_ABILITY_MASK	0x07e0
#define  MII_AN_FLOW_CONTROL	0x0400
#define  MII_AN_100BASET4	0x0200
#define  MII_AN_100BASETX_FD	0x0100
#define  MII_AN_100BASETX_HD	0x0080
#define  MII_AN_10BASET_FD	0x0040
#define  MII_AN_10BASET_HD	0x0020
#define  MII_AN_PROT_MASK	0x001f
#define  MII_AN_PROT_802_3	0x0001

/* Auto-Negotiation Expansion Register */
#define MII_ANER		0x06   //   寄存器保存了PHY自动协商过程的异常信息

#define  MII_ANER_MULT_FAULT	0x0010
#define  MII_ANER_LP_NP_ABLE	0x0008
#define  MII_ANER_NP_ABLE	0x0004
#define  MII_ANER_PAGE_RX	0x0002
#define  MII_ANER_LP_AN_ABLE	0x0001

/* Phy control 2 Register */
#define MII_CTRL2 0x1F      //
#define MII_CTRL2_MDIX_SELECT (1<<14)
#define MII_CTRL2_MDIX_DISABLE (1<<13)




static char version[] = "$Id: mii-operation.c,v 1.8 2017/08/28 10:18:26 ecki Exp ";
#define MAX_ETH		8		/* Maximum # of interfaces */

/* Table of known MII's */
static struct
{
	u_short	id1, id2;
	const char* name;
} mii_id[] =
{
	{ 0x0022, 0x5610, "AdHoc AH101LF" },
	{ 0x0022, 0x5520, "Altimata AC101LF" },
	{ 0x0000, 0x6b90, "AMD 79C901A HomePNA" },
	{ 0x0000, 0x6b70, "AMD 79C901A 10baseT" },
	{ 0x0181, 0xb800, "Davicom DM9101" },
	{ 0x0043, 0x7411, "Enable EL40-331" },
	{ 0x0015, 0xf410, "ICS 1889" },
	{ 0x0015, 0xf420, "ICS 1890" },
	{ 0x0015, 0xf430, "ICS 1892" },
	{ 0x02a8, 0x0150, "Intel 82555" },
	{ 0x7810, 0x0000, "Level One LXT970/971" },
	{ 0x2000, 0x5c00, "National DP83840A" },
	{ 0x0181, 0x4410, "Quality QS6612" },
	{ 0x0282, 0x1c50, "SMSC 83C180" },
	{ 0x0300, 0xe540, "TDK 78Q2120" },
};
#define NMII (sizeof(mii_id)/sizeof(mii_id[0]))

/*--------------------------------------------------------------------*/

struct option longopts[] =
{
 /* { name  has_arg  *flag  val } */
	{"advertise",	1, 0, 'A'},	/* Change capabilities advertised. */
	{"force",		1, 0, 'F'},	/* Change capabilities advertised. */
	{"phy",		1, 0, 'p'},	/* Set PHY (MII address) to report. */
	{"log",		0, 0, 'l'},	/* Set PHY (MII address) to report. */
	{"restart",		0, 0, 'r'},	/* Restart link negotiation */
	{"reset",		0, 0, 'R'},	/* Reset the transceiver. */
	{"verbose", 	0, 0, 'v'},	/* Report each action taken.  */
	{"version", 	0, 0, 'V'},	/* Emit version information.  */
	{"watch", 		0, 0, 'w'},	/* Constantly monitor the port.  */
	{"help", 		0, 0, '?'},	/* Give help */
	{"modify",		0, 0, 'M'},
	{"display",		0, 0, 'D'},
	{"search",		0, 0, 's'},
	{"powerdown",	0, 0, 'P'},
	{ 0, 0, 0, 0 }
};

static HI_U32 opt_reg_index=0,  opt_reg_data=0;
static HI_U32 opt_reg_modify=0, opt_reg_display=0;


static HI_S32 nway_advertise = 0;
static HI_S32 fixed_speed = 0;
static HI_S32 override_phy = -1;

static HI_S32 skfd = -1;		/* AF_INET socket for ioctl() calls. */
static struct ifreq ifr;
static HI_S32 phy_val[32];

char buf[100];
static HI_S32 bmcr=0, bmsr=0, advert=0, lkpar=0;
/*--------------------------------------------------------------------*/

const struct
{
	const char* name;
	u_short	value;
} media[] =
{
	/* The order through 100baseT4 matches bits in the BMSR */
	{ "10baseT-HD",	MII_AN_10BASET_HD },
	{ "10baseT-FD",	MII_AN_10BASET_FD },
	{ "100baseTx-HD",	MII_AN_100BASETX_HD },
	{ "100baseTx-FD",	MII_AN_100BASETX_FD },
	{ "100baseT4",	MII_AN_100BASET4 },
	{ "100baseTx",	MII_AN_100BASETX_FD | MII_AN_100BASETX_HD },
	{ "10baseT",	MII_AN_10BASET_FD | MII_AN_10BASET_HD },
};
#define NMEDIA (sizeof(media)/sizeof(media[0]))


static HI_S32 mii_readl(HI_S32 skfd, HI_S32 location)
{
	struct mii_data *mii = (struct mii_data *)&ifr.ifr_data;
	mii->reg_num = location;
	if (ioctl(skfd, SIOCGMIIREG, &ifr) < 0)
	{
		fprintf(stderr, "SIOCGMIIREG on %s failed: %s\n", ifr.ifr_name,
			strerror(errno));
		return -1;
	}
	return mii->val_out;
}


static char* mii_list(HI_S32 mask, HI_S32 best)
{
	static char buf[100];
	HI_S32 i;
	*buf = '\0';
	mask >>= 5;
	for (i = 4; i >= 0; i--)
	{
		if (mask & (1<<i))
		{
			strcat(buf, " ");
			strcat(buf, media[i].name);
			if (best)
				break;
		}
	}
	if (mask & (1<<5))
	strcat(buf, " flow-control");
	return buf;
}



static void mii_writel(HI_S32 skfd, HI_S32 location, HI_S32 value)//将值(value)写入第几个寄存器(location)
{
	struct mii_data *mii = (struct mii_data *)&ifr.ifr_data;
	mii->reg_num = location;
	mii->val_in = value;
	if (ioctl(skfd, SIOCSMIIREG, &ifr) < 0)
	{
		fprintf(stderr, "SIOCSMIIREG on %s failed: %s\n", ifr.ifr_name,
			strerror(errno));
	}
}





static HI_S32 param_set(char* arg)
{
	HI_S32 mask, i;
	char* s;
	mask = strtoul(arg, &s, 16);
	if ((*arg != '\0') && (*s == '\0'))
	{
		if ((mask & MII_AN_ABILITY_MASK) &&
			!(mask & ~MII_AN_ABILITY_MASK))
	    return mask;
		goto failed;
	}
	else
	{
		mask = 0;
		s = strtok(arg, ", ");
		do
		{
			for (i = 0; i < NMEDIA; i++)
			if (s && strcasecmp(media[i].name, s) == 0)
				break;
			if (i == NMEDIA) goto failed;
			mask |= media[i].value;
		} while ((s = strtok(NULL, ", ")) != NULL);
	}
	return mask;
failed:
	fprintf(stderr, "Invalid media specification '%s'.\n", arg);
	return -1;
}

/*--------------------------------------------------------------------*/



HI_S32 mii_phy(HI_S32 sock, HI_S32 phy_id)
{

	HI_S32 i;
	mii_readl(sock, MII_BMSR);
	for (i = 0; i < 32 ; i++)
		phy_val[i] = mii_readl(sock, i);// 挨着读寄存器，并把值给数组phy_val[];
	if (phy_val[MII_BMCR] == 0xffff  || phy_val[MII_BMSR] == 0x0000) //判断控制寄存器和状态寄存器的值
	{
		fprintf(stderr, "  No MII transceiver present!.\n");
		return -1;
	}
	bmcr = phy_val[MII_BMCR];
	bmsr = phy_val[MII_BMSR];
	advert = phy_val[MII_ANAR];
	lkpar = phy_val[MII_ANLPAR];
	sprintf(buf, "%s: ", ifr.ifr_name);//eth0网卡
	fflush(stdout);
	return 0;
}

/*--------------------------------------------------------------------*/
static void current_status(HI_S32 skfd, char* ifname)
{
	sprintf(buf, "%s: ", ifr.ifr_name);
	if (bmcr & MII_BMCR_AN_ENA)
	{
		if (bmsr & MII_BMSR_AN_COMPLETE)
		{
			if (advert & lkpar)
			{
				strcat(buf, (lkpar & MII_AN_ACK) ? "negotiated" : "no autonegotiation,");
			strcat(buf, mii_list(advert & lkpar, 1));
			strcat(buf, ", ");
		}
		else
		{
			strcat(buf, "autonegotiation failed, ");
		}
	}
	else if (bmcr & MII_BMCR_RESTART)
	{
	    strcat(buf, "autonegotiation restarted, ");
	}
	}
	else
	{
		sprintf(buf+strlen(buf), "%s Mbit, %s duplex, ",
			(bmcr & MII_BMCR_100MBIT) ? "100" : "10",
			(bmcr & MII_BMCR_DUPLEX) ? "full" : "half");
	}
	strcat(buf, (bmsr & MII_BMSR_LINK_VALID) ? "link ok" : "no link");
	printf("%s\n",buf);
}

/*--------------------------------------------------------------------*/

static HI_S32 watch_one_operation(HI_S32 skfd, char* ifname, HI_S32 index ,HI_S32 maybe)
{

	static HI_S32 status[MAX_ETH] = { 0, /* ... */ };
	HI_S32 now;
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
	if (ioctl(skfd, SIOCGMIIPHY, &ifr) < 0)
	{
		if (!maybe||errno != ENODEV)
			fprintf(stderr, "SIOCGMIIPHY on '%s' failed: %s\n",
				ifname, strerror(errno));
		return -1;
	}
	now = (mii_readl(skfd, MII_BMCR)|(mii_readl(skfd, MII_BMSR) << 16));
	if  (status[index] != now)
		current_status(skfd, ifname);
		status[index] = now;
		return 0;
	}

/*--------------------------------------------------------------------*/

const char* usage = "usage: %s [-VvRrwls] [-A media,... | -F media] [interface ...]\n"
"    -V, --version          display version information\n"
"    -v, --verbose          more verbose output\n"
"    -R, --reset            reset MII to poweron state\n"
"    -r, --restart          restart autonegotiation\n"
"    -w, --watch            monitor for link status changes\n"
"    -l, --log              with -w, write events to syslog\n"
"    -A, --advertise=media,... advertise only specified media\n"
"    -F, --force=media  force specified media technology\n"
"    -s, --search		search the all phy value\n"
"    -u,                start up auto-mdix \n"
"    -d,                shutdown auo-mdix\n"
"    -D  reg            display phy reg value\n"
"    -M  reg value      modify phy reg use value\n"
"    media: 100baseT4, 100baseTx-FD, 100baseTx-HD, 10baseT-FD, 10baseT-HD,\n"
"       (to advertise both HD and FD) 100baseTx, 10baseT\n"
"    Example:\n"
"        show  phy reg(0x1f) value\n"
"            mii-operation -D 0x1f \n"
"        modify  phy reg(0x1f) value to 0x4ab2\n"
"            mii-operation -M 0x1F 0x4AB2 \n"
"";



HI_S32 main(HI_S32 argc, char **argv)
{
	HI_S32 i, c, ret=0;
	time_t t=0;
	char s[6];
	char a[20];
	struct mii_data *mii = (struct mii_data *)&ifr.ifr_data;
	HI_U32 temp=0;

	skfd = socket(AF_INET, SOCK_DGRAM,0);
	if(skfd<0)
	{
		perror("socket");
		exit(-1);
	}
	for (i = 0; i < MAX_ETH; i++)
	{
		sprintf(s, "eth%d", i);
		strncpy(ifr.ifr_name, s, IFNAMSIZ);
		if (ioctl(skfd, SIOCGMIIPHY, &ifr) < 0)
		{
			if (errno != ENODEV)
	    	fprintf(stderr, "SIOCGMIIPHY on '%s' failed: %s\n",s, strerror(errno));
			return 1;
		}
		break;
	}
	mii_phy(skfd,mii->phy_id);
	while ((c = getopt_long(argc, argv, "A:F:p:lrRvVwudMDs?", longopts, 0)) != EOF)
	switch (c)
	{
		case 'A':
			nway_advertise = param_set(optarg);
			if(nway_advertise==-1)
				break;
			mii_writel(skfd, MII_ANAR, nway_advertise | 1);
			printf("restarting autonegotiation...\n");
			mii_writel(skfd, MII_BMCR, 0x0000);
			mii_writel(skfd, MII_BMCR, MII_BMCR_AN_ENA|MII_BMCR_RESTART);
				break;

		case 'F':
			fixed_speed = param_set(optarg);
			if(fixed_speed==-1)
				break;
			if (fixed_speed & (MII_AN_100BASETX_FD|MII_AN_100BASETX_HD))
				temp |= MII_BMCR_100MBIT;
			if (fixed_speed & (MII_AN_100BASETX_FD|MII_AN_10BASET_FD))
				temp |= MII_BMCR_DUPLEX;
			mii_writel(skfd, MII_BMCR, temp);
			break;

		case 'p':
			override_phy = atoi(optarg);
			printf("using the specified MII index %d.\n", override_phy);
			sprintf(s, "eth%d", override_phy);
			watch_one_operation(skfd, s, 0, 0);
			break;

		case 'r':
			printf("restarting autonegotiation...\n");
			mii_writel(skfd, MII_BMCR, 0x0000);
			mii_writel(skfd, MII_BMCR, MII_BMCR_AN_ENA|MII_BMCR_RESTART);
			break;

		case 'R':
			printf("resetting the transceiver...\n");
			mii_writel(skfd, MII_BMCR, MII_BMCR_RESET);
			break;

		case 'v':
			printf("  product info: ");
			for (i = 0; i < NMII; i++)
			if ((mii_id[i].id1 == phy_val[2]) &&(mii_id[i].id2 == (phy_val[3] & 0xfff0)))
				break;
			if (i < NMII)
				printf("%s rev %d\n", mii_id[i].name, phy_val[3]&0x0f);
			else
				printf("vendor %02x:%02x:%02x, model %d rev %d\n",
			phy_val[2]>>10, (phy_val[2]>>2)&0xff,
				((phy_val[2]<<6)|(phy_val[3]>>10))&0xff,
					(phy_val[3]>>4)&0x3f, phy_val[3]&0x0f);
			printf("  basic mode:   ");
			if (bmcr & MII_BMCR_RESET)
				printf("software reset, ");
			if (bmcr & MII_BMCR_LOOPBACK)
				printf("loopback, ");
			if (bmcr & MII_BMCR_ISOLATE)
				printf("isolate, ");
			if (bmcr & MII_BMCR_COLTEST)
				printf("collision test, ");
			if (bmcr & MII_BMCR_AN_ENA)
			{
				printf("autonegotiation enabled\n");
			}
			else
			{
				printf("%s Mbit, %s duplex\n",
					(bmcr & MII_BMCR_100MBIT) ? "100" : "10",
					(bmcr & MII_BMCR_DUPLEX) ? "full" : "half");
			}
			printf("  basic status: ");
			if (bmsr & MII_BMSR_AN_COMPLETE)
				printf("autonegotiation complete, ");
			else if (bmcr & MII_BMCR_RESTART)
				printf("autonegotiation restarted, ");
			if (bmsr & MII_BMSR_REMOTE_FAULT)
				printf("remote fault, ");
			printf((bmsr & MII_BMSR_LINK_VALID) ? "link ok" : "no link");
			printf("\n  capabilities:%s", mii_list(bmsr >> 6, 0));
			printf("\n  advertising: %s", mii_list(advert, 0));
			if (lkpar & MII_AN_ABILITY_MASK)
				printf("\n  link partner:%s", mii_list(lkpar, 0));
				printf("\n");
			break;
		case 's':
			printf("Using SIOCGMIIPHY=0x%x\n", SIOCGMIIPHY);
			printf("  registers for MII PHY %d: ", mii->phy_id);
			for (i = 0; i < 32; i++)
				printf("%s %4.4x", ((i % 8) ? "" : "\n   "), phy_val[i]);
			printf("\n");
			break;

		case 'V':
			printf("%s\n%s\n", version, RELEASE);
			for (i = 0; i < MAX_ETH; i++)
				{
					sprintf(s, "eth%d", i);
					watch_one_operation(skfd, s, i, 1);
				}
			break;

		case 'l':
			for (i = 0; i < MAX_ETH; i++)
				{
					sprintf(s, "eth%d", i);
					current_status(skfd, s);
				}
			syslog(LOG_INFO, "%s", buf);
			break;

		case 'w':
			t = time(NULL);//得到系统时间
			strftime(a, sizeof(a), "%T", localtime(&t));//转化成本地时间
			printf("%s ", a);
			while (1)
			{
				sleep(1);
				if (optind == argc)
				{
					for (i = 0; i < MAX_ETH; i++)
					{
						sprintf(s, "eth%d", i);
						watch_one_operation(skfd, s, i, 1);
					}
				}
				else
				{
					for (i = optind; i < argc; i++)
					temp=watch_one_operation(skfd, argv[i], i-optind, 0);
					if(temp==-1)
					break;
				}
			}
			break;

		case 'u':
			printf("start up auto-mdix.......done!\n");
			temp = mii_readl(skfd, MII_CTRL2);
			mii_writel(skfd, MII_CTRL2,( temp & (~MII_CTRL2_MDIX_DISABLE) &(~MII_CTRL2_MDIX_SELECT)) );
			for (i = 0; i < MAX_ETH; i++)
					{
						sprintf(s, "eth%d", i);
						watch_one_operation(skfd, s, i, 1);
					}
			break;

		case 'd':
			printf("shutdown auto-mdix.......done!\n");
			temp = mii_readl(skfd, MII_CTRL2);
			mii_writel(skfd, MII_CTRL2,( temp |MII_CTRL2_MDIX_DISABLE|MII_CTRL2_MDIX_SELECT ) );
			for (i = 0; i < MAX_ETH; i++)
					{
						sprintf(s, "eth%d", i);
						watch_one_operation(skfd, s, i, 1);
					}
			break;

		case 'M':
			if ((optind+2) == argc)  //带两个参数
			{
				opt_reg_index = strtoul(argv[2],NULL,16);
				opt_reg_data  = strtoul(argv[3],NULL,16);
				mii_writel(skfd, opt_reg_index,opt_reg_data);//将值写入寄存器
				printf("Reg index 0x%X, value 0x%X is written into the reg \n.",opt_reg_index,opt_reg_data);
			}
			else
			{
				printf("the form you input is wrong\n");
				printf("Example:\n modify  phy reg(0x1f) value to 0x4ab2\n mii-operation -M 0x1F 0x4AB2 \n" );
			}
			break;

		case 'D':
			if ((optind+1) == argc) //选项带了一个参数
			{
				opt_reg_display++;
				opt_reg_index=strtoul(argv[2],NULL,16);
				temp=mii_readl(skfd, opt_reg_index);//将值写入寄存器
				printf("Reg index 0x%X,data is 0x%X now.\n",opt_reg_index,temp);
				opt_reg_modify = 0;
			}
			else
			{
				printf("the form you input is wrong\n");
				printf("Example:\n show phy reg(0x1f) value\n mii-operation -D 0x1f \n" );
			}
			break;

		case '?':
			fprintf(stderr, usage, argv[0]);
			break;
	}
	close(skfd);
	return ret;
}
