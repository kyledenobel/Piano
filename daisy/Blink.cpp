#include "libDaisy/src/daisy_seed.h"
#include "libDaisy/src/daisy.h"
#include "key.hpp"
#include "keyboard.hpp"
#include "enclosure_funcs.hpp"

#define NUM_OF_KEYS 24


// Use the daisy namespace to prevent having to type
// daisy:: before all libdaisy functions
using namespace daisy;

// Declare a DaisySeed object called hardware
daisy::DaisySeed hardware;

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
    daisy::GPIO* gpio_arr[NUM_OF_KEYS] = {NULL};

    // value of daisy::GPIO pins on the last loop iteration
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

    enclosures[Keyboard::C_Sharp] = {.f = &enclosure_C_Sharpf_func,
                                    .h1 = &enclosure_C_Sharph1_func,
                                    .h2 = &enclosure_C_Sharph2_func,
                                    .h3 = &enclosure_C_Sharph3_func, 
                                    .h4 = &enclosure_C_Sharph4_func};

    enclosures[Keyboard::D] = {.f = &enclosure_Df_func,
                                    .h1 = &enclosure_Dh1_func,
                                    .h2 = &enclosure_Dh2_func,
                                    .h3 = &enclosure_Dh3_func, 
                                    .h4 = &enclosure_Dh4_func};

    enclosures[Keyboard::D_Sharp] = {.f = &enclosure_D_Sharpf_func,
                                    .h1 = &enclosure_D_Sharph1_func,
                                    .h2 = &enclosure_D_Sharph2_func,
                                    .h3 = &enclosure_D_Sharph3_func, 
                                    .h4 = &enclosure_D_Sharph4_func};


    enclosures[Keyboard::E] = {.f = &enclosure_Ef_func,
                                    .h1 = &enclosure_Eh1_func,
                                    .h2 = &enclosure_Eh2_func,
                                    .h3 = &enclosure_Eh3_func, 
                                    .h4 = &enclosure_Eh4_func};

    enclosures[Keyboard::F] = {.f = &enclosure_Ff_func,
                                    .h1 = &enclosure_Fh1_func,
                                    .h2 = &enclosure_Fh2_func,
                                    .h3 = &enclosure_Fh3_func, 
                                    .h4 = &enclosure_Fh4_func};

    enclosures[Keyboard::F_Sharp] = {.f = &enclosure_F_Sharpf_func,
                                    .h1 = &enclosure_F_Sharph1_func,
                                    .h2 = &enclosure_F_Sharph2_func,
                                    .h3 = &enclosure_F_Sharph3_func, 
                                    .h4 = &enclosure_F_Sharph4_func};
                                    
    enclosures[Keyboard::G] = {.f = &enclosure_Gf_func,
                                    .h1 = &enclosure_Gh1_func,
                                    .h2 = &enclosure_Gh2_func,
                                    .h3 = &enclosure_Gh3_func, 
                                    .h4 = &enclosure_Gh4_func};

    enclosures[Keyboard::G_Sharp] = {.f = &enclosure_G_Sharpf_func,
                                    .h1 = &enclosure_G_Sharph1_func,
                                    .h2 = &enclosure_G_Sharph2_func,
                                    .h3 = &enclosure_G_Sharph3_func, 
                                    .h4 = &enclosure_G_Sharph4_func};

    enclosures[Keyboard::A] = {.f = &enclosure_Af_func,
                                    .h1 = &enclosure_Ah1_func,
                                    .h2 = &enclosure_Ah2_func,
                                    .h3 = &enclosure_Ah3_func, 
                                    .h4 = &enclosure_Ah4_func};

    enclosures[Keyboard::A_Sharp] = {.f = &enclosure_A_Sharpf_func,
                                    .h1 = &enclosure_A_Sharph1_func,
                                    .h2 = &enclosure_A_Sharph2_func,
                                    .h3 = &enclosure_A_Sharph3_func, 
                                    .h4 = &enclosure_A_Sharph4_func};
                                    
    enclosures[Keyboard::B] = {.f = &enclosure_Bf_func,
                                    .h1 = &enclosure_Bh1_func,
                                    .h2 = &enclosure_Bh2_func,
                                    .h3 = &enclosure_Bh3_func, 
                                    .h4 = &enclosure_Bh4_func};

    enclosures[Keyboard::C_O] = {.f = &enclosure_C_Of_func,
                                    .h1 = &enclosure_C_Oh1_func,
                                    .h2 = &enclosure_C_Oh2_func,
                                    .h3 = &enclosure_C_Oh3_func, 
                                    .h4 = &enclosure_C_Oh4_func};

    enclosures[Keyboard::C_Sharp_O] = {.f = &enclosure_C_O_Sharpf_func,
                                    .h1 = &enclosure_C_O_Sharph1_func,
                                    .h2 = &enclosure_C_O_Sharph2_func,
                                    .h3 = &enclosure_C_O_Sharph3_func, 
                                    .h4 = &enclosure_C_O_Sharph4_func};

    enclosures[Keyboard::D_O] = {.f = &enclosure_D_Of_func,
                                    .h1 = &enclosure_D_Oh1_func,
                                    .h2 = &enclosure_D_Oh2_func,
                                    .h3 = &enclosure_D_Oh3_func, 
                                    .h4 = &enclosure_D_Oh4_func};

    enclosures[Keyboard::D_Sharp_O] = {.f = &enclosure_D_O_Sharpf_func,
                                    .h1 = &enclosure_D_O_Sharph1_func,
                                    .h2 = &enclosure_D_O_Sharph2_func,
                                    .h3 = &enclosure_D_O_Sharph3_func, 
                                    .h4 = &enclosure_D_O_Sharph4_func};


    enclosures[Keyboard::E_O] = {.f = &enclosure_E_Of_func,
                                    .h1 = &enclosure_E_Oh1_func,
                                    .h2 = &enclosure_E_Oh2_func,
                                    .h3 = &enclosure_E_Oh3_func, 
                                    .h4 = &enclosure_E_Oh4_func};

    enclosures[Keyboard::F_O] = {.f = &enclosure_F_Of_func,
                                    .h1 = &enclosure_F_Oh1_func,
                                    .h2 = &enclosure_F_Oh2_func,
                                    .h3 = &enclosure_F_Oh3_func, 
                                    .h4 = &enclosure_F_Oh4_func};

    enclosures[Keyboard::F_Sharp_O] = {.f = &enclosure_F_O_Sharpf_func,
                                    .h1 = &enclosure_F_O_Sharph1_func,
                                    .h2 = &enclosure_F_O_Sharph2_func,
                                    .h3 = &enclosure_F_O_Sharph3_func, 
                                    .h4 = &enclosure_F_O_Sharph4_func};
                                    
    enclosures[Keyboard::G_O] = {.f = &enclosure_G_Of_func,
                                    .h1 = &enclosure_G_Oh1_func,
                                    .h2 = &enclosure_G_Oh2_func,
                                    .h3 = &enclosure_G_Oh3_func, 
                                    .h4 = &enclosure_G_Oh4_func};

    enclosures[Keyboard::G_Sharp_O] = {.f = &enclosure_G_O_Sharpf_func,
                                    .h1 = &enclosure_G_O_Sharph1_func,
                                    .h2 = &enclosure_G_O_Sharph2_func,
                                    .h3 = &enclosure_G_O_Sharph3_func, 
                                    .h4 = &enclosure_G_O_Sharph4_func};

    enclosures[Keyboard::A_O] = {.f = &enclosure_A_Of_func,
                                    .h1 = &enclosure_A_Oh1_func,
                                    .h2 = &enclosure_A_Oh2_func,
                                    .h3 = &enclosure_A_Oh3_func, 
                                    .h4 = &enclosure_A_Oh4_func};

    enclosures[Keyboard::A_Sharp_O] = {.f = &enclosure_A_O_Sharpf_func,
                                    .h1 = &enclosure_A_O_Sharph1_func,
                                    .h2 = &enclosure_A_O_Sharph2_func,
                                    .h3 = &enclosure_A_O_Sharph3_func, 
                                    .h4 = &enclosure_A_O_Sharph4_func};
                                    
    enclosures[Keyboard::B_O] = {.f = &enclosure_B_Of_func,
                                    .h1 = &enclosure_B_Oh1_func,
                                    .h2 = &enclosure_B_Oh2_func,
                                    .h3 = &enclosure_B_Oh3_func, 
                                    .h4 = &enclosure_B_Oh4_func};



    freqs[Keyboard::C] = {.f = 1.318359375000000e+02,
                            .h1 = 2.607421875000000e+02,
                            .h2 = 3.925781250000000e+02,
                            .h3 = 5.214843750000000e+02,
                            .h4 = 9.140625000000000e+02};

    freqs[Keyboard::C_Sharp] = {.f = 1.376953125000000e+02,
                                .h1 = 2.753906250000000e+02,
                                .h2 = 4.160156250000000e+02, 
                                .h3 = 5.537109375000000e+02,
                                .h4 = 9.697265625000000e+02};

    freqs[Keyboard::D] = {.f = 1.464843750000000e+02,
                            .h1 =2.929687500000000e+02,
                            .h2 = 4.394531250000000e+02,
                            .h3 = 5.859375000000000e+02,
                            .h4 = 8.818359375000000e+02};

    freqs[Keyboard::D_Sharp] = {.f = 1.552734375000000e+02,
                            .h1 = 3.105468750000000e+02,
                            .h2 = 4.658203125000000e+02,
                            .h3 = 6.210937500000000e+02,
                            .h4 = 7.763671875000000e+02};

    freqs[Keyboard::E] = {.f = 1.640625000000000e+02,
                            .h1 = 3.281250000000000e+02,
                            .h2 = 4.951171875000000e+02,
                            .h3 = 9.902343750000000e+02,
                            .h4 = 1.154296875000000e+03};

    freqs[Keyboard::F] = {.f = 1.728515625000000e+02,
                            .h1 = 3.486328125000000e+02,
                            .h2 = 5.244140625000000e+02,
                            .h3 = 6.972656250000000e+02,
                            .h4 = 1.224609375000000e+03};

    freqs[Keyboard::F_Sharp] = {.f = 1.845703125000000e+02,
                            .h1 = 3.691406250000000e+02,
                            .h2 = 5.537109375000000e+02,
                            .h3 = 9.257812500000000e+02,
                            .h4 = 1.297851562500000e+03};                                                            

    freqs[Keyboard::G] = {.f = 1.962890625000000e+02,
                          .h1 = 3.925781250000000e+02,
                          .h2 = 5.888671875000000e+02,
                          .h3 = 7.851562500000000e+02,
                          .h4 = 9.814453125000000e+02};

    freqs[Keyboard::G_Sharp] = {.f = 2.080078125000000e+02,
                                .h1 = 4.160156250000000e+02,
                                .h2 = 6.240234375000000e+02,
                                .h3 = 8.320312500000000e+02,
                                .h4 = 1.040039062500000e+03};

    freqs[Keyboard::A] = {.f = 2.197265625000000e+02,
                        .h1 = 4.423828125000000e+02,
                        .h2 = 6.650390625000000e+02,
                        .h3 = 8.876953125000000e+02,
                        .h4 = 110351562500000e+03};

    freqs[Keyboard::A_Sharp] = {.f = 2.343750000000000e+02,
                            .h1 = 4.658203125000000e+02,
                            .h2 = 7.001953125000000e+02,
                            .h3 = 9.316406250000000e+02,
                            .h4 = 1.166015625000000e+03};

    freqs[Keyboard::B] = {.f = 2.460937500000000e+02,
                            .h1 = 4.921875000000000e+02,
                            .h2 = 7.412109375000000e+02,
                            .h3 = 9.873046875000000e+02,
                            .h4 = 1.236328125000000e+03};

    freqs[Keyboard::C_O] = {.f = 2.607421875000000e+02,
                            .h1 = 5.214843750000000e+02,
                            .h2 = 7.851562500000000e+02,
                            .h3 = 1.048828125000000e+03,
                            .h4 = 1.312500000000000e+03};

    freqs[Keyboard::C_Sharp_O] = {.f = 2.753906250000000e+02,
                            .h1 = 5.537109375000000e+02,
                            .h2 = 1.954101562500000e+03,
                            .h3 = 2.238281250000000e+03,
                            .h4 = 2.525390625000000e+03};

    freqs[Keyboard::D_O] = {.f = 2.929687500000000e+02,
                            .h1 = 5.859375000000000e+02,
                            .h2 = 8.818359375000000e+02,
                            .h3 = 1.473632812500000e+03,
                            .h4 = 1.772460937500000e+03};

    freqs[Keyboard::D_Sharp_O] = {.f = 3.105468750000000e+02,
                            .h1 = 6.210937500000000e+02,
                            .h2 = 9.345703125000000e+02,
                            .h3 = 1.248046875000000e+03,
                            .h4 = 1.561523437500000e+03};

    freqs[Keyboard::E_O] = {.f = 3.281250000000000e+02,
                            .h1 = 9.902343750000000e+02,
                            .h2 = 1.321289062500000e+03,
                            .h3 = 1.655273437500000e+03,
                            .h4 = 2.329101562500000e+03};

    freqs[Keyboard::F_O] = {.f = 3.486328125000000e+02,
                            .h1 = 6.972656250000000e+02,
                            .h2 = 1.048828125000000e+03,
                            .h3 = 1.400390625000000e+03,
                            .h4 = 1.754882812500000e+03};

    freqs[Keyboard::F_Sharp_O] = {.f = 3.691406250000000e+02,
                            .h1 = 7.412109375000000e+02,
                            .h2 = 1.110351562500000e+03,
                            .h3 = 1.860351562500000e+03,
                            .h4 = 2.238281250000000e+03};                                                            

    freqs[Keyboard::G_O] = {.f = 3.925781250000000e+02,
                          .h1 = 7.851562500000000e+02,
                          .h2 = 1.177734375000000e+03,
                          .h3 = 1.971679687500000e+03,
                          .h4 = 2.373046875000000e+03};

