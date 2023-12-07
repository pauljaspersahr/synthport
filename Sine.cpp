#include "Sine.h"
#include "Note.h"

bool Sine::open(PaDeviceIndex index) {
  PaStreamParameters outputParameters;

  outputParameters.device = index;
  if (outputParameters.device == paNoDevice) {
    return false;
  }

  const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
  if (pInfo != 0) {
    printf("Output device name: '%s'\r", pInfo->name);
  }

  outputParameters.channelCount = 2;         /* stereo output */
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  PaError err = Pa_OpenStream(
      &stream_, NULL, /* no input */
      &outputParameters, SAMPLE_RATE, paFramesPerBufferUnspecified,
      paClipOff, /* we won't output out of range samples so don't bother clipping them */
      &Sine::paCallback,
      this /* Using 'this' for userData so we can cast to Sine* in paCallback method */
  );
  if (err != paNoError) {
    /* Failed to open stream to device !!! */
    return false;
  }

  err = Pa_SetStreamFinishedCallback(stream_, &Sine::paStreamFinished);

  if (err != paNoError) {
    Pa_CloseStream(stream_);
    stream_ = 0;

    return false;
  }

  return true;
}

bool Sine::close() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_CloseStream(stream_);
  stream_ = 0;

  return (err == paNoError);
}

bool Sine::start() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_StartStream(stream_);

  return (err == paNoError);
}

bool Sine::stop() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_StopStream(stream_);

  return (err == paNoError);
}

int Sine::paCallbackMethod(const void* inputBuffer, void* outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags) {
  float* out = (float*)outputBuffer;
  float sampleRate = 44100.0;  // Sample rate
  float const frequency(noteFrequncy(Note::A3));

  for (unsigned long i = 0; i < framesPerBuffer; i++) {
    float t = frameCount_ / sampleRate;
    *out++ = sin(2 * M_PI * frequency * t);  // left channel
    *out++ = sin(2 * M_PI * frequency * t);  // right channel
    frameCount_++;
  }

  return paContinue;
}

void Sine::paStreamFinishedMethod() {
  printf("Stream Completed: %s\n", message);
}
