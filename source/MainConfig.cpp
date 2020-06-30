/**
 * @file MainConfig.cpp
 *
 * @brief main configuration
 *
 */

#include "MainConfig.h"
//#include "SOFBlock.h"

// main configuration sector index of flash memory.
const uint8_t config_sector_index = 7;

void MainConfig::reset_default(void)
{
    clear();
    (*this)["eth"] = "dhcp";
    (*this)["ip"] = "";
    (*this)["mask"] = "255.255.255.0";
    (*this)["gw"] = "";
}

bool MainConfig::load_config()
{
    // SOFReader reader;

    // if (reader.open(config_sector_index) != kSOF_ErrNone) {
    //     return false;
    // }

    // return load_from((char *)reader.get_physical_data_addr(), reader.get_data_size());
    return true;
}

static bool save_func(void *user_data, char c)
{
    // SOFWriter *writer = (SOFWriter*)user_data;

    // return writer->write_byte_data((uint8_t)c);
    return true;
}

bool MainConfig::save_config()
{
    // size_t need_bytes = estimate_save();
    // SOFWriter writer;

    // if (writer.open(config_sector_index) != kSOF_ErrNone) {
    //     printf("open(%d) fail: format\r\n", config_sector_index);
    //     SOFBlock::format(config_sector_index);
    //     writer.open(config_sector_index);
    // } else {
    //     if (need_bytes > writer.get_free_size()) {
    //         printf("too small free size(%u/%u): format\r\n", need_bytes, writer.get_free_size());
    //         writer.close();
    //         SOFBlock::format(config_sector_index);
    //         writer.open(config_sector_index);
    //     }
    // }

    // return save_to(save_func, &writer);
    return true;
}




