#pragma once

#include "model/IBuffer.h"

#include <array>

template <size_t Frames, size_t N>
class MultiBuffer : public IBuffer {

  // N Buffer with Frames frames per Buffer for right and left Channel
  using Buffer = std::array<float, 2 * Frames * N>;

  void fill(float* out) const;

  float& operator[](size_t index);

 private:
  Buffer buffer_{};
};

template <size_t Frames, size_t N>
float& MultiBuffer<Frames, N>::operator[](size_t index) {
  if (index > Frames) {
    throw std::invalid_argument("Subscript index out if bounce");
  }
  return buffer_[index];
}