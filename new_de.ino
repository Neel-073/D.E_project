  #include <Wire.h> 
//#include<LiquidCrystal.h>
//LiquidCrystal lcd(2,3,7,6,5,4);
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define sensorPin1 13 // Entry sensor
#define sensorPin2 2 // Exit sensor
#define relayPin 8    // Relay control pin

int sensorState1 = 0;
int sensorState2 = 0;
int count = 0;
int ready_entrer = 0;
int ready_sortir = 0;

void setup() 
{
    pinMode(sensorPin1, INPUT_PULLUP);
    pinMode(sensorPin2, INPUT_PULLUP);
    pinMode(relayPin, OUTPUT); // Set relay pin as output
    digitalWrite(relayPin, HIGH); // Turn relay OFF (assuming LOW activates it)

    lcd.init();   // Initialize the LCD
    lcd.backlight();
    lcd.setCursor(4, 0);
    lcd.print("COUNTER");
    lcd.setCursor(0, 1);
    lcd.print("No Visitors     ");
    delay(200);
}

void loop() 
{  
    sensorState1 = digitalRead(sensorPin1);
    sensorState2 = digitalRead(sensorPin2);

    if (sensorState1 == LOW) {
        ready_entrer = 1;
    } else if (sensorState2 == LOW) {
        ready_sortir = 1;
    }

    if (ready_entrer == 1 && sensorState2 == LOW) {
        count++; 
        ready_entrer = 0;
        ready_sortir = 0;
        delay(500);
    } else if (ready_sortir == 1 && sensorState1 == LOW) {
        count--; 
        ready_sortir = 0;
        ready_entrer = 0;
        delay(500);
    }

    // Control the relay based on visitor count
    if (count > 0) {
        digitalWrite(relayPin, LOW); // Turn OFF the relay (assuming HIGH turns it off)
    } else {
        digitalWrite(relayPin, HIGH); // Turn ON the relay (assuming LOW activates it)
    }

    // Display visitor count on the LCD
    if (count <= 0) {
        lcd.setCursor(0, 1);
        lcd.print("No visitors    ");
    } 
    else if (count > 0 && count < 10) {
        lcd.setCursor(0, 1);
        lcd.print("Visitors:   ");
        lcd.setCursor(12, 1);
        lcd.print(count);
        lcd.setCursor(13, 1);
        lcd.print("  "); 
    } 
    else {
        lcd.setCursor(0, 1);
        lcd.print("Visitors:");
        lcd.setCursor(12, 1);
        lcd.print(count);  
    }
}
