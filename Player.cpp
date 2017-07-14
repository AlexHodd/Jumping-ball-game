#include <stdlib.h>

#include <iostream>

using std::cout;
using std::endl;

#include "Player.h"

#include "Keyboard.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Goomba.h"
#include "Coin.h"
#include "przepasc.h"
#include "bass.h"



Player::Player(const Sprite &_sprite, float2 _position, float _orientation)
    : Entity(_sprite, _position, _orientation),
      firePressed(false),
      movingDir(0), jumpPressed(false), jump(0)
{
    sprite.play(0,0);
}

Player::~Player()
{
}

void Player::update()
{
    Entity *e = collisionWith<Goomba>();
    if (e!=NULL)
    {
        float2 coll = collisionSeparate(e);
        if ( fabs(coll.x) > fabs(coll.y) ){

        streamHandle = BASS_StreamCreateFile(FALSE, "aj.mp3", 0, 0, BASS_MP3_SETPOS); // odpowidad za pojedynczy dzwiek
        BASS_ChannelPlay(streamHandle, TRUE);   // odworzy tylko raz |
        kill();
        }
        else
        {
          streamHandle = BASS_StreamCreateFile(FALSE, "aj.mp3", 0, 0, BASS_MP3_SETPOS); // odpowidad za pojedynczy dzwiek
        BASS_ChannelPlay(streamHandle, TRUE);   // odworzy tylko raz |
         kill();
        }



    }




e = collisionWith<przepasc>();
 if (e!=NULL)
 {
     streamHandle = BASS_StreamCreateFile(FALSE, "arg.mp3", 0, 0, BASS_MP3_SETPOS); // odpowidad za pojedynczy dzwiek
        BASS_ChannelPlay(streamHandle, TRUE);   // odworzy tylko raz |
   kill();

 }

    e = collisionWith<Coin>();
    if (e!=NULL)
        e->kill();

    float2 targetSpeed(0, -.2f);
    if (Keyboard::pressed('a'))
    {
        targetSpeed.x -= .2f;
        if (movingDir!=1)
            sprite.play(5, 7);
        movingDir = 1;
    }
    else if (Keyboard::pressed('d'))
    {
        targetSpeed.x += .2f;
        if (movingDir!=-1)
            sprite.play(1, 3);
        movingDir = -1;


    }
    else
    {
        if (movingDir==1)
            sprite.play(4,4);
        else if (movingDir==-1)
            sprite.play(0,0);
        sprite.pause();
        movingDir = 0;
    }

    if (Keyboard::pressed('w'))
    {
        if (!jumpPressed)
        {
            jumpPressed = true;
            if (
                fabs(
                Terrain::get().collisionWith('#',
                    position + float2(0, -.1f),
                    float2(.5f, .5f)).y - .1f

                     ) < .001f
                )
               streamHandle = BASS_StreamCreateFile(FALSE, "kaboom.mp3", 0, 0, BASS_MP3_SETPOS); // odpowidad za pojedynczy dzwiek
        BASS_ChannelPlay(streamHandle, TRUE);   // odworzy tylko raz |
                jump = 14;
        }
        if (--jump>0)
            targetSpeed.y = .3f;
    }
    else
        jumpPressed = false;

    velocity = targetSpeed * .5f + velocity * .5f;
    if (velocity.len() < .02f) velocity.zero();

    position += velocity;

    float2 coll( Terrain::get().collisionWith('#',
        position, float2(.5f, .5f)) );
    if ( !coll.isZero())
    {
        position += coll;

    }


    sprite.update();
    Terrain::get().setViewPos(position);
}
