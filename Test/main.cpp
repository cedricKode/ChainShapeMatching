#include <iostream>

#include <gtest/gtest.h>

#include "Hair.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ----------- STRANDPOINT ------------

TEST(StrandPoint, defaultCtor)
{
    StrandPoint p;
    auto pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.m_x, 0.0f);
    EXPECT_FLOAT_EQ(pos.m_y, 0.0f);
    EXPECT_FLOAT_EQ(pos.m_z, 0.0f);
}

TEST(StrandPoint, setPosition)
{
    StrandPoint p;
    p.setPosition({0.5f, -0.2f, 12.303f});
    auto pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.m_x, 0.5f);
    EXPECT_FLOAT_EQ(pos.m_y, -0.2f);
    EXPECT_FLOAT_EQ(pos.m_z, 12.303f);
}

TEST(StrandPoint, setRestLength)
{
    StrandPoint p;
    p.setRestLength(1.0f);
    auto restLength = p.getRestLength();
    EXPECT_EQ(restLength, 1.0f);
}

TEST(StrandPoint, setPointAndStrandId)
{
    StrandPoint p;
    p.setPointId(1, 2);
    auto pointId = p.getPointId();
    auto strandId = p.getStrandId();
    EXPECT_EQ(pointId, 1);
    EXPECT_EQ(strandId, 2);
}

TEST(StrandPoint, setVelocity)
{
    StrandPoint p;
    p.setVelocity({0.0f, -0.2f, 0.0f});
    auto vel = p.getVelocity();
    EXPECT_FLOAT_EQ(vel.m_x, 0.0f);
    EXPECT_FLOAT_EQ(vel.m_y, -0.2f);
    EXPECT_FLOAT_EQ(vel.m_z, 0.0f);
}

TEST(StrandPoint, setCurrentCenterOfMass)
{
    StrandPoint p;
    p.setCurrentCenterOfMassOfRegion({0.0f, -1.2f, 0.0f});
    auto centerOfMass = p.getCurrentCenterOfMassOfRegion();
    EXPECT_FLOAT_EQ(centerOfMass.m_x, 0.0f);
    EXPECT_FLOAT_EQ(centerOfMass.m_y, -1.2f);
    EXPECT_FLOAT_EQ(centerOfMass.m_z, 0.0f);
}

// ----------- STRAND ------------

TEST(Strand, setStrandId)
{
    Strand s;
    s.setStrandId(20);
    auto strandId = s.getStrandId();
    EXPECT_EQ(strandId, 20);
}

// ----------- HAIR ------------

TEST(Hair, setHead)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1000;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    auto headP = h.getPosition();
    auto headR = h.getRadius();
    auto numS = h.getNumberOfStrandsInHair();

    EXPECT_FLOAT_EQ(headP.m_x, 0.0f);
    EXPECT_FLOAT_EQ(headP.m_y, 1.0f);
    EXPECT_FLOAT_EQ(headP.m_z, 2.0f);

    EXPECT_EQ(headR, 2.0f);

    EXPECT_EQ(numS, 1000);
}

TEST(Hair, copyHair)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1000;
    size_t regionWidth = 3;
    Hair h1(headPosition, radiusOfHead, numStrands, regionWidth);
    Hair h2;
    h2 = h1;
    auto headP = h2.getPosition();
    auto headR = h2.getRadius();
    auto numS = h2.getNumberOfStrandsInHair();

    EXPECT_FLOAT_EQ(headP.m_x, 0.0f);
    EXPECT_FLOAT_EQ(headP.m_y, 1.0f);
    EXPECT_FLOAT_EQ(headP.m_z, 2.0f);

    EXPECT_FLOAT_EQ(headR, 2.0f);

    EXPECT_EQ(numS, 1000);
}

TEST(Hair, numOfStrands)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1000;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    h.createStrands();
    auto numS = h.m_strandsInHair.size();

    EXPECT_EQ(numS, numStrands);
}

