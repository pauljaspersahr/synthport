#pragma once

#include "model/IAudioEngine.h"

class EmptyEngine : public IAudioEngine {

 public:
  void nextBuffer(float* out, unsigned long framesPerBuffer) override {}
  void process(std::span<float> buffer) override {}
};