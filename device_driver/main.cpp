#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_memory_device.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	//FlashMemoryDevice* hardware = nullptr;
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };

	int data = driver.read(0xFF);

	EXPECT_EQ(0, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
