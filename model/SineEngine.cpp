#include "model/SineEngine.h"

void SineEngine::nextBuffer(float* out, unsigned long framesPerBuffer) {
  unsigned long const stereoFrames = 2 * framesPerBuffer;
  float const frequency(noteFrequency(Note::A4));
  float sampleRate = 44100.0;

  for (unsigned long ii = 0; ii < stereoFrames; ii = ii + 2) {
    float t = frameCount_ / sampleRate;
    out[ii] = sin(2 * M_PI * frequency * t);
    out[ii + 1] = sin(2 * M_PI * frequency * t);
    frameCount_++;
  }
}

void SineEngine::process(std::span<float> buffer) {

  float const frequency(noteFrequency(Note::A4));
  float sampleRate = 44100.0;

  for (unsigned long ii = 0; ii < buffer.size(); ii = ii + 2) {
    float t = frameCount_ / sampleRate;
    buffer[ii] = sin(2 * M_PI * frequency * t);
    buffer[ii + 1] = sin(2 * M_PI * frequency * t);
    frameCount_++;
  }

  upstream_->process(buffer);
}