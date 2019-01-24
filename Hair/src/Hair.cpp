//---------------------------------------------------------------------------------------
///  @file Hair.cpp
///  @brief This file contains implementations of methods devoted to constructing hair
///  simulation. It contains all points, which take part in simulation, and
///  strands, which describe connections between points.
//---------------------------------------------------------------------------------------

#include <random>
#include <math.h>

#include "Hair.h"

Hair::Hair(const ngl::Vec3 &_headPosition, float _radiusOfHead,
           size_t _numStrands, size_t _halfRegionWidth)
{

    m_position = _headPosition;
    m_numStrands = _numStrands;
    m_radiusOfHead = _radiusOfHead;
    m_halfRegionWidth = _halfRegionWidth;
}
//---------------------------------------------------------------------------------------
ngl::Vec3 Hair::getPosition() const
{
    return m_position;
}
//---------------------------------------------------------------------------------------
float Hair::getRadius() const
{
    return  m_radiusOfHead;
}
//---------------------------------------------------------------------------------------
void Hair::setGravityForce(ngl::Vec3 &_gravity)
{
    m_gravity = _gravity;
}
//---------------------------------------------------------------------------------------
ngl::Vec3 Hair::getGravityForce() const
{
    return m_gravity;
}
//---------------------------------------------------------------------------------------
void Hair::setNumberOfStrandsInHair(size_t &_numStrands)
{
    m_numStrands = _numStrands;
}
//---------------------------------------------------------------------------------------
void Hair::setPosition(ngl::Vec3 _pos)
{
    m_position = _pos;
}
//---------------------------------------------------------------------------------------
void Hair::setRadius(float &_radius)
{
    m_radiusOfHead = _radius;
}
//---------------------------------------------------------------------------------------
void Hair::setSelfCollision(bool _selfCollisionToggle)
{
    m_enableSelfCollision = _selfCollisionToggle;
}
//---------------------------------------------------------------------------------------
void Hair::clear()
{
    m_allPoints.clear();
    m_allPointsToDraw.clear();
    m_strandsInHair.clear();
}
//---------------------------------------------------------------------------------------
void Hair::setHalfRegionWidth(size_t _halfRegionWidth)
{
    m_halfRegionWidth = _halfRegionWidth;
}
//---------------------------------------------------------------------------------------
void Hair::createStrands()
{
    // Set random position of the first point of the strands
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angle1(0.0f, 360.0f);
    std::uniform_real_distribution<float> angle2(0.0f, 360.0f);

    // Set half region widt, half region width may be just odd integer number
    // between 1 and 7. May be it is possible to use 9 and more as half region width, but
    // it will lead to very stiff hair 
    size_t regionWidth = m_halfRegionWidth;

    // Set random mass for each point
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<float> mass(1.1f, 1.9f);
    float massToSet = mass(gen1);

    for (size_t j = 0; j < m_numStrands; j++)
    {
        std::uniform_real_distribution<float> distanceInsideStrand(0.2f, 0.23f);
        std::uniform_real_distribution<> numOfPointsInStrand(25, 30);

        // Creating some number of root points on head (which equals to sphere
        // in this implementation)
        // Root point equals to direction (vector from head center to root point)

        float angle1Num = angle1(gen);
        float angle2Num = angle2(gen);

        float x = m_position.m_x + m_radiusOfHead *
                std::sin(angle1Num) * std::cos(angle2Num);
        float y = m_position.m_y + m_radiusOfHead *
                std::sin(angle1Num) * std::sin(angle2Num);
        float z = m_position.m_z + m_radiusOfHead *
                std::cos(angle1Num);

        ngl::Vec3 firstPoint(x,y,z);
        ngl::Vec3 strandDirection = firstPoint - m_position;

        size_t numPoints = size_t(numOfPointsInStrand(gen));
        float distance = distanceInsideStrand(gen);

        ngl::Vec3 positionToSetPoint = {0.0f,0.0f,0.0f};

        for (size_t i = 0; i < numPoints; i++)
        {
            // Create point and after that add it to strand

            // Setting up position of each point in Strand
            // In a case of root point, we don't need to move it along direction
            // In a case of non-root point, we have to move point along direction
            // to pre-defined distance
            if (i == 0 )
            {
                positionToSetPoint = firstPoint;
            }
            else
            {
                float length = strandDirection.length();
                positionToSetPoint = positionToSetPoint + distance *
                        (strandDirection / length);
            }

            // velocity by default = {0,0,0}
            ngl::Vec3 vel = {0,0,0};

            StrandPoint s_point(positionToSetPoint, vel, massToSet, regionWidth);
            s_point.setPointId(i, j);
            s_point.setPointIdInVector(m_allPoints.size());

            m_allPoints.push_back(s_point);
        }

    }

    for (size_t j = 0; j < m_numStrands; j++)
    {
        Strand s(this);
        // Add point reference to vector of points inside strands
        for (auto &p : m_allPoints)
        {
            if (p.getStrandId() == j)
            {
                s.addPointToStrand(&p);
            }
         }

        s.setStrandId(j);
        m_strandsInHair.push_back(s);
    }

    std::vector<size_t> indicies;

    // Create vector to draw (make it on initialization step to save time
    // and not to do it everytime in drawing part)

    for (auto s : m_strandsInHair)
    {
        for (auto p : s.getAllRefPointsInStrand())
        {
            size_t index = p->getPointIdInVector();
            indicies.push_back(index);
            if (p->getPointId() == 0)
                continue;
            indicies.push_back(index);
        }
        indicies.pop_back();
    }
    indicies.pop_back();

    for (auto i : indicies )
        m_allPointsToDraw.push_back(&m_allPoints[i]);

}
//---------------------------------------------------------------------------------------
size_t Hair::getNumberOfStrandsInHair() const
{
    return m_numStrands;
}
//---------------------------------------------------------------------------------------
void Hair::originalCentersOfMass()
{
    for (auto &s : m_strandsInHair)
        s.originalCentersOfMass();
}
//---------------------------------------------------------------------------------------
void Hair::restLength()
{
    for (auto &s : m_strandsInHair)
    {
        for (auto &p : s.getAllRefPointsInStrand())
        {
            if (p->getPointId() + 1 < s.getAllRefPointsInStrand().size())
            {
                ngl::Vec3 pointA = p->getOriginalPosition();
                ngl::Vec3 pointB = s.getAllRefPointsInStrand()[p->getPointId() + 1]->
                        getOriginalPosition();

                float length = std::sqrt((pointA.m_x-pointB.m_x)*(pointA.m_x-pointB.m_x) +
                                         (pointA.m_y-pointB.m_y)*(pointA.m_y-pointB.m_y) +
                                         (pointA.m_z-pointB.m_z)*(pointA.m_z-pointB.m_z));
                p->setRestLength(length);
            }
            else
            {
                // Last point has no rest length
                p->setRestLength(0.0f);
            }
        }
    }
}

