#include <gtest/gtest.h>
#include <PitchTracker.h>

namespace {
constexpr auto SAMPLING_RATE = 44100.f;
constexpr int32_t BUFFER_SIZE = 441;
}  // namespace

namespace test {
TEST(PitchTrackerTest, SineEstimation) {
  PitchTracker pitchTracker;
  pitchTracker.prepareToPlay(SAMPLING_RATE, BUFFER_SIZE);

  for (const auto frequencyInHz : {80.f, 90.f, 100.f, 110.f, 120.f, 130.f,
                                   140.f, 150.f, 200.f, 250.f, 300.f, 1000.f}) {
    constexpr auto signalSize = 4 * BUFFER_SIZE;
    const auto sine = generateSine(frequencyInHz / SAMPLING_RATE, signalSize);

    auto f0 = 0.f;
    for (auto i = 0; i < signalSize; i += BUFFER_SIZE) {
      f0 = pitchTracker.track(sine.data() + i, BUFFER_SIZE);
    }

    constexpr auto TOLERANCE = 0.02f;
    EXPECT_NEAR(f0, frequencyInHz, frequencyInHz * TOLERANCE);
  }
}
}  // namespace test
