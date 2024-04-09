#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_VideoExt.h"
#include "OMX_RoleNames.h"

#undef LOG_TAG
#define LOG_TAG "HIOMX_CORE"

#define DEBUG 1

#ifndef HI_ADVCA_FUNCTION_RELEASE
#ifdef DEBUG
#define DEBUG_PRINT                   ALOGD
#else
#define DEBUG_PRINT(format...)
#endif

#define DEBUG_PRINT_ERROR             ALOGE
#define DEBUG_PRINT_ALWS              ALOGE
#else

#define DEBUG_PRINT(format...)
#define DEBUG_PRINT_ERROR(format...)
#define DEBUG_PRINT_ALWS(format...)
#endif

#define DYNAMIC_LOAD
#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

/* macros */
#define MAX_COMP_NUM                        (45)  // total component num
#define MAX_ROLES_OF_COMP                   (5)  // total roles of one component
#define MAX_COMP_NAME_LEN                   (50)  // max len of one component name
#define MAX_INSTANCES                       (7) // total instances of all components

typedef struct _ComponentTable {
    OMX_STRING name;//avc, hevc, etc.
    OMX_STRING loadname;//decoder, decoder.secure, encoder
    OMX_STRING pRoleArray[MAX_ROLES_OF_COMP];
} ComponentTable;

/******************************vars******************************/

static OMX_U32 g_InitCount = 0;
static pthread_mutex_t g_Mutex = PTHREAD_MUTEX_INITIALIZER;

static OMX_PTR pModules[MAX_INSTANCES] = {0};
static OMX_PTR pComponents[COUNTOF(pModules)] = {0};

static ComponentTable g_ComponentTable[MAX_COMP_NUM] =
{
    /*video encoder components */
    {"OMX.hisi.video.encoder.avc",          OMX_VENC_COMPONENT_NAME,        {OMX_ROLE_VIDEO_ENCODER_AVC,      0}},
#ifdef OMXVENC_SUPPORT_HEVC
    {"OMX.hisi.video.encoder.hevc",         OMX_VENC_COMPONENT_NAME,        {OMX_ROLE_VIDEO_ENCODER_HEVC,     0}},
#endif

     /*video decoder components */
    {"OMX.hisi.video.decoder.avc",                  OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVC,         0}},
    {"OMX.hisi.video.decoder.mpeg2",                OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG2,       0}},
    {"OMX.hisi.video.decoder.mpeg4",                OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG4,       0}},
#ifdef VP8_SUPPORT
    {"OMX.hisi.video.decoder.vp8",                  OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP8,         0}},
#endif
#ifdef VP9_SUPPORT
    {"OMX.hisi.video.decoder.vp9",                  OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP9,         0}},
#endif
    {"OMX.hisi.video.decoder.hevc",                 OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_HEVC,        0}},
    {"OMX.hisi.video.decoder.dolby-vision",         OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_DOLBYVISION, 0}},

    /*secure video decoder components */
    {"OMX.hisi.video.decoder.avc.secure",           OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVC,         0}},
    {"OMX.hisi.video.decoder.mpeg2.secure",         OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG2,       0}},
    {"OMX.hisi.video.decoder.mpeg4.secure",         OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG4,       0}},
#ifdef VP8_SUPPORT
    //{"OMX.hisi.video.decoder.vp8.secure",           OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP8,         0}},
#endif
#ifdef VP9_SUPPORT
    {"OMX.hisi.video.decoder.vp9.secure",           OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP9,         0}},
#endif
    {"OMX.hisi.video.decoder.hevc.secure",          OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_HEVC,        0}},
    {"OMX.hisi.video.decoder.dolby-vision.secure",  OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_DOLBYVISION, 0}},

#if (!defined(ANDROID) || !defined(ANDROID_O))

#if (defined(REAL8_SUPPORT) || defined(REAL9_SUPPORT))
    /* For copyright, vfmw didn't support std real. */
    {"OMX.hisi.video.decoder.real",         OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_RV,       0}},
    {"OMX.hisi.video.decoder.real.secure",  OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_RV,       0}},
