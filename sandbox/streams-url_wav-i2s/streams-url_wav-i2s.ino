/**
 * @file test-memory_wav-serial.ino
 * @author Phil Schatzmann
 * @brief decode WAV stream from url and output it on I2S
 * @version 0.1
 * @date 2021-96-25
 * 
 * @copyright Copyright (c) 2021
 
 */
#include "AudioTools.h"
#include "CodecWAV.h"

using namespace audio_tools;  

// UrlStream -copy-> AudioOutputStream -> WAVDecoder -> I2S
URLStream url;
I2SStream i2s;                  // I2S stream 
WAVDecoder decoder(i2s);        // decode wav to pcm and send it to I2S
AudioOutputStream out(decoder); // output to decoder
StreamCopy copier(out, url);    // copy in to out


void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Debug);  

// url.begin("http://pi.local:5002//api/tts?text=hallo my name is sam")
//  url.begin("http://192.168.1.37:12101/api/text-to-speech?play=false", UrlStream::POST, "text/plain","Hallo, my name is Alice");

  I2SConfig config = out.defaultConfig(TX_MODE);
  config.sample_rate = 16000; 
  config.bits_per_sample = 32;
  config.channels = 1;

  i2s.begin(config);

}

void loop(){
  if (wav) {
    copier.copy();
  } else {
    stop();
  }
}