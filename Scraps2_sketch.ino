#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define resetButton 6
#define lowButton 5
#define medButton 4
#define highButton 3
#define mosfetGate 7
#define buzzer 8

int outputLevel = 0; //heat to mosfetGate
int heatState = 0; //state of system, keeps track of what year to display
int heatLevel = 0;
double holdMillis = 0;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.clearDisplay();
  delay(1000);
  pinMode(resetButton, INPUT);
  pinMode(lowButton, INPUT);
  pinMode(medButton, INPUT);
  pinMode(highButton, INPUT);
  pinMode(mosfetGate, OUTPUT);
  display.clearDisplay();
}

void loop() {

    switch(heatState) {
    case 0:
      outputLevel = 0;
      analogWrite(mosfetGate, outputLevel);
      tone(buzzer, 131);
      resetScrollText();
      delay(50);
      display.clearDisplay();
      delay(50);
      break;
    case 1:
      outputLevel = 70;
      analogWrite(mosfetGate, outputLevel);
      tone(buzzer, 82);
      lowScrollText();
      delay(50);
      display.clearDisplay();
      delay(50);
      break;
    case 2:
      outputLevel = 170;
      analogWrite(mosfetGate, outputLevel);
      tone(buzzer, 20);
      medScrollText();
      delay(50);
      display.clearDisplay();
      delay(50);
      break;
    case 3:
      outputLevel = 255;
      analogWrite(mosfetGate, outputLevel);
      tone(buzzer, 39);
      highScrollText();
      delay(50);
      display.clearDisplay();
      delay(50);
      break;
}

  if (digitalRead(resetButton) == HIGH) {
    heatState = 0;
  }
   if (digitalRead(lowButton) == HIGH) {
    heatState = 1;
  } 
  if (digitalRead(medButton) == HIGH) {
    heatState = 2;
  }
   if (digitalRead(highButton) == HIGH) {
    heatState = 3;
  }

}

void highScrollText(void) {
  holdMillis = millis();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(20,2);
  display.clearDisplay();
  display.println("2018");
  display.display();
  delay(3000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(1,0);
  display.clearDisplay();
  display.print("11,300,000   tons");
  display.display();
  delay(500);
  
  while ((digitalRead(resetButton) == LOW) && (digitalRead(lowButton) == LOW) && (digitalRead(medButton) == LOW) && ((millis() - holdMillis) < 17000) ) {
    //Scroll text to the left
    display.startscrollleft(0x00, 0x0F);
  }

if (digitalRead(resetButton) == HIGH) {
    heatState = 0;
}
if (digitalRead(lowButton) == HIGH) {
    heatState = 1;
}
if (digitalRead(medButton) == HIGH) {
    heatState = 2;
}
 
  holdMillis = millis();
  display.stopscroll();
}

void medScrollText(void) {
  holdMillis = millis();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(20,2);
  display.clearDisplay();
  display.println("2000");
  display.display();
  delay(3000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.clearDisplay();
  display.print("6,280,000    tons");
  display.display();
  delay(500);
  
  while ((digitalRead(resetButton) == LOW) && (digitalRead(lowButton) == LOW) && (digitalRead(highButton) == LOW) && ((millis() - holdMillis) < 17000) ) {
    //Scroll text to the left
    display.startscrollleft(0x00, 0x0F);
  }

if (digitalRead(resetButton) == HIGH) {
    heatState = 0;
}
if (digitalRead(lowButton) == HIGH) {
    heatState = 1;
}
if (digitalRead(highButton) == HIGH) {
    heatState = 3;
}
 
  holdMillis = millis();
  display.stopscroll();
}

void lowScrollText(void) {
  holdMillis = millis();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(20,2);
  display.clearDisplay();
  display.println("1980");
  display.display();
  delay(3000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.clearDisplay();
  display.print("2,320,000    tons");
  display.display();
  delay(500);
  
  while ((digitalRead(resetButton) == LOW) && (digitalRead(highButton) == LOW) && (digitalRead(medButton) == LOW) && ((millis() - holdMillis) < 17000) ) {
    //Scroll text to the left
    display.startscrollleft(0x00, 0x0F);
  }

if (digitalRead(resetButton) == HIGH) {
    heatState = 0;
}
if (digitalRead(highButton) == HIGH) {
    heatState = 3;
}
if (digitalRead(medButton) == HIGH) {
    heatState = 2;
}
 
  holdMillis = millis();
  display.stopscroll();
}

void resetScrollText(void) {
  holdMillis = millis();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(20,2);
  display.clearDisplay();
  display.println("1960");
  display.display();
  delay(3000);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.clearDisplay();
  display.print("1,710,000    tons");
  display.display();
  delay(500);
  
  while ((digitalRead(highButton) == LOW) && (digitalRead(lowButton) == LOW) && (digitalRead(medButton) == LOW) && ((millis() - holdMillis) < 17000) ) {
    //Scroll text to the left
    display.startscrollleft(0x00, 0x0F);
  }

if (digitalRead(highButton) == HIGH) {
    heatState = 3;
}
if (digitalRead(lowButton) == HIGH) {
    heatState = 1;
}
if (digitalRead(medButton) == HIGH) {
    heatState = 2;
}
 
  holdMillis = millis();
  display.stopscroll();
}
