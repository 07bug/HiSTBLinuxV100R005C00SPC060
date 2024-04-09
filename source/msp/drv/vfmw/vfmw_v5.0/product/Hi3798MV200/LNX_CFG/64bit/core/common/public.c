#include "basedef.h"
#include "mem_manage.h"
#include "public.h"
#ifdef ENV_SOS_KERNEL
#include "vfmw_sos_kernel_osal.h"
#else
#include "vfmw_linux_kernel_osal.h"
#endif
#include "vfmw_osal_ext.h"

extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;

#ifdef ENV_ARMLINUX_KERNEL
#define  TRACE_MEM_SIZE     (16*1024*2)
#define  MAX_FUNC_NAME_LEN  (15)

/* Trace object */
typedef struct hiTRACE_OBJ_S
{
    SINT8    s8FuncName[MAX_FUNC_NAME_LEN + 1];
    SINT32   s32LineNum;
    SINT32   s32Data;
    UINT32   u32Time;
} TRACE_OBJ_S;

/* Traver */
typedef struct  hiTRACE_DESC_S
{
    /* ID */
    UINT32   u32ValidFlag[4];

    /* Base Addr */
    TRACE_OBJ_S  *pstTraceBaseObj;
    UADDR       s32TraceBasePhyAddr;

    /* Index */
    SINT32   s32MaxTraceNumMinus4;
    SINT32   s32CurrTraceNum;
} TRACE_DESC_S;


TRACE_DESC_S *s_pstTracer = 0;
UADDR  TracerPhyAddr = 0;

VOID  *g_fpLog    = NULL;
SINT32 g_LogEnable = 0;
SINT8  g_LogFileName[500];
#endif

UINT32 g_PrintEnable = DEFAULT_PRINT_ENABLE;    /* print control */
UINT32 g_PrintDevice = DEFAULT_PRINT_DEVICE;    /* print output device */
SINT8  g_TmpMsg[1024];                          /* print msg tmp space */

SINT32 g_TraceCtrl = 0xffffffff;                /* vfmw run state control */
SINT32 g_TraceBsPeriod = 200;                   /* bit stream print period */
SINT32 g_TraceFramePeriod = 0;                  /* frame info print period */
SINT32 g_TraceImgPeriod = 500;                  /* image info print period */
SINT32 g_TunnelLineNumber = 10;                 /* line number of tunnel mode */
SINT32 g_SecProcSelect = 0;                     /* secure proc control */

char *g_strDefine[] =
{
    "vdec_vdh",
    "vdec_vdh_safe",
    "vdec_vdh1",
    "vdec_vdh2",
    "vdec_scd",
    "vdec_scd_safe",
    "vdec_scd1",
    "VFMW_Chan_Ctx",
    "VFMW_Chan_Vdh",
    "VFMW_Chan_Scd",
    "VFMW_DspCtxMem",
    "RESERVE_1",
    "RESERVE_2",
    "mmu_vdh",
    "mmu_vdh_safe",
    "VFMW_Hal_%d",
    "VFMW_VP9Prob_%d",
    "VFMW_ScdMsg_%d",
    "%s/vfmw_raw_save_%d.dat",
    "%s/vfmw_seg_save_%d.dat",
    "%s/vfmw_yuv_save_%d.yuv",
    "%s/2d_0x%x.yuv",
    "%s/1d_0x%x.yuv",
    "%s/vfmw_metadata_save_%d.dat",
    "%s/vfmw_metadata_reorder_save_%d.dat",
    "%s/vfmw_el_save_%d.dat",
    "VFMW_Tracer",
    "VFMW_BigTile1d_YUV"
};

char *VFMW_GetString(VFMW_STRING_E enStringName)
{
    if (enStringName >= VFMW_STRING_BUTT)
    {
        dprint(PRN_FATAL, "___________invalid parm= %d ____________\n", enStringName);
        return "";
    }

    return g_strDefine[enStringName];
}