//null it 
    freqs[Keyboard::G_Sharp_O] = {.f = 4.160156250000000e+02,
                                .h1 = 8.320312500000000e+02,
                                .h2 = 1.248046875000000e+03,
                                .h3 = 0,
                                .h4 = 2.088867187500000e+03};

    freqs[Keyboard::A_O] = {.f = 4.394531250000000e+02,
                        .h1 = 8.818359375000000e+02,
                        .h2 = 1.324218750000000e+03,
                        .h3 = 1.769531250000000e+03,
                        .h4 = 2.217773437500000e+03};

//null it
    freqs[Keyboard::A_Sharp_O] = {.f = 4.658203125000000e+02,
                            .h1 = 9.345703125000000e+02,
                            .h2 = 1.400390625000000e+03,
                            .h3 = 1875,
                            .h4 = 0};  
                                                 
    freqs[Keyboard::B_O] = {.f = 4.951171875000000e+02,
                            .h1 = 9.902343750000000e+02,
                            .h2 = 1.485351562500000e+03,
                            .h3 = 1.986328125000000e+03,
                            .h4 = 2.493164062500000e+03}; 
                                           

    // init keyboard
    Keyboard piano(freqs, enclosures);

    // init buttons
    daisy::GPIO C = daisy::GPIO();            // D0
    daisy::GPIO C_Sharp = daisy::GPIO();      // D1
    daisy::GPIO D = daisy::GPIO();            // D2
    daisy::GPIO D_Sharp = daisy::GPIO();      // D3
    daisy::GPIO E = daisy::GPIO();            // D4
    daisy::GPIO F = daisy::GPIO();            // D5
    daisy::GPIO F_Sharp = daisy::GPIO();      // D6
    daisy::GPIO G = daisy::GPIO();            // D7
    daisy::GPIO G_Sharp = daisy::GPIO();      // D8
    daisy::GPIO A = daisy::GPIO();            // D9
    daisy::GPIO A_Sharp = daisy::GPIO();      // D10
    daisy::GPIO B = daisy::GPIO();            // D11

    daisy::GPIO C_O = daisy::GPIO();          // D12
    daisy::GPIO C_Sharp_O = daisy::GPIO();    // D13
    daisy::GPIO D_O = daisy::GPIO();          // D14
    daisy::GPIO D_Sharp_O = daisy::GPIO();    // D15
    daisy::GPIO E_O = daisy::GPIO();          // D16
    daisy::GPIO F_O = daisy::GPIO();          // D17
    daisy::GPIO F_Sharp_O = daisy::GPIO();    // D18
    daisy::GPIO G_O = daisy::GPIO();          // D19
    daisy::GPIO G_Sharp_O = daisy::GPIO();    // D20
    daisy::GPIO A_O = daisy::GPIO();          // D21
    daisy::GPIO A_Sharp_O = daisy::GPIO();    // D26
    daisy::GPIO B_O = daisy::GPIO();          // D27

    
    // add all daisy::GPIO pins to daisy::GPIO arr
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


    // config all daisy::GPIO pins that will be used
    daisy::GPIO::Config gpio_cfg = daisy::GPIO::Config();
    gpio_cfg.mode = daisy::GPIO::Mode::INPUT;
    gpio_cfg.pull = daisy::GPIO::Pull::PULLUP;
    gpio_cfg.speed = daisy::GPIO::Speed::HIGH;
    daisy::Pin gpio_pin = daisy::Pin();

    // C
    gpio_pin.pin = 12;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C.Init(gpio_cfg);

    // C#
    gpio_pin.pin = 11;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    C_Sharp.Init(gpio_cfg);

    // D
    gpio_pin.pin = 10;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D.Init(gpio_cfg);

    // D#
    gpio_pin.pin = 9;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D_Sharp.Init(gpio_cfg);

    // E
    gpio_pin.pin = 8;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    E.Init(gpio_cfg);

    // F
    gpio_pin.pin = 2;
    gpio_pin.port = daisy::GPIOPort::PORTD;
    gpio_cfg.pin = gpio_pin;
    F.Init(gpio_cfg);

    // F#
    gpio_pin.pin = 12;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    F_Sharp.Init(gpio_cfg);

    // G
    gpio_pin.pin = 10;
    gpio_pin.port = daisy::GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    G.Init(gpio_cfg);

    // G#
    gpio_pin.pin = 11;
    gpio_pin.port = daisy::GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    G_Sharp.Init(gpio_cfg);

    // A
    gpio_pin.pin = 4;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    A.Init(gpio_cfg);

    // A#
    gpio_pin.pin = 5;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    A_Sharp.Init(gpio_cfg);

    // B
    gpio_pin.pin = 8;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    B.Init(gpio_cfg);

    // C O
    gpio_pin.pin = 9;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C_O.Init(gpio_cfg);

    // C# O
    gpio_pin.pin = 6;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    C_Sharp_O.Init(gpio_cfg);

    // D O
    gpio_pin.pin = 7;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    D_O.Init(gpio_cfg);

    // D# O
    gpio_pin.pin = 0;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    D_Sharp_O.Init(gpio_cfg);

    // E O
    gpio_pin.pin = 3;
    gpio_pin.port = daisy::GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    E_O.Init(gpio_cfg);

    // F O
    gpio_pin.pin = 1;
    gpio_pin.port = daisy::GPIOPort::PORTB;
    gpio_cfg.pin = gpio_pin;
    F_O.Init(gpio_cfg);

    // F# O
    gpio_pin.pin = 7;
    gpio_pin.port = daisy::GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    F_Sharp_O.Init(gpio_cfg);

    // G O
    gpio_pin.pin = 6;
    gpio_pin.port = daisy::GPIOPort::PORTA;
    gpio_cfg.pin = gpio_pin;
    G_O.Init(gpio_cfg);

    // G# O
    gpio_pin.pin = 11;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    G_Sharp_O.Init(gpio_cfg);

    // A O
    gpio_pin.pin = 4;
    gpio_pin.port = daisy::GPIOPort::PORTC;
    gpio_cfg.pin = gpio_pin;
    A_O.Init(gpio_cfg);

    // A# O
    gpio_pin.pin = 11;
    gpio_pin.port = daisy::GPIOPort::PORTD;
    gpio_cfg.pin = gpio_pin;
    A_Sharp_O.Init(gpio_cfg);

    // B O
    gpio_pin.pin = 9;
    gpio_pin.port = daisy::GPIOPort::PORTG;
    gpio_cfg.pin = gpio_pin;
    B_O.Init(gpio_cfg);

    // Init DAC
    daisy::DacHandle dac = daisy::DacHandle();
    daisy::DacHandle::Config cfg = {.target_samplerate = 48000,
                             .chn = daisy::DacHandle::Channel::ONE,
                             .mode = daisy::DacHandle::Mode::POLLING,
                             .bitdepth = daisy::DacHandle::BitDepth::BITS_8,
                             .buff_state = daisy::DacHandle::BufferState::ENABLED};
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
        daisy::System::GetUs();
        if(!(C.Read()))
        {
            hardware.SetLed(true);
        }
        else
        {
            hardware.SetLed(false);
        }

        // check if a pin is low
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
            // read daisy::GPIO pin
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
