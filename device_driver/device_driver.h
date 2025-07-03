#pragma once
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
    const int MAX_TRY_COUNT = 4;
    FlashMemoryDevice* m_hardware;

private:
    void postContidionCheck(long address, int result);
};

class ReadFailException : public std::exception {
public:
    explicit ReadFailException(char const* _Message)
        : exception(_Message)
    {
    }
};
