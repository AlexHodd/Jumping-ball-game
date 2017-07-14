#include "Goomba.h"

#include "Terrain.h"

Goomba::Goomba(const Sprite &_sprite, float2 _position, float _orientation)
    : Entity(_sprite, _position, _orientation),
    movingDir(0)
{
    sprite.play();
}

Goomba::~Goomba()
{
    //dtor
}

void Goomba::update()
{
    velocity = float2( (float)movingDir*.04f, -.2f );
    position += velocity;

    float2 coll( Terrain::get().collisionWith('#',
        position, float2(.5f, .5f)) );
    position += coll;
    if (coll.x!=0) movingDir = -movingDir;
    sprite.update();
}
