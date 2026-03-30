/**
 * @author: Kyle de Nobel
 * 
 * @brief: Testing of the Key class. Dumps the current value into a piano.txt file.
 *          This piano.txt file is read by test.py to visualize what is happening.
 * 
 * @date: 3/18/2026
 */


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "key.hpp"
#include "keyboard.hpp"
#include "enclosure_funcs.hpp"

#define NUM_OF_KEYS 24

using namespace std;


unsigned int global_time = 0;


int main()
{
    // arrays for initializing keyboard
    Keyboard::freqs_t freqs[NUM_OF_KEYS] = {0};
    Keyboard::note_enclosures_t enclosures[NUM_OF_KEYS];

    // value of daisy::GPIO pins on the last loop iteration
    bool last_press[NUM_OF_KEYS] = {0};

    // array of newly pressed keys
    vector<Keyboard::note_t> new_press;
    new_press.reserve(NUM_OF_KEYS);

    // array of newly depressed keys
    vector<Keyboard::note_t> new_depress;
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
                                    .h3 = &null_freq, 
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
                                    .h4 = &null_freq};
                                    
    enclosures[Keyboard::B_O] = {.f = &enclosure_B_Of_func,
                                    .h1 = &enclosure_B_Oh1_func,
                                    .h2 = &enclosure_B_Oh2_func,
                                    .h3 = &enclosure_B_Oh3_func, 
                                    .h4 = &enclosure_B_Oh4_func};



    freqs[Keyboard::C] = {.f = 131.8359,
                            .h1 = 266.6016,
                            .h2 = 401.3672,
                            .h3 = 536.1328,
                            .h4 = 670.8984};

    freqs[Keyboard::C_Sharp] = {.f = 137.6953,
                                .h1 = 278.3203,
                                .h2 = 418.9453, 
                                .h3 = 559.5703,
                                .h4 = 700.1953};

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

    freqs[Keyboard::G] = {.f = 196.2891,
                          .h1 = 395.5078,
                          .h2 = 594.7266,
                          .h3 = 793.9453,
                          .h4 = 993.1641};

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


    // // Set the onboard LED
    // hardware.SetLed(led_state);
    // // Toggle the LED state for the next time around.
    // led_state = !led_state;

    // loop variables
    bool pin_val;
    double piano_val;
    uint8_t dac_val = 0;

    double time_max = 3;
    double step_size = 0.0001;
    int length = time_max/step_size;
    double output[length];

    bool pressed = false;

    // Loop forever
    for(int t = 0; t < length; t++)
    {
        global_time = static_cast<unsigned int>(t);
        if((!pressed) && (static_cast<double>(t)*step_size) > 0.1)
        {
            pressed = true;
            piano.press(Keyboard::note_t::C);
            // new_press.push_back(Keyboard::note_t::C);
            cout << "hit" << endl;
        }
        

        // pass new press array to keyboard to signal a press
        // piano.press(new_press);
        // piano.depress(new_depress);

        // clear new press and new depress vectors
        new_press.clear();
        new_depress.clear();

        // get new value from piano
        piano_val = piano.get_sound();
        // convert double to uint8_t
        dac_val = static_cast<uint8_t>(((piano_val) + 1.0)*128.0);
        // change dac
        output[t] = dac_val;
    }

    fstream file;
    file.open("piano.txt", std::ios_base::openmode::_S_out);
    for(int i = 0; i < length; i++) {
        file << output[i] << endl;
    }
    file.close();

    return 0;
}