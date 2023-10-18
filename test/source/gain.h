// gain.h
#pragma once
#include <vector>

void apply_gain(std::vector<float>& samples) {
  for (auto& sample : samples) {
    sample *= 0.5f;
  }
}
