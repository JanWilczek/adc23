#include <gtest/gtest.h>
#include <fft.h>
#include <vector>

namespace test {
TEST(FFTTest, ForwardInverseNoScaling) {
  constexpr auto FFT_SIZE = 512;
  FFT fft{FFT_SIZE};

  auto unitStep = fft.alignedBuffer();
  std::fill(unitStep.begin(), unitStep.end(), 1.f);
  auto dft = std::vector<std::complex<float>>(FFT_SIZE);
  auto output = fft.alignedBuffer();

  fft.forward(unitStep, dft.data());
  fft.inverse(dft.data(), output);

  for (const auto el : output) {
    EXPECT_FLOAT_EQ(1.f, el);
  }
}
}  // namespace test