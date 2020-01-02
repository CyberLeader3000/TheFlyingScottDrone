/*
 * Drone Neopixels
 * 
 * Author: Amy Loeliger
 * Target Device: Teensy 3.1 
 * Description: Code to demonstrate the neopixels on the drone.
 */

 
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

// Prototype functions
void show_all();
void clear_one();
void clear_all();
void set_all(unsigned char, unsigned char, unsigned char, unsigned char);
void ring_out(unsigned char, unsigned char, unsigned char, unsigned int);
void ring_in(unsigned char, unsigned char, unsigned char, unsigned int);
void fill_out(unsigned char, unsigned char, unsigned char, unsigned int);
void fill_in(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_forward_solid(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_back_solid(unsigned char , unsigned char, unsigned char, unsigned int);
void arrow_right_solid(unsigned char , unsigned char, unsigned char, unsigned int);
void arrow_left_solid(unsigned char , unsigned char, unsigned char, unsigned int);
void arrow_forward_fill(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_back_fill(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_right_fill(unsigned char, unsigned char, unsigned char, unsigned int);
void arrow_left_fill(unsigned char, unsigned char, unsigned char, unsigned int);

// Initialises classes
void setup() {
  pixels1.begin(); 
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
}

// Calls the functions to be run
void loop() {
  ring_out(200,0,200,500);
  ring_in(200,0,200,500);
  
  ring_out(0,200,0,500);
  ring_in(0,200,0,500);
  
  ring_out(200,0,0,500);
  ring_in(200,0,0,500);
  
  ring_out(0,0,200,500);
  ring_in(0,0,200,500);
  
  fill_out(200,0,200,500);
  fill_in(0,0,0,500);

  fill_out(0,200,0,500);
  fill_in(0,0,0,500);

  fill_out(200,0,0,500);
  fill_in(0,0,0,500);
  
  fill_out(150,0,150,500);
  fill_in(0,0,0,500);

  arrow_back_fill(0,150,0,250);

  arrow_back_solid(0,150,0,2000);

  arrow_left_fill(0,150,0,250);
    
  arrow_left_solid(0,150,0,2000);

  arrow_forward_fill(0,150,0,250);

  arrow_forward_solid(0,150,0,2000);

  arrow_right_fill(0,150,0,250);

  arrow_right_solid(0,150,0,2000);
}

// Updates neopixel colours on each strip
void show_all(){
    pixels1.show(); 
    pixels2.show(); 
    pixels3.show(); 
    pixels4.show(); 
}

// Clears the same neopixel on each strip
void clear_one(){
    pixels1.clear();  
    pixels2.clear(); 
    pixels3.clear(); 
    pixels4.clear(); 
}

// Clears all neopixels on each strip
void clear_all(){
  int i;
  for(i=0; i<NUMPIXELS; i++) {
    pixels1.clear();  
    pixels2.clear(); 
    pixels3.clear(); 
    pixels4.clear(); 
  }
}

// Sets the neopixel to the colour defined
void set_all(unsigned char pixel_num, unsigned char red, unsigned char green, unsigned char blue){
    pixels1.setPixelColor(pixel_num, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(pixel_num, pixels2.Color(red, green, blue));
    pixels3.setPixelColor(pixel_num, pixels3.Color(red, green, blue));
    pixels4.setPixelColor(pixel_num, pixels4.Color(red, green, blue));
}

// Neopixels turn on in sequence outwards on each strip at the same time with the previous neopixel turning off when the next one turns on
void ring_out(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
  
  int i;
  
  for(i=0; i<NUMPIXELS; i++) {

    clear_one();

    set_all(i, red, green, blue);
    
    show_all();
    
    delay(delay_time); 
  }
}

// Neopixels turn on in sequence inwards on each strip at the same time with the previous neopixel turning off when the next one turns on
void ring_in(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
  
  int i;
  
  for(i=NUMPIXELS; i>-1; i--) {
    
    set_all(i, red, green, blue);
    
    show_all();

    clear_one();
    
    delay(delay_time); 
  }
}

void fill_out(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    
    int i;
    
    clear_one();

    for(i=0; i<NUMPIXELS; i++) {
    
      set_all(i, red, green, blue);
    
      show_all();
    
      delay(delay_time); 
  }
}

void fill_in(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {

    int i;

    for(i=NUMPIXELS; i>-1; i--) {
    
      set_all(i, red, green, blue);
    
      show_all();
    
      delay(delay_time);
  
  }
}

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

void arrow_forward_fill(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();

    for(i=NUMPIXELS; i>-1; i--) {

    pixels4.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(i, pixels2.Color(red, green, blue));

    show_all();

    delay(delay_time);
    
    } 
}

void arrow_back_fill(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();

    for(i=NUMPIXELS; i>-1; i--) {

    pixels1.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels3.setPixelColor(i, pixels2.Color(red, green, blue));

    show_all();

    delay(delay_time);
    
    } 
}

void arrow_right_fill(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();

    for(i=NUMPIXELS; i>-1; i--) {

    pixels1.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels2.setPixelColor(i, pixels2.Color(red, green, blue));

    show_all();

    delay(delay_time);
    
    } 
}

void arrow_left_fill(unsigned char red, unsigned char green, unsigned char blue, unsigned int delay_time) {
    int i;

    clear_all();

    for(i=NUMPIXELS; i>-1; i--) {

    pixels3.setPixelColor(i, pixels1.Color(red, green, blue));   
    pixels4.setPixelColor(i, pixels2.Color(red, green, blue));

    show_all();

    delay(delay_time);
    
    } 
}
