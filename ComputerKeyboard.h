#ifndef COMPUTERKEYBOARD_H
#define COMPUTERKEYBOARD_H

#include "Keyboard.h"

#include <iostream>
#include <map>
#include <string>

// For Windows
#ifdef _WIN32
#include <conio.h>
#else
// For Unix/Linux
#include <ncurses.h>
#endif

class ComputerKeyboard final : public Keyboard {
  using UserInput = char;

 public:
  Key getInput() const final {
    char ch;

#ifdef _WIN32
    // Windows implementation using _kbhit and _getch from conio.h
    while (!_kbhit())
      ;  // Wait for a key press
    ch = _getch();
#else
    // Unix/Linux implementation using ncurses
    initscr();  // Start curses mode
    cbreak();   // Line buffering disabled
    noecho();   // Don't echo while we do getch

    ch = getch();

    endwin();  // End curses mode
#endif
    auto it = keys_.find(ch);

    return it != keys_.end() ? it->second : Key::NoKey;
  }

 private:
  static std::map<UserInput, Key> keys_;
};

std::map<ComputerKeyboard::UserInput, Key> ComputerKeyboard::keys_ = {
    {'a', Key::C_lower}, {'w', Key::Cs}, {'s', Key::D},  {'e', Key::Ds},
    {'d', Key::E},       {'f', Key::F},  {'t', Key::Fs}, {'g', Key::G},
    {'y', Key::Gs},      {'h', Key::A},  {'u', Key::As}, {'j', Key::B},
    {'k', Key::C_upper}};

#endif  // COMPUTERKEYBOARD_H