TEST(Hair, numOfPoints)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1000;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    h.createStrands();

    auto numPointsFromVector = h.m_allPoints.size();
    auto numPointsFromStrands = 0;
    for (auto s : h.m_strandsInHair)
        numPointsFromStrands += s.getNumberOfPointInStrand();

    EXPECT_EQ(numPointsFromVector, numPointsFromStrands);
}

TEST(Hair, gravityForce)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    h.createStrands();

    ngl::Vec3 gravity = {0.0f, 0.0f, 0.0f};
    h.setGravityForce(gravity);
    ngl::Vec3 getGravity = h.getGravityForce();

    EXPECT_FLOAT_EQ(getGravity.m_x, 0.0f);
    EXPECT_FLOAT_EQ(getGravity.m_y, 0.0f);
    EXPECT_FLOAT_EQ(getGravity.m_z, 0.0f);
}

TEST(Hair, optimalRotation)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    h.createStrands();
    h.originalCentersOfMass();
    h.restLength();

    ngl::Vec3 gravity = {0.0f, 0.0f, 0.0f};
    h.setGravityForce(gravity);
    ngl::Vec3 getGravity = h.getGravityForce();

    for (auto &p : h.m_allPoints)
        p.addGravityForce(getGravity);

    for (auto &p : h.m_allPoints)
        p.updatePositionAndVelocity(0.1f, headPosition, radiusOfHead);

    for (auto &s : h.m_strandsInHair)
        s.optimalTransformation();

    // Old position equals to current, so matrix of rotation between this
    // two positions have to be identity

    Eigen:: MatrixXf identityMatrix;
    identityMatrix.setIdentity(3,3);
    for (auto p : h.m_allPoints)
    {
        Eigen:: MatrixXf currentMatrix = p.getOptimalRotation();
        EXPECT_FLOAT_EQ(currentMatrix(0,0), identityMatrix(0,0));
        EXPECT_FLOAT_EQ(currentMatrix(0,1), identityMatrix(0,1));
        EXPECT_FLOAT_EQ(currentMatrix(0,2), identityMatrix(0,2));
        EXPECT_FLOAT_EQ(currentMatrix(1,0), identityMatrix(1,0));
        EXPECT_FLOAT_EQ(currentMatrix(1,1), identityMatrix(1,1));
        EXPECT_FLOAT_EQ(currentMatrix(1,2), identityMatrix(1,2));
        EXPECT_FLOAT_EQ(currentMatrix(2,0), identityMatrix(2,0));
        EXPECT_FLOAT_EQ(currentMatrix(2,1), identityMatrix(2,1));
        EXPECT_FLOAT_EQ(currentMatrix(2,2), identityMatrix(2,2));
    }
}

TEST(Hair, goalPosition)
{
    ngl::Vec3 headPosition = {0.0f, 1.0f, 2.0f};
    float radiusOfHead = 2.0f;
    size_t numStrands = 1;
    size_t regionWidth = 3;
    Hair h(headPosition, radiusOfHead, numStrands, regionWidth);
    h.createStrands();
    h.originalCentersOfMass();
    h.restLength();

    ngl::Vec3 gravity = {0.0f, 0.0f, 0.0f};
    h.setGravityForce(gravity);
    ngl::Vec3 getGravity = h.getGravityForce();

    for (auto &p : h.m_allPoints)
        p.addGravityForce(getGravity);

    for (auto &p : h.m_allPoints)
        p.updatePositionAndVelocity(0.1f, headPosition, radiusOfHead);

    for (auto &s : h.m_strandsInHair)
        s.optimalTransformation();

    for (auto &s : h.m_strandsInHair)
        s.currentCenterOfTheMass();

    for (auto &s : h.m_strandsInHair)
        s.goalPosition();

    // Old position equals to current, so goal position also have to be similar to them

    for (auto p : h.m_allPoints)
    {
        ngl::Vec3 goalPos = p.getGoalPosition();
        ngl::Vec3 oldPos = p.getOldPosition();
        EXPECT_FLOAT_EQ(goalPos.m_x, oldPos.m_x);
        EXPECT_FLOAT_EQ(goalPos.m_y, oldPos.m_y);
        EXPECT_FLOAT_EQ(goalPos.m_z, oldPos.m_z);
    }
}
