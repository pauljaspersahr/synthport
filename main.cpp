/** @file paex_sine.c
    @ingroup examples_src
    @brief Play a sine wave for several seconds.
    @author Ross Bencina <rossb@audiomulch.com>
    @author Phil Burk <philburk@softsynth.com>
*/
/*
 * $Id: paex_sine.c 1752 2011-09-08 03:21:55Z philburk $
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com/
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * The text above constitutes the entire PortAudio license; however,
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
 * they can be incorporated into the canonical version. It is also
 * requested that these non-binding requests be included along with the
 * license above.
 */

#include "ComputerKeyboard.h"
#include "Sine.h"

#include "model/PortAudioContext.h"
#include "model/SineEngine.h"

#include "portaudio.h"

int main() {
  Sine sine;
  PortAudioContext context{std::make_unique<SineEngine>()};

  ScopedPaHandler paInit;
  if (paInit.result() != paNoError)
    goto error;

  if (context.open(Pa_GetDefaultOutputDevice())) {
    if (context.start()) {
      std::puts("Context\n");
      Pa_Sleep(1000);
      context.stop();
      }
      context.close();
    }

  if (sine.open(Pa_GetDefaultOutputDevice())) {
    if (sine.start()) {
      std::puts("sine\n");
      Pa_Sleep(1000);
      // ComputerKeyboard keyboard{};
      // while (true) {
      //   auto key = keyboard.getInput();
      //   if (std::holds_alternative<InvalidKey>(key))
      //     break;
      //   sine.applyInput(key);
      //}
      sine.stop();
      }
    sine.close();
    }


  printf("Test finished.\n");
  return paNoError;

error:
  fprintf(stderr, "An error occurred while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", paInit.result());
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(paInit.result()));
  return 1;
}
