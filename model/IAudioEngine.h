#ifndef IAUDIOENGINE_H
#define IAUDIOENGINE_H

class IAudioEngine {

 public:
  virtual ~IAudioEngine() = default;
  virtual void nextBuffer(float* out, unsigned long framesPerBuffer) = 0;
};

#endif  // IAUDIOENGINE_H