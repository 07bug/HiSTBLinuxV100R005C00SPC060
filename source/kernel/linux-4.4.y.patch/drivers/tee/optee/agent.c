#include <linux/tee_drv.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include "../tee_private.h"
#include "optee_private.h"

#define MAX_AGENT_NUM	128

struct tee_user_space_agent {
        struct tee_agent_kernel_ops ops;
        void *buf;
        unsigned int buf_len;
        int ret;
        struct list_head link;
        struct completion data_to_agent;
        struct completion data_from_agent;
};

static struct tee_agent_kernel_ops *optee_tee_agent[MAX_AGENT_NUM];

static DEFINE_MUTEX(agent_mutex);

static bool tee_kernel_ops_valid(struct tee_agent_kernel_ops *tee_ops)
{
	if (!tee_ops || !tee_ops->tee_agent_run || !tee_ops->agent_id
	    || !tee_ops->agent_name)
		return false;

	return true;
}

static void tee_kernel_agent_set_available(struct tee_agent_kernel_ops *ops,
					   bool avail)
{
	mutex_lock(&ops->mutex);
	ops->avail = avail;
	mutex_unlock(&ops->mutex);
}

static struct tee_agent_kernel_ops *tee_kernel_agent_from_id
				(unsigned int agent_id)
{
	int i;

	mutex_lock(&agent_mutex);
	for (i = 0; i < MAX_AGENT_NUM; i++)
		if (optee_tee_agent[i] &&
		   (agent_id == optee_tee_agent[i]->agent_id))
			break;

	if (i == MAX_AGENT_NUM) {
		mutex_unlock(&agent_mutex);
		return NULL;
	}
	mutex_unlock(&agent_mutex);

	return optee_tee_agent[i];
}

int tee_agent_kernel_register(struct tee_agent_kernel_ops *tee_ops)
{
	int i;

	if (!tee_kernel_ops_valid(tee_ops))
		return -EINVAL;

	if (tee_kernel_agent_from_id(tee_ops->agent_id)) {
		pr_err("agent :%x already registered\n", tee_ops->agent_id);
		return -EBUSY;
	}

	mutex_lock(&agent_mutex);
	for (i = 0; i < MAX_AGENT_NUM; i++) {
		if (!optee_tee_agent[i])
			break;
	}

	if (i == MAX_AGENT_NUM) {
		pr_err("Too many agent, the max num agent supported is \
							128!\n");
		mutex_unlock(&agent_mutex);
		return -ENOMEM;
	}

	optee_tee_agent[i] = tee_ops;

	mutex_unlock(&agent_mutex);

	tee_kernel_agent_set_available(optee_tee_agent[i], true);

	return 0;
}
EXPORT_SYMBOL(tee_agent_kernel_register);

int tee_agent_kernel_unregister(struct tee_agent_kernel_ops *tee_ops)
{
	int i;

	if (!tee_kernel_ops_valid(tee_ops))
		return -EINVAL;

	tee_kernel_agent_set_available(tee_ops, false);

	mutex_lock(&agent_mutex);
	for (i = 0; i < MAX_AGENT_NUM; i++)
		if (optee_tee_agent[i] &&
		   (tee_ops->agent_id == optee_tee_agent[i]->agent_id))
			break;

	if (i == MAX_AGENT_NUM) {
		pr_err("agent :%d is not registered\n", tee_ops->agent_id);
		mutex_unlock(&agent_mutex);
		return -EINVAL;
	}

	optee_tee_agent[i] = NULL;

	mutex_unlock(&agent_mutex);

	return 0;
}
EXPORT_SYMBOL(tee_agent_kernel_unregister);

int optee_tee_agent_cmd(unsigned int agent_id, void *virt, unsigned int size)
{
	int i, rc;

	/* virt and size must be both null or be both valid */
	if ((!virt && size)||(virt && !size)) {
		pr_err("invalid args virt:%p size:%d!\n", virt, size);
		return -EINVAL;
	}

	mutex_lock(&agent_mutex);
	for (i = 0; i < MAX_AGENT_NUM; i++)
		if (optee_tee_agent[i] &&
		   (agent_id == optee_tee_agent[i]->agent_id))
			break;

	if (i == MAX_AGENT_NUM) {
		pr_err("%s %d agent :%x is not find\n", __func__, __LINE__,
				agent_id);
		mutex_unlock(&agent_mutex);
		return -ENXIO;
	}

	mutex_unlock(&agent_mutex);

	mutex_lock(&optee_tee_agent[i]->mutex);

	if (!optee_tee_agent[i]->avail) {
		mutex_unlock(&optee_tee_agent[i]->mutex);
		return -ENXIO;
	}
	rc = optee_tee_agent[i]->tee_agent_run(optee_tee_agent[i]->agent_data,
					      virt, size);

	mutex_unlock(&optee_tee_agent[i]->mutex);

	return rc;
}

