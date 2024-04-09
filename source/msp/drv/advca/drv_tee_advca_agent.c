/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_advca_agent.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#include <linux/fs.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#ifdef CONFIG_OPTEE
#include <linux/tee_drv.h>
#else
#include "tee_client_constants.h"
#include "teek_ns_client.h"
#include "agent.h"
#include "mem.h"
#endif
#include "hi_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define ADVCA_AGENT_ID	0x2A13C812

typedef enum
{
    ADVCA_GET_KLAD_RESCOURE = 0x0,
    ADVCA_RELEASE_KLAD_RESCOURE = 0x1,
} advca_cmd_t;

struct advca_ctrl_t
{
    advca_cmd_t cmd;
    unsigned int time_out;
    unsigned int ret_code;
};

extern struct mutex sd_klad_mutex;
static struct timer_list  timer;

#ifdef CONFIG_OPTEE

void advca_agent_mutex_lock_timeout(unsigned long arg)
{
    printk("Warning: TEE klad get the sd_klad_mutex lock timeout!!!\n");
    mod_timer(&timer, jiffies + * ((unsigned long*)arg));
}
static int advca_ops(struct advca_ctrl_t* advca_ctrl)
{
    int ret = 0;
    mmb_addr_t addr;
    int iommu;

    if (!advca_ctrl)
    {
        HI_PRINT("parameters from tee is NULL!\n");
        return -1;
    }

    advca_ctrl->ret_code = 0;

    timer.function = advca_agent_mutex_lock_timeout;
    timer.data = (unsigned long)(&advca_ctrl->time_out);
    timer.expires = jiffies + advca_ctrl->time_out;

    switch (advca_ctrl->cmd)
    {

#if defined(CONFIG_ARCH_HI3798MV2X) && defined(CONFIG_TEE)
        case ADVCA_GET_KLAD_RESCOURE:
        {
            add_timer(&timer);
            mutex_lock(&sd_klad_mutex);
            del_timer_sync(&timer);
            ret = 0;
            break;
        }
        case ADVCA_RELEASE_KLAD_RESCOURE:
        {
            mutex_unlock(&sd_klad_mutex);
            advca_ctrl->ret_code = 0;
            ret = 0;
            break;
        }
#endif
        default :
        {
            HI_PRINT("%s error!\n", __func__);
            ret = -1;
            return ret;
        }
    }
    return ret;
}

static int advca_agent_run(void* priv, void* virt, unsigned int size)
{
    struct advca_ctrl_t* advca_ctrl = NULL;

    if (!virt || !size || size < sizeof(*advca_ctrl))
    {
        HI_PRINT("parameter from tee is null!\n");
        return -1;
    }
    advca_ctrl = (struct advca_ctrl_t*)virt;
    return advca_ops(advca_ctrl);
}


struct tee_agent_kernel_ops advca_agent_ops =
{
    .agent_name = "advca_agent",
    .agent_id = ADVCA_AGENT_ID,
    .mutex = __MUTEX_INITIALIZER(advca_agent_ops.mutex),
    .tee_agent_run = advca_agent_run,
};

int advca_agent_register(void)
{
    return tee_agent_kernel_register(&advca_agent_ops);
}

int advca_agent_unregister(void)
{
    return tee_agent_kernel_unregister(&advca_agent_ops);
}

#else
static int advca_agent_init(struct tee_agent_kernel_ops* agent_instance)
{
    return 0;
}

static int advca_agent_exit(struct tee_agent_kernel_ops* agent_instance)
{
    return 0;
}

static int advca_tee_agent_work(void* data)
{
    int ret = 0;
    int agent_station = 0;
    struct tee_agent_kernel_ops* agent_instance =
        (struct tee_agent_kernel_ops*)data;

    while (!kthread_should_stop())
    {
        ret = TC_NS_wait_event(agent_instance->agent_id);
        if (ret)
        {
            HI_PRINT("%s wait event fail\n", agent_instance->agent_name);
            break;
        }
        if (agent_instance->tee_agent_work)
        { agent_station = agent_instance->tee_agent_work(agent_instance); }
        else
        {
            HI_PRINT("%s stop, exit.\n", agent_instance->agent_name);
            break;
        }
        ret = TC_NS_send_event_response(agent_instance->agent_id);
        if (ret)
        {
            HI_PRINT("%s send event response fail\n", agent_instance->agent_name);
            break;
        }
    }
    return ret;
}

#define AGENT_BUFF_SIZE (4*1024)
static int advca_tee_agent_run(struct tee_agent_kernel_ops* agent_instance)
{
    TC_NS_Shared_MEM* shared_mem = NULL;
    TC_NS_DEV_File dev;
    int ret;

    /*1. Allocate agent buffer */
#ifdef CONFIG_TEE_VMX_ULTRA
    shared_mem = tc_mem_allocate(&dev, AGENT_BUFF_SIZE);
#else
    shared_mem = tc_mem_allocate(&dev, AGENT_BUFF_SIZE, true);
#endif
    if (IS_ERR(shared_mem))
    {
        HI_PRINT("allocate agent buffer fail\n");
        ret = PTR_ERR(shared_mem);
        goto out;
    }
    agent_instance->agent_buffer = shared_mem;

    /*2. Register agent buffer to TEE */
    ret = TC_NS_register_agent(&dev, agent_instance->agent_id, shared_mem);
    if (ret)
    {
        HI_PRINT("register agent buffer fail\n");
        ret = -1;
        goto out;
    }

    /*3. Creat thread to run agent */
    agent_instance->agent_thread
        = kthread_run(advca_tee_agent_work, (void*)agent_instance, "agent_%s", agent_instance->agent_name);
    if (IS_ERR(agent_instance->agent_thread))
    {
        HI_PRINT("kthread creat fail\n");
        ret = PTR_ERR(agent_instance->agent_thread);
        agent_instance->agent_thread = NULL;
        goto out;
    }
    return 0;

out:
    if (!IS_ERR_OR_NULL(shared_mem))
    { tc_mem_free(shared_mem); }
    if (!IS_ERR_OR_NULL(agent_instance->agent_thread))
    {
        kthread_stop(agent_instance->agent_thread);
        agent_instance->agent_thread = NULL;
    }

    return ret;
}

