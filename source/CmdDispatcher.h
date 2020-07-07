#ifndef __CmdDispatcher_h__
#define __CmdDispatcher_h__

#include "mbed.h"

class CmdDispatcher {
public:
    CmdDispatcher();

    void addCmd();
    void dispatch(const char *buffer);
private:
}

#endif
