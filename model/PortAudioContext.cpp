#include "model/PortAudioContext.h"

bool PortAudioContext::open(PaDeviceIndex index) {
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
      &outputParameters, sampleRate_, paFramesPerBufferUnspecified,
      paClipOff, /* we won't output out of range samples so don't bother clipping them */
      &PortAudioContext::paCallback,
      this /* Using 'this' for userData so we can cast to Sine* in paCallback method */
  );
  if (err != paNoError) {
    /* Failed to open stream to device !!! */
    return false;
  }

  err = Pa_SetStreamFinishedCallback(stream_,
                                     &PortAudioContext::paStreamFinished);

  if (err != paNoError) {
    Pa_CloseStream(stream_);
    stream_ = 0;

    return false;
  }

  return true;
}

bool PortAudioContext::close() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_CloseStream(stream_);
  stream_ = 0;

  return (err == paNoError);
}

bool PortAudioContext::start() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_StartStream(stream_);

  return (err == paNoError);
}

bool PortAudioContext::stop() {
  if (stream_ == 0)
    return false;

  PaError err = Pa_StopStream(stream_);

  return (err == paNoError);
}

int PortAudioContext::paCallbackMethod(const void* inputBuffer,
                                       void* outputBuffer,
                                       unsigned long framesPerBuffer,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags) {

  float* out = static_cast<float*>(outputBuffer);
  // audioEngine_->nextBuffer(out, framesPerBuffer);
  processor_.callback(std::span<float>{out, 2 * framesPerBuffer});

  return paContinue;
}

void PortAudioContext::paStreamFinishedMethod() {
  printf("Stream Completed: %s\n", message);
}