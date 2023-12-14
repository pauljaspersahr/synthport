#include <gtest/gtest.h>

#include "model/PortAudioContext.h"
#include "model/SineEngine.h"

void sine(float* out, unsigned long framesPerBuffer) {
  float sampleRate = 44100.0;  // Sample rate
  float const frequency(noteFrequency(Note::A4));
  static size_t frameCount_ = 0;

  // std::cout << "freuquency = " << frequency << "\n";
  for (unsigned long i = 0; i < framesPerBuffer; i++) {
    float t = frameCount_ / sampleRate;
    *out++ = sin(2 * M_PI * frequency * t);  // left channel
    *out++ = sin(2 * M_PI * frequency * t);  // right channel
    frameCount_++;
  }
};

// Test case for the add function
TEST(PortModelTests, SineEngine) {

  float res_[128];
  sine(res_, 64);
  sine(res_, 64);
  std::vector<float> res(res_, res_ + 128);

  SineEngine sine{};
  float out_[128];
  sine.nextBuffer(out_, 64);
  sine.nextBuffer(out_, 64);
  std::vector<float> out(out_, out_ + 128);
  // for (size_t i = 0; i < 128; i++) {
  //   std::cout << "sine  " << res[i] << "\n";
  //   std::cout << "engine" << data[i] << "\n";
  // }
  EXPECT_EQ(out, res);
}