#ifdef HI_MINIBOOT_SUPPORT
#include "app.h"
#endif
#include "ir.h"
#include "ir_protocol.h"
#include "ir_utils.h"

#ifdef HI_MINIBOOT_SUPPORT
#include "errno.h"
#endif


#define RSTEP_NBITS       18
#define CHECK_RSTEPX_NBITS    8
#define RSTEP_UNIT        315 /* us */
#define RSTEP_HEADER_PULSE    (2 * RSTEP_UNIT)

#define RSTEP_BIT_START       (1 * RSTEP_UNIT)
#define RSTEP_BIT_END     (1 * RSTEP_UNIT)

enum RSTEP_STATE {
    STATE_INACTIVE,     //0
    STATE_BIT_START,    //1
    STATE_BIT_END,      //2
    STATE_CHECK_RSTEPX,   //3
    STATE_FINISHED,     //4
};

struct rstep_ir {
    enum RSTEP_STATE state;
    unsigned long long bits;
    unsigned long long scancode;
    int count;
    struct key_attr this_key;
    struct key_attr last_key;
    int has_last_key;
    struct ir_signal prev_signal;
};

extern u32 g_bTimeOutFlag;

static struct rstep_ir rstep_data;
static unsigned long rstep_repeat_next_time;
static struct timer_list rstep_timer;
static void rstep_keyup_proc(unsigned long i)
{
    struct key_attr *last_key;
    extern struct ir_priv ir_local;

    last_key = &rstep_data.last_key;
    if ( rstep_data.has_last_key
            && last_key->key_stat != KEY_STAT_UP) {
        last_key->key_stat = KEY_STAT_UP;
        if (ir_local.key_up_event) {
            ir_insert_key_tail(ir_local.key_buf, last_key);
            wake_up_interruptible(&ir_local.read_wait);
        }
    }
}
void rstep_init(void)
{
    init_timer(&rstep_timer);
    rstep_timer.expires = 0;
    rstep_timer.data = (unsigned long)~0;
    rstep_timer.function = rstep_keyup_proc;
    memset(&rstep_data, 0, sizeof(struct rstep_ir));
}
void rstep_exit(void)
{
    del_timer(&rstep_timer);
}
static int ir_rstep_decode(struct rstep_ir *data, struct ir_signal signal, struct ir_protocol *ip)
{
    if (!geq_margin(signal.duration, RSTEP_UNIT, RSTEP_UNIT / 2))
        goto out;

again:
    hiir_debug("RSTEP decode started at state %i (%uus %s)\n",
            data->state, signal.duration, TO_STR(signal.pulse));

    if (!geq_margin(signal.duration, RSTEP_UNIT, RSTEP_UNIT / 2))
        return 0;

    switch (data->state) {

    case STATE_INACTIVE:
        if (!eq_margin(signal.duration, RSTEP_BIT_START, RSTEP_UNIT / 2) || (!signal.pulse))
            break;

        data->bits = 0;
        data->count = 0;
        data->state = STATE_BIT_START;
        return 0;

    case STATE_BIT_START:
        if (!is_transition(&signal, &data->prev_signal))
            break;

        data->bits <<= 1;
        if (!signal.pulse)
            data->bits |= 1;
        data->count++;
        data->state = STATE_BIT_END;

        if (data->count == ip->attr.wanna_bits)
            goto again;

        if (geq_margin(signal.duration, 2*RSTEP_UNIT, RSTEP_UNIT / 2))
            data->state = STATE_BIT_START;

        return 0;

    case STATE_CHECK_RSTEPX:

    case STATE_BIT_END:
	hiir_debug("RSTEP decode date bit cnt=%d\n",data->count);
    if (data->count == ip->attr.wanna_bits) {

        data->scancode = data->bits;
        data->this_key.lower = data->scancode & 0x1ffff;
        data->this_key.upper = 0;

		data->count = 0;

        data->state = STATE_FINISHED;
    }
    else
    {
        data->state = STATE_BIT_START;
        decrease_duration(&signal, RSTEP_BIT_END);
    }

    goto again;

    case STATE_FINISHED:
        return 0;
    }

out:
    hiir_error("RSTEP decode failed at state %i (%uus %s), data->count:%d, key = 0x%.08llx\n",
               data->state, signal.duration, TO_STR(signal.pulse), data->count, data->scancode & 0x1ffff);
	data->count = 0;
    data->state = STATE_INACTIVE;
    return -EINVAL;
}