#endif
    {"OMX.hisi.video.decoder.vc1",          OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VC1,      0}},
    {"OMX.hisi.video.decoder.mpeg1",        OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG1,    0}},
    {"OMX.hisi.video.decoder.h263",         OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_H263,     0}},
    {"OMX.hisi.video.decoder.divx3",        OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_DIVX3,    0}},
    {"OMX.hisi.video.decoder.vp6",          OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP6,      0}},
    {"OMX.hisi.video.decoder.wmv",          OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_WMV,      0}},
    {"OMX.hisi.video.decoder.avs",          OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVS,      0}},
    {"OMX.hisi.video.decoder.avs2",         OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVS2,     0}},
    {"OMX.hisi.video.decoder.sorenson",     OMX_VDEC_NORMAL_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_SORENSON, 0}},
    {"OMX.hisi.video.decoder.vc1.secure",   OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VC1,      0}},
    {"OMX.hisi.video.decoder.mpeg1.secure", OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_MPEG1,    0}},
    {"OMX.hisi.video.decoder.divx3.secure", OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_DIVX3,    0}},
    {"OMX.hisi.video.decoder.vp6.secure",   OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_VP6,      0}},
    {"OMX.hisi.video.decoder.wmv.secure",   OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_WMV,      0}},
    {"OMX.hisi.video.decoder.avs.secure",   OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVS,      0}},
    {"OMX.hisi.video.decoder.avs2.secure",  OMX_VDEC_SECURE_COMPONENT_NAME, {OMX_ROLE_VIDEO_DECODER_AVS2,     0}},
#endif

    /*audio decoder components */
#ifdef ANDROID
    {"OMX.hisi.audio.decoder.ac3", "OMX.hisi.audio.ddpdec", {OMX_ROLE_AUDIO_DECODER_AC3, 0}},
    {"OMX.hisi.audio.decoder.eac3", "OMX.hisi.audio.ddpdec", {OMX_ROLE_AUDIO_DECODER_EAC3, 0}},
#else
    {"OMX.hisi.audio.decoder.mp3",          "OMX.hisi.audio.mp3dec",        {OMX_ROLE_AUDIO_DECODER_MP3,      0}},
    {"OMX.hisi.audio.decoder.aac",          "OMX.hisi.audio.aacdec",        {OMX_ROLE_AUDIO_DECODER_AAC,      0}},
    {"OMX.hisi.audio.decoder.ac3",          "OMX.hisi.audio.ddpdec",        {OMX_ROLE_AUDIO_DECODER_AC3,      0}},
    {"OMX.hisi.audio.decoder.eac3",         "OMX.hisi.audio.ddpdec",        {OMX_ROLE_AUDIO_DECODER_EAC3,     0}},
    {"OMX.hisi.audio.decoder.dts",          "OMX.hisi.audio.dtsdec",        {OMX_ROLE_AUDIO_DECODER_DTS,      0}},
    {"OMX.hisi.audio.decoder.dra",          "OMX.hisi.audio.dradec",        {OMX_ROLE_AUDIO_DECODER_DRA,      0}},
    {"OMX.hisi.audio.decoder.cook",         "OMX.hisi.audio.cookdec",       {OMX_ROLE_AUDIO_DECODER_RA,       0}},
    {"OMX.hisi.audio.decoder.opus",         "OMX.hisi.audio.opusdec",       {OMX_ROLE_AUDIO_DECODER_OPUS,     0}},
    {"OMX.hisi.audio.decoder.vorbis",       "OMX.hisi.audio.vorbisdec",     {OMX_ROLE_AUDIO_DECODER_VORBIS,   0}},

    /*audio encoder components */
    {"OMX.hisi.audio.encoder.aac",          "OMX.hisi.audio.aacenc",        {OMX_ROLE_AUDIO_ENCODER_AAC,      0}},
#endif
    /* terminate the table */
    {0, 0, {0}},
};

static OMX_ERRORTYPE change_component_name(char **pcComponentName)
{
    OMX_U32 i;
    OMX_ERRORTYPE ret = OMX_ErrorNone;

    char *cComponentName = *pcComponentName;
    OMX_U32 count = COUNTOF(g_ComponentTable);

    for (i = 0; i < count; i++)
    {
        if (!cComponentName || !g_ComponentTable[i].name)
        {
            DEBUG_PRINT_ERROR("%s: param is invalid\n",__func__);

            return OMX_ErrorBadParameter;
        }

        if (!strncmp(cComponentName, g_ComponentTable[i].name, MAX(strlen(cComponentName), strlen(g_ComponentTable[i].name))))
        {
            cComponentName = g_ComponentTable[i].loadname;
            break;
        }
    }

    if (i == count)
    {
        DEBUG_PRINT_ERROR("%s :: can not find so lib by component name:%s \n",__func__, cComponentName);
        ret = OMX_ErrorInvalidComponentName;
    }

    *pcComponentName = cComponentName;

    return ret;
}

