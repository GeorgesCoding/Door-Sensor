#include "AudioTools.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"
#include "audio.h"

AudioInfo info(44100, 2, 16); // sampling rate, # channels, bits per sample
I2SStream i2s; // transmits audio data
MemoryStream data(audio, length); // mp3 data source
MP3DecoderHelix codec; // mp3 decoder
EncodedAudioStream decoder(&i2s, &codec); // decoding stream
StreamCopy copier(decoder, data); // copy in to out

void setup(void)
{
  // setup I2S
  auto config = i2s.defaultConfig(TX_MODE);
  config.copyFrom(info);
  config.pin_bck = 26;
  config.pin_data = 22;
  config.pin_ws = 25;
  i2s.begin(config);

  // setup I2S based on sampling rate
  decoder.begin();
}

void loop()
{
  // copy sound to output stream
  copier.copy();
}