#include <Arduino.h>
#include <WiFi.h>

const int button = 14;
const int port = 80;
const char *address = "*******";  
const char *ssid = "****";          
const char *password = "********";
WiFiClient client;

void setup(void)
{
    Serial.begin(115200);
    pinMode(button, INPUT);

    Serial.print("\n\n\nConnecting to WiFi");
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nSuccessfully connected to WiFi\n");
    Serial.print("Now connecting to server");

    while (!client.connect(address, port))
    {
        Serial.print(".");
    }

    Serial.println("\nConnected to server");
}

void loop()
{
    if (digitalRead(button) == HIGH)
    {
        client.print("1");
        delay(500);
    }

    if (digitalRead(button) == LOW)
    {
        client.print("0");
        delay(500);
    }
}