#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_memory_device.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(DeviceDriver, ReadFromHWSuccess) {
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };

	EXPECT_CALL(hardware, read(_))
		.Times(5)
		.WillRepeatedly(Return(99));

	int data = driver.read(0xFF);

	EXPECT_EQ(99, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
