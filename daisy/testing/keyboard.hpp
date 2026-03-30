#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "key.hpp"
#include <vector>
#include <unordered_map>

class Keyboard {
public:
    typedef enum {
        C = 0,
        C_Sharp = 1,
        D = 2,
        D_Sharp = 3,
        E = 4,
        F = 5,
        F_Sharp = 6,
        G = 7,
        G_Sharp = 8,
        A = 9,
        A_Sharp = 10,
        B = 11,
        C_O = 12,
        C_Sharp_O = 13,
        D_O = 14,
        D_Sharp_O = 15,
        E_O = 16,
        F_O = 17,
        F_Sharp_O = 18,
        G_O = 19,
        G_Sharp_O = 20,
        A_O = 21,
        A_Sharp_O = 22,
        B_O = 23
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
     * @brief press a single or multiple keys on a keyboard
     * @param[in] notes pointer to a note array
     */
    void press(const note_t notes);

    /**
     * @brief depresses a key
     * @param[in] notes pointer to a note array
     */
    void depress(const note_t notes);

    /**
     * @brief gets the magnitude of the sum of all of the pressed notes
     * @return normalized sound wave between -1 and 1
    */
    double get_sound();

    /**
    * @brief returns all of the keys
    */
    std::unordered_map<note_t, Key> get_keys();

private:
    // map to hold all of the keys
    std::unordered_map<note_t, Key> keys;
    // keeps track of time when the key was pressed
    std::unordered_map<note_t, uint32_t> key_press_time;
    // keeps track of pressed keys
    std::unordered_map<note_t, Key*> pressed_keys;
    // the current number of active keys pressed
    unsigned int num_active_keys;
};


#endif