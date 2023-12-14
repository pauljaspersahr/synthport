#pragma once

#include "model/EmptyEngine.h"
#include "model/IAudioEngine.h"
#include "model/MultiBuffer.h"
#include "model/Note.h"

#include <memory>

class SineEngine : public IAudioEngine {

 public:
  SineEngine(std::unique_ptr<IAudioEngine>&& engine)
      : upstream_{std::move(engine)} {}

  SineEngine() : upstream_{std::make_unique<EmptyEngine>()} {}

  void nextBuffer(float* out, unsigned long framesPerBuffer) override;

  void process(std::span<float> buffer) override;

 private:
  std::unique_ptr<IAudioEngine> upstream_;
  float sampleRate_{44100.0};
  size_t frameCount_{};
};
