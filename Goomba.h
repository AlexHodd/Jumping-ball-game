#ifndef GOOMBA_H
#define GOOMBA_H

#include "Entity.h"

class Goomba : public Entity
{
    public:
        Goomba(const Sprite &, float2, float);
        virtual ~Goomba();

        void update();
    protected:
        int movingDir;
    private:
};

#endif // GOOMBA_H
