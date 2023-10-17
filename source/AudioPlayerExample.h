#pragma once
#include <numbers>

namespace example {
enum class DataCallbackResult { Stop, Continue };

class AudioStream {};

class AudioPlayer {
public:
  AudioPlayer(float sampleRate, int channelCount)
      : sampleRate{sampleRate},
        channelCount{channelCount},
        phaseIncrement{2.f * std::numbers::pi_v<float> * 440.f / sampleRate} {}

  float getSample() {
    phase = std::fmod(phase + phaseIncrement, 2 * std::numbers::pi_v<float>);
    return std::sin(phase);
  }

  DataCallbackResult onAudioReady(AudioStream* audioStream,
                                  void* audioData,
                                  int32_t framesCount) {
    auto* floatData = reinterpret_cast<float*>(audioData);

    for (auto frame = 0; frame < framesCount; ++frame) {
      const auto sample = getSample();
      for (auto channel = 0; channel < channelCount; ++channel) {
        floatData[frame * channelCount + channelCount] = sample;
        //   floatData[frame * channelCount + channel] = sample;
      }
    }
    return DataCallbackResult::Continue;
  }

private:
  float sampleRate = 0.f;
  int channelCount = 0;
  float phase = 0.f;
  float phaseIncrement = 0.f;
};
}  // namespace example
