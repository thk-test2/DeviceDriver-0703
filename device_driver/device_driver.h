#pragma once
#include <set>
#include <string>
#include <stdexcept>

#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver() = default;
    DeviceDriver(FlashMemoryDevice* hardware);

    int read(long address);
    void write(long address, int data);

    void setDevice(FlashMemoryDevice* hardware) {
        m_hardware = hardware;
    }

protected:
    const int MAX_TRY_COUNT = 5;
    FlashMemoryDevice* m_hardware;
};