void Hair::render()
{
    for (auto s : m_strandsInHair)
        s.render();
}
//---------------------------------------------------------------------------------------
void Hair::updateSimulation()
{
    for (auto &p : m_allPoints)
        p.updateSimulation();
}
//---------------------------------------------------------------------------------------
void Hair::update(float _timeStep)
{
    // This is the main function of simulation

    // Cleare all external forces (collision and gravity)
    for (auto &p : m_allPoints)
        p.clearExtForce();

    // Add gravity force
    for (auto &p : m_allPoints)
        p.addGravityForce(m_gravity);

    // Collision with head
    for (auto &p : m_allPoints)
        p.addCollisionWithHeadForce(m_position, m_radiusOfHead);

    // Self-collision (but just if it is enable)
    if (m_enableSelfCollision)
    {
        for (auto &p1 : m_allPoints)
            for (auto &p2 : m_allPoints)
                if (p1.getPointIdInVector() != p2.getPointIdInVector())
                    p1.addSelfCollision(p2);
    }

    // First step -- updating velocity and position according to external forces
    for (auto &p : m_allPoints)
        p.updatePositionAndVelocity(_timeStep, m_position, m_radiusOfHead);

    // Compute optimal transformation
    for (auto &s : m_strandsInHair)
        s.optimalTransformation();

    // Computer current centers of mass
    for (auto &s : m_strandsInHair)
        s.currentCenterOfTheMass();

    // Compute goal position
    for (auto &s : m_strandsInHair)
        s.goalPosition();

    // Strain limiting goal position
    for (auto &s : m_strandsInHair)
        s.strainLimitingGoalPosition();

    // Update Position and Velocity according to goal Position
    for (auto &p : m_allPoints)
        p.updatePositionAndVelocityByGoalPosition(_timeStep);

    // Personal addition -- Strain limiting for final position
    for (auto &s : m_strandsInHair)
        s.strainLimitingPosition();

}
