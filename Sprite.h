#ifndef SPRITE_H
#define SPRITE_H

#include "float2.hpp"

class Texture2D;

class Sprite
{
    public:
        Sprite(Texture2D *, int = 1, float = 24.f);
        ~Sprite() {}

        void update();
        void draw(float2 = float2(), float = 0.f, float = 1.f);

        void play(int =0, int =-1);
        void resume() { state = PLAYING; }
        void pause() { state = PAUSED; }
    protected:
        Texture2D *texture;
        int frameCount, rangeStart, rangeEnd;
        float currentFrame;
        enum { PAUSED, PLAYING } state;
        float fps;
        unsigned int lastTime;
    private:
};

#endif // SPRITE_H
