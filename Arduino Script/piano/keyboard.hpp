#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "key.hpp"
#include <vector>
#include <map>

class Keyboard {
public:
    typedef enum {
        C,
        C_sharp,
        D,
        D_sharp,
        E,
        F,
        F_sharp,
        G,
        G_sharp,
        A,
        A_sharp,
        B,
        C_O,
        C_sharp_O,
        D_O,
        D_sharp_O,
        E_O,
        F_O,
        F_sharp_O,
        G_O,
        G_sharp_O,
        A_O,
        A_sharp_O,
        B_O
    } note_t;

    /**
     * @brief the frequencies in a note
     */
    typedef struct {
        double f;
        double h1;
        double h2;
        double h3;
        double h4;
    } freqs_t;

    /**
     * @brief the enclosure for every frequency in a note
     */
    typedef struct {
        Key::enclosure f;
        Key::enclosure h1;
        Key::enclosure h2;
        Key::enclosure h3;
        Key::enclosure h4;
    } note_enclosures_t;

    /**
   * @brief constructor for a Keyboard object that initializes frequencies and enclosures
   * @param freqs array for freqs_t in order from C to B_O
   * @param enclosures array of enclosures in order from C to B_O
   */
    Keyboard(freqs_t freqs[24], note_enclosures_t enclosures[24]);

    /**
   * @brief default constructor for Keyboard object
   */
    Keyboard();

    /**
   * @brief copy constructor for Keyboard object
   */
    Keyboard(const Keyboard& board);

    /**
     * @brief plays a single or multiple keys on a keyboard
     * @param[in] notes pointer to a note array
     */
    void press(std::vector<note_t> notes);

    /**
     * @brief depresses a key
     * @param[in] notes pointer to a note array
     */
    void depress(std::vector<note_t> notes);

    /**
     * @brief gets the magnitude of the sum of all of the pressed notes
    */
    double get_sound();

    /**
    * @brief returns all of the keys
    */
    std::map<note_t, Key> get_keys();

private:
    // map to hold all of the keys
    std::map<note_t, Key> keys;
    // keeps track of time when the key was pressed
    std::map<note_t, unsigned long> key_press_time;
    // keeps track of pressed keys
    std::map<note_t, Key*> pressed_keys;
    // the current number of active keys pressed
    unsigned int num_active_keys;
};


#endif