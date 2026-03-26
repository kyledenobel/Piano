#include "key.hpp"
#include "keyboard.hpp"
#include <unordered_map>
#include <vector>
#include "daisy_seed.h"


Keyboard::Keyboard(freqs_t freqs[24], note_enclosures_t enclosures[24])
{
    unsigned long curr_time = daisy::System::GetUs();
    for(int i = Keyboard::note_t::C; i < Keyboard::note_t::B_O; i++)
    {
        keys.emplace(std::make_pair((Keyboard::note_t)i, Key(freqs[i].f, freqs[i].h1, freqs[i].h2, freqs[i].h3, freqs[i].h4)));
        keys.at((Keyboard::note_t)i).set_enclosure(enclosures[i].f, Key::FUNDAMENTAL);
        keys.at((Keyboard::note_t)i).set_enclosure(enclosures[i].h1, Key::HARMONIC1);
        keys.at((Keyboard::note_t)i).set_enclosure(enclosures[i].h2, Key::HARMONIC2);
        keys.at((Keyboard::note_t)i).set_enclosure(enclosures[i].h3, Key::HARMONIC3);
        keys.at((Keyboard::note_t)i).set_enclosure(enclosures[i].h4, Key::HARMONIC4);
        key_press_time.insert({(Keyboard::note_t)i, curr_time});
    }
    num_active_keys = 0;
}

Keyboard::Keyboard()
{
    num_active_keys = 0;
}

Keyboard::Keyboard(const Keyboard& board)
{
    this->key_press_time = board.key_press_time;
    this->keys = board.keys;
    this->num_active_keys = board.num_active_keys;
    this->pressed_keys = board.pressed_keys;
}


void Keyboard::press(const std::vector<note_t>& notes)
{
    unsigned long curr_time = daisy::System::GetUs();
    for(note_t note : notes)
    {
        pressed_keys.insert({note, &keys.at(note)});
        key_press_time.at(note) = curr_time;
    }
    num_active_keys++;
}

void Keyboard::depress(const std::vector<note_t>& notes)
{
    for(note_t note : notes)
    {
        pressed_keys.erase(note);
    }
    num_active_keys--;
}

double Keyboard::get_sound()
{
    double sound = 0.0;
    unsigned long curr_time = daisy::System::GetUs();
    double elapsed_time;
    note_t curr_note;
    for(auto iter = pressed_keys.begin(); iter != pressed_keys.end(); iter++)
    {
        curr_note = iter->first;
        elapsed_time = static_cast<double>(curr_time - key_press_time.at(curr_note)) / 0.000001;
        sound += iter->second->get_curr_value(elapsed_time);
    }
    // normalize
    sound = sound / static_cast<double>(num_active_keys);
    return sound;
}

std::unordered_map<Keyboard::note_t, Key> Keyboard::get_keys()
{
    return keys;
}