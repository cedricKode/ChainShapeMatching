//---------------------------------------------------------------------------------------
///  @file Strand.cpp
///  @brief This file contains implementations of methods devoted to constructing strands
///  which consisting of points. Strands devoted to show connections between points
//---------------------------------------------------------------------------------------

#include "Strand.h"
#include "Hair.h"

size_t Strand::getStrandId() const
{
    return m_strandid;
}
//---------------------------------------------------------------------------------------
void Strand::setStrandId(size_t _strandid)
{
    m_strandid = _strandid;
}
//---------------------------------------------------------------------------------------
size_t Strand::getNumberOfPointInStrand()
{
    return m_pointsInStrandRef.size();
}
//---------------------------------------------------------------------------------------
std::vector<StrandPoint *> Strand::getAllRefPointsInStrand() const
{
    return m_pointsInStrandRef;
}
//---------------------------------------------------------------------------------------
void Strand::originalCentersOfMass()
{
    for (auto p : m_pointsInStrandRef)
    {
        // Finding datasets of points, according to regionWidth
        size_t regionWidth = p->getRegionWidth();

        int startId = int(p->getPointId()) - int(regionWidth);
        size_t endId = p->getPointId() + regionWidth;
        if (startId < 0) {startId = 0;}

        if (endId > m_pointsInStrandRef.size() - 1)
        {
            endId = m_pointsInStrandRef.size()  - 1;
        }


        std::vector <size_t> _regionOfPoints;
        for (size_t i = size_t(startId); i <= endId; i++)
            _regionOfPoints.push_back(m_pointsInStrandRef[i]->getPointIdInVector());

        // Find original center of mass of found region
        float massSum = 0;
        ngl::Vec3 _originalCenterOfMassOfRegion = {0,0,0};

        for (auto i : _regionOfPoints)
        {
            _originalCenterOfMassOfRegion +=
                    m_hair->m_allPoints[i].getOriginalPosition() *
                    m_hair->m_allPoints[i].getMass();

            massSum += m_hair->m_allPoints[i].getMass();
        }

        _originalCenterOfMassOfRegion /= massSum;
        p->setRegionOfPointsAndCenterOfMass(_regionOfPoints,
                                            _originalCenterOfMassOfRegion);
    }
}
//---------------------------------------------------------------------------------------
void Strand::optimalTransformation()
{
    for (auto &p : m_pointsInStrandRef)
    {
        // First step is finding centroids for both dataset
        ngl::Vec3 centroidOfOldPositions = {0.0f,0.0f,0.0f};
        ngl::Vec3 centroidOfCurrentPositions = {0.0f,0.0f,0.0f};

        // May be here it is more efficient to use center of mass instead of centroid
        // Original algorithm implies of usage centroids
        for (auto i : p->getIndiciesOfRegionOfPointstor())
        {
            centroidOfOldPositions += m_hair->m_allPoints[i].getOldPosition();
            centroidOfCurrentPositions += m_hair->m_allPoints[i].getPosition();
        }
        centroidOfOldPositions /= p->getIndiciesOfRegionOfPointstor().size();
        centroidOfCurrentPositions /= p->getIndiciesOfRegionOfPointstor().size();

        // Second step is finding matrix for SVD algorythm
        Eigen::Vector3f centroidOfOldPositionsEigen(centroidOfOldPositions.m_x,
                                                    centroidOfOldPositions.m_y,
                                                    centroidOfOldPositions.m_z);

        Eigen::Vector3f centroidOfCurrentPositionsEigen(centroidOfCurrentPositions.m_x,
                                                        centroidOfCurrentPositions.m_y,
                                                        centroidOfCurrentPositions.m_z);

        int n = int(p->getIndiciesOfRegionOfPointstor().size());

        Eigen::MatrixXf A;
        A.setZero(n,3);

        Eigen::MatrixXf B;
        B.setZero(n,3);

        int offset = 0;

        for (auto i : p->getIndiciesOfRegionOfPointstor())
        {
            A(offset, 0) =
                    m_hair->m_allPoints[i].getOldPosition().m_x -
                    centroidOfOldPositionsEigen(0);
            A(offset, 1) =
                    m_hair->m_allPoints[i].getOldPosition().m_y -
                    centroidOfOldPositionsEigen(1);
            A(offset, 2) =
                    m_hair->m_allPoints[i].getOldPosition().m_z -
                    centroidOfOldPositionsEigen(2);

            B(offset, 0) =
                    m_hair->m_allPoints[i].getPosition().m_x -
                    centroidOfCurrentPositionsEigen(0);
            B(offset, 1) =
                    m_hair->m_allPoints[i].getPosition().m_y -
                    centroidOfCurrentPositionsEigen(1);
            B(offset, 2) =
                    m_hair->m_allPoints[i].getPosition().m_z -
                    centroidOfCurrentPositionsEigen(2);

            offset++;
        }

        Eigen::MatrixXf H;
        H.setZero(3,3);

        Eigen:: MatrixXf optimalRotation;
        Eigen::VectorXf optimalTranslation;

        // This is a method to fix mistake, which may occure in calculation SVD
        if (A == B)
        {
            H = A.transpose() * A;
            optimalRotation.setIdentity(3,3);
        }
        else
        {
            H = A.transpose()  * B;

            // Third step is usage of SVD algorythm
            Eigen::JacobiSVD<Eigen::MatrixXf> svd( H,
                                                   Eigen::ComputeThinU |
                                                   Eigen::ComputeThinV);

            optimalRotation = svd.matrixV() * svd.matrixU().transpose();

            // Check situation with "mirrored" result
            if (optimalRotation.determinant() < 0)
            {
                optimalRotation(0,2) *= -1;
                optimalRotation(1,2) *= -1;
                optimalRotation(2,2) *= -1;
            }
        }

        // Final step is finding optimal translation
        optimalTranslation = -1 * optimalRotation * centroidOfOldPositionsEigen  +
                centroidOfCurrentPositionsEigen;

        p->optimalTransformation(optimalRotation, optimalTranslation);
    }
}
//---------------------------------------------------------------------------------------
void Strand::currentCenterOfTheMass()
{
    for (auto &p : m_pointsInStrandRef)
    {
        float massSum = 0;
        ngl::Vec3 _currentCenterOfMassOfRegion = {0,0,0};
        for (auto i : p->getIndiciesOfRegionOfPointstor())
        {
            _currentCenterOfMassOfRegion +=
                    m_hair->m_allPoints[i].getPosition() *
                    m_hair->m_allPoints[i].getMass();

            massSum += m_hair->m_allPoints[i].getMass();
        }
        _currentCenterOfMassOfRegion /= massSum;

        p->setCurrentCenterOfMassOfRegion(_currentCenterOfMassOfRegion);
    }
}
//---------------------------------------------------------------------------------------
void Strand::goalPosition()
{
    for (auto &p : m_pointsInStrandRef)
    {
        Eigen::Vector3f _originalPositionEigen;
        _originalPositionEigen[0] = p->getOriginalPosition().m_x;
        _originalPositionEigen[1] = p->getOriginalPosition().m_y;
        _originalPositionEigen[2] = p->getOriginalPosition().m_z;

        ngl::Vec3 goalPosition = {0,0,0};

        size_t nr = p->getIndiciesOfRegionOfPointstor().size();
        for (auto i : p->getIndiciesOfRegionOfPointstor())
        {
            Eigen::VectorXf firstPart = m_hair->m_allPoints[i].getOptimalRotation() *
                    (_originalPositionEigen -
                     m_hair->m_allPoints[i].getOriginalCenterOfMassOfRegion());

            ngl::Vec3 firstPartNGL = {0,0,0};
            firstPartNGL.m_x = firstPart(0);
            firstPartNGL.m_y = firstPart(1);
            firstPartNGL.m_z = firstPart(2);

            ngl::Vec3 secondPartNGL = {0,0,0};
            secondPartNGL = m_hair->m_allPoints[i].getCurrentCenterOfMassOfRegion();

            ngl::Vec3 sum = (firstPartNGL+ secondPartNGL);
            goalPosition += sum;
        }

        goalPosition /= nr;

        p->goalPosition(goalPosition);
    }
}
//---------------------------------------------------------------------------------------
void Strand::strainLimitingGoalPosition()
{

    for (auto &p : m_pointsInStrandRef)
    {
        if (p->getPointId() != 0)
        {
            size_t prevId = (p->getPointId()) - 1;
            float restLength = m_pointsInStrandRef[prevId]->getRestLength();

            ngl::Vec3 prevPos = m_pointsInStrandRef[prevId]->getGoalPosition();
            ngl::Vec3 currentPos = p->getGoalPosition();

            float currentLenght = std::sqrt((currentPos.m_x - prevPos.m_x)*
                                            (currentPos.m_x - prevPos.m_x) +
                                            (currentPos.m_y - prevPos.m_y)*
                                            (currentPos.m_y - prevPos.m_y) +
                                            (currentPos.m_z - prevPos.m_z)*
                                            (currentPos.m_z - prevPos.m_z));

            ngl::Vec3 diff = currentPos - prevPos;
            ngl::Vec3 newPos = prevPos + restLength * (diff / currentLenght);
            p->setGoalPosition(newPos);
        }
    }
}
//---------------------------------------------------------------------------------------
void Strand::strainLimitingPosition()
{
    for (auto &p : m_pointsInStrandRef)
    {
        if (p->getPointId() != 0)
        {
            size_t prevId = (p->getPointId()) - 1;
            float restLength = m_pointsInStrandRef[prevId]->getRestLength();

            ngl::Vec3 prevPos = m_pointsInStrandRef[prevId]->getPosition();
            ngl::Vec3 currentPos = p->getPosition();

            float currentLenght = std::sqrt((currentPos.m_x - prevPos.m_x)*
                                            (currentPos.m_x - prevPos.m_x) +
                                            (currentPos.m_y - prevPos.m_y)*
                                            (currentPos.m_y - prevPos.m_y) +
                                            (currentPos.m_z - prevPos.m_z)*
                                            (currentPos.m_z - prevPos.m_z));

            ngl::Vec3 diff = currentPos - prevPos;
            ngl::Vec3 newPos = prevPos + restLength * (diff / currentLenght);

            // Move points on head
            float epsilon = 0.01f;
            if ((newPos - m_hair->getPosition()).length() <
                    (epsilon + m_hair->getRadius()))
            {
                ngl::Vec3 newPosition = m_hair->getPosition() +
                        (m_hair->getRadius() + epsilon) *
                        ((newPos - m_hair->getPosition()) /
                         (newPos - m_hair->getPosition()).length());
                newPos = newPosition;
            }

            p->setPosition(newPos);

            // Modification to algorithm. If use just v_i+1 = v_i + f_ext
            // than velocity tend to grow to infinity. So in a situation
            // when previous position equals to position I limit velocity

            float delta = 0.001f;

            if (((p->getPosition() - p->getOldPosition()).m_x < delta) &&
                ((p->getPosition() - p->getOldPosition()).m_y < delta) &&
                ((p->getPosition() - p->getOldPosition()).m_z < delta))
            {
                p->setVelocity(m_hair->getGravityForce());
            }
        }
    }
}
//---------------------------------------------------------------------------------------
void Strand::render()
{
    for (auto p : m_pointsInStrandRef)
    {
        p->render();
    }
}
