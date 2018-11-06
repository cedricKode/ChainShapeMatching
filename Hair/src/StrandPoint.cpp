#include "StrandPoint.h"

Vector3 StrandPoint::getPosition() const
{
    return m_position;
}

void StrandPoint::setPosition(const Vector3 &_pos)
{
    m_position = _pos;
}

Vector3 StrandPoint::getVelocity() const
{
    return m_velocity;
}

void StrandPoint::setVelocity(const Vector3 &_vel)
{
    m_velocity = _vel;
}

float StrandPoint::getMass() const
{
    return m_mass;
}

void StrandPoint::setMass(float _mass)
{
    m_mass = _mass;
}

float StrandPoint::getRestLength() const
{
    return m_restlength;
}

void StrandPoint::setRestLength(float _restlength)
{
    m_restlength = _restlength;
}

float StrandPoint::getRadius() const
{
    return m_radius;
}
void StrandPoint::setRadius(float _radius)
{
    m_radius = _radius;
}

int StrandPoint::getRegionWidth() const
{
    return m_w;
}
void StrandPoint::setRegionWidth(int _w)
{
    m_w = _w;
}

int StrandPoint::getPointId() const
{
    return m_pointid;
}

void StrandPoint::setPointId(int _pointid)
{
    m_pointid = _pointid;
}

int StrandPoint::getNumberOfBelongedRegions() const
{
    return m_nbelongedregions;
}

void StrandPoint::updateNumberOfBelongedRegions()
{
    m_nbelongedregions += 1;
}
