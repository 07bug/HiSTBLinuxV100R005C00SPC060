#ifndef IDRMSERVICE_H__
#define IDRMSERVICE_H__

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "IDrm.h"
#include "ICrypto.h"

using namespace android;

class IDrmService: public IInterface
{
public:
    DECLARE_META_INTERFACE(DrmService);

    virtual sp<IDrm>      makeDrm() = 0;
    virtual sp<ICrypto>   makeCrypto() = 0;
};

// ----------------------------------------------------------------------------

class BnDrmService: public BnInterface<IDrmService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

#endif // IDRMSERVICE_H__
