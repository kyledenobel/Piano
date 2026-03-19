#ifndef KEY_HPP
#define KEY_HPP

/**
 * @brief Key class for a single piano key
 * @note fundamental and harmonics should be given in Hertz
 */
class Key {
public:
    // function handle for an enclosure of a frequency vs time. Input is elapsed time from the key press
    typedef double (*enclosure)(double);

    typedef enum {
        FUNDAMENTAL = 0,
        HARMONIC1 = 1,
        HARMONIC2 = 2,
        HARMONIC3 = 3,
        HARMONIC4 = 4,
    } enclosure_selection_t;

    Key(double f, double h1, double h2, double h3, double h4);

    /**
     * @brief gets the value of the combined fundamental and harmonics at elapsed time t from the key press
     * @param t the time elapsed since the key was pressed
     */
    double get_curr_value(const double t);

    /**
     * @brief sets the enclosure function of the fundamental or a harmonic
     * @param enclosure an enclosure function
     * @param selection the fundamental or harmonic to set the enclosure for
     */
    void set_enclosure(const enclosure enclosure, const enclosure_selection_t selection);

    double get_fundamental();

private:
    // fundamental frequency of the note
    double fundamental;
    // first harmonic frequency of the note
    double harmonic1;
    // second harmonic frequency of the note
    double harmonic2;
    // third harmonic frequency of the note
    double harmonic3;
    // fourth harmonic frequency of the note
    double harmonic4;

    // enclosure funtion handle for the fundamental frequency
    enclosure fundamental_enclosure;
    // enclosure funtion handle for the first harmonic
    enclosure harmonic1_enclosure;
    // enclosure funtion handle for the second harmonic
    enclosure harmonic2_enclosure;
    // enclosure funtion handle for the third harmonic
    enclosure harmonic3_enclosure;
    // enclosure funtion handle for the fourth harmonic
    enclosure harmonic4_enclosure;
};




#endif