#ifdef ENV_ARMLINUX_KERNEL
#define VF0  0x1a2a3a4a
#define VF1  0x55657585
#define VF2  0x0f152f35
#define VF3  0x4a5f6a7f

SINT32 DBG_CreateTracer(VOID)
{
    SINT32 ret;
    MEM_RECORD_S MemRecord;

    if (s_pstTracer)
    {
        return DBG_OK;
    }

#ifdef HI_SMMU_SUPPORT
    MemRecord.eMode = MEM_MMU_MMU;
#endif

    ret = MEM_AllocMemBlock(VFMW_GetString(VFMW_STRING_TRACER), 0, TRACE_MEM_SIZE, &MemRecord, 0);
    if (ret != MEM_MAN_OK)
    {
        return DBG_ERR;
    }

    MEM_AddMemRecord(MemRecord.PhyAddr, MemRecord.VirAddr, MemRecord.Length);

    s_pstTracer = (TRACE_DESC_S *)MemRecord.VirAddr;
    TracerPhyAddr = MemRecord.PhyAddr;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet(MemRecord.VirAddr, 0, TRACE_MEM_SIZE);

    s_pstTracer->pstTraceBaseObj = (TRACE_OBJ_S *)(MemRecord.VirAddr + sizeof(TRACE_DESC_S));
    s_pstTracer->s32TraceBasePhyAddr = (MemRecord.PhyAddr + sizeof(TRACE_DESC_S));

    s_pstTracer->s32MaxTraceNumMinus4 = (MemRecord.Length - sizeof(TRACE_DESC_S)) / sizeof(TRACE_OBJ_S) - 4;
    s_pstTracer->s32CurrTraceNum = 0;

    s_pstTracer->u32ValidFlag[0] = VF0;
    s_pstTracer->u32ValidFlag[1] = VF1;
    s_pstTracer->u32ValidFlag[2] = VF2;
    s_pstTracer->u32ValidFlag[3] = VF3;

    dprint(PRN_DBG, "________________ mem_phy, trace_phy,trace_max = 0x%x, 0x%x,%d _________________\n", MemRecord.PhyAddr,
           (MemRecord.PhyAddr + sizeof(TRACE_DESC_S)), s_pstTracer->s32MaxTraceNumMinus4 );

    return DBG_OK;
}

VOID DBG_DestroyTracer(VOID)
{
    UADDR PhyAddr;

    if (s_pstTracer == NULL)
    {
        return;
    }

    PhyAddr = MEM_Vir2Phy((SINT8 *)s_pstTracer);

    MEM_ReleaseMemBlock(PhyAddr, (SINT8 *)s_pstTracer);

    dprint(PRN_DBG, "=============== destroy tracer: phy,vir = 0x%x,%p ===================\n", PhyAddr, s_pstTracer);
    s_pstTracer = NULL;

    return;
}

VOID DBG_AddTrace(SINT8 *pFuncName, SINT32 nLine, SINT32 Data)
{
    SINT32 s32CurrTraceNum;
    TRACE_OBJ_S *pstTraceObj;

    if (s_pstTracer == NULL)
    {
        return;
    }

    s32CurrTraceNum = s_pstTracer->s32CurrTraceNum;

    s_pstTracer->s32CurrTraceNum = (s32CurrTraceNum < s_pstTracer->s32MaxTraceNumMinus4) ? (s32CurrTraceNum + 1) : 0;
    pstTraceObj = s_pstTracer->pstTraceBaseObj + s32CurrTraceNum;

    pstTraceObj->s32LineNum = nLine;
    pstTraceObj->s32Data = Data;

    pstTraceObj->u32Time = vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInUs();

    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy(pstTraceObj->s8FuncName, pFuncName, MAX_FUNC_NAME_LEN);

    return;
}

