#include <gtest/gtest.h>
#include <AudioFile.h>
#include <numbers>
#include <CSVWriter.h>
#include <AudioPlayerExample.h>

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

TEST(OutputTest, GenerateCSV) {
  // some fancy audio processing, FFTs, etc...

  // write the output CSV
  CSVWriter csv;
  csv.enableAutoNewRow(2);
  csv << "Frequency [Hz]"
      << "Magnitude";
  csv << 100 << 0.1f;
  csv << 200 << 0.2f;
  csv << 300 << 0.3f;
  csv << 400 << 0.2f;
  csv << 500 << 0.1f;
  csv.writeToFile("dft_data.csv");
}

TEST(OutputTest, AudioPlayerExample) {
  AudioFile<double> audioFile;
  AudioFile<double>::AudioBuffer buffer;

  int numChannels = 2;
  buffer.resize(numChannels);

  int numSamplesPerChannel = 100;
  buffer[0].resize(numSamplesPerChannel);
  buffer[1].resize(numSamplesPerChannel);

  float sampleRate = 44100.f;

  auto outputData = std::vector<float>(numSamplesPerChannel * numChannels, 0.f);
  example::AudioPlayer audioPlayer{sampleRate, numChannels};

  audioPlayer.onAudioReady(nullptr, reinterpret_cast<void*>(outputData.data()),
                           numSamplesPerChannel - 1);

  for (int i = 0; i < numSamplesPerChannel; i++) {
    buffer[0][i] = outputData[i * numChannels];
    buffer[1][i] = outputData[i * numChannels + 1];
  }

  ASSERT_TRUE(audioFile.setAudioBuffer(buffer));
  audioFile.setSampleRate(static_cast<uint32_t>(sampleRate));
  ASSERT_TRUE(audioFile.save("audio_player_output.wav"));
}
}  // namespace test
