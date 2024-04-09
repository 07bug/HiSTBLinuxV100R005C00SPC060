#include <common_log.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
#define HITEST_MILLISECOND (1000) /*���� 1s=10^3ms(����)*/
#define HITEST_NANOSECOND (1000000000) /*���� 1s=10^9ns(����)*/

static HI_BOOL    s_bFaildflag = HI_FALSE;/*HI_TRUE:����ִ��ʧ��*/
static HI_U32 s_u32OkCount    = 0;
static HI_U32 s_u32FailCount  = 0;
static HI_U32 s_u32ErrorCount = 0;
struct timespec s_stTimeingOne, s_stTimeingTwo, s_stTimeingThree, s_stTimeingFour, s_stTimeingFive; /*��ʱ��ʼʱ��*/
static HITEST_LOG_LEVEL_E s_eLogLevel = HITEST_LOG_LEVEL_CLOSE; /*Log��ӡ����*/

/***********************************************************************************
* Function:      HITEST_OkPrint
* Description:   ok print
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         pFunc      ����HITEST_OkPrint��Դ����
*                s32Ret     ִ��pFunc�����ķ���ֵ
*                 s32Line    ִ��pFunc������Ӧ���к�
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_OkPrint(HI_CHAR* pFunc, HI_S32 s32Ret, HI_S32 s32Line)
{
    FILE* pOkFile = HI_NULL;
    pOkFile = fopen("ok_file", "wt");

    if (HI_NULL == pOkFile)
    {
        printf("open file fail ,line = %d\n", __LINE__);
        return ;
    }

    fprintf(pOkFile, "OK: ret = %x,%s,line = %d\n", s32Ret, pFunc, s32Line);
    printf("OK: ret = %x,%s,line = %d\n", s32Ret, pFunc, s32Line);

    s_u32OkCount++;
    fclose(pOkFile);
    return;
}

/***********************************************************************************
* Function:      HITEST_FailPrint
* Description:   fail print
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         pFunc      ����HITEST_FailPrint��Դ����
*                s32Ret     ִ��pFunc�����ķ���ֵ
*                 s32Line    ִ��pFunc������Ӧ���к�
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_FailPrint(HI_CHAR* pFunc, HI_S32 s32Ret, HI_S32 s32Line)
{
    FILE* pFailFile = HI_NULL;
    pFailFile = fopen("fail_file", "wt");

    if (HI_NULL == pFailFile)
    {
        printf("open file fail ,line = %d\n", __LINE__);
        return ;
    }

    fprintf(pFailFile, "FAIL: ret = %x,%s,line = %d\n", s32Ret, pFunc, s32Line);
    printf("FAIL: ret = %x,%s,line = %d\n", s32Ret, pFunc, s32Line);

    s_u32FailCount++;
    s_bFaildflag = HI_TRUE;
    fclose(pFailFile);
    return;
}

/***********************************************************************************
* Function:      HITEST_ErrorPrint
* Description:   fail print
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         pFunc      ����HITEST_ErrorPrint��Դ����
*                s32Ret     ִ��pFunc�����ķ���ֵ
*                 s32Line    ִ��pFunc������Ӧ���к�
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_ErrorPrint(HI_CHAR* pFunc, HI_S32 s32Ret, HI_S32 s32Line)
{
    FILE* pErrorfile = HI_NULL;
    pErrorfile = fopen("error_file", "at");

    if (HI_NULL == pErrorfile)
    {
        printf("open file fail ,line = %d\n", __LINE__);
        return ;
    }

    fprintf(pErrorfile, "ERROR: ret = %x,%s ,line = %d\n", s32Ret, pFunc, s32Line);
    printf("ERROR: ret = %x,%s ,line = %d\n", s32Ret, pFunc, s32Line);

    s_u32ErrorCount++;
    fclose(pErrorfile);
    return;
}

/***********************************************************************************
* Function:      HITEST_TimeStamps
* Description:   ����ִ��ʱ��ͳ��
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         s32TimerID ʱ��ͳ�ƶ�Ӧ��ID,��ϸ��Ӧ��ο�HITEST_TIMER_ORDER_E
*                eTimingFlg ��ʱ��ִ������,��ϸ��ο�HITEST_TIMING_E
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_TimeStamps(HITEST_TIMER_ORDER_E s32TimerID, HITEST_TIMING_E eTimingFlg)
{
    if (s32TimerID < HITEST_TIMER_ONE || s32TimerID > HITEST_TIMER_BUTT ||
        eTimingFlg < HITEST_TIMING_START || eTimingFlg > HITEST_TIMING_BUTT)
    {
        printf("%s,%d,input error,Timing fail\n", __FUNCTION__, __LINE__);
        return;
    }

    struct timespec stTimeingStart;

    memset(&stTimeingStart, 0, sizeof(stTimeingStart));

    clock_gettime(CLOCK_MONOTONIC, &stTimeingStart);

    if (eTimingFlg == HITEST_TIMING_START)
    {
        switch (s32TimerID)
        {
            case HITEST_TIMER_ONE:
                memcpy(&s_stTimeingOne, &stTimeingStart, sizeof(stTimeingStart));
                break;

            case HITEST_TIMER_TWO:
                memcpy(&s_stTimeingTwo, &stTimeingStart, sizeof(stTimeingStart));
                break;

            case HITEST_TIMER_THREE:
                memcpy(&s_stTimeingThree, &stTimeingStart, sizeof(stTimeingStart));
                break;

            case HITEST_TIMER_FOUR:
                memcpy(&s_stTimeingFour, &stTimeingStart, sizeof(stTimeingStart));
                break;

            case HITEST_TIMER_FIVE:
                memcpy(&s_stTimeingFive, &stTimeingStart, sizeof(stTimeingStart));
                break;

            default:
                break;
        }
    }
    else
    {
        struct timespec stTimeingBegin, stTimeingEnd, stTimeGap;
        memset(&stTimeingBegin, 0, sizeof(stTimeingBegin));
        memset(&stTimeingEnd, 0, sizeof(stTimeingEnd));
        clock_gettime(CLOCK_MONOTONIC, &stTimeingEnd);

        switch (s32TimerID)
        {
            case HITEST_TIMER_ONE:
                memcpy(&stTimeingBegin, &s_stTimeingOne, sizeof(s_stTimeingOne));
                break;

            case HITEST_TIMER_TWO:
                memcpy(&stTimeingBegin, &s_stTimeingTwo, sizeof(s_stTimeingTwo));
                break;

            case HITEST_TIMER_THREE:
                memcpy(&stTimeingBegin, &s_stTimeingThree, sizeof(s_stTimeingThree));
                break;

            case HITEST_TIMER_FOUR:
                memcpy(&stTimeingBegin, &s_stTimeingFour, sizeof(s_stTimeingFour));
                break;

            case HITEST_TIMER_FIVE:
                memcpy(&stTimeingBegin, &s_stTimeingFive, sizeof(s_stTimeingFive));
                break;

            default:
                break;
        }

        HI_U64 u64TimeDif = 0; /*��λ:����*/
        memset(&stTimeGap, 0, sizeof(stTimeGap));
        stTimeGap.tv_sec = stTimeingEnd.tv_sec - stTimeingBegin.tv_sec;
        stTimeGap.tv_nsec = stTimeingEnd.tv_nsec - stTimeingBegin.tv_nsec;

        if (stTimeGap.tv_nsec < 0)
        {
            stTimeGap.tv_sec--;
            stTimeGap.tv_nsec += HITEST_NANOSECOND;
        }

        u64TimeDif = (stTimeGap.tv_sec) + (stTimeGap.tv_nsec / HITEST_MILLISECOND / HITEST_MILLISECOND / HITEST_MILLISECOND);
        printf("%s,%d,DIF:%lld microseconds\n", __FUNCTION__, __LINE__, u64TimeDif * HITEST_MILLISECOND);
    }

    return;
}
/***********************************************************************************
* Function:      HITEST_FinalResult
* Description:   ��ʼ����Ԫ�������Խ����ʾ��
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         pFunc      ����HITEST_ErrorPrint��Դ����
*                 s32Line    ִ��pFunc������Ӧ���к�
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_InitResultFlag(HI_VOID)
{
    system("rm -f ok_file");
    system("rm -f error_file");
    s_bFaildflag = HI_FALSE;
    return;
}
/***********************************************************************************
* Function:      HITEST_GetResultFlag
* Description:   ��ʼ����Ԫ�������Խ����ʾ��
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         ��
* Output:        ��
* Return:        s_bFaildflag ��״̬
* Others:        ��
***********************************************************************************/
HI_BOOL HITEST_GetResultFlag(HI_VOID)
{
    return s_bFaildflag;
}