VOID DBG_PrintTracer(SINT32 TracerMemroy)
{
    SINT32 i;
    SINT32 s32CurrTraceNum;
    UINT32 *pv;
    TRACE_OBJ_S *pstTraceObj;
    TRACE_DESC_S *pstThisTracer;

    if (s_pstTracer == NULL)
    {
        pstThisTracer = (TRACE_DESC_S *)vfmw_Osal_Func_Ptr_S.pfun_Osal_ioremap(TracerMemroy, 1024 * 1024);
        if (pstThisTracer == NULL)
        {
            dprint(PRN_ALWS, "map vir address for '%x' failed!!!\n", TracerMemroy);
            return;
        }

        pstThisTracer->pstTraceBaseObj = (TRACE_OBJ_S *)((UINT8*)pstThisTracer + sizeof(TRACE_DESC_S));

        dprint(PRN_ALWS, "tracer memory '0x%x' is mapped to '%p'\n", TracerMemroy, pstThisTracer);
    }
    else
    {
        pstThisTracer = s_pstTracer;
    }

    if (pstThisTracer == NULL)
    {
        dprint(PRN_ALWS, "map vir address for '%x' failed!!!\n", TracerMemroy);
        return;
    }

    pv = &pstThisTracer->u32ValidFlag[0];

    if (pv[0] != VF0 || pv[1] != VF1 || pv[2] != VF2 || pv[3] != VF3)
    {
        dprint(PRN_ALWS, "no valid trace info stored in '%x'!!!\n", TracerMemroy);
        return;
    }

    dprint(PRN_ALWS, "====================== tracer context =====================\n");
    dprint(PRN_ALWS, "%-25s :%x\n", "pstTraceBaseObj", pstThisTracer->pstTraceBaseObj);
    dprint(PRN_ALWS, "%-25s :%p\n", "s32TraceBasePhyAddr", pstThisTracer->s32TraceBasePhyAddr);
    dprint(PRN_ALWS, "%-25s :%d\n", "s32MaxTraceNumMinus4", pstThisTracer->s32MaxTraceNumMinus4);
    dprint(PRN_ALWS, "%-25s :%d\n", "s32CurrTraceNum", pstThisTracer->s32CurrTraceNum);

    s32CurrTraceNum = pstThisTracer->s32CurrTraceNum;

    for (i = 0; i < pstThisTracer->s32MaxTraceNumMinus4; i++)
    {
        s32CurrTraceNum = (s32CurrTraceNum == 0) ? pstThisTracer->s32MaxTraceNumMinus4 : (s32CurrTraceNum - 1);
        pstTraceObj = pstThisTracer->pstTraceBaseObj + s32CurrTraceNum;

        dprint(PRN_ALWS, "-%05d-", i);
        dprint(PRN_ALWS, "func:%-15s;", pstTraceObj->s8FuncName);
        dprint(PRN_ALWS, " line:%5d;", pstTraceObj->s32LineNum);
        dprint(PRN_ALWS, " data:0x%08x(%-10d);", pstTraceObj->s32Data, pstTraceObj->s32Data);
        dprint(PRN_ALWS, " time:%u\n", pstTraceObj->u32Time);
    }

    if (s_pstTracer == NULL)
    {
        vfmw_Osal_Func_Ptr_S.pfun_Osal_iounmap(pstThisTracer);
    }

    return;
}
#endif

SINT32 IsDprintTypeEnable(UINT32 type)
{
    if ((PRN_ALWS != type) && (0 == (g_PrintEnable & (1 << type))))
    {
        return 0;
    }

    return 1;
}

VOID vfmw_dprint_nothing(VOID)
{
    return;
}

#ifdef ENV_ARMLINUX_KERNEL
SINT32 dprint_vfmw(UINT32 type, const SINT8 *format, ...)
{
    va_list args;
    SINT32 nTotalChar = 0;

    if (IsDprintTypeEnable(type) == 0)
    {
        return -1;
    }

    va_start(args, format);
    nTotalChar = vsnprintf(g_TmpMsg, sizeof(g_TmpMsg), format, args);
    va_end(args);

    if ((nTotalChar <= 0) || (nTotalChar >= 1023))
    {
        return -1;
    }

    if (DEV_SCREEN == g_PrintDevice)
    {
#ifndef  HI_ADVCA_FUNCTION_RELEASE
        return ( printk("N: %s", g_TmpMsg) );
#else
        return 0;
#endif
    }
    else
    {
        /*NOT support yet...*/
    }

    return -1;
}
#endif

