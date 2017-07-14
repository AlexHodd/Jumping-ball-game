#ifndef FLOAT2_HPP
#define FLOAT2_HPP

#include <math.h>

struct float2
{
    float x,y;

    float2():x(0),y(0) {}
    float2(float x, float y):x(x),y(y) {}

    float2(float f):x(cos(f*0.01745f)),y(sin(f*0.01745f)) {}

    float2 &operator+=(float2 f) { x+=f.x; y+=f.y; return *this; }
    float2 operator+(float2 f) { return float2(x+f.x, y+f.y); }
    float2 operator-(float2 f) { return float2(x-f.x, y-f.y); }

    float2 normalized()
    {
        if ( fabs(x)<.001f && fabs(y)<.001f )
            return float2(0.f, 0.f);
        else
            return *this/sqrt(x*x+y*y);
    }
    float2 operator*(float f) { return float2(x*f, y*f); }
    float2 operator/(float f) { return float2(x/f, y/f); }
    void clampLen(float f)
    {
        if ( fabs(x)<.001f && fabs(y)<.001f )
            return;
        float len = sqrt(x*x+y*y);
        if (len > f)
        {
            x*=f/len;
            y*=f/len;
        }
    }
    float len(void)
    {
        return sqrt(x*x+y*y);
    }
    float toAngle()
    {
        return atan2(y, x)*57.2957795f;
    }

    void zero() { x=y=0.f; }
    bool isZero() { return x==0.f && y==0.f; }
};

#endif // FLOAT2_HPP
