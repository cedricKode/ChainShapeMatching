#ifndef STRANDPOINT_H_
#define STRANDPOINT_H_
#include "Vector.h"

class StrandPoint
{
public:
    StrandPoint()=default;
    ~StrandPoint()=default;
    StrandPoint(const StrandPoint &)=default;
    StrandPoint(StrandPoint &&)=default;
    StrandPoint & operator =(const StrandPoint &)=default;
    StrandPoint & operator =(StrandPoint &&)=default;

    Vector3 getPosition() const;
    void setPosition(const Vector3 &pos);

    Vector3 getVelocity() const;
    void setVelocity(const Vector3 &vel);

    float getMass() const;
    void setMass(float _mass);

    float getRestLength() const;
    void setRestLength(float _restlength);

    float getRadius() const;
    void setRadius(float _radius);

    int getRegionWidth() const;
    void setRegionWidth(int _w);

    int getPointId() const;
    void setPointId(int _pointid);

    int getNumberOfBelongedRegions() const;
    // This may be counted just form Texture Data, because we need to no previous points
    // from the same strund, plus follow points from the same strand, plus region width
    void updateNumberOfBelongedRegions();

    void update();

private:
    Vector3 m_position;
    Vector3 m_velocity;

    float m_mass;
    float m_restlength;
    float m_radius;

    int m_w;
    int m_pointid;
    int m_nbelongedregions = 0;
};

#endif
