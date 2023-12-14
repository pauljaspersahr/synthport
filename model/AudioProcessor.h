#pragma once

#include "model/IAudioEngine.h"
#include "model/IBuffer.h"

#include <memory>

class AudioProcessor {
 public:
  using BufferPtr = std::unique_ptr<IBuffer>;
  using AudioEnginePtr = std::unique_ptr<IAudioEngine>;

  AudioProcessor(BufferPtr&& buffer, AudioEnginePtr&& engine)
      : buffer_{std::move(buffer)}, engine_{std::move(engine)} {}

  ~AudioProcessor() = default;
  AudioProcessor() = delete;

  AudioProcessor(AudioProcessor const&) = delete;
  AudioProcessor(AudioProcessor&&) = default;

  AudioProcessor& operator=(AudioProcessor const&) = delete;
  AudioProcessor& operator=(AudioProcessor&&) = default;

  void callback(std::span<float> out) { engine_->process(out); }

 private:
  BufferPtr buffer_;
  AudioEnginePtr engine_;
};