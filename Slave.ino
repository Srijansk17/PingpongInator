  #include <WiFi.h>

  // Wi-Fi settings
  const char* ssid = "ESP32_Master";
  const char* password = "123456789";

  // Button pins for Player 2 control
  const int buttonUpPin = 25;
  const int buttonDownPin = 26;

  // Paddle position
  int paddleY = 4;
  int paddleHeight = 3;

  WiFiClient client;

  void setup() {
    Serial.begin(115200);

    pinMode(buttonUpPin, INPUT_PULLUP);
    pinMode(buttonDownPin, INPUT_PULLUP);

    // Connect to Wi-Fi as a client
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");

    // Connect to Board 1 (Server)
    while (!client.connect("192.168.4.1", 80)) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to Master (Board 1)");
  }

  void loop() {
    // Read input for paddle movement
    if (digitalRead(buttonUpPin) == LOW && paddleY > 0) {
      paddleY--;  // Move paddle up
    }
    if (digitalRead(buttonDownPin) == LOW && paddleY < 5) {
      paddleY++;  // Move paddle down
    }

    // Send paddle position to Board 1
    if (client.connected()) {
      client.print(String(paddleY) + "\n");  // Send current paddle position
    }

    delay(100);  // Adjust delay for smoother paddle control
  }
