
#include "device_driver.h"

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) 
    : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    postContidionCheck(address, result);
    return result;
}

void DeviceDriver::postContidionCheck(long address, int result)
{
    for (int i = 0; i < MAX_TRY_COUNT; ++i) {
        int compare = (int)(m_hardware->read(address));
        if (result != compare)
            throw ReadFailException("���� ������ ��ġ���� �ʽ��ϴ�.");
    }
}

void DeviceDriver::write(long address, int data)
{
    int result = read(address);
    if (result != 0xFF) {
        throw WriteFailException("�̹� �����Ͱ� ������ �ּ��Դϴ�.");
    }

    m_hardware->write(address, (unsigned char)data);
}
