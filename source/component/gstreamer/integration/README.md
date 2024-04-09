# 简介
本文档描述插件式交付版本的特性清单及安装使用说明等


# 特性清单

## 支持平台
Hi3798CV200芯片, linux平台, gstreamer 1.10.2

## 已完成功能
### 支持视频格式
H.264 / H.265 / VP6 / VP8 / VC1 / AVS / MPEG1 / MPEG2 / MPEG4 / DIVX3
### 支持音频格式
AAC / MP3 / AC3,EAC3
### 支持的网络协议
HTTP/HLS/DASH
### 支持的文件格式
MP3、AVI、TS、MKV、MP4、MOV

## 运行方法
### gst-examples
使用gst-play可以完成基本的播放seek, pause-resume功能
### gst-validate
默认的27个场景可以运行, 部分出现failed(对于ubuntu gstreamer版本也是failed), 部分出现coredump(对于ubuntu gstreamer版本也coredump), 部分出现卡住现象, 对比某些场景ubuntu上也卡住有些没卡住, 有差异的场景主要和下面列出的已知问题2相关.
### gst-lunch
可以运行

## 已知问题:
1. DASH播放分辨率切换时还有问题, 还未定位, 其他分辨率切换功能正常.
2. 部分AVI, TS格式demux出来的pts不正常, 而我们现在解码器处理pts还未兼容, 导致出现不同步现象以及gst-validate卡住问题.
3. trick-mode还不支持


# 安装使用
以下描述交付软件包的编译安装及使用说明

## 前置条件
1. 编译服务器上已经配置部署海思基础镜像编译环境并编译通过
2. 烧录好镜像的Hi3798CV200单板

## 步骤
### 1. 编译
```
# 创建SDK路径软连接; SDK_DIR=../../HiSTBLinux.Hi3798CV200/
ln -s $SDK_DIR HiSTBLinux
rm -rf out/*

source HiSTBLinux/code/env.sh
source build/sme/envsetup.sh build/sme/project/histb.linux/hi3798cv200.plugin_only.cfg.mk dbg
sm
```
### 2. 安装
将out/histb.linux.hi3798cv200.plugin_only/dbg/目录下的bin/推到单板的/usr/bin/目录, config/scenarios目录推送到单板/data目录, lib/推到单板的/usr/lib目录(先删除下单板上的/usr/lib/gstplugins目录)
```
rm -rf /usr/lib/gstplugins/
```
### 3. 运行
#### gst-launch
gst-launch用法与gstreamer官方用法一致, 可以参考以下链接: https://gstreamer.freedesktop.org/documentation/tools/gst-launch.html
基本用法如下,提供基本播放功能
```
export GST_PLUGIN_PATH=/usr/lib/gstplugins/
gst-launch-1.0 --gst-disable-registry-fork playbin flags=0x67 uri=file:///mnt/dump/movie/audio/aac.mp4
```
#### gst-validate
gst-validate用法与gstreamer官方用法一致, 可以参考以下链接: https://gstreamer.freedesktop.org/data/doc/gstreamer/head/gst-validate/html/gst-validate.html
基本用法如下,提供基本验证gstreamer相应播放场景功能,可以自己添加测试场景, 官方自带默认场景在/data/scenarios目录下
```
export GST_PLUGIN_PATH=/usr/lib/gstplugins/
export GST_VALIDATE_SCENARIOS_PATH=/data/scenarios
gst-validate-1.0  playbin uri=file:///mnt/dump/movie/audio/mp3.mp3 --set-scenario simple_seeks
```
### gst-play
gst-play为gst-example中编译出的测试程序, 提供基本的播放, seek以及暂停恢复功能
```
export GST_PLUGIN_PATH=/usr/lib/gstplugins/
gst-play http://192.168.1.1/1.mp4
#播放起来以后可以按方向左右键进行前进后退操作, 按空格键进行暂停恢复操作, 按q退出.
```


# 其它说明
- 源码目录中*source/sme/source/plugins/gst-plugins-hisilicon-1.10.2*以及*source/sme/thirdparty/patches/gst-omx-1.10.2/*为核心交付件, 包含音视频OMX硬解及音视频hal输出插件. 因为公司安全编码规范要求, 引入了安全函数库, 在*platform/libhwsecurec*下,去除源码只保留头文件及二进制so.
- 其它包含gst-core, gst-plugin-base,gst-plugin-good,gst-plugin-bad等gstreamer社区开源包以及其在Hi3798CV200 linux平台上的编译脚本等,其中thirdparty/sme目录底下的开源源码包可以通过执行./clean.sh清除, 通过执行./download.sh重新从各开源包网站下载.
- 如交付客户对gstreamer比较熟悉,只需使用海思芯片平台上的解码和输出插件, 则只需使用gst-plugins-hisilicon-1.10.2源码即可, 编译方式与gst-plugin-good等包方式类似./confifure xxx; make即可, 具体参数可参考source/sme/source/plugins/pkg_gst_hisi.mk中configure调用. 如不希望引入华为安全函数库, 需要修改源码文件, 替换安全函数库为标准函数(memcpy等).