static OMX_BOOL check_component_role(OMX_IN OMX_U32 nIndex, OMX_IN OMX_STRING role)
{
    OMX_U32 i;

    for (i = 0; i < MAX_ROLES_OF_COMP && g_ComponentTable[nIndex].pRoleArray[i]; i++)
    {
        if (!g_ComponentTable[nIndex].pRoleArray[i] || !role)
        {
            DEBUG_PRINT_ERROR("%s: param is invalid\n",__func__);

            break;
        }

        if(!strncmp(g_ComponentTable[nIndex].pRoleArray[i], role, MAX(strlen(g_ComponentTable[nIndex].pRoleArray[i]), strlen(role))))
        {
            return OMX_TRUE;
        }
    }

    return OMX_FALSE;
}

OMX_ERRORTYPE OMX_Init()
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;

    DEBUG_PRINT("%s :: enter!\n", __func__);

    if (pthread_mutex_lock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n",__func__);
        return OMX_ErrorUndefined;
    }

    g_InitCount++;

    if (pthread_mutex_unlock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n",__func__);
        return OMX_ErrorUndefined;
    }

    DEBUG_PRINT("%s :: exit!\n", __func__);

    return eError;
}

OMX_ERRORTYPE OMX_GetHandle(
        OMX_HANDLETYPE *pHandle,
        OMX_STRING cComponentName,
        OMX_PTR pAppData,
        OMX_CALLBACKTYPE *pCallBacks)
{
    static const char prefix[] = "lib";
    static const char postfix[] = ".so";

    OMX_ERRORTYPE (*pComponentInit)(OMX_HANDLETYPE, OMX_STRING);
    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMX_COMPONENTTYPE *componentType;

    OMX_U32 i = 0;

    DEBUG_PRINT("%s :: enter!\n", __func__);

    if ((NULL == cComponentName) || (NULL == pHandle) || (NULL == pCallBacks))
    {
        DEBUG_PRINT_ERROR("%s :: invalid param!\n", __func__);

        return OMX_ErrorBadParameter;
    }

    if (strlen(cComponentName) >= MAX_COMP_NAME_LEN)
    {
        DEBUG_PRINT_ERROR("%s :: invalid component name!\n", __func__);

        return OMX_ErrorInvalidComponentName;
    }

    DEBUG_PRINT("%s :: component name:%s !\n", __func__, cComponentName);

    if (!g_InitCount)
    {
        DEBUG_PRINT_ERROR("Attempt to call OMX Methods without calling OMX_Init in prior");

        return OMX_ErrorUndefined;
    }

    if (pthread_mutex_lock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n",__func__);

        return OMX_ErrorUndefined;
    }

    for (i = 0; i < COUNTOF(pModules); i++)
    {
        if(pModules[i] == NULL)
        {
            break;
        }
    }

    if (i >= COUNTOF(pModules))
    {
        err = OMX_ErrorInsufficientResources;
        DEBUG_PRINT_ERROR("%s :: modules load too much!\n", __func__);
        goto UNLOCK_MUTEX;
    }

    char buf[sizeof(prefix) + MAX_COMP_NAME_LEN + sizeof(postfix)];

    err = change_component_name(&cComponentName);

    strncpy(buf, prefix, sizeof(prefix));
    strncat(buf, cComponentName, strlen(cComponentName));
    strncat(buf, postfix, sizeof(postfix));

    DEBUG_PRINT("%s :: prepare to load  %s\n", __func__, buf);

#ifdef DYNAMIC_LOAD
    pModules[i] = dlopen(buf, RTLD_LAZY | RTLD_GLOBAL);
    if (pModules[i] == NULL)
    {
        DEBUG_PRINT_ERROR("%s :: dlopen %s failed because %s\n", __func__, buf, dlerror());
        err = OMX_ErrorComponentNotFound;
        goto UNLOCK_MUTEX;
    }

    const char *pErr = dlerror();
    if (pErr != NULL)
    {
        DEBUG_PRINT_ERROR("%s:: dlopen failed :%s\n", __func__, pErr);
    }

    /* Get a function pointer to the "OMX_ComponentInit" function.  If
     * there is an error, we can't go on, so set the error code and exit */
    pComponentInit = dlsym(pModules[i], "component_init");
    pErr = dlerror();
    if (pErr != NULL)
    {
        DEBUG_PRINT_ERROR("dlsym error:%s\n", pErr);
    }

    if (pComponentInit == NULL)
    {
        DEBUG_PRINT_ERROR("%s:: dlsym failed for module %p\n", __func__, pModules[i]);
        err = OMX_ErrorComponentNotFound;
        goto CLEAN_UP;
    }
#else
    extern OMX_ERRORTYPE component_init(OMX_HANDLETYPE, OMX_STRING);
    pComponentInit = OMX_ComponentInit;
#endif

    DEBUG_PRINT("%s :: load  %s ok\n", __func__, buf);

    *pHandle = malloc(sizeof(OMX_COMPONENTTYPE));
    if (*pHandle == NULL)
    {
        err = OMX_ErrorInsufficientResources;
        DEBUG_PRINT_ERROR("%s:: malloc of pHandle* failed\n", __func__);
        goto CLEAN_UP;
    }

    /* We now can access the dll.  So, we need to call the "OMX_ComponentInit"
     * method to load up the "handle" (which is just a list of functions to
     * call) and we should be all set.*/
    pComponents[i] = *pHandle;
    componentType = (OMX_COMPONENTTYPE*) *pHandle;
    componentType->nSize = sizeof(OMX_COMPONENTTYPE);
    err = (*pComponentInit)(*pHandle, cComponentName);
    if (err != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("%s :: OMX_ComponentInit failed 0x%08x\n", __func__, err);
        goto CLEAN_UP;
    }

    err = (componentType->SetCallbacks)(*pHandle, pCallBacks, pAppData);
    if (err != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("%s :: Core: SetCallBack failed %d\n", __func__, err);
        goto CLEAN_UP;
    }

    goto UNLOCK_MUTEX;  // Component is found, and thus we are done

CLEAN_UP:
    if(*pHandle != NULL)
    {
        free(*pHandle);
        *pHandle = NULL;
    }

    pComponents[i] = NULL;

#ifdef DYNAMIC_LOAD
    dlclose(pModules[i]);
#endif

    pModules[i] = NULL;

UNLOCK_MUTEX:
    if (pthread_mutex_unlock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
        err = OMX_ErrorUndefined;
    }

    return (err);
}

