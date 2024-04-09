# Hi3798mv100 （Huawei ec6108v9 IPTV）Linux的编译 烧录 blog
本文记录了为华为机顶盒EC6108v9c（海思Hi3798mv100芯片）编译内核、烧录uboot以及刷入Ubuntu 22.04 rootfs的过程。
## 基本环境
目标板：IPTV退役的华为机顶盒EC6108v9（ hisilicon Hi3798mv100 2G 8G emmc）
编译环境：Ubuntu 22.04
海思linux内核：HiSTBLinux 适用于hi3798mv100 mv200 
SDK: HiSTBLinuxV100R005C00SPC041B060

## 环境准备

```
git clone https://github.com/glinuz/hi3798mv100
#切换到工作目录
cd HiSTBLinuxV100R005C00SPC041B020  #$SDK_path
#安装需要的编译工具，可以使用SDK带的shell脚本，也可以自己安装
sh server_install.sh
#or
apt-get install gcc make gettext bison flex bc zlib1g-dev libncurses5-dev lzma
#拷贝SDK中预先定义的
cp configs/hi3798mv100/hi3798mdmo1g_hi3798mv100_cfg.mak ./cfg.mak

source ./env.sh  #SDK各种环境变量
#按需修改编译的配置
make menuconfig
make build -j4 2>&1  | tee -a buildlog.txt
```
制成功后，在out/hi3798mv100可以找到编译好的fastboot-burn.bin、bootargs.bin、hi_kernel.bin，分别是uboot引导文件、uboot引导参数配置和linux内核。
## 使用HiTool烧录到eMMC
TTL连接图见[hi3798mv100-ec6109.jpg]，具体烧录方案可以搜索hitool教程。

hitool烧录界面配置建[hit00l-burn.png]

eMMC分区为uboot 1M、bootargs 1M、kernel 8M、rootfs 128M，具体见[emmc_partitions.xml].

如果修改分区大小，调整分区大小，需同步修改bootargs.txt 和 emmc_partitions.xml。

configs/hi3798mv100/prebuilts/bootargs.txt，并重新生成bootargs.bin文件

```
bootcmd=mmc read 0 0x1FFFFC0 0x1000 0x4000;bootm 0x1FFFFC0
bootargs=console=ttyAMA0,115200 root=/dev/mmcblk0p4 rootfstype=ext4 rootwait blkdevparts=mmcblk0:1M(fastboot),1M(bootargs),8M(kernel),128M(rootfs),-(system)

mkbootargs  -s 1M -r bootargs.txt  -o bootargs.bin
```
bootcmd操作说明：从第0个mmc设备块上2M字节处开始（0x1000的十进制4096,4096*512/1024=2M），读取16×512个字节（0x4000的十进制16384*512/1024=8M）到内存0x1FFFFC0处，并从此处引导。

打开串口console，以便进行调试。console=ttyAMA0,115200
uboot启动过程输出如下：
```
Bootrom start
Boot from eMMC
Starting fastboot ...

System startup
DDRS
Reg Version:  v1.1.0
Reg Time:     2016/1/18  14:01:18
Reg Name:     hi3798mdmo1g_hi3798mv100_ddr3_1gbyte_16bitx2_4layers_emmc.reg

Jump to DDR


Fastboot 3.3.0 (root@glinuz) (Jul 25 2020 - 08:25:47)

Fastboot:      Version 3.3.0
Build Date:    Jul 25 2020, 08:26:41
CPU:           Hi3798Mv100 
Boot Media:    eMMC
DDR Size:      1GB


MMC/SD controller initialization.
MMC/SD Card:
    MID:         0x15
    Read Block:  512 Bytes
    Write Block: 512 Bytes
    Chip Size:   7456M Bytes (High Capacity)
    Name:        "8GME4R"
    Chip Type:   MMC
    Version:     5.1
    Speed:       52000000Hz
    Mode:        DDR50
    Bus Width:   8bit
    Boot Addr:   0 Bytes
Net:   upWarning: failed to set MAC address


Boot Env on eMMC
    Env Offset:          0x00100000
    Env Size:            0x00010000
    Env Range:           0x00010000
ID_WORD have already been locked


SDK Version: HiSTBLinuxV100R005C00SPC041B020_20161028

Reserve Memory
    Start Addr:          0x3FFFE000
    Bound Addr:          0x8D24000
    Free  Addr:          0x3F8FC000
    Alloc Block:  Addr         Size
                  0x3FBFD000   0x400000
                  0x3F8FC000   0x300000

Press Ctrl+C to stop autoboot

MMC read: dev # 0, block # 4096, count 16384 ... 16384 blocks read: OK

84937034 Bytes/s
## Booting kernel from Legacy Image at 01ffffc0 ...
   Image Name:   Linux-3.18.24_s40
   Image Type:   ARM Linux Kernel Image (uncompressed)
   Data Size:    6959232 Bytes = 6.6 MiB
   Load Address: 02000000
   Entry Point:  02000000
   Verifying Checksum ... OK
   XIP Kernel Image ... OK
OK
ATAGS [0x00000100 - 0x00000300], 512Bytes

Starting kernel ...
```
## 高级编译
### 自定义linux内核
ARM平台内核配置文件采用defconfig格式，正确使用和保存deconfig的流程如下：

source/kernel/linux-3.18.y/arch/arm/configs/hi3798mv100_defconfig 
cd source/kernel/linux-3.18.y/
可以使用本git库提供的hi3798mv100_defconfig-0812
1. 先备份hi3798mv100_defconfig
2. make ARCH=arm hi3798mv100_defconfig #从defconfig生成标准linux内核配置.config文件
3. make ARCH=arm menuconfig #修改内核配置，并保存
4. make ARCH=arm savedefconfig #重新生成defconfg文件
5. cp defconfig arch/arm/configs/hi3798mv100_defconfig  #复制defconfig文件到正确的位置。
6. make distclean #清理之前编译生产的文件
7. cd $SDK_path;make linux  #重新编译kernel

需关注的kernel编译参数 才能支持docker：

    打开devtmpfs,/dev 文件系统

    打开open by fhandle syscalls

    打开cgroup功能
    

## 刷机包-二进制文件
文件下载 release
fastboot-bin.bin  uboot分区包
bootargs.bin   uboot参数分区包
hi_kernel.bin  kernel分区包
rootfs_128m.ext  root根分区包
emmc_partitions.xml  刷机分区配置文件
如调整分区大小，需要重新生成bootargs.bin 和调整分区配置文件。
使用华为hi-tool,emmc烧录
