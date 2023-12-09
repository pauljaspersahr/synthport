#ifndef PORTAUDIOCONTEXT_H
#define PORTAUDIOCONTEXT_H

#include "IAudioContext.h"
#include "IAudioEngine.h"

#include "portaudio.h"

#include <memory>

class PortAudioContext : public IAudioContext {
 public:
  PortAudioContext(std::unique_ptr<IAudioEngine> audioEngine)
      : audioEngine_{std::move(audioEngine)} {}

  bool open(int deviceIndex) override;
  bool close() override;
  bool start() override;
  bool stop() override;

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
    return ((PortAudioContext*)userData)
        ->paCallbackMethod(inputBuffer, outputBuffer, framesPerBuffer, timeInfo,
                           statusFlags);
  }
  void paStreamFinishedMethod();

  /*
     * This routine is called by portaudio when playback is done.
     */
  static void paStreamFinished(void* userData) {
    return ((PortAudioContext*)userData)->paStreamFinishedMethod();
  }

 private:
  std::unique_ptr<IAudioEngine> audioEngine_{};
  PaStream* stream_{};
  unsigned long sampleRate_{44100};
  char message[20];
};

#endif  // PORTAUDIOCONTEXT_H