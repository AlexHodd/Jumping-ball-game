#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>
#include "bass.h"
#include <iostream>

using std::cout;
using std::endl;

#include "Sprite.h"
#include "ResourceFactory.h"
#include "ComponentManager.h"
#include "Keyboard.h"

#include "Player.h"
#include "Terrain.h"
#include "Coin.h"

int screenWidth=800, screenHeight=600;
HSTREAM streamHandle;

void end(void)
{
    cout<<"Game terminated"<<endl;
}

Sprite *gameOver;
Sprite *youWon;

enum GameState
{
    PLAY, GAMEOVER, YOUWON
} gameState = PLAY;

void renderScene(void) {
    glClearColor(100.f/255.f, 149.f/255.f, 237.f/255.f, .5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -1.f);
    glPushMatrix();
        Terrain::get().draw();
        ComponentManager::draw();
    glPopMatrix();
    switch ( gameState )
    {
    case GAMEOVER:
        gameOver->draw(float2(0,0), 0.f, 16.f);
        break;
    case YOUWON:
        youWon->draw(float2(0,0), 0.f, 16.f);
        break;
    }
    glutSwapBuffers();
}

void resize(int wid, int hei)
{
    screenWidth = wid;
    screenHeight = hei ? hei : 1;
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float scale = 8.f;
    glOrtho(-scale*(float)wid/(float)hei*.98f, scale*(float)wid/(float)hei*.98f, -scale, scale, .1f, 10.f);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    BASS_ChannelPlay(streamHandle, FALSE); // jesli sie skonczy utwór to jeszcze ra z odworzy gra
    switch ( gameState)
    {
    case PLAY:
        ComponentManager::update();
        ComponentManager::find<Player>();
        Player *p = ComponentManager::next<Player>();
        if (p==NULL) // player killed
            gameState = GAMEOVER;
        else if (ComponentManager::count<Coin>() == 0 )
            gameState = YOUWON;
        break;
    }
    glutPostRedisplay();
}

void keyb(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 27:
        cout<<"shutdown by Escape"<<endl;
        exit(EXIT_SUCCESS);
    }
    Keyboard::get().keyb(k, true);
}

void keybUp(unsigned char k, int x, int y)
{
    Keyboard::get().keyb(k, false);
}

int main(int argc, char **argv) {
    cout<<"Initialization"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(240, 64);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Tanks Game");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    BASS_Init(-1, 44100, 0, 0, NULL);
    cout<<"BASS Init : "<<BASS_ErrorGetCode()<<endl;
    BASS_Start();
    streamHandle = BASS_StreamCreateFile(FALSE, "intro2.mp3", 0, 0, BASS_MP3_SETPOS); /// intro pliku

    glutKeyboardFunc(keyb);
    glutKeyboardUpFunc(keybUp);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    Terrain::get().create("level1.txt");
    Terrain::get().setViewSize(float2(21, 16));

    gameOver = new Sprite(ResourceFactory::load("gameover.bmp"));
    youWon = new Sprite(ResourceFactory::load("youwon.bmp"));

    atexit(end);
    cout<<"Game started"<<endl;
    glutMainLoop();
}
