#pragma once
#include "DelayLine.h"

namespace CF {
class FeedForwardFilter {
public:
  float process(float sample);
  void setDelay(int newDelay) { this->delay = newDelay; }
  void setGain(float newGain) { this->gain = newGain; }

private:
  DL::DelayLine delayLine{};
  int delay;
  float gain;
};
}  // namespace CF
