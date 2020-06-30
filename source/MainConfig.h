/**
 * @file MainConfig.h
 *
 * @brief main configuration
 *
 */
#pragma once

#include "dconfig.h"
#include "mbed.h"

class MainConfig : public DConfig
{
public:
    virtual void reset_default(void);

    bool load_config();
    bool save_config();

    void lock_config() {
        mutex_.lock();
    }

    void unlock_config() {
        mutex_.unlock();
    }

protected:
    Mutex mutex_;
};




