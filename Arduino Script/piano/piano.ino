/*


DAC
https://www.analog.com/media/en/technical-documentation/data-sheets/dac08.pdf 


IO Expander
https://www.ti.com/lit/ds/symlink/pcf8574.pdf

*/


#define ARDUINO_PIANO

#include "key.hpp"
#include "keyboard.hpp"
#include <vector>

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



  // setup piano and copy it to the global instance
  Keyboard piano_setup(freqs, enclosures);
  piano = piano_setup;

  // setup I2C things
  Wire.begin();
  Wire.setClock(100000);
  Serial.println("finished initailization");
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

  // cast sound to a 
  
  

}
