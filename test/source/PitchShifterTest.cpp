#include <gtest/gtest.h>
#include <PitchShifter.hpp>
#include <vector>

namespace {
constexpr auto SAMPLING_RATE = 44100.f;
constexpr int32_t BUFFER_SIZE = 441;

float detectFrequencyOf(const std::vector<float>& pureTone) {
  auto i = 0;
  // skip initial zeros
  while (i < std::ssize(pureTone) and pureTone[i] == 0.f) {
    i++;
  }

  auto zeroCrossingsCount = 0;
  auto lastZeroCrossingId = i;
  auto sumOfHalfPeriodLengths = 0;
  while (i + 1 < std::ssize(pureTone)) {
    if (pureTone[i] * pureTone[i + 1] < 0.f) {
      // look for the first zero-crossing
      if (zeroCrossingsCount != 0) {
        sumOfHalfPeriodLengths += i + 1 - lastZeroCrossingId;
      }
      lastZeroCrossingId = i + 1;
      zeroCrossingsCount++;
    }
    i++;
  }

  zeroCrossingsCount -= 1;

  if (zeroCrossingsCount <= 0 or sumOfHalfPeriodLengths == 0) {
    return 0.f;
  }

  return zeroCrossingsCount * SAMPLING_RATE / (2 * sumOfHalfPeriodLengths);
}
}  // namespace

namespace test {
TEST(PitchShifterTest, PitchShiftSineAt3rdFFTBinByOctave) {
  PitchShifter pitchShifter;
  pitchShifter.prepareToPlay(SAMPLING_RATE, BUFFER_SIZE);

  constexpr auto FFT_SIZE = pitchShifter.FFT_SIZE;
  constexpr auto binFrequencyDiffHz = SAMPLING_RATE / FFT_SIZE;

  // test frequency corresponds to the 3rd FFT bin
  constexpr auto testFrequencyHz = 2.f * binFrequencyDiffHz;

  const auto sineSignal =
      generateSine(testFrequencyHz / SAMPLING_RATE, 10 * FFT_SIZE);

  auto output = zerosLike(sineSignal);

  constexpr auto PITCH_SHIFT_RATIO = 2.f;
  pitchShifter.setPitchShift(PITCH_SHIFT_RATIO);

  for (auto pos = 0; pos + BUFFER_SIZE <= std::ssize(output);
       pos += BUFFER_SIZE) {
    pitchShifter.process(sineSignal.data() + pos, BUFFER_SIZE,
                         output.data() + pos);
  }

  // skip the transient
  output.erase(output.begin(), output.begin() + 2 * FFT_SIZE);

  const auto f0 = detectFrequencyOf(output);

  constexpr auto testFrequencyRaisedByOctave =
      testFrequencyHz * PITCH_SHIFT_RATIO;
  EXPECT_NEAR(f0, testFrequencyRaisedByOctave, 0.001);
}
}  // namespace test
