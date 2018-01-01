/*********************************************************************
Erics basic Arduino Oscilloscope using 0.96" OLED display with Arduino Nano

My Youtube Channel  : http://www.youtube.com/mkmeorg
More info found at http://www.mkme.org
Buy the Arduino Nano here: http://amzn.to/2lBO5te
Buy the OLED here: http://amzn.to/2DLpt8J
Uses Adafruit Library 
12C Info:
0X3C is address for cheap ebay units
Used I2C Scanner to find address
SDA connected to pin Analog 4
SCL connected to pin Analog 5
Monochrome OLEDs based on SSD1306 drivers

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Analog Pins
int channelAI = A0;      // probe
int delayAI = A1;       // delay potentiometer
float delayVariable =5; // 10 seems good for decent update- bit fast
float scale = 0;
int xCounter = 0;
int yPosition = 0;
int readings[85];
int counter = 0;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();

}


void loop() 
{
display.setTextColor(WHITE);  
//delayVariable = analogRead(delayAI);
  //delayVariable = (delayVariable/10);
  scale = 47.0/1023.0; 
  // commented out above delay items as no pot/encoder installed yet
  
  
  //record readings
  for(xCounter = 0; xCounter < 85; xCounter += 1)
    {                                 
      yPosition = analogRead(channelAI);
      readings[xCounter] = (yPosition*scale);
      delay (delayVariable);
    }
  
  display.clearDisplay();

  //Draw Voltage Ref Lines
  display.drawLine( 10, 0, 10, 47, WHITE);
  display.drawLine( 5, 47-(.166 *1023.0 * scale), 10, 47-(.166 *1023.0 * scale), WHITE);
  display.drawLine( 0, 47-(.33 *1023.0 * scale), 10, 47-(.33 *1023.0 * scale), WHITE);
  display.drawLine( 5, 47-(.5 *1023.0 * scale), 10, 47-(.5 *1023.0 * scale), WHITE);
  display.drawLine( 0, 47-(.66 *1023.0 * scale), 10, 47-(.66 *1023.0 * scale), WHITE);
  display.drawLine( 5, 47-(.84 *1023.0 * scale), 10, 47-(.84 *1023.0 * scale), WHITE);

  for(xCounter = 0; xCounter < 85; xCounter += 1)
    {
       display.drawPixel(xCounter, 47-readings[xCounter], WHITE);
       if(xCounter>1){
         display.drawLine(xCounter-1, 47-readings[xCounter-1], xCounter, 47-readings[xCounter], WHITE);
       }
    }
  
  display.display();     
} 



