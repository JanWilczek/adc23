#include <gtest/gtest.h>
#include <AudioFile.h>
#include <numbers>

namespace test {
TEST(OutputTest, GenerateSine) {
  AudioFile<double> audioFile;
  AudioFile<double>::AudioBuffer buffer;

  int numChannels = 1;
  buffer.resize(numChannels);

  int numSamplesPerChannel = 100;
  buffer[0].resize(numSamplesPerChannel);

  float sampleRate = 44100.f;
  float frequency = 440.f;

  for (int i = 0; i < numSamplesPerChannel; i++) {
    float sample = std::sin(2. * std::numbers::pi_v<float> * frequency *
                            static_cast<float>(i) / sampleRate);
    buffer[0][i] = sample * 0.5f;
  }

  ASSERT_TRUE(audioFile.setAudioBuffer(buffer));
  audioFile.setSampleRate(sampleRate);
  ASSERT_TRUE(audioFile.save("sine.wav"));
}

TEST(OutputTest, GenerateCSV) {}
}  // namespace test
