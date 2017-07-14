#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>

using std::vector;

#include "Sprite.h"

class Terrain
{
    public:
        static Terrain &get(void)
        {
            static Terrain instance;
            return instance;
        }
        void create(const char *);
        void load(const char *);
        void draw();
        void setViewSize(float2 _viewSize) { halfViewSize = _viewSize*.5f; }
        void setViewPos(float2 _viewPos);
        float2 collisionWith(char, float2, float2);
        float2 collisionWithNot(char, float2, float2);
    protected:
        Sprite tile[1];
        const char *fname;
        int sizeX, sizeY;
        char *tiles;
//        vector<float2> nonWalkable;
        float2 halfViewSize, viewPos;

        virtual ~Terrain();
        void die(int);
    private:
        Terrain();
        Terrain(Terrain const &);
        void operator=(Terrain const &);
};

#endif // TERRAIN_H
