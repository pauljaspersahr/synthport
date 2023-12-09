#ifndef IAUDIOENGINE_H
#define IAUDIOENGINE_H

#include <vector>

class IAudioEngine {

 public:
  virtual ~IAudioEngine() = default;
  virtual std::vector<float> nextBuffer(unsigned long framesPerBuffer) = 0;
};

#endif  // IAUDIOENGINE_H