static void user_agent_init(struct tee_user_space_agent *agent)
{
	init_completion(&agent->data_to_agent);
	init_completion(&agent->data_from_agent);
	agent->ret = 0;
	agent->buf = NULL;
	agent->buf_len = 0;
}

static int user_agent_run(void *priv, void *buf,
			  unsigned int len)
{
	int rc;
	struct tee_user_space_agent *uagent =
		container_of(priv, struct tee_user_space_agent, ops);

	if (!uagent) {
		pr_err("agent :%p buf:%p len:%d\n", (void*)uagent, buf, len);
		return -EINVAL;
	}

	uagent->buf = buf;
	uagent->buf_len = len;
	complete(&uagent->data_to_agent);

	rc = wait_for_completion_interruptible(&uagent->data_from_agent);

	/* when the agent call is finished, reset the agent buf */
	if (rc)
		uagent->ret = rc;
	uagent->buf = NULL;
	uagent->buf_len = 0;

	return uagent->ret;
}

int optee_agent_register(struct tee_context *ctx, u32 agent_id)
{
	struct tee_user_space_agent *agent;
	struct optee_context_data *ctxdata = ctx->data;
	int rc;

	agent = kmalloc(sizeof(*agent), GFP_KERNEL);
	if (!agent)
		return -ENOMEM;

	user_agent_init(agent);
	agent->ops.agent_name = "user_agent";
	agent->ops.agent_id = agent_id;
	agent->ops.tee_agent_run = user_agent_run;
	agent->ops.agent_data = agent;
	mutex_init(&agent->ops.mutex);

	rc = tee_agent_kernel_register(&agent->ops);

	if (!rc) {
		mutex_lock(&ctxdata->mutex);
		list_add(&agent->link, &ctxdata->agent_list);
		mutex_unlock(&ctxdata->mutex);
	} else
		kfree(agent);

	return rc;
}

int optee_agent_unregister(struct tee_context *ctx, u32 agent_id)
{
	struct tee_user_space_agent *agent;
	struct tee_agent_kernel_ops *kagent;
	struct optee_context_data *ctxdata = ctx->data;

	kagent = tee_kernel_agent_from_id(agent_id);
	if (!kagent)
		return -ENXIO;
	agent =	container_of(kagent, struct tee_user_space_agent, ops);

	/* release the agent thread */
	agent->ret = -EINTR;
	complete(&agent->data_from_agent);

	if (tee_agent_kernel_unregister(&agent->ops))
		panic("unregister agent :%u failed\n", agent_id);

	mutex_lock(&ctxdata->mutex);
	list_del(&agent->link);
	mutex_unlock(&ctxdata->mutex);

	kfree(agent);

	return 0;
}

int optee_agent_recv(struct tee_context *ctx, u32 agent_id,
		     struct tee_ioctl_buf_data *ubuf)
{
	struct tee_user_space_agent *agent;
	struct tee_agent_kernel_ops *kagent;

	kagent = tee_kernel_agent_from_id(agent_id);
	if (!kagent)
		return -ENXIO;
	agent =	container_of(kagent, struct tee_user_space_agent, ops);

	if (wait_for_completion_interruptible(&agent->data_to_agent))
		return -ERESTARTSYS;

	if (ubuf->buf_len < agent->buf_len)
		return -ENOMEM;

	if (agent->buf && agent->buf_len && u64_to_user_ptr(ubuf->buf_ptr))
		if (copy_to_user(u64_to_user_ptr(ubuf->buf_ptr), agent->buf, agent->buf_len))
			return -EFAULT;
	ubuf->buf_len = agent->buf_len;

	return 0;
}

int optee_agent_send(struct tee_context *ctx, u32 agent_id,
		     struct tee_ioctl_buf_data *ubuf)
{
	struct tee_user_space_agent *agent;
	struct tee_agent_kernel_ops *kagent;
	int rc = 0;

	kagent = tee_kernel_agent_from_id(agent_id);
	if (!kagent)
		return -ENXIO;

	agent =	container_of(kagent, struct tee_user_space_agent, ops);

	if ((!agent->buf && agent->buf_len) ||
	    (agent->buf && !agent->buf_len )){
		rc = -EINVAL;
		goto out;
	}

	if (agent->buf_len < ubuf->buf_len) {
		rc = -ENOMEM;
		goto out;
	}
	if (agent->buf && u64_to_user_ptr(ubuf->buf_ptr) && ubuf->buf_len)
		if (copy_from_user(agent->buf, u64_to_user_ptr(ubuf->buf_ptr),
				   ubuf->buf_len)) {
			rc = -EFAULT;
			goto out;
		}
	agent->ret = rc;
	complete(&agent->data_from_agent);
out:
	return rc;
}

void optee_agent_release(struct tee_context *ctx)
{
	struct optee_context_data *ctxdata = ctx->data;
	struct tee_user_space_agent *agent, *agent_tmp;

	list_for_each_entry_safe(agent, agent_tmp, &ctxdata->agent_list, link)
		optee_agent_unregister(ctx, agent->ops.agent_id);
}
