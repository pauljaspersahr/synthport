#pragma once

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
  Input getInput() const final {
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
    std::clog << "Key Pressed: " << ch << "\n";

    auto it = keys_.find(ch);
    return it != keys_.end() ? it->second : InvalidKey::Unkown;
  }

 private:
  static std::map<UserInput, Input> keys_;
};

std::map<ComputerKeyboard::UserInput, Input> ComputerKeyboard::keys_ = {
    {'a', PianoKey::C_lower},   {'w', PianoKey::Cs},
    {'s', PianoKey::D},         {'e', PianoKey::Ds},
    {'d', PianoKey::E},         {'f', PianoKey::F},
    {'t', PianoKey::Fs},        {'g', PianoKey::G},
    {'y', PianoKey::Gs},        {'h', PianoKey::A},
    {'u', PianoKey::As},        {'j', PianoKey::B},
    {'k', PianoKey::C_upper},   {',', ControlKey::OctaveDown},
    {'.', ControlKey::OctaveUp}};