HI_VOID HITEST_SetResultFlag(HI_BOOL flag)
{
    s_bFaildflag = flag;
}

/***********************************************************************************
* Function:      HITEST_FinalResult
* Description:   print final result.
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         pFunc      ����HITEST_ErrorPrint��Դ����
*                 s32Line    ִ��pFunc������Ӧ���к�
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_FinalResult(HI_CHAR* pFunc, HI_S32 s32Line)
{
    if (s_bFaildflag == HI_SUCCESS)
    {
        HITEST_OkPrint(pFunc, HI_SUCCESS, s32Line);
    }
    else
    {
        HITEST_ErrorPrint(pFunc, HI_FAILURE, s32Line);
    }

    return;
}

/***********************************************************************************
* Function:      TEST_Entry
* Description:   ���Ȳ�������ִ��
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         argc       ����ģ���ִ���ļ���Ӧ����θ���
*                 argv       ����ģ���ִ���ļ���Ӧ������б�
*                HITEST_List ����ģ���Ӧ��case��Ϣ
*                s32ListLen  ����ģ���Ӧ��case����
* Output:        ��
* Return:        HI_FAILURE  ʧ��
*                HI_SUCCESS  �ɹ�
* Others:        ��
***********************************************************************************/
HI_S32 TEST_Entry(HI_S32 s32Argc, HI_CHAR* pArgv[], HITEST_FUNC_S stFunc[], HI_S32 s32ListLen)
{
    HI_S32 u32FunNum = 0;
    HI_S32 s32Len = s32ListLen;
    //TEEC_Result result;

    if (stFunc == HI_NULL || s32Len <= 0)
    {
        printf("HITEST_List is null\n");
        return HI_FAILURE;
    }

    if (s32Argc == 1)
    {
        while(stFunc[u32FunNum].hiTest_FUN_pfn != HI_NULL)
        {
            printf("####Run function %s,u32FuncNum=%d####\n", stFunc[u32FunNum].pFunName, u32FunNum + 1);
            //printf("is 0x%x\n",stFunc[u32FunNum].hiTest_FUN_pfn);
            stFunc[u32FunNum].hiTest_FUN_pfn();
            u32FunNum++;
            if (u32FunNum == s32Len)
                break;
        }
        return HI_SUCCESS;
    }
#if 1
    if (s32Argc == 1)
    {
        printf("Usage1 :%s 0<num<%d\n", pArgv[0], s32Len);
        printf("Usage2 :%s FunName\n", pArgv[0]);
        return HI_FAILURE;
    }

    /*����Ϊ����,��ڶ��������׸���ĸΪ���� "./abc  100"  */
    if ( pArgv[1][0] >= '0'  && pArgv[1][0] <= '9')
    {
        u32FunNum = atoi(pArgv[1]);
        u32FunNum = u32FunNum - 1;

        if (u32FunNum >= s32Len)
        {
            printf("Test case from 1 to %d\n", s32Len);
            return HI_FAILURE;
        }

        if (stFunc[u32FunNum].hiTest_FUN_pfn != HI_NULL)
        {
            printf("####Run function %s,u32FuncNum=%d####\n", stFunc[u32FunNum].pFunName, u32FunNum + 1);
            //printf("is 0x%x\n",stFunc[u32FunNum].hiTest_FUN_pfn);
            stFunc[u32FunNum].hiTest_FUN_pfn();
        }

        return HI_SUCCESS;
    }
    else   /*����Ϊ������,��ڶ������� "./abc  HI_Mediaplayer_initialize_iNorm_01" */
    {
        HI_S32 s32Index = 0;
        //HI_S32 ret = 0;
        HI_U32 u32CmdLen = strlen(pArgv[1]);

        for (s32Index = 0; s32Index < s32Len; s32Index++)
        {
            if (u32CmdLen == strlen(stFunc[s32Index].pFunName) &&
                (!strcmp(pArgv[1], stFunc[s32Index].pFunName)) &&
                (stFunc[s32Index].hiTest_FUN_pfn != HI_NULL))
            {
                printf("#############Run function %s###############\n",
                       stFunc[s32Index].pFunName);
                stFunc[s32Index].hiTest_FUN_pfn();
                /*
                                if (!stFunc[s32Index].hiTest_FUN_pfn())
                                    HITEST_SetResultFlag(0);
                                else
                                    HITEST_SetResultFlag(1);

                                HITEST_FinalResult((HI_CHAR*)stFunc[s32Index].pFunName, s32_FuncLine_g);
                                */
                return HI_SUCCESS;
            }
        }

        s32Index--;

        if (u32CmdLen != strlen(stFunc[s32Index].pFunName) ||
            (strcmp(pArgv[1], stFunc[s32Index].pFunName)) ||
            (stFunc[s32Index].hiTest_FUN_pfn == HI_NULL))
        {
            printf("Usage :%s FunName\n", pArgv[0]);
            return HI_FAILURE;
        }
    }
#endif
    return HI_FAILURE;
}

/***********************************************************************************
* Function:      HITEST_InitLogLevel
* Description:   ��ʼ��log��ӡ����
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:         eLogLevel      log��ӡ���𣬼�ö��HITEST_LOG_LEVEL_E
* Output:        ��
* Return:        ��
* Others:        ��
***********************************************************************************/
HI_VOID HITEST_InitLogLevel(HITEST_LOG_LEVEL_E eLogLevel)
{
    s_eLogLevel = eLogLevel;
    return;
}

/***********************************************************************************
* Function:      HITEST_InitLogLevel
* Description:  ��ȡ��ǰlog��ӡ����
* Data Accessed: (Optional)
* Data Updated:  (Optional)
* Input:          ��
* Output:        ��ǰ��ӡ����
* Return:        ��
* Others:        ��
***********************************************************************************/
HITEST_LOG_LEVEL_E HITEST_GetLogLevel()
{
    return s_eLogLevel;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

