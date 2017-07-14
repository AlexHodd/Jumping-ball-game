#include <windows.h>

#include <gl/gl.h>

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::fstream;
using std::ios;

#include "Texture2D.h"

#define GL_ABGR 0x8000
#define GL_BGR 0x80E0

void Texture2D::die(int e)
{
    cout<<"Texture '"<<fname<<"' loading error: "<<e<<endl;
    exit(EXIT_FAILURE);
}

Texture2D::Texture2D(const char *_fname)
{
    fname = _fname;
    cout<<"Texture2D::Texture2D("<<fname<<")"<<endl;
    fstream f(fname, ios::in | ios::binary);
    if (!f.is_open())
        die(1);
    BITMAPFILEHEADER bfh;
    f.read((char*)&bfh, sizeof(BITMAPFILEHEADER));
    if (f.gcount() != sizeof(BITMAPFILEHEADER))
        die(2);
    if (bfh.bfType != 'B' + ('M'<<8) )
        die(3);
    BITMAPINFOHEADER bih;
    f.read((char*)&bih, sizeof(BITMAPINFOHEADER));
    if (f.gcount() != sizeof(BITMAPINFOHEADER))
        die(4);
    int width = bih.biWidth;
    int height = bih.biHeight;
    int dataSize = width*height*bih.biBitCount/8;
    unsigned char *img;
    switch (bih.biBitCount)
    {
    case 32:
        img = new unsigned char[dataSize];
        f.read((char*)img, 16);
        if (f.gcount()!=16)
            die(5);
        break;
    case 24:
        img = new unsigned char[dataSize];
        break;
    default:
        die(6);
    }
    f.read((char*)img, dataSize);
    if ( f.gcount() != dataSize)
        die(7);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        bih.biBitCount==24?GL_RGB8:GL_RGBA8,
        width, height, 0,
        bih.biBitCount==24?GL_BGR:GL_ABGR,
        GL_UNSIGNED_BYTE,
        img);
    delete[] img;
}

Texture2D::~Texture2D()
{
    cout<<"Texture2D{"<<fname<<"}::~Texture2D()"<<endl;
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}
