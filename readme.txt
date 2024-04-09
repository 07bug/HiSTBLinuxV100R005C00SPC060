# Hi3798mv100 （Huawei ec6108v9 IPTV）Linux的编译 烧录 blog
本文记录了为华为机顶盒EC6108v9c（海思Hi3798mv100芯片）编译内核、烧录uboot以及刷入Ubuntu 22.04 rootfs的过程。
## 基本环境
目标板：IPTV退役的华为机顶盒EC6108v9c（ hisilicon Hi3798mv100 1G 8G emmc）
编译环境：Ubuntu 22.04
海思linux内核：HiSTBLinux 适用于hi3798mv100 mv200 
SDK: HiSTBLinuxV100R005C00SPC060

## 环境准备

```
https://github.com/zjkanjie/HiSTBLinuxV100R005C00SPC060
#切换到工作目录
cd HiSTBLinuxV100R005C00SPC060  #$SDK_path
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
具体烧录方案可以搜索hitool教程。

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

根目录下 hi3798mv100_defconfig 是我配置好的 hi3798mv100 芯片的 支持Docker 的配置 替换到 /source/kernel/linux-4.4.y.patch 编译即可!


rootfs_128m.ext  root根分区包
emmc_partitions.xml  刷机分区配置文件
如调整分区大小，需要重新生成bootargs.bin 和调整分区配置文件。
使用华为hi-tool,emmc烧录
