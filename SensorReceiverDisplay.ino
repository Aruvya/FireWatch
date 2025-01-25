#include <LiquidCrystal_I2C.h>       // Include the library for an LCD display with an I2C interface
#include <Wire.h>                    // Include the library for I2C communication
#include <iarduino_RF433_Receiver.h> //  Include the library for the 433 MHz receiver (MX-RM-5V)

// Component initialization
iarduino_RF433_Receiver radio(2);    // Create the receiver object, pin 2 for connection
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD display with I2C address 0x27, 16x2 characters

int data;                            // Variable to store received data
void setup() {
    Serial.begin(19200);             // Initialize the serial port for debugging
    radio.begin();                   // Initialize the receiver
    radio.setDataRate(i433_1KBPS);   // Set the data reception rate to 1 Kbps
    radio.openReadingPipe(5);        // Open channel 5 for receiving data
    radio.startListening();          // Start listening mode
    lcd.init();                      // Initialize the LCD display
    lcd.backlight();                 // Turn on the backlight
    lcd.clear();                     // Clear the display before use
}

void loop() {
    if (radio.available()) {         // Check if data is available in the receiver buffer
        radio.read(&data, sizeof(data)); // Read the data into the data variable

        // Log the data to the Serial Monitor
        Serial.println("Полученные данные: " + String(data));

        // Display the data on the LCD screen
        lcd.clear();                 // Clear the display before showing new data
        lcd.setCursor(0, 0);         // Set the cursor to the beginning of the first row
        lcd.print("Данные: ");       // Print the label
        lcd.print(data);             // Print the received data

        delay(5000);                 // Delay to keep the data visible on the screen
    }
}
