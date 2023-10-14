#include <algorithm>
#include <array>
#include <vector>
#include <cmath>
#include <cassert>
#include "FractionalDelayLine.h"

using namespace std;

namespace DL {

float FractionalDelayLine::popSample() {
    assert(delay >= 0.f);
    assert(delay < static_cast<float>(buffer.size()));
    auto readHead = writeHead - 1 - delay;
    if (readHead < 0) {
    readHead += std::ssize(buffer);
    }
    auto truncatedReadHead = static_cast<int>(std::floor(readHead));
    auto truncatedReadHeadPlusOne = static_cast<int>(std::ceil(readHead)); // truncatedReadHead + 1; 
    const auto truncatedReadHeadWeight =
        std::abs(readHead - truncatedReadHeadPlusOne);
    const auto truncatedReadHeadPlusOneWeight =
        std::abs(readHead - truncatedReadHead);
    if (truncatedReadHeadPlusOne >= std::ssize(buffer)) {
        truncatedReadHeadPlusOne -= std::ssize(buffer);
    }
    assert(0 <= truncatedReadHead);
    assert(0 <= truncatedReadHeadPlusOne);
    assert(truncatedReadHead < std::ssize(buffer));
    assert(truncatedReadHeadPlusOne < std::ssize(buffer));
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
