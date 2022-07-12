/*SPI_VFD Library - display() and noDisplay()
 * 
                    O2 Rules

  Demonstrates the use a 20x2 VFD display.  The SPI_VFD
  library works with all VFD displays that are compatible with the
  NEC PD16314 driver and has the SPI pins brought out

  The circuit:
   VFD Clock to digital pin 2
   VFD Data to digital pin 3
   VFD Chip select to digital pin 4
   VFD VCC (power) to 5V
   VFD Ground (power) to Ground

*/
// include the library code:
#include <SPI_VFD.h>
#include <SparkFunDS1307RTC.h>
#include <Wire.h>

// initialize the library with the numbers of the interface pins-8
SPI_VFD vfd(11, 12, 13);


// Comment out the line below if you want month printed before date.
// E.g. October 31, 2016: 10/31/16 vs. 31/10/16
#define PRINT_USA_DATE
#define SQW_INPUT_PIN 2   // Input pin to read SQW
#define SQW_OUTPUT_PIN 13 // LED to indicate SQW's state

void setup() {
  // set up the LCD's number of columns and rows:
  vfd.begin(20, 2);
  vfd.noDisplay();
  // Print a message to the LCD.
  vfd.print("Initializing");
  delay(1000);

  // Use the serial monitor to view time/date output
  Serial.begin(9600);
  pinMode(SQW_INPUT_PIN, INPUT_PULLUP);
  pinMode(SQW_OUTPUT_PIN, OUTPUT);
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));

  rtc.begin(); // Call rtc.begin() to initialize the library
  // (Optional) Sets the SQW output to a 1Hz square wave.
  // (Pull-up resistor is required to use the SQW pin.)
  //rtc.writeSQW(SQW_SQUARE_1);

  // Now set the time...
  // You can use the autoTime() function to set the RTC's clock and
  // date to the compiliers predefined time. (It'll be a few seconds
  // behind, but close!)
  //rtc.autoTime();
  // Or you can use the rtc.setTime(s, m, h, day, date, month, year)
  // function to explicitly set the time:
  // e.g. 7:32:16 | Monday October 31, 2016:
  //rtc.setTime(16, 46, 11, 3, 12, 7, 22);  // Uncomment to manually set time
  //rtc.set12Hour(); // Use rtc.set12Hour to set to 12-hour mode
  vfd.noDisplay();
}

void loop() {
  // Turn on the display:
  vfd.display();
  vfd.setCursor(0, 0);
  static int8_t lastSecond = -1;

  // Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
  // etc. return functions.
  rtc.update();

  if (rtc.second() != lastSecond) // If the second has changed
  {
    vfd.print("     ");
    printTime(); // Print the new time
    vfd.display();
    lastSecond = rtc.second(); // Update lastSecond value
  }
}

void printTime()
{
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  vfd.print(String(rtc.hour()) + ":"); // Print hour

  if (rtc.minute() < 10)
  {
    Serial.print('0'); // Print leading '0' for minute
    vfd.print('0'); // Print leading '0' for minute
  }
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  vfd.print(String(rtc.minute()) + ":"); // Print minute
 


  if (rtc.second() < 10)
  {
    Serial.print('0'); // Print leading '0' for second
    vfd.print('0'); // Print leading '0' for second
  }
  Serial.print(String(rtc.second())); // Print second
  vfd.print(String(rtc.second())); // Print second
  
  if (rtc.is12Hour()) // If we're in 12-hour mode
  {
    //vfd.noDisplay();
    // Use rtc.pm() to read the AM/PM state of the hour
    if (rtc.pm())
    {
      Serial.print(" PM"); // Returns true if PM
      vfd.print(" PM"); // Returns true if PM
      //vfd.display();
    }
    else
    {
      Serial.print(" AM");
      vfd.print(" AM");
      //vfd.display();
    }
  }

  Serial.print(" | ");
  //vfd.print(" | ");
  vfd.setCursor(0, 1);
  vfd.print(" ");
  // Few options for printing the day, pick one:
  Serial.print(rtc.dayStr()); // Print day string
  vfd.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print(" - ");
  vfd.print(" - ");
#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
               String(rtc.date()) + "/");  // Print date
  vfd.print(String(rtc.month()) + "/" +   // Print month
            String(rtc.date()) + "/");  // Print date
#else
  Serial.print(String(rtc.date()) + "/" +    // (or) print date
               String(rtc.month()) + "/"); // Print month
  vfd.print(String(rtc.date()) + "/" +    // (or) print date
            String(rtc.month()) + "/"); // Print month
#endif
  Serial.println(String(rtc.year()));        // Print year
  vfd.print(String(rtc.year()));        // Print year
  }
