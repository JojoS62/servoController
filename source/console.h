#ifndef __Console_h__
#define __Console_h__

/*
* @file console.h
*
* @brief console implementation
*
*/
#include "mbed.h"
#include <vector>
#include "cmdb.h"
#include "globals.h"

#define CONSOLE_STACK_SIZE (6*1024)

class Console {
    public:
    Console(BufferedSerial *serial);

    void process();

    private:
    Cmdb cmdb;
    vector<cmd> cmds;

    void init();
    void dispatcher(Cmdb& cmdb, int cid);
};

#endif // __Console_h__