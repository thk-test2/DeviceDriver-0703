
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

TEST(DeviceDriver, ReadFromHWFail) {
	MockFlashMemoryDevice hardware;
	DeviceDriver driver{ &hardware };

	EXPECT_CALL(hardware, read(_))
		.Times(5)
		.WillOnce(Return(99))
		.WillOnce(Return(99))
		.WillOnce(Return(99))
		.WillOnce(Return(99))
		.WillOnce(Return(100));

	try {
		driver.read(0xFF);
	}
	catch (std::runtime_error& e) {
		EXPECT_EQ(std::string{ e.what() },
			std::string{ "읽은 값들이 일치하지 않습니다." });
	}
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
