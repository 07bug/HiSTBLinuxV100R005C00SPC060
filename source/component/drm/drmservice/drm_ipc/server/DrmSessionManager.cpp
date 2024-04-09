#define LOG_TAG "DrmSessionManager"
#include <utils/Logger.h>

#include <unistd.h>
#include <utils/String8.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "DrmSessionManager.h"
#include "DrmSessionClientInterface.h"

static String8 GetSessionIdString(const Vector<HI_U8>& sessionId)
{
    String8 sessionIdStr;

    for (size_t i = 0; i < sessionId.size(); ++i)
    {
        sessionIdStr.appendFormat("%u ", sessionId[i]);
    }

    return sessionIdStr;
}

HI_BOOL isEqualSessionId(const Vector<HI_U8>& sessionId1, const Vector<HI_U8>& sessionId2)
{
    if (sessionId1.size() != sessionId2.size())
    {
        return HI_FALSE;
    }

    for (size_t i = 0; i < sessionId1.size(); ++i)
    {
        if (sessionId1[i] != sessionId2[i])
        {
            return HI_FALSE;
        }
    }

    return HI_TRUE;
}

sp<DrmSessionManager> DrmSessionManager::Instance()
{
    static sp<DrmSessionManager> drmSessionManager = new DrmSessionManager();
    return drmSessionManager;
}

DrmSessionManager::DrmSessionManager()
    : mTime(0)
{

}


DrmSessionManager::~DrmSessionManager()
{

}

HI_VOID DrmSessionManager::addSession(
    HI_S32 pid, sp<DrmSessionClientInterface> drm, const Vector<HI_U8>& sessionId)
{
    HI_LOGI("addSession(pid %d, drm %p, sessionId %s)", pid, drm.get(),
            GetSessionIdString(sessionId).string());

    Mutex::Autolock lock(mLock);
    SessionInfo info;
    info.drm = drm;
    info.sessionId = sessionId;
    info.timeStamp = getTime_l();
    ssize_t hisi_index = mSessionMap.indexOfKey(pid);

    if (hisi_index < 0)
    {
        // new pid
        SessionInfos infosForPid;
        infosForPid.push_back(info);
        mSessionMap.add(pid, infosForPid);
    }
    else
    {
        mSessionMap.editValueAt(hisi_index).push_back(info);
    }

}

HI_VOID DrmSessionManager::useSession(const Vector<HI_U8>& sessionId)
{
    HI_LOGI("useSession(%s)", GetSessionIdString(sessionId).string());

    Mutex::Autolock lock(mLock);

    for (size_t i = 0; i < mSessionMap.size(); ++i)
    {
        SessionInfos& infos = mSessionMap.editValueAt(i);

        for (size_t j = 0; j < infos.size(); ++j)
        {
            SessionInfo& info = infos.editItemAt(j);

            if (isEqualSessionId(sessionId, info.sessionId))
            {
                info.timeStamp = getTime_l();
                return;
            }
        }
    }
}

HI_VOID DrmSessionManager::removeSession(const Vector<HI_U8>& sessionId)
{
    HI_LOGI("removeSession(%s)", GetSessionIdString(sessionId).string());

    Mutex::Autolock lock(mLock);

    for (size_t i = 0; i < mSessionMap.size(); ++i)
    {
        SessionInfos& infos = mSessionMap.editValueAt(i);

        for (size_t j = 0; j < infos.size(); ++j)
        {
            if (isEqualSessionId(sessionId, infos[j].sessionId))
            {
                infos.removeAt(j);
                return;
            }
        }
    }
}

HI_VOID DrmSessionManager::removeDrm(sp<DrmSessionClientInterface> drm)
{
    HI_LOGI("removeDrm(%p)", drm.get());

    Mutex::Autolock lock(mLock);
    HI_BOOL found = HI_FALSE;

    for (size_t i = 0; i < mSessionMap.size(); ++i)
    {
        SessionInfos& infos = mSessionMap.editValueAt(i);

        for (size_t j = 0; j < infos.size();)
        {
            if (infos[j].drm == drm)
            {
                HI_LOGI("removed session (%s)", GetSessionIdString(infos[j].sessionId).string());
                j = infos.removeAt(j);
                found = HI_TRUE;
            }
            else
            {
                ++j;
            }
        }

        if (found)
        {
            break;
        }
    }
}

HI_S64 DrmSessionManager::getTime_l()
{
    return mTime++;
}
