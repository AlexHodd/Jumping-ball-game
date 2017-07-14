#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity
{
    public:
        Coin(const Sprite &, float2, float);
        virtual ~Coin();
    protected:
    private:
};

#endif // COIN_H
