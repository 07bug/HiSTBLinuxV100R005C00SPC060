/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <boot.h>
#include <compile.h>
#include <module.h>
#include <delay.h>
#include <stdio.h>
#include <cpu-arch.h>

void reboot(void)
{
	printf("system reboot\n");
	mdelay(100);
	modules_reboot();
	reset_cpu(0);
}

#ifdef CONFIG_SYS_SRST_SUPPORT
void sreset(void)
{
	printf("sys soft resetting ...\n");
	mdelay(100);
	modules_reboot();
	reset_cpu(0);
}
#endif

