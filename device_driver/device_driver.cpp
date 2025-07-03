#include "device_driver.h"
#include <set>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) 
    : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int result = 0;
    set<int> readSet;

    for (int i = 0; i < 5; ++i) {
        result = (int)(m_hardware->read(address));
        readSet.insert(result);
    }
    
    if (readSet.size() > 1);
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