/* call condition:
 * if rstep_match return not match, this routine will be called.
 */
enum IR_MATCH_RESULT rstep_match_error_handle(enum IR_MATCH_TYPE type,struct ir_buffer *head,struct ir_protocol *ip)
{
    struct key_attr *symbol;
    int n, i;
    symbol = &head->buf[head->reader];
    if (!symbol->upper && !symbol->lower)
    {
        return IR_MATCH_NOT_MATCH;
    }
    switch (type) {
    case IR_MTT_HEADER:
         hiir_info("rstep, header matching. symbol[l,u]:[%d, %d],"\
            "header:[p, s, f]:[%d, %d, %d]\n",
            (u32)symbol->lower, (u32)symbol->upper,
            ip->attr.header.pluse, ip->attr.header.space,
            ip->attr.header.factor);

         if (data_fallin((u32)symbol->lower, (u32)ip->attr.header.minp,
                        (u32)ip->attr.header.maxp)
            && (data_fallin(symbol->upper, ip->attr.header.minp,
                            ip->attr.header.maxp)
                || data_fallin(symbol->upper, 2*RSTEP_UNIT * (100 - ip->attr.header.factor) / 100,
                               2*RSTEP_UNIT * (100 + ip->attr.header.factor) / 100)))
        {
            hiir_info("rstep, header matching: match!\n");
            return IR_MATCH_MATCH;
        }
        hiir_info("rstep, header matching: header mismatch!\n");
        break;
    case IR_MTT_FRAME:
        hiir_debug("rstep, frame matching. symbol[l,u]:[%d, %d],"\
            "header:[p, s, f]:[%d, %d, %d]\n",
            (u32)symbol->lower, (u32)symbol->upper,
            ip->attr.header.pluse, ip->attr.header.space,
            ip->attr.header.factor);

       if (!data_fallin(symbol->lower, ip->attr.header.minp,
                         ip->attr.header.maxp)

            || (!data_fallin(symbol->upper, ip->attr.header.minp,
                             ip->attr.header.maxp)
                && !data_fallin(symbol->upper, 2*RSTEP_UNIT * (100 - ip->attr.header.factor) / 100,
                                2*RSTEP_UNIT * (100 + ip->attr.header.factor) / 100)))
        {
            hiir_info("rstep, frame matching: header not match!\n");
            return IR_MATCH_NOT_MATCH;
        }
        hiir_info("rstep, frame matching, header match at:%d, [l, u]:[%d, %d]\n",
            head->reader, (u32)symbol->lower, (u32)symbol->upper);
                /* try find burst. */
		for (i = head->reader + 1, n = 1; n < MAX_DATA_BITS; n++, i++) {
            if (i >= MAX_SYMBOL_NUM)
                i -= MAX_SYMBOL_NUM;
            symbol = &head->buf[i];
            if (!symbol->upper && !symbol->lower) {
                hiir_debug("%s->%d, needs more data\n",
                        __func__,__LINE__);
                return IR_MATCH_NEED_MORE_DATA;
            }
            hiir_debug("rstep, frame matching. symbol[l,u]:[%d, %d] at %d,"\
                    "burst:[p, s, f]:[%d, %d, %d]\n",
                    (u32)symbol->lower, (u32)symbol->upper, i,
                    ip->attr.burst.pluse, ip->attr.burst.space,
                    ip->attr.burst.factor);
            /* ignore lower symbol. */
            if (symbol->upper > ip->attr.burst.maxs
                    || data_fallin(symbol->upper,
                        ip->attr.burst.mins,
                        ip->attr.burst.maxs)) {
                hiir_debug("rstep, frame matching: burst match at %d. symbol[l,u]:[%d, %d],"\
                    "burst:[p, s, f]:[%d, %d, %d]\n", i,
                    (u32)symbol->lower, (u32)symbol->upper,
                    ip->attr.burst.pluse, ip->attr.burst.space,
                    ip->attr.burst.factor);
                if (n >= ip->attr.burst_offset)
                    n = n - ip->attr.burst_offset;
                else
                    n = ip->attr.burst_offset - n;
                if (n <= RSTEP_BURST_OFFSET) {
                    hiir_debug(KERN_DEBUG"%s->%d, rstep frame err matching :"\
                            " burst at %d, (n=%d), frame match!\n",
                            __func__,__LINE__,i, n);
                    return IR_MATCH_MATCH;
                } else {
                    hiir_info(KERN_DEBUG "%s->%d, rstep frame err matching :"\
                            " burst at %d,(n=%d), frame not match!\n",
                            __func__,__LINE__,i,n);
                    return IR_MATCH_NOT_MATCH;
                }
            }
        }

        hiir_debug("%s->%d, burst not found!\n", __func__,__LINE__);
        break;
    case IR_MTT_BURST:
        break;
    }
    return IR_MATCH_NOT_MATCH;
}
/* call condition:
 * if parse_rstep returns !0, this routine can be called.
 */
