/*


DAC
https://www.analog.com/media/en/technical-documentation/data-sheets/dac08.pdf 


IO Expander
https://www.ti.com/lit/ds/symlink/pcf8574.pdf

*/


#define ARDUINO_PIANO

#include "key.hpp"
#include "keyboard.hpp"
#include "enclosure_funcs.hpp"
#include <vector>
#include "Arduino.h"
#include "variant_DAISY_SEED.h"

// global Keyboard object
Keyboard piano = Keyboard();
// button array
#define NUM_OF_KEYS 24
bool curr_buttons[NUM_OF_KEYS] = {0};
bool last_buttons[NUM_OF_KEYS] = {0};
// define IO expander addresses
#define IO_EXPANDER_1 0
#define IO_EXPANDER_2 0
#define IO_EXPANDER_3 0
// button presses
std::vector<Keyboard::note_t> new_button_pressed;
std::vector<Keyboard::note_t> new_button_depressed;


void setup() {
  // setup serial
  Serial.begin(9600);
  Serial.print("Beginning initialization...  ");
  Keyboard::freqs_t freqs[NUM_OF_KEYS] = {0};
  Keyboard::note_enclosures_t enclosures[NUM_OF_KEYS];

  // initialize all freqs and enclosures
  enclosures[Keyboard::C] = {.f = &enclosure_Cf_func,
                            .h1 = &enclosure_Ch1_func,
                            .h2 = &enclosure_Ch2_func,
                            .h3 = &enclosure_Ch3_func,
                            .h4 = &enclosure_Ch4_func};
  enclosures[Keyboard::C_sharp] = {.f = &enclosure_C_Sharpf_func,
                                  .h1 = &enclosure_C_sharph1_func,
                                  .h2 = &enclosure_C_sharph2_func,
                                  .h3 = &enclosure_C_sharph3_func, 
                                  .h4 = &enclosure_C_sharph4_func};



  freqs[Keyboard::C] = {.f = 131.8359,
                        .h1 = 266.6016,
                        .h2 = 401.3672,
                        .h3 = 536.1328,
                        .h4 = 670.8984};
  freqs[Keyboard::C_sharp] = {.f = 137.6953,
                              .h1 = 278.3203,
                              .h2 = 418.9453, 
                              .h3 = 559.5703,
                              .h4 = 700.1953};



  // setup piano and copy it to the global instance
  Keyboard piano_setup(freqs, enclosures);
  piano = piano_setup;

  // setup I2C things
  Wire.begin();
  Wire.setClock(100000);
  Serial.println("finished initailization");

  // initialize GPIO pins for DAC
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // read from keys 0 - 7
  unsigned char data;
  Wire.requestFrom(IO_EXPANDER_1, 1);
  while(Wire.available())
  {
    data = Wire.read();
  }
  for(int i = 0; i < 8; i++)
  {
    curr_buttons[i] = ((data >> i) & 1);
  }

  // read from keys 8 - 15
  Wire.requestFrom(IO_EXPANDER_2, 1);
  while(Wire.available())
  {
    data = Wire.read();
  }
  for(int i = 0; i < 8; i++)
  {
    curr_buttons[i+8] = ((data >> i) & 1);
  }

  // read from keys 16 - 23
  Wire.requestFrom(IO_EXPANDER_3, 1);
  while(Wire.available())
  {
    data = Wire.read();
  }
  for(int i = 0; i < 8; i++)
  {
    curr_buttons[i+16] = ((data >> i) & 1);
  }


  for(int i = 0; i < NUM_OF_KEYS; i++)
  {
    // check if a new key has been pressed
    if(curr_buttons[i] == true && last_buttons[i] == false)
    {
      new_button_pressed.push_back((Keyboard::note_t)i);
    }
    // check if a key has been depressed
    if(curr_buttons[i] == false && last_buttons[i] == true)
    {
      new_button_depressed.push_back((Keyboard::note_t)i);
    }
    // update last button array
    last_buttons[i] = curr_buttons[i];
  }

  // press and depress keys accordingly
  piano.press(new_button_pressed);
  piano.depress(new_button_depressed);

  // get sound from piano
  double sound = piano.get_sound();

  // TODO:remove
  Serial.println("sound = %f", sound);

  // cast sound to a uint8_t (unsigned char)
  // sound is bounded between [-1, 1] 
  // add 1 to get bounds between [0, 2]
  // multiply by 128.0 to get bounds between [0, 256]
  // cast to unsigned char to get 8 bits to send to DAC
  unsigned char to_dac = (unsigned char) ((sound + 1) * 128.0)

  // send to DAC via pins
  for(int pin = 0; pin < 8; pin++)
  {
    digitalWrite(pin + 5, ((to_dac >> pin) & 0x1))
  }
  
}
