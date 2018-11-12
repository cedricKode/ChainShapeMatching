#include "StrandPoint.h"
#include <iostream>

StrandPoint::StrandPoint(ngl::Vec3 &_position, ngl::Vec3 &_velocty, float _mass, size_t _regionWidth)
{
    m_velocity = _velocty;
    m_position = _position;
    m_mass = _mass;
    m_w = _regionWidth;
}

ngl::Vec3  StrandPoint::getPosition() const
{
    return m_position;
}

void StrandPoint::setPosition(const ngl::Vec3  &_pos)
{
    m_position = _pos;
}

ngl::Vec3  StrandPoint::getVelocity() const
{
    return m_velocity;
}

void StrandPoint::setVelocity(const ngl::Vec3  &_vel)
{
    m_velocity = _vel;
}

float StrandPoint::getMass() const
{
    return m_mass;
}

float StrandPoint::getRestLength() const
{
    return m_restlength;
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

void StrandPoint::render()
{
    std::cout << m_position.m_x << " " << m_position.m_y << " " << m_position.m_z << "\n";
}