void advca_agent_mutex_lock_timeout(unsigned long arg)
{
    printk("Warning: TEE klad get the sd_klad_mutex lock timeout!!!\n");
    mod_timer(&timer, jiffies + * ((unsigned long*)arg));
}

static int advca_agent_work(struct tee_agent_kernel_ops* agent_instance)
{
    struct advca_ctrl_t* advca_ctrl = (struct advca_ctrl_t*)agent_instance->agent_buffer->kernel_addr;
    int ret = 0;

    if (!advca_ctrl)
    {
        HI_PRINT("%s :system err!\n", __func__);
        return -1;
    }

    advca_ctrl->ret_code = 0;

    timer.function = advca_agent_mutex_lock_timeout;
    timer.data = (unsigned long)(&advca_ctrl->time_out);
    timer.expires = jiffies + advca_ctrl->time_out;

    switch (advca_ctrl->cmd)
    {
#if defined(CONFIG_ARCH_HI3798MV2X) && defined(CONFIG_TEE)
        case ADVCA_GET_KLAD_RESCOURE:
        {
            add_timer(&timer);
            mutex_lock(&sd_klad_mutex);
            del_timer_sync(&timer);
            ret = 0;
            break;
        }
        case ADVCA_RELEASE_KLAD_RESCOURE:
        {
            mutex_unlock(&sd_klad_mutex);
            advca_ctrl->ret_code = 0;
            ret = 0;
            break;
        }
#endif
        default :
        {
            HI_PRINT("%s error!\n", __func__);
            ret = -1;
            return ret;
        }
    }

    return ret;
}

static int advca_tee_agent_init(struct tee_agent_kernel_ops* agent_instance)
{
    int ret;

    if ((NULL == agent_instance) || (agent_instance->agent_id == 0) ||
        (agent_instance->agent_name == NULL) ||
        (agent_instance->tee_agent_work == NULL))
    {
        HI_PRINT("agent is invalid\n");
        return -1;;
    }

    /* Initialize the agent */
    if (agent_instance->tee_agent_init)
    { ret = agent_instance->tee_agent_init(agent_instance); }
    else
    {
        HI_PRINT("tee_agent_init %s should not be null\n", agent_instance->agent_name);
        return -1;
    }

    if (ret)
    {
        HI_PRINT("tee_agent_init %s failed\n", agent_instance->agent_name);
        return -1;
    }

    /* Run the agent */
    if (agent_instance->tee_agent_run)
    { ret = agent_instance->tee_agent_run(agent_instance); }
    else
    {
        HI_PRINT("tee_agent_run %s should not be null\n", agent_instance->agent_name);
        return -1;
    }

    if (ret)
    {
        HI_PRINT("tee_agent_run %s failed\n", agent_instance->agent_name);
        if (agent_instance->tee_agent_exit)
        { agent_instance->tee_agent_exit(agent_instance); }
        return -1;;
    }

    return 0;

}

static int advca_agent_stop(struct tee_agent_kernel_ops* agent_instance)
{
    TC_NS_send_event_response(agent_instance->agent_id);

    if (TC_NS_wakeup_event(agent_instance->agent_id))
    {
        printk("failed to wake up event %d\n", agent_instance->agent_id);
    }

    if (TC_NS_unregister_agent(agent_instance->agent_id))
    {
        printk("failed to unregister agent %d\n", agent_instance->agent_id);
    }

    if (!IS_ERR_OR_NULL(agent_instance->agent_thread))
    {
        kthread_stop(agent_instance->agent_thread);
    }

    if (!IS_ERR_OR_NULL(agent_instance->agent_buffer))
    {
        tc_mem_free(agent_instance->agent_buffer);
    }
    return 0;
}

static struct tee_agent_kernel_ops advca_agent_ops =
{
    .agent_name = "advca_agent",
    .agent_id = ADVCA_AGENT_ID,
    .tee_agent_init = advca_agent_init,
    .tee_agent_run = advca_tee_agent_run,
    .tee_agent_work = advca_agent_work,
    .tee_agent_exit = advca_agent_exit,
    .tee_agent_stop = advca_agent_stop,
    .list = LIST_HEAD_INIT(advca_agent_ops.list)
};

int advca_agent_register(void)
{
    tee_agent_kernel_register(&advca_agent_ops);
    advca_tee_agent_init(&advca_agent_ops);

    return 0;
}

int advca_agent_unregister(void)
{
    int ret = 0;
    struct tee_agent_kernel_ops* agent_instance = &advca_agent_ops;

    if (agent_instance->tee_agent_exit)
    {
        ret = agent_instance->tee_agent_exit(agent_instance);
    }
    else
    {
        HI_PRINT("tee_agent_init %s should not be null\n", agent_instance->agent_name);
        return -1;
    }
    if (agent_instance->tee_agent_work)
    { agent_instance->tee_agent_work = NULL; }

    if (agent_instance->tee_agent_stop)
    { agent_instance->tee_agent_stop(agent_instance); }

    return 0;

}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
