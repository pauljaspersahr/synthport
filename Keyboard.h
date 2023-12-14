#pragma once

#include <variant>

enum class InvalidKey { Unkown };

enum class PianoKey {
  C_lower,
  Cs,
  D,
  Ds,
  E,
  F,
  Fs,
  G,
  Gs,
  A,
  As,
  B,
  C_upper,
};

enum class ControlKey { OctaveUp, OctaveDown };
using Input = std::variant<InvalidKey, PianoKey, ControlKey>;

class Keyboard {
 public:
  virtual ~Keyboard() = default;
  virtual Input getInput() const = 0;
};
