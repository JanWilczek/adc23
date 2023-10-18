#include "DelayLine.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

namespace DL {

float DelayLine::popSample() {
  auto readHead = writeHead - delay;
  if (readHead < 0) {
    readHead += std::ssize(buffer);
  }
  const auto outputSample = buffer[readHead];
  return outputSample;
}
void DelayLine::pushSample(float inputSample) {
  buffer[writeHead] = inputSample;
  writeHead++;
  writeHead %= std::ssize(buffer);
}
void DelayLine::setDelay(int newDelay) {
  delay = newDelay;
}

}  // namespace DL
