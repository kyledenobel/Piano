#include "daisy_seed.h"
#include "libDaisy/src/per/dac.h"
#include "key.hpp"
#include "keyboard.hpp"
#include "enclosure_funcs.hpp"

#define NUM_OF_KEYS 24


// Use the daisy namespace to prevent having to type
// daisy:: before all libdaisy functions
using namespace daisy;

// Declare a DaisySeed object called hardware
DaisySeed hardware;

int main(void)
{
    // Declare a variable to store the state we want to set for the LED.
    bool led_state;
    led_state = true;

    // Configure and Initialize the Daisy Seed
    // These are separate to allow reconfiguration of any of the internal
    // components before initialization.
    hardware.Configure();
    hardware.Init();

    // arrays for initializing keyboard
    Keyboard::freqs_t freqs[NUM_OF_KEYS] = {0};
    Keyboard::note_enclosures_t enclosures[NUM_OF_KEYS];

    // array to hold all buttons
    GPIO* gpio_arr[NUM_OF_KEYS] = {NULL};

    // value of gpio pins on the last loop iteration
    bool last_press[NUM_OF_KEYS] = {0};

    // array of newly pressed keys
    std::vector<Keyboard::note_t> new_press;
    new_press.reserve(NUM_OF_KEYS);

    // array of newly depressed keys
    std::vector<Keyboard::note_t> new_depress;
    new_depress.reserve(NUM_OF_KEYS);

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


    freqs[Keyboard::G] = {.f = 196.2891,
                          .h1 = 395.5078,
                          .h2 = 594.7266,
                          .h3 = 793.9453,
                          .h4 = 993.1641};
    freqs[Keyboard::G_sharp] = {.f = 108.3984,
                                .h1 = 219.7266,
                                .h2 = 331.0547,
                                .h3 = 442.3828,
                                .h4 = 553.7109};
    freqs[Keyboard::A] = {.f = 2.197265625000000e+02,
                        .h1 = 4.423828125000000e+02,
                        .h2 = 6.650390625000000e+02,
                        .h3 = 8.876953125000000e+02,
                        .h4 = 110351562500000e+03};
    freqs[Keyboard::A_sharp] = {.f = max}

    // init keyboard
    Keyboard piano(freqs, enclosures);

    // init buttons
    GPIO C = GPIO();            // D0
    GPIO C_Sharp = GPIO();      // D1
    GPIO D = GPIO();            // D2
    GPIO D_Sharp = GPIO();      // D3
    GPIO E = GPIO();            // D4
    GPIO F = GPIO();            // D5
    GPIO F_Sharp = GPIO();      // D6
    GPIO G = GPIO();            // D7
    GPIO G_Sharp = GPIO();      // D8
    GPIO A = GPIO();            // D9
    GPIO A_Sharp = GPIO();      // D10
    GPIO B = GPIO();            // D11

    GPIO C_O = GPIO();          // D12
    GPIO C_Sharp_O = GPIO();    // D13
    GPIO D_O = GPIO();          // D14
    GPIO D_Sharp_O = GPIO();    // D15
    GPIO E_O = GPIO();          // D16
    GPIO F_O = GPIO();          // D17
    GPIO F_Sharp_O = GPIO();    // D18
    GPIO G_O = GPIO();          // D19
    GPIO G_Sharp_O = GPIO();    // D20
    GPIO A_O = GPIO();          // D21
    GPIO A_Sharp_O = GPIO();    // D26
    GPIO B_O = GPIO();          // D27

    
    // add all gpio pins to gpio arr
    gpio_arr[0] = &C;
    gpio_arr[1] = &C_Sharp;
    gpio_arr[2] = &D;
    gpio_arr[3] = &D_Sharp;
    gpio_arr[4] = &E;
    gpio_arr[5] = &F;
    gpio_arr[6] = &F_Sharp;
    gpio_arr[7] = &G;
    gpio_arr[8] = &G_Sharp;
    gpio_arr[9] = &A;
    gpio_arr[10] = &A_Sharp;
    gpio_arr[11] = &B;

    gpio_arr[12] = &C_O;
    gpio_arr[13] = &C_Sharp_O;
    gpio_arr[14] = &D_O;
    gpio_arr[15] = &D_Sharp_O;
    gpio_arr[16] = &E_O;
    gpio_arr[17] = &F_O;
    gpio_arr[18] = &F_Sharp_O;
    gpio_arr[19] = &G_O;
    gpio_arr[20] = &G_Sharp_O;
    gpio_arr[21] = &A_O;
    gpio_arr[22] = &A_Sharp_O;
    gpio_arr[23] = &B_O;


    // config all gpio pins that will be used
    GPIO::Config gpio_cfg = GPIO::Config();
    gpio_cfg.mode = GPIO::Mode::INPUT;
    gpio_cfg.pull = GPIO::Pull::PULLUP;
    gpio_cfg.speed = GPIO::Speed::HIGH;
    Pin gpio_pin = Pin();

    // C
    gpio_pin.pin = 12;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C.Init(gpio_cfg);

    // C#
    gpio_pin.pin = 11;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    C_Sharp.Init(gpio_cfg);

    // D
    gpio_pin.pin = 10;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D.Init(gpio_cfg);

    // D#
    gpio_pin.pin = 9;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D_Sharp.Init(gpio_cfg);

    // E
    gpio_pin.pin = 8;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    E.Init(gpio_cfg);

    // F
    gpio_pin.pin = 2;
    gpio_pin.port = GPIOPort::PORTD;
    gpio_cfg.pin = gpio_pin;
    F.Init(gpio_cfg);

    // F#
    gpio_pin.pin = 12;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    F_Sharp.Init(gpio_cfg);

    // G
    gpio_pin.pin = 10;
    gpio_pin.port = GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    G.Init(gpio_cfg);

    // G#
    gpio_pin.pin = 11;
    gpio_pin.port = GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    G_Sharp.Init(gpio_cfg);

    // A
    gpio_pin.pin = 4;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    A.Init(gpio_cfg);

    // A#
    gpio_pin.pin = 5;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    A_Sharp.Init(gpio_cfg);

    // B
    gpio_pin.pin = 8;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    B.Init(gpio_cfg);

    // C O
    gpio_pin.pin = 9;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C_O.Init(gpio_cfg);

    // C# O
    gpio_pin.pin = 6;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C_Sharp_O.Init(gpio_cfg);

    // D O
    gpio_pin.pin = 7;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    D_O.Init(gpio_cfg);

    // D# O
    gpio_pin.pin = 0;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D_Sharp_O.Init(gpio_cfg);

    // E O
    gpio_pin.pin = 3;
    gpio_pin.port = GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    E_O.Init(gpio_cfg);

    // F O
    gpio_pin.pin = 1;
    gpio_pin.port = GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    F_O.Init(gpio_cfg);

    // F# O
    gpio_pin.pin = 7;
    gpio_pin.port = GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    F_Sharp_O.Init(gpio_cfg);

    // G O
    gpio_pin.pin = 6;
    gpio_pin.port = GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    G_O.Init(gpio_cfg);

    // G# O
    gpio_pin.pin = 11;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    G_Sharp_O.Init(gpio_cfg);

    // A O
    gpio_pin.pin = 4;
    gpio_pin.port = GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    A_O.Init(gpio_cfg);

    // A# O
    gpio_pin.pin = 11;
    gpio_pin.port = GPIOPort::PORTD;
    gpio_cfg.pin = gpio_pin;
    A_Sharp_O.Init(gpio_cfg);

    // B O
    gpio_pin.pin = 9;
    gpio_pin.port = GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    B_O.Init(gpio_cfg);

    // Init DAC
    DacHandle dac = DacHandle();
    DacHandle::Config cfg = {.target_samplerate = 48000,
                             .chn = DacHandle::Channel::ONE,
                             .mode = DacHandle::Mode::POLLING,
                             .bitdepth = DacHandle::BitDepth::BITS_8,
                             .buff_state = DacHandle::BufferState::ENABLED};
    dac.Init(cfg);          // DAC OUT 1

    // init last press array
    for(int i = 0; i < NUM_OF_KEYS; i++)
    {
        last_press[i] = (gpio_arr[i])->Read();
    }







    // // Set the onboard LED
    // hardware.SetLed(led_state);
    // // Toggle the LED state for the next time around.
    // led_state = !led_state;

    // loop variables
    bool pin_val;
    double piano_val;
    uint8_t dac_val;


    // Loop forever
    for(;;)
    {
        System::GetUs();

        // check if a pin is low
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
            // read gpio pin
            pin_val = gpio_arr[i]->Read();

            // check if pin is low (it is pressed)
            if(!pin_val)
            {
                // check if key was already pressed
                if(last_press[i] != pin_val)
                {
                    // new press, add to array of pressed pins
                    new_press.push_back((Keyboard::note_t) i);
                }
            }

            // check if pin is high (it is not pressed)
            else
            {
                // check if key was already depressed
                if(last_press[i] != pin_val)
                {
                    // new depress, add to array of depressed pins
                    new_depress.push_back((Keyboard::note_t) i);
                }
            }

            // update last press array
            last_press[i] = pin_val;
        }

        // pass new press array to keyboard to signal a press
        piano.press(new_press);
        piano.depress(new_depress);

        // clear new press and new depress vectors
        new_press.clear();
        new_depress.clear();

        // get new value from piano
        piano_val = piano.get_sound();
        // convert double to uint8_t
        dac_val = static_cast<uint8_t>(((piano_val) + 1.0)*128.0);
        // change dac
        dac.WriteValue(daisy::DacHandle::Channel::ONE, dac_val);
    }
}
