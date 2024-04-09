#ifndef DRM_SESSION_MANAGER_H_
#define DRM_SESSION_MANAGER_H_
#include <common/hi_type.h>
#include <utils/RefBase.h>
#include <utils/KeyedVector.h>
#include <utils/threads.h>
#include <utils/Vector.h>
#include "DrmSessionClientInterface.h"

using namespace android;

HI_BOOL isEqualSessionId(const Vector<HI_U8>& sessionId1, const Vector<HI_U8>& sessionId2);

struct SessionInfo
{
    sp<DrmSessionClientInterface> drm;
    Vector<HI_U8> sessionId;
    HI_S64 timeStamp;
};

typedef Vector<SessionInfo> SessionInfos;
typedef KeyedVector<HI_S32, SessionInfos > PidSessionInfosMap;

struct DrmSessionManager : public RefBase
{
    static sp<DrmSessionManager> Instance();

    DrmSessionManager();
    //DrmSessionManager(sp<DrmSessionClientInterface> processInfo);

    HI_VOID addSession(HI_S32 pid, sp<DrmSessionClientInterface> drm, const Vector<HI_U8>& sessionId);
    HI_VOID useSession(const Vector<HI_U8>& sessionId);
    HI_VOID removeSession(const Vector<HI_U8>& sessionId);
    HI_VOID removeDrm(sp<DrmSessionClientInterface> drm);
    HI_BOOL reclaimSession(HI_S32 callingPid);

protected:
    virtual ~DrmSessionManager();

private:

    HI_S64 getTime_l();
    HI_BOOL getLowestPriority_l(HI_S32* lowestPriorityPid, HI_S32* lowestPriority);
    HI_BOOL getLeastUsedSession_l(
        HI_S32 pid, sp<DrmSessionClientInterface>* drm, Vector<HI_U8>* sessionId);

    //sp<DrmSessionClientInterface> mProcessInfo;
    mutable Mutex mLock;
    PidSessionInfosMap mSessionMap;
    HI_S64 mTime;

};

#endif  // DRM_SESSION_MANAGER_H_
