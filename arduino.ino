#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"

#define REPORTING_PERIOD_MS 2500
OakOLED oled;
PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup()
{
    Serial.begin(115200); 
    oled.begin();
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
   
    Serial.print("Networking...");
    
    if (!pox.begin()) {
    Serial.println("FAILED");
    for(;;);
    } else {
    Serial.println("SUCCESS");
    }
  }
void loop()
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    int heartRate = pox.getHeartRate();
    int SpO2 = pox.getSpO2();
     if(heartRate > 55 && SpO2<99 )
     {   
      Serial.print(heartRate);
      Serial.print(" ");
      Serial.println(SpO2);
  
      oled.clearDisplay();
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(10, 20);
      oled.println("Heart BPM:");
      // value  HR
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(75,20);
      oled.print(pox.getHeartRate());
      //
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(10, 35);
      oled.println("SpO2:");
      // value SpO2
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(45,35);
      oled.print(pox.getSpO2());
      oled.display(); 
      tsLastReport = millis();
     }
     else 
     { 
      
      oled.clearDisplay();
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(10, 20);
      oled.println("Heart BPM:");
      // value  HR
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(75,20);
      oled.print(0);
      //
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(10, 35);
      oled.println("SpO2:");
      // value SpO2
      oled.setTextSize(1);
      oled.setTextColor(1);
      oled.setCursor(45,35);
      oled.print(0);
      oled.display(); 
      tsLastReport = millis();
     }
     
    }
}
