#ifndef SINE_H
#define SINE_H

#include "Keyboard.h"
#include "Note.h"

#include "portaudio.h"

#include <math.h>
#include <stdio.h>
#include <iostream>

#define NUM_SECONDS (5)
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)

#ifndef M_PI
#define M_PI (3.14159265)
#endif

#define TABLE_SIZE (200)

class Sine {
 public:
  Sine() : stream_(0), left_phase(0), right_phase(0) {
    /* initialise sinusoidal wavetable */
    for (int i = 0; i < TABLE_SIZE; i++) {
      sine[i] = (float)sin(((double)i / (double)TABLE_SIZE) * M_PI * 2.);
    }

    sprintf(message, "No Message");
  }

  bool open(PaDeviceIndex index);

  bool close();

  bool start();

  bool stop();

 private:
  /* The instance callback, where we have access to every method/variable in object of class Sine */

  int paCallbackMethod(const void* inputBuffer, void* outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags);

  /* This routine will be called by the PortAudio engine when audio is needed.
    ** It may called at interrupt level on some machines so don't do anything
    ** that could mess up the system like calling malloc() or free().
    */
  static int paCallback(const void* inputBuffer, void* outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags, void* userData) {
    /* Here we cast userData to Sine* type so we can call the instance method paCallbackMethod, we can do that since
           we called Pa_OpenStream with 'this' for userData */
    return ((Sine*)userData)
        ->paCallbackMethod(inputBuffer, outputBuffer, framesPerBuffer, timeInfo,
                           statusFlags);
  }
  void paStreamFinishedMethod();

  /*
     * This routine is called by portaudio when playback is done.
     */
  static void paStreamFinished(void* userData) {
    return ((Sine*)userData)->paStreamFinishedMethod();
  }
  PaStream* stream_;
  float sine[TABLE_SIZE];
  int left_phase;
  int right_phase;
  char message[20];
  size_t frameCount_{};
};

class ScopedPaHandler {
 public:
  ScopedPaHandler() : _result(Pa_Initialize()) {}
  ~ScopedPaHandler() {
    if (_result == paNoError) {
      Pa_Terminate();
    }
  }

  PaError result() const { return _result; }

 private:
  PaError _result;
};

#endif  // SINE_H