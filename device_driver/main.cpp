
#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_memory_device.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverFixture : public Test {
protected:
	void SetUp() {
		driver.setDevice(&hardware);
	}

public:
	MockFlashMemoryDevice hardware;
	DeviceDriver driver;
};

TEST_F(DeviceDriverFixture, ReadFromHWSuccess) {
	EXPECT_CALL(hardware, read((long)0xA))
		.Times(5)
		.WillRepeatedly(Return((int)0xDD));

	EXPECT_EQ((int)0xDD, driver.read(0xA));
}

TEST_F(DeviceDriverFixture, ReadFromHWFail) {
	EXPECT_CALL(hardware, read((long)0xA))
		.Times(5)
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xCC));

	try {
		driver.read((long)0xA);
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
