#include <FractionalDelayLine.h>
#include <gtest/gtest.h>

namespace test {
	TEST(Flanger, FractionalDelay) {
		DL::FractionalDelayLine delayLine;

		delayLine.pushSample(1);
		delayLine.pushSample(2);
		delayLine.pushSample(3);
		delayLine.pushSample(4);

		delayLine.setDelay(100);
		ASSERT_FLOAT_EQ(0, delayLine.popSample());

		delayLine.setDelay(1.5f);
		ASSERT_FLOAT_EQ(2.5f, delayLine.popSample());

		delayLine.setDelay(2.3f);
		ASSERT_FLOAT_EQ(1.7f, delayLine.popSample());

		delayLine.setDelay(3.3f);
		ASSERT_NEAR(0.7f, delayLine.popSample(), 0.001f);

		delayLine.setDelay(2.f);
		ASSERT_FLOAT_EQ(2.f, delayLine.popSample());
	}
}
