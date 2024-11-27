#include <LiquidCrystal.h>
#include <WiFi.h>

// LCD Pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 14, 27, 26, 25, 33);

// Wi-Fi Access Point credentials
const char* ssid = "ESP32_Game_AP";  
const char* password = "123456789";  

// Buttons
const int buttonSinglePlayer = 23;
const int buttonMultiPlayer = 22;
bool multiplayerMode = false;
int player1Pos = 0;
int player2Pos = 0;

// Wi-Fi server
WiFiServer server(80);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // LCD setup
  lcd.begin(16, 2);  
  lcd.setCursor(0, 0);
  lcd.print("Ping Pong Game");
  delay(2000);
  lcd.clear();

  // Setup buttons
  pinMode(buttonSinglePlayer, INPUT_PULLUP);
  pinMode(buttonMultiPlayer, INPUT_PULLUP);

  // Display instructions and wait for input
  lcd.setCursor(0, 0);
  lcd.print("Press Button 1");
  lcd.setCursor(0, 1);
  lcd.print("for 1-Player");

  lcd.setCursor(0, 1);
  lcd.print("Press Button 2");
  lcd.setCursor(0, 1);
  lcd.print("for 2-Player");

  // Wait for the input to select game mode
  while (true) {
    if (digitalRead(buttonSinglePlayer) == LOW) {
      multiplayerMode = false;
      startGame();
      break;
    } else if (digitalRead(buttonMultiPlayer) == LOW) {
      multiplayerMode = true;
      startGame();
      break;
    }
  }

  // Start Wi-Fi in AP mode
  WiFi.softAP(ssid, password);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
}

void loop() {
  // If Multiplayer, handle Wi-Fi communication
  if (multiplayerMode) {
    WiFiClient client = server.available();
    if (client) {
      String request = client.readStringUntil('\r');
      client.flush();
      if (request.indexOf("/up") != -1) player2Pos = max(0, player2Pos - 1);
      if (request.indexOf("/down") != -1) player2Pos = min(1, player2Pos + 1);
    }
  }

  // Update the game display
  displayGame();
  delay(100);
}

void startGame() {
  player1Pos = 0;
  player2Pos = 0;
  lcd.clear();
  
  if (multiplayerMode) {
    lcd.print("2-Player Mode");
  } else {
    lcd.print("1-Player Mode");
  }
  
  delay(2000);
  lcd.clear();
  Serial.println("Game Started");
}

void displayGame() {
  // Display Player 1 and Player 2 positions
  lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.setCursor(player1Pos * 2, 0); // Player 1 position
  lcd.print("O");

  lcd.setCursor(0, 1);
  lcd.print("P2:");
  lcd.setCursor(player2Pos * 2, 1); // Player 2 position
  lcd.print("O");

  // Debugging serial output
  Serial.print("Player 1 Pos: ");
  Serial.println(player1Pos);
  Serial.print("Player 2 Pos: ");
  Serial.println(player2Pos);
}
