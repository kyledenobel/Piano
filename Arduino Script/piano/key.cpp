#include "key.hpp"
#include <cmath>
#ifdef ARDUINO_PIANO
#include "arduino.h"
#endif

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// dummy function used for key initialization
double dummy(double t) {return 1.0;};

Key::Key(double f, double h1, double h2, double h3, double h4) :
    fundamental(f), harmonic1(h1), harmonic2(h2), harmonic3(h3), harmonic4(h4)
{
    fundamental_enclosure = &dummy;
    harmonic1_enclosure = &dummy;
    harmonic2_enclosure = &dummy;
    harmonic3_enclosure = &dummy;
    harmonic4_enclosure = &dummy;
}

double Key::get_curr_value(const double t)
{
    double f = (std::cos(2.0*M_PI*fundamental*t)) * (fundamental_enclosure(t));
    double h1 = (std::cos(2.0*M_PI*harmonic1*t) * harmonic1_enclosure(t));
    double h2 = (std::cos(2.0*M_PI*harmonic2*t) * harmonic2_enclosure(t));
    double h3 = (std::cos(2.0*M_PI*harmonic3*t) * harmonic3_enclosure(t));
    double h4 = (std::cos(2.0*M_PI*harmonic4*t) * harmonic4_enclosure(t));

    return (1.0/5.0) * (f + h1 + h2 + h3 + h4);
}

void Key::set_enclosure(const enclosure enclosure, const enclosure_selection_t selection)
{
    switch (selection)
    {
    case FUNDAMENTAL:
        fundamental_enclosure = enclosure;
        break;
    case HARMONIC1:
        harmonic1_enclosure = enclosure;
        break;
    case HARMONIC2:
        harmonic2_enclosure = enclosure;
        break;
    case HARMONIC3:
        harmonic3_enclosure = enclosure;
        break;
    case HARMONIC4:
        harmonic4_enclosure = enclosure;
        break;
    default:
        break;
    }
}

double Key::get_fundamental()
{
    return fundamental;
}