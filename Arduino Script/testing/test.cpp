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

#include "../piano/key.hpp"
#include "../piano/keyboard.hpp"


using namespace std;

void visualize(double* arr, int length);


double e1(double t)
{
    return pow((t+1.1), 20);
}

int main()
{

    Key k1(100.0, 200.0, 400.0, 800.0, 1600.0);

    k1.set_enclosure(&e1, Key::HARMONIC4);

    double time_max = 0.04;
    double step_size = 0.000001;
    int length = time_max/step_size;
    double arr[length];

    for(int t = 0; t < length; t++)
    {
        arr[t] = k1.get_curr_value(static_cast<double>(t)*step_size);
    }

    //visualize(arr, length);

    fstream file;
    file.open("piano.txt", std::ios_base::openmode::_S_out);
    for(int i = 0; i < length; i++) {
        file << arr[i] << endl;
    }
    file.close();
    

    return 0;
}


void visualize(double* arr, int length)
{
    std::string str = "";
    for(unsigned int j = 0; j < length; j++) {
        for(unsigned char i = 0; i < (arr[j]*20.0); i++) {
            str += '*';
        }
        std::cout << str << std::endl;
        str = "";
    }
}
