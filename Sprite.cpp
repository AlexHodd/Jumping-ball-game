#include <windows.h>

#include <gl/gl.h>

#include "Sprite.h"
#include "Texture2D.h"

Sprite::Sprite(Texture2D *_texture, int _frameCount /* =1 */, float _fps /* =24.f*/ )
    :
    texture(_texture),
    frameCount(_frameCount),
    rangeStart(0), rangeEnd(_frameCount-1),
    currentFrame(0.f),
    state(PAUSED), fps(_fps),
    lastTime( GetTickCount() )
{
}

void Sprite::update()
{
    if (state == PLAYING)
    {
        currentFrame += fps*(GetTickCount()-lastTime)/1000.f;
        if (currentFrame > rangeEnd+1)
            currentFrame=rangeStart;
        lastTime = GetTickCount();
    }
}

void Sprite::draw(float2 position /* = float2() */, float orientation /* = 0.f */, float scale /* = 0.f */)
{
    texture->bind();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.f);
    glRotatef(orientation, 0,0,1);
    glScalef(scale, scale, scale);
    glBegin(GL_QUADS);
        glTexCoord2f( (.03f+(int)currentFrame)/(float)frameCount, .03f);
        glVertex3f(-.5f, -.5f, 0.f);
        glTexCoord2f( (.97f+(int)currentFrame)/(float)frameCount, .03f);
        glVertex3f( .5f, -.5f, 0.f);
        glTexCoord2f( (.97f+(int)currentFrame)/(float)frameCount, .97f);
        glVertex3f( .5f,  .5f, 0.f);
        glTexCoord2f( (.03f+(int)currentFrame)/(float)frameCount, .97f);
        glVertex3f(-.5f,  .5f, 0.f);
    glEnd();
    glPopMatrix();
}

void Sprite::play(int start /* =0 */, int end /* =-1 */)
{
    currentFrame = rangeStart = start;
    rangeEnd = end != -1 ? end : frameCount - 1;
    state = PLAYING;
}
