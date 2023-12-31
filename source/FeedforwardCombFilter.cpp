#include "FeedforwardCombFilter.h"

namespace CF {

float FeedForwardCombFilter::process(float sample) {
  delayLine.setDelay(delay);
  const auto delayedSample = delayLine.popSample();
  delayLine.pushSample(sample);

  const auto outputSample = delayedGain * delayedSample + directGain * sample;
  // Scale output sample to stay in the [-1, 1] range
  const auto scaledOutputSample = 0.5f * outputSample;
  return scaledOutputSample;
}

}  // namespace CF
