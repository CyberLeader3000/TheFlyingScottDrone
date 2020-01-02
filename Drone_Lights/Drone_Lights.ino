/**********************************************************************************
 * Drone Neopixels      Copyright 2020 Amy Loeliger
 * 
 * This is copyrighted under the BSD new license, the full text can be found here:
 * https://opensource.org/licenses/BSD-3-Clause
 * 
 * Author: Amy Loeliger
 * Target Device: Teensy 3.1 
 * Description: Code to display arrows for directions, to direct people
 * 
 * Date: 2020 Jan 02
 *********************************************************************************/

#include <Adafruit_NeoPixel.h>

// Sets the pin number of each strip
#define STRIP1        5     // Neopixel strip 1
#define STRIP2        4     // Neopixel strip 2
#define STRIP3        3     // Neopixel strip 3
#define STRIP4        2     // Neopixel strip 4

// Sets the number of neopixels
#define NUMPIXELS 11 

// Declares each strip of neopixels
Adafruit_NeoPixel pixels1(NUMPIXELS, STRIP1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, STRIP2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS, STRIP3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(NUMPIXELS, STRIP4, NEO_GRB + NEO_KHZ800);

// Custom neopixel prototype functions
void show_all();
void clear_one();
void clear_all();
void set_all(unsigned char, unsigned char, unsigned char, unsigned char);
void arrow_forward_solid(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_back_solid(unsigned char , unsigned char, unsigned char, unsigned int);
void arrow_right_solid(unsigned char , unsigned char, unsigned char, unsigned int);
void arrow_left_solid(unsigned char , unsigned char, unsigned char, unsigned int);

int pin = 12;   // Input PWM from FMU
unsigned long duration;   // High time of PWM signal

void setup() {
 // Initialises classes
  pixels1.begin(); 
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();

  pinMode(pin,INPUT);
}

// Update arrow twice a second
void loop() {
  // get direction information from FMU
  duration = pulseIn(pin, HIGH);

  // Determine direction arrow to display
  if (duration > 900 && duration <1100){            // 1ms - Turn off
    clear_all();
  }
  else if (duration > 1150 && duration < 1350){     // 1.25ms - Forward
    arrow_forward_solid(0,150,0,500);
  }
  else if (duration > 1400 && duration < 1600){     // 1.5ms - Right
    arrow_right_solid(0,150,0,500);
  }
  else if (duration >1650 && duration < 1850){      // 1.75ms - Back
    arrow_back_solid(0,150,0,500);
  }
  else if (duration > 1900 && duration <2100){      // 2ms - Left
    arrow_left_solid(0,150,0,500);
  }
}

// ****Support Functions****

/***************************************************************
       Updates neopixel colours on each strip
***************************************************************/
void show_all(){
    pixels1.show(); 
    pixels2.show(); 
    pixels3.show(); 
    pixels4.show(); 
}

/***************************************************************
       Clears the same neopixel on each strip
***************************************************************/
void clear_one(){
    pixels1.clear();  
    pixels2.clear(); 
    pixels3.clear(); 
    pixels4.clear(); 
}

/***************************************************************
       Clears all neopixels on each strip
***************************************************************/
void clear_all(){
  int i;
  for(i=0; i<NUMPIXELS; i++) {
    pixels1.clear();  
    pixels2.clear(); 
    pixels3.clear(); 
    pixels4.clear(); 
  }
}

/***************************************************************
       Sets the neopixel to the colour defined
***************************************************************/
void set_all(unsigned char pixel_num, unsigned char red, unsigned char green, unsigned char blue){
    pixels1.setPixelColor(pixel_num, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(pixel_num, pixels2.Color(red, green, blue));
    pixels3.setPixelColor(pixel_num, pixels3.Color(red, green, blue));
    pixels4.setPixelColor(pixel_num, pixels4.Color(red, green, blue));
}

/***************************************************************
       Displays solid forward arrow
***************************************************************/
void arrow_forward_solid(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();
   
    for(i=0; i<NUMPIXELS; i++) {

    pixels4.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(i, pixels2.Color(red, green, blue));

    }
    show_all(); 
    delay(delay_time);  
}

/***************************************************************
       Displays solid back arrow
***************************************************************/
void arrow_back_solid(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();
    
    for(i=0; i<NUMPIXELS; i++) {

    pixels1.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels3.setPixelColor(i, pixels2.Color(red, green, blue));

    }
    show_all();    
    delay(delay_time);
}

/***************************************************************
       Displays solid right arrow
***************************************************************/
void arrow_right_solid(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();
    
    for(i=0; i<NUMPIXELS; i++) {

    pixels1.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(i, pixels2.Color(red, green, blue));

    }
    show_all(); 
    delay(delay_time);   
}

/***************************************************************
       Displays solid left arrow
***************************************************************/
void arrow_left_solid(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();
    
    for(i=0; i<NUMPIXELS; i++) {

    pixels3.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels4.setPixelColor(i, pixels2.Color(red, green, blue));

    }
    show_all();   
    delay(delay_time); 
}
