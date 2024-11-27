#include <LiquidCrystal.h>

// Define the pin connections
const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define the custom smiley character
byte smiley[8] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup() {
  lcd.begin(16, 2);         // Initialize 16x2 LCD
  lcd.createChar(0, smiley); // Create the smiley character at location 0
}

void loop() {
  // First part of the message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank you sooo");
  
  lcd.setCursor(0, 1);
  lcd.print("much Shastryyyy!");
  
  delay(2000); // Display first part for 3 seconds
  
  // Second part of the message with the smiley
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("It was really a");
  
  lcd.setCursor(0, 1);
  lcd.print("fun course <3 ");
  
  // Display the smiley at the end of the second line
  lcd.setCursor(15, 1);
  lcd.write(byte(0)); // Display the custom smiley character
  
  delay(3000); // Display second part for 3 seconds
  
  // Repeat
}
