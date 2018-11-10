#ifndef STRANDPOINT_H_
#define STRANDPOINT_H_
#include "ngl/Vec3.h"

class StrandPoint
{
public:
    StrandPoint()=default;
    ~StrandPoint()=default;
    StrandPoint(const StrandPoint &)=default;
    StrandPoint(StrandPoint &&)=default;
    StrandPoint & operator =(const StrandPoint &)=default;
    StrandPoint & operator =(StrandPoint &&)=default;

    ngl::Vec3 getPosition() const;
    void setPosition(const ngl::Vec3  &pos);

    ngl::Vec3 getGoalPosition() const;
    // Calculated after evaluating optimal transformation
    void setGoalPosition(const ngl::Vec3  &_goalPos);

    ngl::Vec3 getVelocity() const;
    void setVelocity(const ngl::Vec3  &vel);

    float getMass() const;
    void setMass(float _mass);

    // Will be the same for all points inside one strand, so
    // may be this function will be deleted later
    float getRestLength() const;
    void setRestLength(float _restlength);

    // Setting radius for calculationg collision
    float getRadius() const;
    void setRadius(float _radius);

    // Region of observing "neigbour" points of the same strand inside 2DTexture
    int getRegionWidth() const;
    void setRegionWidth(int _w);

    int getPointId() const;
    void setPointId(int _pointid);

    // This may be counted just form Texture Data
    int getNumberOfBelongedRegions() const;
    void updateNumberOfBelongedRegions();

    bool checkCollisionWithHead() const;
    // if collision exist -- calculate penaltyForce between head and point
    ngl::Vec3 penaltyForcePointToHead();

    // Summing up all forces for one point, plus adding gravity
    void addGravityForce(ngl::Vec3 &_gravityForce);
    void updateExternalForces(ngl::Vec3 &_force);

private:

    // original poisition in stored in one of the 2DTexture

    ngl::Vec3  m_position;
    ngl::Vec3  m_velocity;

    // Calculated after evaluating optimal transformation
    ngl::Vec3  m_goalPosition;

    ngl::Vec3 m_extternalForces;

    float m_mass;
    float m_restlength;
    float m_radius;

    int m_w;
    int m_pointid;
    int m_nbelongedregions = 0;
};

#endif
