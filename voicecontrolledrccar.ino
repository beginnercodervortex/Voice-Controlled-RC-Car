#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// === Motor Driver Pin Setup ===
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D0
#define ENB D5

ESP8266WebServer server(80);  // Web server on port 80

void setup() {
  Serial.begin(115200);
  Serial.println("Booting RC Car...");

  // Set motor pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Setup Wi-Fi Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Akshita", "12345678");

  Serial.println("Wi-Fi AP started");
  Serial.print("Connect to IP: ");
  Serial.println(WiFi.softAPIP());

  // === Web Routes ===
  server.on("/", HTTP_GET, []() {
    Serial.println("Homepage (/) requested");
    server.send(200, "text/html", "<h2>AksAni's RC Car is ready!</h2>");
  });

  server.on("/forward", HTTP_GET, []() {
    Serial.println("Command received: FORWARD");
    moveForward();
    server.send(200, "text/plain", "Moving Forward");
  });

  server.on("/backward", HTTP_GET, []() {
    Serial.println("Command received: BACKWARD");
    moveBackward();
    server.send(200, "text/plain", "Moving Backward");
  });

  server.on("/left", HTTP_GET, []() {
    Serial.println("Command received: LEFT");
    turnLeft();
    server.send(200, "text/plain", "Turning Left");
  });

  server.on("/right", HTTP_GET, []() {
    Serial.println("Command received: RIGHT");
    turnRight();
    server.send(200, "text/plain", "Turning Right");
  });

  server.on("/stop", HTTP_GET, []() {
    Serial.println("Command received: STOP");
    stopMotors();
    server.send(200, "text/plain", "Stopped");
  });

  server.begin();
  Serial.println("Web server started and listening...");
}

// === Motor Control Functions with Debugging ===

void moveForward() {
  Serial.println("Action: Moving forward");
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);
  stopMotors();
}

void moveBackward() {
  Serial.println("Action: Moving backward");
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(400);
  stopMotors();
}

void turnLeft() {
  Serial.println("Action: Turning left");
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(400);
  stopMotors();
}

void turnRight() {
  Serial.println("Action: Turning right");
  analogWrite(ENA, 1023);
  analogWrite(ENB, 1023);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(400);
  stopMotors();
}

void stopMotors() {
  Serial.println("Action: Stopping motors");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// === Main Loop ===
void loop() {
  server.handleClient();
}