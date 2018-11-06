#ifndef VEC3_H_
#define VEC3_H_

struct Vector3
{
    Vector3(float _x, float _y, float _z) : x(_x), y(_y),z(_z){}
    Vector3()=default;
    Vector3(const Vector3 &)=default;

    void operator +=(const Vector3 &_rhs)
    {
        x+=_rhs.x;
        y+=_rhs.y;
        z+=_rhs.z;
    }

    float x=0.0f;
    float y=0.0f;
    float z=0.0f;
};


struct Vector4
{
    Vector4(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a){}
    Vector4()=default;
    Vector4(const Vector4 &)=default;

    float r=0.0f;
    float g=0.0f;
    float b=0.0f;
    float a=0.0f;
};

#endif
