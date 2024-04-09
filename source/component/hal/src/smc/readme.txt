TVOS2_V1.x
|-- Android.mk
|-- test
|   |-- CUnit
|   |   |-- Android.mk
|   |   |-- include //(CUnit 头文件 不需关注)
|   |   |
|   |   |-- lib     //(CUnit 库 不需关注)
|   |   |-- main.c  //(不需关注)
|   |   |-- tvos_hal_frontend_testcace.c //(frontend ST测试程序 Cunit)
|   |   `-- tvos_hal_smc_testcase.c      //(smc      ST测试程序 Cunit)
|   |-- sample_frontend
|   |   |-- Android.mk
|   |   `-- test_tvos_hal_frontend.c      //(frontend sample)
|   `-- sample_smc
|       |-- Android.mk
|       `-- test_tvos_hal_smc.c           //(smc      sample)
|-- tvos_hal_aout.h
|-- tvos_hal_av.h
|-- tvos_hal_caption.h
|-- tvos_hal_dmx.h
|-- tvos_hal_enc.h
|-- tvos_hal_errno.h
|-- tvos_hal_frontend.c             //(frontend 模块源码)
|-- tvos_hal_frontend.h
|-- tvos_hal_smc.c                  //(smc      模块源码)
|-- tvos_hal_smc.h
|-- tvos_hal_source.h
|-- tvos_hal_system.h
|-- tvos_hal_type.h
`-- tvos_hal_vout.h