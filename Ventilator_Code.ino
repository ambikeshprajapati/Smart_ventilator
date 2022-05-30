#include <PulseSensorPlayground.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);     // Set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myservo;                          // create servo object to control a servo
const int PulseWire = 0;                // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;                   // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;  
int pos = 0;                            // an int variable which will be used to give position to the servo
PulseSensorPlayground pulseSensor;      // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {
  lcd.init();                           // initialize the lcd 
  lcd.backlight();                      // turns on the backlight of the lcd
  Serial.begin(9600); 
  pulseSensor.analogInput(PulseWire);   // take the pulse sensor input from the analog pin 0
  pulseSensor.blinkOnPulse(LED13);      // auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);  
  myservo.attach(9);                    // attaches the servo on pin 9 to the servo object
  myservo.write(0);                     // set the servo at 0 position
  lcd.setCursor(0,1);                   // sets the cursor at row 0 column 0
  lcd.print("   Ventilator   ");        // prints 16x2 LCD MODULE
  lcd.setCursor(1,0);                   // sets the cursor at row 1 column 2
  lcd.print("The Life Saving ");
  int myBPM;                            // take int variable where the pulse rate will be stored
  myBPM=analogRead(PulseWire);          // put the pulserate reading in the myBPM variable
    if (myBPM>1)                        // check the condition that pulseSenseor is reading the data or not
    {
    Serial.println("HeartBeat Happened"); // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: ");               // Print phrase "BPM: " 
    Serial.println(myBPM);               // prints the pulserate on the serial monitor
    lcd.init();                          // initialize the lcd   
    lcd.setCursor(0,0);                  // sets the cursor at row 0 column 0
    lcd.print("YourPulseRate Is");       // prints 16x2 LCD MODULE
    lcd.setCursor(0,1);                  // sets the cursor at row 1 column 0
    lcd.print(myBPM);                    // prints the pulserate on the LCD
    }
}
void loop() {
  for (pos = 0; pos <90; pos += 1) {     // goes from 0 degrees to 90 degrees
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(10);                           // waits 10 ms for the servo to reach the position
  }
  for (pos = 90; pos > 0; pos -= 1) {    // goes from 90 degrees to 0 degrees
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(10);                           // waits 10 ms for the servo to reach the position
  }
}
