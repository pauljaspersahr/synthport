#pragma once

#include <memory>
#include <span>

class IAudioEngine {

 public:
  virtual ~IAudioEngine() = default;
  virtual void nextBuffer(float* out, unsigned long framesPerBuffer) = 0;
  virtual void process(std::span<float> buffer) = 0;
};