void rstep_parse_error_handle(struct ir_priv *ir,
        struct ir_protocol *ip, struct ir_buffer *symb_head,
        struct ir_buffer *key_head)
{
    struct key_attr *symbol;

    symbol = &symb_head->buf[symb_head->reader];
    while ((symbol->upper || symbol->lower)) {
        /* clear symbols till burst appears. */
        hiir_debug("%s->%d, process symbol:[l,u] at %d:[%d, %d]\n",
                __func__,__LINE__,symb_head->reader,
                (u32)symbol->lower,(u32)symbol->upper);
        if (symbol->upper > ip->attr.burst.maxs
                || data_fallin(symbol->upper,
                    ip->attr.burst.mins,
                    ip->attr.burst.maxs)) {
            (HI_VOID)ir_next_reader_clr_inc(symb_head);
            break;
        }
        symbol = ir_next_reader_clr_inc(symb_head);
    }
}

enum IR_MATCH_RESULT rstep_match(enum IR_MATCH_TYPE type,
        struct ir_buffer *head, struct ir_protocol *ip)
{
    struct key_attr *symbol;
    int n;
    symbol = &head->buf[head->reader];
    if (!symbol->upper && !symbol->lower)
        return IR_MATCH_NOT_MATCH;
    switch (type) {
    case IR_MTT_HEADER:
        hiir_info("rstep, header matching. symbol[l,u]:[%d, %d],"\
            "header:[p, s, f]:[%d, %d, %d]\n",
            (u32)symbol->lower, (u32)symbol->upper,
            ip->attr.header.pluse, ip->attr.header.space,
            ip->attr.header.factor);

         if (data_fallin((u32)symbol->lower, (u32)ip->attr.header.minp,
                        (u32)ip->attr.header.maxp)
            && (data_fallin(symbol->upper, ip->attr.header.minp,
                            ip->attr.header.maxp)
                || data_fallin(symbol->upper, 2*RSTEP_UNIT * (100 - ip->attr.header.factor) / 100,
                               2*RSTEP_UNIT * (100 + ip->attr.header.factor) / 100)))
        {
            hiir_info("rstep, header matching: match!\n");
            return IR_MATCH_MATCH;
        }
        hiir_info("rstep, header matching: header mismatch!\n");
        break;
    case IR_MTT_FRAME:
        hiir_info("rstep, frame matching. symbol[l,u]:[%d, %d],"\
            "header:[p, s, f]:[%d, %d, %d]\n",
            (u32)symbol->lower, (u32)symbol->upper,
            ip->attr.header.pluse, ip->attr.header.space,
            ip->attr.header.factor);

         if (!data_fallin(symbol->lower, ip->attr.header.minp,
                         ip->attr.header.maxp)

            || (!data_fallin(symbol->upper, ip->attr.header.minp,
                             ip->attr.header.maxp)
                && !data_fallin(symbol->upper, 2*RSTEP_UNIT * (100 - ip->attr.header.factor) / 100,
                                2*RSTEP_UNIT * (100 + ip->attr.header.factor) / 100)))
        {
            hiir_info("rstep, header matching: not match!\n");
            return IR_MATCH_NOT_MATCH;
        }
        hiir_info("rstep, frame matching, header match at:%d, [l, u]:[%d, %d]\n",
            head->reader, (u32)symbol->lower, (u32)symbol->upper);
        /* try find burst. */
        n = head->reader + ip->attr.burst_offset + 1;
        if (n >= MAX_SYMBOL_NUM)
            n -= MAX_SYMBOL_NUM;
        symbol = &head->buf[n];
        /* ignore lower symbol. */
        if (symbol->upper > ip->attr.burst.maxs
            || data_fallin(symbol->upper,
                ip->attr.burst.mins,
                ip->attr.burst.maxs)) {
            hiir_info("rstep, frame matching: burst match at %d."\
                " symbol[l,u]:[%d, %d],"\
                "burst:[p, s, f]:[%d, %d, %d]\n", head->reader,
                (u32)symbol->lower, (u32)symbol->upper,
                ip->attr.burst.pluse, ip->attr.burst.space,
                ip->attr.burst.factor);

            return IR_MATCH_MATCH;
        }
        hiir_info("%s->%d, burst not found!\n", __func__,__LINE__);
        break;
    case IR_MTT_BURST:
        break;
    }
    return IR_MATCH_NOT_MATCH;
}

