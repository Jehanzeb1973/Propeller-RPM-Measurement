
#include <U8g2lib.h>


//1.3" I2C OLED display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//1.5" SPI OLED Display
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2_2(U8G2_R0, /* cs=*/ 05, /* dc=*/ 2, /* reset=*/ 16);  


int sensorPin = 15;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int propblades=2;

unsigned int revs=0;
long millisold=0;
long timeold=0;//for calculating RPM

void IRAM_ATTR isr() {
  if((millis()-millisold)>4)
  {
 revs++;
  }
  millisold=millis();
  }

void setup() {
 
  Serial.begin(115200);
    pinMode(sensorPin, INPUT);
    attachInterrupt(sensorPin, isr, FALLING);
 millisold=millis();
 timeold=millis();
       u8g2.setBusClock(100000); //important to set bus clock at 1MHz otherwise other devices on I2C bus may not work
  u8g2.begin();
  u8g2_2.begin();
   u8g2.setFont(u8g2_font_inb21_mn);  // choose a suitable font
   u8g2_2.setFont(u8g2_font_inb21_mn);  // choose a suitable font
  //u8g2_2.setFont(u8g2_font_9x15_mr);  // choose a suitable font
 // u8g2.setFont(u8g2_font_6x12_mr);  // choose a suitable font
}

void loop() {
  int RPM=0;
  // read the value from the sensor:
  //sensorValue = analogRead(sensorPin);
    RPM=(revs*60000)/(propblades*(millis()-timeold));
     revs=0;
timeold=millis();
   u8g2.clearBuffer();  // clear the internal memory
    u8g2.setCursor(02,35);
  u8g2.print(String(RPM));
    u8g2.sendBuffer();          // transfer internal memory to the display
   u8g2_2.clearBuffer();  // clear the internal memory
    u8g2_2.setCursor(02,35);
  u8g2_2.print(String(RPM));
    u8g2_2.sendBuffer();          // transfer internal memory to the display
  delay(300);
 
}
