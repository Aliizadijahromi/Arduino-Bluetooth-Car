#include <SoftwareSerial.h>
#include <DHT.h>

// Bluetooth HC-06
SoftwareSerial BT(10, 11);  // RX, TX

// Motor
const int IN1 = 8;
const int IN2 = 9;

// DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char command;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Motor initially stopped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  BT.begin(9600);
  dht.begin();

  BT.println("System Ready");
  BT.println("F = Forward");
  BT.println("B = Backward");
  BT.println("S = Stop");
  BT.println("T = Temperature & Humidity");
}

void loop() {

  if (BT.available()) {

    command = BT.read();

    if (command == 'F' || command == 'f') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      BT.println("Motor Forward");
    }

    else if (command == 'B' || command == 'b') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      BT.println("Motor Backward");
    }

    else if (command == 'S' || command == 's') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      BT.println("Motor Stop");
    }

    else if (command == 'T' || command == 't') {

      float humidity = dht.readHumidity();
      float temperature = dht.readTemperature();

      if (isnan(humidity) || isnan(temperature)) {
        BT.println("DHT11 Error!");
      }
      else {
        BT.print("Temperature: ");
        BT.print(temperature);
        BT.println(" C");

        BT.print("Humidity: ");
        BT.print(humidity);
        BT.println(" %");
      }
    }
  }
}
