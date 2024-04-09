在使用HAL之前，请务必仔细阅读此文档。
=========================================
编译-测试
=========================================
1，HAL目录位置
    头文件目录: device\hal

    实现文件目录：device\hisilicon\bigfish\sdk\hal

2.  如何运行
2.1 获取root权限
    在串口输入:
    su;

2.2 运行sample(具体参考各模块下的readme文档，如device/hisilicon/bigfish/sdk/hal/sample/aout/)
    以aout模块为例，
    cd system/bin
    ./sample_hal_aout

2.3 运行test(具体参考各模块下的readme文档，如device/hisilicon/bigfish/sdk/hal/test/aout/)
    cd system/bin
    ./test_hal_aout