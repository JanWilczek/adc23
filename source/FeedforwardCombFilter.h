#pragma once
#include "DelayLine.h"

namespace CF {
class FeedForwardCombFilter {
public:
  float process(float sample);
  void setDelay(int newDelay) { this->delay = newDelay; }
  void setDelayedGain(float newGain) { this->delayedGain = newGain; }
  void setDirectGain(float newGain) { this->directGain = newGain; }

private:
  DL::DelayLine delayLine{};
  int delay;
  float delayedGain{1.f};
  float directGain{1.f};
};
}  // namespace CF
