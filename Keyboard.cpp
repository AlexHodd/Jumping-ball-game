#include "Keyboard.h"

bool Keyboard::keys[128];

Keyboard::Keyboard()
{
    for (int i=0; i<128; ++i)
        keys[i] = false;
}

void Keyboard::keyb(unsigned char k , bool v)
{
    keys[k] = v;
}

bool Keyboard::pressed(unsigned char k)
{
    if (k>='A' && k<='Z')
        k+=32;
    return keys[k];
}
