#include "Strand.h"
#include <random>

Strand::Strand(ngl::Vec3 &_firstPointPosition, ngl::Vec3 &_directionToPlacingPoints, size_t _numPoints, float _distance)
{
    m_numPoints = _numPoints;
    m_distance = _distance;

    ngl::Vec3 positionToSetPoint = 0;

    std::random_device rdInt;
    std::mt19937 genInt(rdInt());
    std::uniform_real_distribution<> width(1, 5);

    for (int i = 0; i < _numPoints; i++)
    {
        // Setting up position of each point in Strand
        // In a case of root point, we don't need to move it along direction
        // In a case of not-root point, we have to move point along direction to pre-defined distance
        if (i == 0 )
        {
            positionToSetPoint = _firstPointPosition;
        }
        else
        {
            float length = _directionToPlacingPoints.length();
            positionToSetPoint = positionToSetPoint + _distance * (_directionToPlacingPoints / length);
        }

        // velocity by default = {0,0,0}
        ngl::Vec3 vel = {0,0,0};

        // set random mass for each point
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> mass(0.1f, 0.9f);

        // set random half-width region value (which have to be odd) for each point
        size_t regionWidth = width(genInt);
        if (regionWidth % 2 == 0) regionWidth += 1;

        StrandPoint s(positionToSetPoint, vel, mass(gen), regionWidth);
        s.setPointId(i);

        m_pointsInStrand.push_back(s);
    }
}

int Strand::getStrandId() const
{
    return m_strandid;
}

void Strand::setStrandId(int _strandid)
{
    m_strandid = _strandid;
}

int Strand::getNumberOfPointInStrand()
{
    return m_numPoints;
}

std::vector<StrandPoint> Strand::getAllPointsInStrand() const
{
    return m_pointsInStrand;
}

void Strand::render()
{
    for (auto p : m_pointsInStrand)
    {
        p.render();
    }
}