int parse_rstep(struct ir_priv *ir, struct ir_protocol *ip,
        struct ir_buffer *rd, struct ir_buffer *wr)
{
    struct ir_signal ir_pulse, ir_space;
    struct rstep_ir *rstep;
    struct key_attr *symbol;
    int ret, i, fail, cnt = 0;

    rstep = &rstep_data;
    symbol = &rd->buf[rd->reader];
    fail = i = 0;
    rstep->state = STATE_INACTIVE;
    while (symbol && symbol->lower && symbol->upper && !fail) {
        hiir_debug("%s->%d, parse symbol [l, u]:[%d, %d] at %d,\n"\
             __func__, __LINE__,(u32)symbol->lower, (u32)symbol->upper,
                rd->reader);

        ir_pulse.duration = symbol->lower;
        ir_pulse.pulse = 1;
        ret = ir_rstep_decode(rstep, ir_pulse, ip);
        if (ret)
            fail = 1;

        rstep->prev_signal = ir_pulse;
        ir_space.duration = symbol->upper;
        ir_space.pulse = 0;
        ret = ir_rstep_decode(rstep, ir_space, ip);
        if (ret)
            fail = 1;
        rstep->prev_signal = ir_space;
        symbol = ir_next_reader_clr_inc(rd);
		hiir_debug("rstep->state=%d\n",rstep->state);
        if (rstep->state == STATE_FINISHED)
        {
            break;
        }
    }
    if (fail) {
        hiir_error("Errors occured while decod rstep frame,"\
                " discard this frame!\n");
        return -1;
    }

	rstep->count=0;
    memcpy(rstep->this_key.protocol_name, ip->ir_code_name, PROTOCOL_NAME_SZ);
    del_timer(&rstep_timer);
    /* if a repeat key. */
    if (rstep->has_last_key
        && (rstep->this_key.lower == rstep->last_key.lower
            && rstep->this_key.upper == rstep->last_key.upper)
        && rstep->last_key.key_stat != KEY_STAT_UP) {

        if (ir->key_repeat_event
                && time_after(jiffies,
                    rstep_repeat_next_time)) {
            rstep->last_key.key_stat = KEY_STAT_HOLD;
            ir_insert_key_tail(wr, &rstep->last_key);
            rstep_repeat_next_time = jiffies +
                msecs_to_jiffies(ir->key_repeat_interval);
            cnt ++;
        }
        goto out;
    }
    /* if a new key recevied, send a key up event of last key. */
    if (rstep->has_last_key
        && rstep->last_key.key_stat != KEY_STAT_UP
        && (rstep->last_key.lower != rstep->this_key.lower
            || rstep->last_key.upper != rstep->this_key.upper)) {
        if (ir->key_up_event) {
            rstep->last_key.key_stat = KEY_STAT_UP;
            ir_insert_key_tail(wr, &rstep->last_key);
            cnt ++;
        }
    }
    /* the new key */
    rstep->this_key.key_stat = KEY_STAT_DOWN;
    ir_insert_key_tail(wr, &rstep->this_key);
    cnt ++;
    rstep_repeat_next_time = jiffies +
        msecs_to_jiffies(ir->key_repeat_interval);
out:
    rstep->has_last_key = 1;
    memcpy(&rstep->last_key, &rstep->this_key, sizeof(struct key_attr));

    rstep_timer.expires = jiffies +
                                 msecs_to_jiffies(ir->key_hold_timeout_time);


    rstep_timer.data = ip->priv;
    add_timer(&rstep_timer);

    return cnt ? 0 : -1;
}


EXPORT_SYMBOL(rstep_match);
EXPORT_SYMBOL(parse_rstep);
EXPORT_SYMBOL(rstep_parse_error_handle);
EXPORT_SYMBOL(rstep_match_error_handle);
