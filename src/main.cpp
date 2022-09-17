#include    <Arduino.h>
#include    <SPI.h>
#include    <Ethernet.h>
#include    <SPI.h>
#include    <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include    "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

#define     ETH_RST         4
#define     ETH_CS          5
#define     ETH_SCLK       18
#define     ETH_MISO       23
#define     ETH_MOSI       19
#define     OLED_SCL       22
#define     OLED_SDA       21


uint8_t mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, OLED_SDA, OLED_SCL);


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.bing.com";    // name address for Google (using DNS)

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

int height = 64;
int width = 128;
int currheight = 0;
int currwidth = 0;
bool invheight = false;
bool invwidth = false;

void ethernetReset(const uint8_t resetPin)
{
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
    delay(250);
    digitalWrite(resetPin, LOW);
    delay(50);
    digitalWrite(resetPin, HIGH);
    delay(350);
}


void setup()
{
    Serial.begin(115200);
    Serial.println("deez");

    display.init();
    display.flipScreenVertically();

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    display.drawString(0, 0, "deez nuts");
    display.display();

    delay(1000);
    display.clear();
    display.display();
}

void loop()
{
  display.clear();
  display.drawString(currwidth, currheight, "deez nuts");
  display.display();
  delay(1);

  if(invheight) {
    currheight = currheight - 1;
  } else {
      currheight = currheight + 1;
  }

  if(invwidth) {
    currwidth = currwidth - 1;
  } else {
    currwidth = currwidth + 1;
  }

  if(currheight == 64-10) {
    invheight = true;
  }
    if(currwidth == 128-45) {
    invwidth = true;
  }
  if(currheight == 0) {
    invheight = false;
  }
    if(currwidth == 0) {
    invwidth = false;
  }
}