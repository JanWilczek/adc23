#include "FractionalDelayLine.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <vector>

using namespace std;

namespace DL {

float FractionalDelayLine::popSample() {
  auto readHead = writeHead - 1 - delay;
  if (readHead < 0) {
    readHead += std::ssize(buffer);
  }
  auto truncatedReadHead = static_cast<int>(std::floor(readHead));
  auto truncatedReadHeadPlusOne =
      static_cast<int>(std::ceil(readHead));  // truncatedReadHead + 1;
  const auto truncatedReadHeadWeight =
      std::abs(readHead - truncatedReadHeadPlusOne);
  const auto truncatedReadHeadPlusOneWeight =
      std::abs(readHead - truncatedReadHead);
  if (truncatedReadHeadPlusOne >= std::ssize(buffer)) {
    truncatedReadHeadPlusOne -= std::ssize(buffer);
  }
  const auto outputSample =
      truncatedReadHeadWeight * buffer[truncatedReadHead] +
      truncatedReadHeadPlusOneWeight * buffer[truncatedReadHeadPlusOne];
  return outputSample;
}

void FractionalDelayLine::pushSample(float inputSample) {
  buffer[writeHead] = inputSample;
  writeHead++;
  writeHead %= std::ssize(buffer);
}

void FractionalDelayLine::setDelay(float newDelay) {
  delay = newDelay;
}

}  // namespace DL
