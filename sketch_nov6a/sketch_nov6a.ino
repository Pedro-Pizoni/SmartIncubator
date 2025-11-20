#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT22
#define DIMMER_PIN 3
#define ZC_PIN 2

DHT dht(DHTPIN, DHTTYPE);

volatile int brilho = 0;
String serialBuffer = "";
unsigned long lastReadTime = 0;

// -----------------------------------
void zeroCrossDetected() {
  int delayMicros = map(brilho, 0, 255, 5000, 200);
  delayMicroseconds(delayMicros);
  digitalWrite(DIMMER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(DIMMER_PIN, LOW);
}
// -----------------------------------

void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("Arduino pronto");

  pinMode(DIMMER_PIN, OUTPUT);
  pinMode(ZC_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(ZC_PIN), zeroCrossDetected, RISING);
  dht.begin();
}

void loop() {

  // ======== Lê comandos do Qt ========
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n') {
      serialBuffer.trim();
      if (serialBuffer.length() > 0) {
        processCommand(serialBuffer);
      }
      serialBuffer = "";
    }
    else if (c != '\r') {
      serialBuffer += c;
    }
  }

  // ======== Envia temperatura/umidade a cada 2s ========
  if (millis() - lastReadTime > 2000) {
    lastReadTime = millis();

    float temp = dht.readTemperature();
    float hum  = dht.readHumidity();

    if (!isnan(temp)) {
      Serial.print("TEMP:");
      Serial.print(temp);
      Serial.print(";HUM:");
      Serial.println(hum);
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd.startsWith("DIM:")) {
    int val = cmd.substring(4).toInt();
    brilho = constrain(val, 0, 255);
  }
}
