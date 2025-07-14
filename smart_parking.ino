#include <ESP8266WiFi.h>
#include <Servo.h>

// WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// ThingSpeak settings
const char* host = "api.thingspeak.com";
String apiKey = "YOUR_THINGSPEAK_API_KEY";

// Servo objects
Servo servo1;
Servo servo2;

// IR sensor pins
const int irPins[5] = {D1, D2, D3, D4, D5};

// Servo pins
const int servoPin1 = D6;
const int servoPin2 = D7;

void setup() {
  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Attach servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Configure IR pins
  for (int i = 0; i < 5; i++) {
    pinMode(irPins[i], INPUT);
  }
}

void loop() {
  int slotStates[5];

  // Read IR sensors
  for (int i = 0; i < 5; i++) {
    slotStates[i] = digitalRead(irPins[i]);
  }

  // Servo logic for slot 1 and 2
  if (slotStates[0] == LOW) {
    servo1.write(0); // Barrier closed
    Serial.println("Slot 1: Occupied");
  } else {
    servo1.write(90); // Barrier open
    Serial.println("Slot 1: Available");
  }

  if (slotStates[1] == LOW) {
    servo2.write(0);
    Serial.println("Slot 2: Occupied");
  } else {
    servo2.write(90);
    Serial.println("Slot 2: Available");
  }

  // Send data to ThingSpeak
  WiFiClient client;
  if (client.connect(host, 80)) {
    String url = "/update?api_key=" + apiKey;
    for (int i = 0; i < 5; i++) {
      url += "&field" + String(i+1) + "=" + String(slotStates[i]);
    }

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    Serial.println("Data sent to ThingSpeak");
  }
  
  client.stop();
  delay(5000); // Wait before next update
}
