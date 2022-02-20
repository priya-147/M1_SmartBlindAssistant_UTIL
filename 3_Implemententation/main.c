#include <"Android">
#include "Buzzer.h"
#include "NewPing.h"
#include "LiquidCrystal_PCF8574.h"
#include "Servo.h"
#define BUZZER_PIN_SIG 2
#define HCSR04_PIN_TRIG 4
#define HCSR04_PIN_ECHO 3
#define SERVO9G_PIN_SIG 5
#define LCD_ADDRESS 0x3F
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
const int servo9gRestPosition = 20;
const int servo9gTargetPosition = 150; 
Buzzer buzzer(BUZZER_PIN_SIG);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LiquidCrystal_PCF8574 lcdI2C;
Servo servo9g;
const int timeout = 10000;
char menuOption = 0;
long time;
void setup()
{
 Serial.begin(9600);
 while (!Serial) ;
 Serial.println("start");
 lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, 
BACKLIGHT);
 servo9g.attach(SERVO9G_PIN_SIG);
 servo9g.write(servo9gRestPosition);
 delay(100);
 servo9g.detach();
 menuOption = menu();
}
void loop() 
{ if(menuOption == '1') {
 buzzer.on(); 
 delay(500); 
 buzzer.off(); 
 delay(500); 
 }
 else if(menuOption == '2') {
 int hcsr04Dist = hcsr04.ping_cm();
 delay(10);
 Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));
 }
 else if(menuOption == '3') 
 {
 lcdI2C.clear();
 lcdI2C.print(" Circuito.io ");
 lcdI2C.selectLine(2); 
 lcdI2C.print(" Rocks! "); 
 delay(1000);
 }
 else if(menuOption == '4') {
 servo9g.attach(SERVO9G_PIN_SIG); 
 servo9g.write(servo9gTargetPosition);
 delay(500); 
 servo9g.write(servo9gRestPosition); 
 delay(500); 
 servo9g.detach(); 
 }
 if (millis() - time0 > timeout)
 {
 menuOption = menu(); 
 } }
char menu()
{
 Serial.println(F("\nWhich component would you like to test?"));
 Serial.println(F("(1) Buzzer"));
 Serial.println(F("(2) Ultrasonic Sensor - HC-SR04"));
 Serial.println(F("(3) LCD 16x2 I2C"));
 Serial.println(F("(4) 9G Micro Servo"));
 Serial.println(F("(menu) send anything else or press on board reset button\n"));
 while (!Serial.available());
 while (Serial.available()) 
 {
 char c = Serial.read();
 if (isAlphaNumeric(c))
 { 
 if(c == '1') 
 Serial.println(F("Now Testing Buzzer"));
 else if(c == '2') 
 Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
 else if(c == '3') 
 Serial.println(F("Now Testing LCD 16x2 I2C"));
 else if(c == '4') 
 Serial.println(F("Now Testing 9G Micro Servo"));
 else
 {
 Serial.println(F("illegal input!"));
 return 0;
 }
 time0 = millis();
 return c;
 }
 }
 }
