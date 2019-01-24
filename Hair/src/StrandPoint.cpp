//---------------------------------------------------------------------------------------
///  @file StrandPoint.cpp
///  @brief This file contains implementations of methods devoted to constructing points
///  in hair simulation.
//---------------------------------------------------------------------------------------

#include "StrandPoint.h"

StrandPoint::StrandPoint(ngl::Vec3 &_position,
                         ngl::Vec3 &_velocty,
                         float _mass,
                         size_t _regionWidth)
{
    m_velocity = _velocty;
    m_position = _position;
    m_originalPosition = _position;
    m_oldPosition = _position;
    m_mass = _mass;
    m_width = _regionWidth;
}
//---------------------------------------------------------------------------------------
ngl::Vec3  StrandPoint::getPosition() const
{
    return m_position;
}
//---------------------------------------------------------------------------------------
ngl::Vec3  StrandPoint::getOldPosition() const
{
    return m_oldPosition;
}
//---------------------------------------------------------------------------------------
ngl::Vec3  StrandPoint::getOriginalPosition() const
{
    return m_originalPosition;
}
//---------------------------------------------------------------------------------------
ngl::Vec3  StrandPoint::getGoalPosition() const
{
    return m_goalPosition;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setGoalPosition(const ngl::Vec3  &_goalPos)
{
    m_goalPosition = _goalPos;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setPosition(const ngl::Vec3  &_pos)
{
    m_position = _pos;
}
//---------------------------------------------------------------------------------------
Eigen::Vector3f StrandPoint::getOriginalCenterOfMassOfRegion() const
{
    return m_originalCenterOfMassOfRegion;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setCurrentCenterOfMassOfRegion(ngl::Vec3 _currentCenterOfMass)
{
    m_currentCenterOfMassOfRegion = _currentCenterOfMass;
}
//---------------------------------------------------------------------------------------
ngl::Vec3 StrandPoint::getCurrentCenterOfMassOfRegion() const
{
    return m_currentCenterOfMassOfRegion;
}
//---------------------------------------------------------------------------------------
Eigen:: MatrixXf StrandPoint::getOptimalRotation() const
{
    return m_optimalRotation;
}
//---------------------------------------------------------------------------------------
Eigen::VectorXf StrandPoint::getOptimalTranslation() const
{
    return m_optimalTranslation;
}
//---------------------------------------------------------------------------------------
ngl::Vec3  StrandPoint::getVelocity() const
{
    return m_velocity;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setVelocity(const ngl::Vec3  &_vel)
{
    m_velocity = _vel;
}
//---------------------------------------------------------------------------------------
float StrandPoint::getMass() const
{
    return m_mass;
}
//---------------------------------------------------------------------------------------
float StrandPoint::getRestLength() const
{
    return m_restLength;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setRestLength(float _length)
{
    m_restLength = _length;
}
//---------------------------------------------------------------------------------------
size_t StrandPoint::getRegionWidth() const
{
    return m_width;
}
//---------------------------------------------------------------------------------------
size_t StrandPoint::getPointId() const
{
    return m_pointId;
}
//---------------------------------------------------------------------------------------
size_t StrandPoint::getPointIdInVector() const
{
    return m_pointidInVector;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setPointIdInVector(size_t _pointidinvector)
{
    m_pointidInVector = _pointidinvector;
}
//---------------------------------------------------------------------------------------
size_t StrandPoint::getStrandId() const
{
    return m_strandId;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setPointId(size_t _pointid, size_t _strandid)
{
    m_pointId = _pointid;
    m_strandId = _strandid;
}
//---------------------------------------------------------------------------------------
void StrandPoint::addGravityForce(ngl::Vec3 &_gravity)
{
    m_forceExt += _gravity;
}
//---------------------------------------------------------------------------------------
void StrandPoint::clearExtForce()
{
    m_forceExt = {0,0,0};
}
//---------------------------------------------------------------------------------------
void StrandPoint::addCollisionWithHeadForce(ngl::Vec3 _headPosition,
                                            float _headRadius)
{
    float epsilon = 0.01f;
    float penaltyConstant = _headRadius;

    ngl::Vec3 distanceVector = m_position - _headPosition;
    if (distanceVector.length() < (epsilon + _headRadius))
    {
        float k = 1.0f; // coefficient of damping
        ngl::Vec3 force = k * _headRadius * (distanceVector / distanceVector.length());
        m_forceExt += force * penaltyConstant;
    }
}
//---------------------------------------------------------------------------------------
void StrandPoint::addSelfCollision(StrandPoint _pointToCollideWith)
{
    float epsilon = 0.01f;
    if ((m_position - _pointToCollideWith.getPosition()).length() < epsilon)
    {
        float coefficient = 2;
        ngl::Vec3 forceToCollide = coefficient *
                (m_position - _pointToCollideWith.getPosition());
        m_forceExt += forceToCollide;
    }
}
//---------------------------------------------------------------------------------------
void StrandPoint::updatePositionAndVelocity(float _timeStep,
                                            ngl::Vec3 _headPosition,
                                            float _headRadius)
{

    // Here also need to check that this point is not inside head
    // If so -> move it to the edge of the head (along the vector)
    // which connects point and heads center

    ngl::Vec3 newVelocity = m_velocity + _timeStep * (m_forceExt / m_mass);
    //ngl::Vec3 newVelocity =  _timeStep * (m_forceExt / m_mass);
    m_oldVelocity = m_velocity;
    m_velocity = newVelocity;

    ngl::Vec3 newPosition = m_position +_timeStep * m_velocity;
    m_oldPosition = m_position;
    m_position = newPosition;

    float epsilon = 0.01f;
    if ((m_position - _headPosition).length() < (epsilon + _headRadius))
    {
        newPosition = _headPosition + (_headRadius + epsilon) *
                ((m_position - _headPosition) / (m_position - _headPosition).length());
        m_position = newPosition;
    }

    if (m_pointId == 0)
    {
        m_position = m_originalPosition;
        m_velocity = {0,0,0};
    }
}
//---------------------------------------------------------------------------------------
std::vector <size_t> StrandPoint::getIndiciesOfRegionOfPointstor() const
{
    return m_indiciesOfRegionOfPoints;
}
//---------------------------------------------------------------------------------------
void StrandPoint::optimalTransformation(Eigen:: MatrixXf _optimalRotation,
                                        Eigen::VectorXf _optimalTranslation)
{
    m_optimalRotation = _optimalRotation;
    m_optimalTranslation = _optimalTranslation;
}
//---------------------------------------------------------------------------------------
void StrandPoint::setRegionOfPointsAndCenterOfMass(std::vector<size_t> _regionOfPoints,
                                                   ngl::Vec3 _originalCenterOfMassOfRegion)
{
    m_indiciesOfRegionOfPoints = _regionOfPoints;

    // Converting to Eigen vector
    m_originalCenterOfMassOfRegion[0] = _originalCenterOfMassOfRegion.m_x;
    m_originalCenterOfMassOfRegion[1] = _originalCenterOfMassOfRegion.m_y;
    m_originalCenterOfMassOfRegion[2] = _originalCenterOfMassOfRegion.m_z;
}
//---------------------------------------------------------------------------------------
void StrandPoint::goalPosition(ngl::Vec3 _goalPosition)
{
    m_goalPosition = _goalPosition;
}
//---------------------------------------------------------------------------------------
void StrandPoint::updatePositionAndVelocityByGoalPosition(float _timeStep)
{
    float epsilon = 0.00001f;

    if (((m_goalPosition - m_oldPosition).m_x < epsilon) &&
        ((m_goalPosition - m_oldPosition).m_y < epsilon) &&
        ((m_goalPosition - m_oldPosition).m_z < epsilon))
    {
        // Nothing to update
        m_velocity = {0.0f, 0.0f, 0.0f};
        m_position += 0;
    }
    else
    {
        // Modification to algorythm -- velocity does not updates according to goal
        // position. Because it gives big mistake which tend to accumulate and leads
        // to incorrect result
        ngl::Vec3 tmpVel = m_oldVelocity + (m_goalPosition - m_oldPosition)/_timeStep;
        m_position = m_oldPosition + _timeStep * tmpVel;
    }

    if (m_pointId == 0)
    {
        m_position = m_originalPosition;
        m_velocity = {0,0,0};
    }
}
//---------------------------------------------------------------------------------------
void StrandPoint::render()
{
    std::cout << m_position.m_x << " "
              << m_position.m_y << " "
              << m_position.m_z << "\n";
}
//---------------------------------------------------------------------------------------
void StrandPoint::updateSimulation()
{
    m_position = m_originalPosition;

    // Set all other to zero
    m_currentCenterOfMassOfRegion = {0.0f, 0.0f, 0.0f};

    m_oldPosition = {0.0f, 0.0f, 0.0f};

    m_velocity = {0.0f, 0.0f, 0.0f};
    m_oldVelocity = {0.0f, 0.0f, 0.0f};

    m_goalPosition = {0.0f, 0.0f, 0.0f};

    m_forceExt =  {0.0f, 0.0f, 0.0f};

    m_optimalRotation.setZero(3,3);
    m_optimalTranslation.setZero(3);
}
