#ifndef SINEENGINE_H
#define SINEENGINE_H

#include "IAudioEngine.h"
#include "Note.h"

class SineEngine : public IAudioEngine {

 public:
  std::vector<float> nextBuffer(unsigned long framesPerBuffer) override {
    unsigned long const stereoFrames = 2 * framesPerBuffer;
    std::vector<float> out(stereoFrames, 0.);
    float const frequency(noteFrequency(Note::A4));
    float sampleRate = 44100.0;

    for (unsigned long ii = 0; ii < stereoFrames; ii = ii + 2) {
      float t = frameCount_ / sampleRate;
      out[ii] = sin(2 * M_PI * frequency * t);
      out[ii + 1] = sin(2 * M_PI * frequency * t);
      frameCount_++;
    }
    return out;
  }

 private:
  float sampleRate_{44100.0};
  size_t frameCount_{};
};

#endif  // SINEENGINE_H