OMX_ERRORTYPE OMX_FreeHandle(OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE retVal = OMX_ErrorUndefined;
    OMX_COMPONENTTYPE *pHandle = NULL;
    OMX_U32 i;

    if (hComponent == NULL)
    {
        DEBUG_PRINT_ERROR("%s :: invalid param!\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pHandle = (OMX_COMPONENTTYPE *)hComponent;

    if (pthread_mutex_lock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n", __func__);
        return OMX_ErrorUndefined;
    }

    /* Locate the component handle in the array of handles */
    for (i = 0; i < COUNTOF(pComponents); i++)
    {
        if (pComponents[i] == hComponent)
        {
            break;
        }
    }

    if (i >= COUNTOF(pComponents))
    {
        DEBUG_PRINT_ERROR("%s :: Core: component %p is not found\n", __func__, hComponent);
        retVal = OMX_ErrorBadParameter;
        goto EXIT;
    }

    if (pHandle->ComponentDeInit == NULL)
    {
        DEBUG_PRINT_ERROR("%s:%d: invalid param!\n", __func__, __LINE__);
        retVal = OMX_ErrorUndefined;
        goto EXIT;
    }

    /* call component deinit method */
    retVal = pHandle->ComponentDeInit(hComponent);
    if (retVal != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("%s :: ComponentDeInit failed %d\n", __func__, retVal);
        goto EXIT;
    }

#ifdef DYNAMIC_LOAD
    dlclose(pModules[i]);
#endif
    pModules[i] = NULL;
    free(pComponents[i]);
    pComponents[i] = NULL;
    retVal = OMX_ErrorNone;

EXIT:
    /* The unload is now complete, so set the error code to pass and exit */
    if (pthread_mutex_unlock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
        return OMX_ErrorUndefined;
    }

    return retVal;
}

OMX_ERRORTYPE OMX_Deinit()
{
    if (pthread_mutex_lock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex lock\n", __func__);
        return OMX_ErrorUndefined;
    }

    if (g_InitCount > 0)
    {
        g_InitCount--;
    }

    if (pthread_mutex_unlock(&g_Mutex) != 0)
    {
        DEBUG_PRINT_ERROR("%s :: Core: Error in Mutex unlock\n", __func__);
        return OMX_ErrorUndefined;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE OMX_SetupTunnel(
        OMX_IN OMX_HANDLETYPE outputComponent,
        OMX_IN OMX_U32             outputPort,
        OMX_IN OMX_HANDLETYPE  inputComponent,
        OMX_IN OMX_U32              inputPort)
{
    /* Not supported right now */
    DEBUG_PRINT("%s: OMX_SetupTunnel Not implemented\n", __func__);

    return OMX_ErrorNotImplemented;
}

OMX_ERRORTYPE OMX_ComponentNameEnum(
        OMX_OUT OMX_STRING cComponentName,
        OMX_IN  OMX_U32 nNameLength,
        OMX_IN  OMX_U32 nIndex)
{
    OMX_U32 Len = MIN(nNameLength, OMX_MAX_STRINGNAME_SIZE);
    if (cComponentName == NULL)
    {
        DEBUG_PRINT_ERROR("%s :: invalid param!\n", __func__);

        return OMX_ErrorBadParameter;
    }

    if ((nIndex < MAX_COMP_NUM) && g_ComponentTable[nIndex].name)
    {
        strncpy(cComponentName, g_ComponentTable[nIndex].name, Len);
        cComponentName[Len - 1] = '\0';
    }
    else
    {
        return OMX_ErrorNoMore;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE OMX_GetRolesOfComponent (
        OMX_IN      OMX_STRING cComponentName,
        OMX_INOUT   OMX_U32 *pNumRoles,
        OMX_OUT     OMX_U8 **roles)
{
    OMX_U32 i = 0;
    OMX_U32 j = 0;
    OMX_BOOL bFound = OMX_FALSE;

    if (!g_InitCount)
    {
        DEBUG_PRINT_ERROR("Attempt to call OMX Methods without calling OMX_Init in prior");

        return OMX_ErrorUndefined;
    }

    if (cComponentName == NULL || pNumRoles == NULL)
    {
        return OMX_ErrorBadParameter;
    }

    while (i < MAX_COMP_NUM)
    {
        if (strncmp(cComponentName, g_ComponentTable[i].name, MAX(strnlen(cComponentName, OMX_MAX_STRINGNAME_SIZE), strlen(g_ComponentTable[i].name))) == 0)
        {
            bFound = OMX_TRUE;
            break;
        }
        i++;
    }

    if (!bFound || i >= MAX_COMP_NUM)
    {
        DEBUG_PRINT_ERROR("%s :: component %s not found\n",__func__, cComponentName);

        return OMX_ErrorComponentNotFound;
    }

    if (roles == NULL)
    {
        for (j = 0; j < MAX_ROLES_OF_COMP && g_ComponentTable[i].pRoleArray[j]; j++);

        *pNumRoles = j;
    }
    else
    {
        for (j = 0; (j < *pNumRoles) && (j < MAX_ROLES_OF_COMP) && g_ComponentTable[i].pRoleArray[j]; j++)
        {
            if (roles[j] == NULL)
            {
                DEBUG_PRINT_ERROR("roles[%ld] is null\n", i);
                return OMX_ErrorUndefined;
            }
            strncpy((OMX_STRING)roles[j], g_ComponentTable[i].pRoleArray[j], OMX_MAX_STRINGNAME_SIZE);
        }
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE OMX_GetComponentsOfRole (
        OMX_IN      OMX_STRING role,
        OMX_INOUT   OMX_U32 *pNumComps,
        OMX_INOUT   OMX_U8  **compNames)
{
    OMX_U32 i = 0;

    if (!g_InitCount)
    {
        DEBUG_PRINT_ERROR("Attempt to call OMX Methods without calling OMX_Init in prior");

        return OMX_ErrorUndefined;
    }

    if (role == NULL)
    {
        DEBUG_PRINT_ERROR("%s :: role is NULL", __func__);

        return OMX_ErrorBadParameter;
    }

    if (pNumComps == NULL)
    {
        DEBUG_PRINT_ERROR("%s :: pNumComps is NULL\n", __func__);

        return OMX_ErrorBadParameter;
    }

    if (compNames == NULL)
    {
        /* must be the first of two calls */
        *pNumComps = 0;
        for (i = 0; i < MAX_COMP_NUM && g_ComponentTable[i].name; i++)
        {
            if (check_component_role(i, role) == OMX_TRUE)
            {
                (*pNumComps)++;
            }
        }
    }
    else
    {
        /* must be the second of two calls */
        OMX_U32 foundRoles = 0;

        for (i = 0; foundRoles < *pNumComps && i < MAX_COMP_NUM && g_ComponentTable[i].name; i++)
        {
            if (check_component_role(i, role) == OMX_TRUE)
            {
                if (compNames[foundRoles] == NULL)
                {
                    DEBUG_PRINT_ERROR("compNames[%ld] is null\n", foundRoles);
                    return OMX_ErrorUndefined;
                }
                strncpy((OMX_STRING)compNames[foundRoles], g_ComponentTable[i].name, strlen(g_ComponentTable[i].name));
                foundRoles++;
            }
        }
    }

    return OMX_ErrorNone;
}
