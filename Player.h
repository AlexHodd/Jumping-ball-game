#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "bass.h"
class Player : public Entity
{
    public:
        Player(const Sprite &, float2, float);
        virtual ~Player();

        virtual void update();
    protected:
        bool firePressed;
        int movingDir;
        bool jumpPressed;
        int jump;
        HSTREAM streamHandle;
    private:
};

#endif // PLAYER_H
