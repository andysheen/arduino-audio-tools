
#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "AudioLibs/AudioSourceIdxSD.h"

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Debug);

  SPI.begin(PIN_AUDIO_KIT_SD_CARD_CLK, PIN_AUDIO_KIT_SD_CARD_MISO, PIN_AUDIO_KIT_SD_CARD_MOSI, PIN_AUDIO_KIT_SD_CARD_CS);  
  while (!SD.begin(PIN_AUDIO_KIT_SD_CARD_CS)) {
       Serial.println("SD.begin failed");
       delay(1000);
  }
  AudioSourceSD<fs::SDFS,fs::File> idx{SD};
  idx.ls(Serial, "/", "mp3","*");

}

void loop() {
}