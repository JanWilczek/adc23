#pragma once
#include <array>

namespace DL {

class DelayLine {
public:
  float popSample();
  void pushSample(float inputSample);
  void setDelay(int newDelay);

private:
  static constexpr auto MAX_DELAY = 48000u;
  std::array<float, MAX_DELAY> buffer{};

  int delay = 4;
  int writeHead = 0;
};
}  // namespace DL