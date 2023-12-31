
#include "FeedforwardCombFilter.h"
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <numbers>

namespace test {
constexpr auto PI = std::numbers::pi_v<float>;
constexpr auto SIGNAL_SIZE = 20;

std::array<float, SIGNAL_SIZE> generateSineWithPeriodOf(float samples) {
  constexpr auto period = 10.f;
  constexpr auto frequency = 1.f / period;
  constexpr auto samplingRate = 1.f;
  constexpr auto amplitude = 1.0f;

  // generate a sine with the period of 10 samples
  std::array<float, SIGNAL_SIZE> signal{};
  for (int i = 0; i < SIGNAL_SIZE; i++) {
    signal[i] = amplitude * std::sin(2 * PI * frequency *
                                     static_cast<float>(i) / samplingRate);
  }

  return signal;
}

TEST(FeedforwardCombFilter, DelayByHalfPeriodResultsInPhaseCancellation) {
  // instantiate the feedforward filter
  CF::FeedForwardCombFilter ffcf;
  auto signal = generateSineWithPeriodOf(10.f);

  // set the delay to 5 samples and both gains to 1
  ffcf.setDelay(5);
  ffcf.setDelayedGain(1.f);
  ffcf.setDirectGain(1.f);

  // filter the sine
  for (int i = 0; i < std::ssize(signal); i++) {
    signal[i] = ffcf.process(signal[i]);
  }

  // the output after the first half of the period should be all zeros
  for (int i = 5; i < std::ssize(signal); i++) {
    ASSERT_NEAR(signal[i], 0.0, 1e-6);
  }
}
}  // namespace test
