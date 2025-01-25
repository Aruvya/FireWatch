#include <DHT.h>                          // Include the library for the DHT11 temperature and humidity sensor
#include <iarduino_RF433_Transmitter.h>   // Include the library for the 433 MHz transmitter (FS1000A)

// Component setup
iarduino_RF433_Transmitter radio(12);     // Create the transmitter object, pin 12 for connection
DHT dht(2, DHT11);                        // Create the DHT11 sensor object on pin 2
const int flamePin = A0;                  // Pin A0 for the analog output of the flame sensor
const int analogSignal = A1;              // Pin A1 for the analog output of the gas sensor
const int digitalSignal = 4;              // Pin 4 for the digital output of the gas sensor

void setup() {
    Serial.begin(9600);                   // Initialize the serial port for debugging
    dht.begin();                          // Initialize the DHT11 sensor
    radio.begin();                        // Initialize the transmitter
    radio.setDataRate(i433_1KBPS);        // Set the data transmission rate to 1 Kbps
    radio.openWritingPipe(5);             // Open the data transmission channel (channel 5)
    pinMode(flamePin, INPUT);             // Set the pin for the flame sensor as input
    pinMode(digitalSignal, INPUT);        // Set the pin for the gas sensor's digital output as input
}

void sendSensorData(int data) {
    radio.write(&data, sizeof(data));     // Transmit data using the transmitter
    delay(5000);                          // Delay for 5 seconds to prevent data flooding
}

void loop() {
    // Read temperature
    float temperature = dht.readTemperature();
    if (!isnan(temperature)) {            // Check if the data is valid
        Serial.println("Температура: " + String(temperature) + "°C");     // Log the temperature  
        sendSensorData((int)temperature); // Send the temperature (cast to int for simplicity)
    }

    // Read gas sensor data
    int gasValue = analogRead(analogSignal);  
    Serial.println("Уровень газа: " + String(gasValue));                 // Log the gas level
    sendSensorData(gasValue);            // Send the gas level

    // Read flame sensor data
    int flameValue = analogRead(flamePin);
    Serial.println("Уровень пламени: " + String(flameValue));           // Log the flame level
    sendSensorData(flameValue);          // Send the flame level
}
