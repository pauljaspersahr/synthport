#ifndef KEYBOARD_H
#define KEYBOARD_H

enum class Key {
  NoKey = -1,
  C_lower = 0,
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
  C_upper
};

class Keyboard {
 public:
  virtual ~Keyboard() = default;
  virtual Key getInput() const = 0;
};

#endif  // KEYBOARD_H