SINT32 CHECK_REC_POS_ENABLE(SINT32 type)
{
    if ((g_TraceCtrl & (1 << type)) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

VOID RecordPOS(SINT32 SmID, VFMW_STATE_TYPE_E VfmwStateType, UINT32 *LastRecPosTimeInMs, SINT8 *FunctionName, SINT32 LineNumber)
{
    SINT32 data = 0;
    UINT32 CurTimeInMs = 0;

    if (CHECK_REC_POS_ENABLE(VfmwStateType))
    {
        CurTimeInMs = vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInMs();

        if ((CurTimeInMs - *LastRecPosTimeInMs) > g_TraceBsPeriod)
        {
            *LastRecPosTimeInMs = CurTimeInMs;
            data = (SmID << 24) + (VfmwStateType << 16);
            REC_POS_NEW(FunctionName, LineNumber, data);
        }
    }
}

SINT32 GetCompressRatio(SINT32 LossCompressEnable, SINT32 CompressRegCfg)
{
    SINT32 CompressRatio;

    if (!LossCompressEnable)
    {
        return COMPRESS_RATIO_LCM;
    }

    switch (CompressRegCfg)
    {
        case 0: /*0.5*/
            CompressRatio = COMPRESS_RATIO_0;
            break;

        case 1: /*0.625*/
            CompressRatio = COMPRESS_RATIO_1;
            break;

        case 2: /*0.75*/
            CompressRatio = COMPRESS_RATIO_2;
            break;

        case 3: /*0.875*/
            CompressRatio = COMPRESS_RATIO_3;
            break;

        default: /*1*/
            CompressRatio = COMPRESS_RATIO_LCM;
            break;
    }

    return CompressRatio;
}

/*************************************************************************/
/*                       �����㷨�벻Ҫ���׸Ķ�                          */
/*************************************************************************/
/* this parameter defines the cutoff between using quick sort and
   insertion sort for arrays; arrays with lengths shorter or equal to the
   below value use insertion sort */

/* �����������������ǣ������������ѭ����������СС��CUTOFF������ʱ����ʹ�ò���
   �������������������ͱ����˶�С���������ֶ������Ķ��⿪���������ȡֵ8����
   ���������Ժ��ܹ�ʱ���������㷨�ﵽ����CUTOFF��ֵ��*/
#define CUTOFF 8            /* testing shows that this is good value */

/* �������swap������
   ��������Ƚϼ򵥣����ǽ���������Ĳ�������������ָ����ʵ�ֵġ�*/
static void swap_kn(char *a, char *b, size_t width)
{
    char tmp;

    if (a != b)
    {
        /* Do the swap one character at a time to avoid potential alignment
           problems. */
        while (width--)
        {
            tmp = *a;
            *a++ = *b;
            *b++ = tmp;
        }
    }
}

/* Դ������������qsort�Ĵ��룬�����Ҿ����Ƚ�����qsortҪ���õĺ����Ĺ��ܱȽϺá�

    shortsort������
    ������������ã������Ѿ����ᵽ�����ǵ��Կ�������ݹ���õ�ʱ���������
��СС��CUTOFF�����飬�͵�������������������򣬶����Ǽ���������������һ��
�ݹ顣��Ϊ��Ȼ�����õ��ǻ������򷽷�����������ʱ���O(n^2)�ɱ��������������
ֻ��8��Ԫ�أ������ٶȱ���Ҫ�ݹ�Ŀ�������Ҫ��öࡣ���⣬��Դ�����ע���У�˵
����һ����������(insertion sort)�������Ҿ������Ӧ����һ��ѡ������Ŷ�
(selection sort)������Ϊʲô��ѡ����������ò�������Ӧ���Ǻ�ѡ�������Ԫ��
�����������й�ϵ��ֻ��ҪN-1�ν���������������ƽ����Ҫ(N^2)/2�Ρ�֮����Ҫѡ��
���������ٵ��㷨������Ϊ�п�����������ĵ���Ԫ�صĴ�С�ܴ�ʹ�ý�����Ϊ����
Ҫ������ƿ����
    ����˵����
       char *lo;      ָ��Ҫ�����������ĵ�һ��Ԫ�ص�ָ��
       char *hi;      ָ��Ҫ���������������һ��Ԫ�ص�ָ��
       size_t width;  �����е���Ԫ�صĴ�С
       int (__cdecl *comp)(const void *,const void *);   �����Ƚ�����Ԫ�ش�
С�ĺ���ָ�룬������������ڵ���qsort��ʱ����Ĳ�������ǰһ��ָ��ָ���Ԫ��
С�ں�һ��ʱ�����ظ����������ʱ������0��������ʱ������������*/
static void shortsort (char *lo, char *hi, size_t width,
                       int (*comp)(const void *, const void *))
{
    char *p, *max;

    /* Note: in assertions below, i and j are alway inside original bound of
       array to sort. */

    while (hi > lo)
    {
        /* A[i] <= A[j] for i <= j, j > hi */
        max = lo;

        /*�������forѭ�������Ǵ�lo��hi��Ԫ���У�ѡ������һ����maxָ��ָ����

        �������*/
        for (p = lo + width; p <= hi; p += width)
        {
            /* A[i] <= A[max] for lo <= i < p */
            if (comp(p, max) > 0)
            {
                max = p;
            }

            /* A[i] <= A[max] for lo <= i <= p */
        }

        /* A[i] <= A[max] for lo <= i <= hi */

        /*�����������hiָ������򽻻�*/
        swap_kn(max, hi, width);

        /* A[i] <= A[hi] for i <= hi, so A[i] <= A[j] for i <= j, j >= hi */

        /*hi��ǰ�ƶ�һ��ָ�롣������һ������hi��������Ѿ��ź���ı�δ���򲿷�

        ���е���Ҫ�������*/

        hi -= width;

        /* A[i] <= A[j] for i <= j, j > hi, loop top condition established */
    }

    /* A[i] <= A[j] for i <= j, j > lo, which implies A[i] <= A[j] for i < j,
       so array is sorted */
}

/*����������Ҫ�Ĳ��֣�qsort������*/
/*ʹ�õ��Ƿǵݹ鷽ʽ������������һ���Զ����ջʽ�ṹ���������������ջ�Ĵ�С*/
#define STKSIZ (8*sizeof(void*) - 2)

void qsort(void *base, UINT32 num, UINT32 width, int (*comp)(const void *, const void *))
{
    /* Note: the number of stack entries required is no more than
       1 + log2(num), so 30 is sufficient for any array */
    /*����ʹ����ĳЩ���ɣ�����ὲ������ʹ��ջ��С�����󲻻����1+log2(num)��
      ���30��ջ��СӦ�����㹻�ˡ�Ϊʲô˵��30�أ���ʵ������STKSIZ�Ķ����п��Լ����sizeof(void*)��4������8*4-2��30*/

    char *lo, *hi;              /* ends of sub-array currently sorting   �����������ָ�룬����ָ��������Ͻ���½�*/
    char *mid;                  /* points to middle of subarray  ������м���ָ��*/
    char *loguy, *higuy;        /* traveling pointers for partition step  ѭ���е��ζ�ָ��*/
    UINT32 size;                /* size of the sub-array  ����Ĵ�С*/
    char *lostk[STKSIZ], *histk[STKSIZ];
    int stkptr;                 /* stack for saving sub-array to be processed  ջ��ָ��*/

    /*���ֻ��һ�������µ�Ԫ�أ����˳�*/
    if (num < 2 || width == 0)
    {
        return;  /* nothing to do */
    }

    stkptr = 0;                 /* initialize stack */

    lo = base;
    hi = (char *)base + width * (num - 1);      /* initialize limits */

    /* this entry point is for pseudo-recursion calling: setting
       lo and hi and jumping to here is like recursion, but stkptr is
       preserved, locals aren't, so we preserve stuff on the stack */

    /*�����ǩ��α�ݹ�Ŀ�ʼ*/
recurse:

    size = (hi - lo) / width + 1;        /* number of el's to sort */

    /* below a certain size, it is faster to use a O(n^2) sorting method */

    /*��sizeС��CUTOFFʱ��ʹ��O(n2)�������㷨����*/
    if (size <= CUTOFF)
    {
        shortsort(lo, hi, width, comp);
    }
    else
    {
        /* First we pick a partitioning element.  The efficiency of the
           algorithm demands that we find one that is approximately the
           median of the values, but also that we select one fast.  We choose the
           median of the first, middle, and last elements, to avoid bad
           performance in the face of already sorted data, or data that is
           made up of multiple sorted runs appended together.  Testing shows that
           a median-of-three algorithm provides better performance than simply
           picking the middle element for the latter case. */

        /*��������Ҫѡ��һ��������㷨�ĸ�Ч��Ҫ�������ҵ�һ�����������м�ֵ
          ���������Ҫ��֤�ܹ��ܿ��ҵ���������ѡ������ĵ�һ��м�������һ�����
          ��ֵ�������������µĵ�Ч�ʡ����Ա�����ѡ�����������м�ֵ���ȵ���ѡ������
          ���м����Ч��Ҫ�ߡ�
              ���ǽ���һ��ΪʲôҪ�����������������⡣�������£����������㷨
          ������ʱ�临�Ӷ���O(n^2)�����������һ���������Ѿ�������ļ����������ѡ����
          ��һ������Ϊ�����Ҳ���������������е��������Ƿ����Ľ���Ƿֳ���һ����
          СΪN-1�������һ����СΪ1�����飬�����Ļ���������Ҫ�ıȽϴ�����N + N-1 + N-2
          + N-3 +...+2+1=(N+1)N/2=O(n^2)�������ѡ��ǰ �� �����������м�ֵ������������
          ����Ҳ�ܹ��õ��ܺõĴ���*/

        mid = lo + (size / 2) * width;      /* find middle element */

        /*��һ�� �м��� �����������Ԫ������*/

        /* Sort the first, middle, last elements into order */
        if (comp(lo, mid) > 0)
        {
            swap_kn(lo, mid, width);
        }

        if (comp(lo, hi) > 0)
        {
            swap_kn(lo, hi, width);
        }

        if (comp(mid, hi) > 0)
        {
            swap_kn(mid, hi, width);
        }

        /* We now wish to partition the array into three pieces, one
           consisting of elements <= partition element, one of elements equal to the
           partition element, and one of elements > than it.  This is done
           below; comments indicate conditions established at every step. */

        /*����Ҫ��������������飬һ����С�ڷ�����ģ�һ���ǵ��ڷ�����ģ�����һ���Ǵ��ڷ�����ġ�*/
        /*�����ʼ����loguy �� higuy����ָ�룬����ѭ���������ƶ���ָʾ��Ҫ����������Ԫ�صġ�higuy�ݼ���loguy���������������forѭ�����ǿ�����ֹ��*/

        loguy = lo;
        higuy = hi;

        /* Note that higuy decreases and loguy increases on every iteration,
           so loop must terminate. */
        for (;;)
        {
            /* lo <= loguy < hi, lo < higuy <= hi,
               A[i] <= A[mid] for lo <= i <= loguy,
               A[i] > A[mid] for higuy <= i < hi,
               A[hi] >= A[mid] */

            /* The doubled loop is to avoid calling comp(mid,mid), since some
               existing comparison funcs don't work when passed the same
               value for both pointers. */

            /*��ʼ�ƶ�loguyָ�룬ֱ��A[loguy]>A[mid]*/

            if (mid > loguy)
            {
                do
                {
                    loguy += width;
                }
                while (loguy < mid && comp(loguy, mid) <= 0);
            }

            /*����ƶ���loguy>=mid��ʱ�򣬾ͼ�������ƶ���ʹ��A[loguy]>a[mid]��
              ��һ��ʵ�������þ���ʹ���ƶ���loguy֮��loguyָ��֮ǰ��Ԫ�ض��ǲ����ڻ���ֵ��Ԫ�ء�*/
            if (mid <= loguy)
            {
                do
                {
                    loguy += width;
                }
                while (loguy <= hi && comp(loguy, mid) <= 0);
            }

            /* lo < loguy <= hi+1, A[i] <= A[mid] for lo <= i < loguy,
               either loguy > hi or A[loguy] > A[mid] */

            /*ִ�е������ʱ��lo<loguy<=hi+1��
              ������lo<=i<loguy����A[i]<=A[mid]��
              ����loguy>hi����������A[loguy]>A[mid]����
              Ҳ����˵��loguyָ��֮ǰ�����A[mid]ҪС���ߵ�����*/

            /*�����ƶ�higuyָ�룬ֱ��A[higuy]<��A[mid]*/
            do
            {
                higuy -= width;
            }
            while (higuy > mid && comp(higuy, mid) > 0);

            /* lo <= higuy < hi, A[i] > A[mid] for higuy < i < hi,
               either higuy == lo or A[higuy] <= A[mid] */

            /*�������ָ�뽻���ˣ����˳�ѭ����*/
            if (higuy < loguy)
            {
                break;
            }

            /* if loguy > hi or higuy == lo, then we would have exited, so
               A[loguy] > A[mid], A[higuy] <= A[mid],
               loguy <= hi, higuy > lo */

            /*���loguy>hi ����higuy==lo��������һ��break����Ѿ�������������
              ����������ˣ���ʱA[loguy]>A[mid],A[higuy]<=A[mid], loguy<=hi��higuy>lo��*/

            /*��������ָ��ָ���Ԫ��*/
            swap_kn(loguy, higuy, width);

            /* If the partition element was moved, follow it.  Only need
               to check for mid == higuy, since before the swap,
               A[loguy] > A[mid] implies loguy != mid. */

            /*�������Ԫ�ص�λ���ƶ��ˣ�����Ҫ��������
              ��Ϊ��ǰ���loguy���������ѭ���еĵڶ���ѭ���Ѿ���֤��loguy>mid,
              ��loguyָ�벻��midָ����ȡ���������ֻ��Ҫ��һ��higuyָ���Ƿ����midָ�룬
              ���ԭ����mid==higuy�����ˣ���ô�����ղŵĽ������м�ֵ���Ѿ�����
              loguyָ���λ�ã�ע�⣺�ղ���ֵ�����ˣ����ǲ�û�н���ָ�롣��higuy��mid��ȣ�
              ����higuy��loguyָ������ݣ�higuy��Ȼ����mid����������mid��loguy�����¸����м�ֵ��*/

            if (mid == higuy)
            { mid = loguy; }

            /* A[loguy] <= A[mid], A[higuy] > A[mid]; so condition at top
               of loop is re-established */

            /*���ѭ��һֱ���е�����ָ�뽻��Ϊֹ*/
        }

        /* A[i] <= A[mid] for lo <= i < loguy,
           A[i] > A[mid] for higuy < i < hi,
           A[hi] >= A[mid]
           higuy < loguy
       implying:
           higuy == loguy-1
           or higuy == hi - 1, loguy == hi + 1, A[hi] == A[mid] */

        /*��һ��ѭ������֮����Ϊ��û��ִ��loguyָ���higuyָ�����ݵĽ�����
          ����loguyָ���ǰ�������Ԫ�ض������ڻ���ֵ����higuyָ��֮�������Ԫ�ض����ڻ���ֵ�����Դ�ʱ�����������
          1)  higuy��loguy��1
          2)  higuy��hi��1��loguy��hi+1
          ���еڶ������������һ��ʼѡ������Ԫ�ص�ʱ��hiָ���Ԫ�غ�midָ���Ԫ��ֵ��ȣ�
          ��hiǰ���Ԫ��ȫ���������ڻ���ֵ��ʹ���ƶ�loguyָ���ʱ��һֱ�ƶ�����hi+1��ֹͣ��
          ���ƶ�higuyָ���ʱ��higuyָ���ƶ�һ����ֹͣ�ˣ�ͣ��hi��1����*/

        /* Find adjacent elements equal to the partition element.  The
           doubled loop is to avoid calling comp(mid,mid), since some
           existing comparison funcs don't work when passed the same value
           for both pointers. */
        higuy += width;

        if (mid < higuy)
        {
            do
            {
                higuy -= width;
            }
            while (higuy > mid && comp(higuy, mid) == 0);
        }

        if (mid >= higuy)
        {
            do
            {
                higuy -= width;
            }
            while (higuy > lo && comp(higuy, mid) == 0);
        }

        /* OK, now we have the following:
              higuy < loguy
              lo <= higuy <= hi
              A[i]  <= A[mid] for lo <= i <= higuy
              A[i]  == A[mid] for higuy < i < loguy
              A[i]  >  A[mid] for loguy <= i < hi
              A[hi] >= A[mid] */

        /*��������Ĵ���higuyָ���֮ǰ�Ķ���С�ڵ���A[mid]��������higuyָ��
          ��loguyָ��֮����ǵ���A[mid]��������loguyָ���֮����Ǵ���A[mid]������
          ʵ�������ǿ��Կ�����higuyָ��ǰ����Ȼ�����е���A[mid]������������������·����֮��
          ȷʵ�ܹ���һ���̶��������������Ĵ�С���Ż��˳����Ч�ʡ�*/

        /* We've finished the partition, now we want to sort the subarrays
           [lo, higuy] and [loguy, hi].
           We do the smaller one first to minimize stack usage.
           We only sort arrays of length 2 or more.*/

        /*���������Ѿ�����˷��������Կ�ʼ��������[lo,higuy]��[loguy,hi]������
          �����ȴ���С���Ǹ����У��������Ա���������ջ��С��N�ɱ����������
          ���ǿ�������һ�£�����һ���Ѿ���������飬���ÿ�ηֳ�N-1��1�����飬
          ��������ÿ�ζ��ȴ���N-1��һ�룬��ô���ǵĵݹ���Ⱦ��Ǻ�N�ɱ�����
          �������ڴ�N��ջ�ռ�Ŀ����Ǻܴ�ġ�����ȴ���1����һ�룬ջ�������ֻ��2�
          ������Ԫ�ظպ��������м�ʱ��ջ�ĳ�����logN������ջ�Ĳ����������ȰѴ��������Ϣ��ջ��*/

        if ( higuy - lo >= hi - loguy )
        {
            if (lo < higuy)
            {
                lostk[stkptr] = lo;
                histk[stkptr] = higuy;
                ++stkptr;
            }                           /* save big recursion for later */

            if (loguy < hi)
            {
                lo = loguy;
                goto recurse;           /* do small recursion */
            }
        }
        else
        {
            if (loguy < hi)
            {
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;               /* save big recursion for later */
            }

            if (lo < higuy)
            {
                hi = higuy;
                goto recurse;           /* do small recursion */
            }
        }
    }

    /* We have sorted the array, except for any pending sorts on the stack.
       Check if there are any, and do them. */

    /*��ջ������ֱ��ջΪ�գ��˳�ѭ��*/
    --stkptr;

    if (stkptr >= 0)
    {
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;           /* pop subarray from stack */
    }

    return;                     /* all subarrays done */
}
