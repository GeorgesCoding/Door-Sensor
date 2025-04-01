/*
#include <AudioTools.h>
#include <AudioTools/AudioCodecs/CodecMP3Helix.h>
#include "audio.h"
*/

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

/*
AudioInfo info(44100, 2, 16);             // sampling rate, # channels, bits per sample
I2SStream i2s;                            // transmits audio data
MemoryStream data(audio, length);         // mp3 data source
MP3DecoderHelix codec;                    // mp3 decoder
EncodedAudioStream decoder(&i2s, &codec); // decoding stream
StreamCopy copier(decoder, data);         // copy in to out
 */

const int port = 80;
const char *ssid = "****";
const char *password = "********";
WiFiServer server(port);

const int led = 27;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(void)
{
  Serial.begin(115200);
  lcd.init();
  pinMode(led, OUTPUT);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);

  // setup I2S
  /*
  auto config = i2s.defaultConfig(TX_MODE);
  config.copyFrom(info);
  config.pin_bck = 26;
  config.pin_data = 22;
  config.pin_ws = 25;
  i2s.begin(config);

  // setup I2S based on sampling rate
  decoder.begin();
   */
  lcd.begin(0, 0);
  lcd.print("connecting to wifi");

  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    lcd.print(".");
  }
  lcd.setCursor(0, 1);
  lcd.print("Successfully connected to WiFi");

  server.begin(port);
  WiFi.setAutoReconnect(true);
  Serial.println(WiFi.localIP());

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("finding client");
}

void loop()
{
  WiFiClient client = server.accept();
  if (client)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Client connected.");

    while (client.connected())
    {
      if (client.available())
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        char command = client.read();

        if (command == '1')
        {
          lcd.print("On");
        }
        else if (command == '0')
        {
          lcd.print("off");
        }
      }
    }
  }
  else
  {
    lcd.print(".");
    delay(1000);
  }
  // copy sound to output stream
  // copier.copy();
}