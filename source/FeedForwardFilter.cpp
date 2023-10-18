#include "FeedForwardFilter.h"

namespace CF {

float FeedForwardFilter::process(float sample) {
  delayLine.setDelay(delay);
  const auto delayedSample = delayLine.popSample();
  delayLine.pushSample(sample);

  const auto outputSample = gain * delayedSample + sample;
  // Scale output sample to stay in the [-1, 1] range
  const auto scaledOutputSample = 0.5f * outputSample;
  return scaledOutputSample;
}

}  // namespace CF
