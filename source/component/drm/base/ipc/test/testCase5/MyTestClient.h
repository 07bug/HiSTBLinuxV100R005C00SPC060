#ifndef _IMMPLAYER_JJJJ_H_
#define _IMMPLAYER_JJJJ_H_

#include "IMyTestClient.h"

using namespace android;

class MyTestClient : public BnMyTestClient
{
    public:
    MyTestClient();
    ~MyTestClient();
    void notify();
    void call_server();
    void Cll_client();
};

#endif // _IMMPLAYER_JJJJ_H_
