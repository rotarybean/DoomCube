#include <Wire.h>
#include <U8g2lib.h>
#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11 sensor type
#define LEDPIN 13    // LED pin on Arduino Nano

DHT dht(DHTPIN, DHTTYPE);

// Initialize the U8g2 library for SSD1306 OLED display in I2C mode with address 0x78
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

void setup() {
    Serial.begin(115200);
    dht.begin();
    u8g2.begin();
    pinMode(LEDPIN, OUTPUT);
}

void fadeLED() {
    for (int brightness = 0; brightness <= 255; brightness++) {
        digitalWrite(LEDPIN, HIGH);
        delayMicroseconds(brightness * 10);
        digitalWrite(LEDPIN, LOW);
        delayMicroseconds((255 - brightness) * 10);
    }
}

void blinkLED(int interval, int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LEDPIN, HIGH);
        delay(interval);
        digitalWrite(LEDPIN, LOW);
        delay(interval);
    }
}

void loop() {
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);
    float humidity = dht.readHumidity();
    
    if (isnan(tempC) || isnan(tempF) || isnan(humidity)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        blinkLED(50, 10);  // Fast blink on failure (50ms on, 50ms off, repeated 10 times)
        return;
    }
    
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    
    u8g2.setCursor(0, 10);
    u8g2.print("Temp: ");
    u8g2.print(tempC);
    u8g2.print(" C");
    
    u8g2.setCursor(0, 25);
    u8g2.print("Temp: ");
    u8g2.print(tempF);
    u8g2.print(" F");
    
    u8g2.setCursor(0, 40);
    u8g2.print("Humidity: ");
    u8g2.print(humidity);
    u8g2.print(" %");
    
    u8g2.sendBuffer();
    
    fadeLED();  // LED fade up in 1 second
    blinkLED(250, 2);  // Blink sequence: 250ms on, 250ms off, repeated twice
    
    delay(2000);  // Update every 2 seconds
}
