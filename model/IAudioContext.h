#pragma once

class IAudioContext {
 public:
  virtual ~IAudioContext() = default;
  virtual bool open(int deviceIndex) = 0;
  virtual bool close() = 0;
  virtual bool start() = 0;
  virtual bool stop() = 0;
};
