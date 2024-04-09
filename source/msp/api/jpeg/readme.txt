（1）目录结构
     jpeg-hal|
             |--->inc_hard 硬件解码实现使用的头文件
             |
             |--->src_hard 硬件解码实现，编译到hi_msp中
             |
             |--->src_soft 纯软件实现，编译到开源代码中，会被include到patch_*相关文件中
             |
             |--->src_comm ，(1) 包含在patch_include_files.c中，在Makefile.in中指定
                             (2) 编译到libhi_msp中，保证里面的实现都是静态函数的，不然会引起符号冲突


（2）声明：
     所有私有的接口实现都不要编译到libjpeg中，否则libjpeg被开源库替换之后会找不到符号的情况，也就是libjpeg和libhi_msp可以单独使用

（3）Makefile独立编译成libhi_jpeg库暂时没有使用，编译到libhi_msp中

（4）Android.bp独立编译成libhi_jpeg暂时也没有使用（根目录下Android.bp）中添加，编译到libhi_msp，现在使用的是Android.mk
