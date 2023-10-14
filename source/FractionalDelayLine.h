#pragma once
#include <array>

namespace DL {

class FractionalDelayLine {
 public:
  float popSample();
  float popSampleNew();
  void pushSample(float inputSample);
  void setDelay(float newDelay);

 private:
  static constexpr auto MAX_DELAY = 48000u;
  std::array<float, MAX_DELAY> buffer{};

  float delay = 4.f;
  int writeHead = 0;
};
}  // namespace DL
