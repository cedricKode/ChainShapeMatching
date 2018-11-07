#include <iostream>
#include <gtest/gtest.h>
#include "Hair.h"
#include "Vector.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ----------- VEC3 ------------

TEST(Vector3, userCtor)
{
    Vector3 a={0.2f, -0.2f, 0.2f};
    EXPECT_FLOAT_EQ(a.x, 0.2f);
    EXPECT_FLOAT_EQ(a.y, -0.2f);
    EXPECT_FLOAT_EQ(a.z, 0.2f);
}

TEST(Vector3, copyCtor)
{
    Vector3 a={0.2f, -0.2f, 0.2f};
    auto b = a;
    EXPECT_FLOAT_EQ(b.x, 0.2f);
    EXPECT_FLOAT_EQ(b.y, -0.2f);
    EXPECT_FLOAT_EQ(b.z, 0.2f);
}

TEST(Vector3, plusEquals)
{
    Vector3 a = {1.0f, 2.0f, 3.0f};
    Vector3 b = {1.0f, 1.0f, 1.0f};
    a += b;
    EXPECT_FLOAT_EQ(a.x, 2.0f);
    EXPECT_FLOAT_EQ(a.y, 3.0f);
    EXPECT_FLOAT_EQ(a.z, 4.0f);
}

// ----------- STRANDPOINT ------------

TEST(StrandPoint, defaultCtor)
{
    StrandPoint p;
    auto pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.x, 0.0f);
    EXPECT_FLOAT_EQ(pos.y, 0.0f);
    EXPECT_FLOAT_EQ(pos.z, 0.0f);
}

TEST(StrandPoint, setPosition)
{
    StrandPoint p;
    p.setPosition({0.5f, -0.2f, 12.303f});
    auto pos = p.getPosition();
    EXPECT_FLOAT_EQ(pos.x, 0.5f);
    EXPECT_FLOAT_EQ(pos.y, -0.2f);
    EXPECT_FLOAT_EQ(pos.z, 12.303f);
}

TEST(StrandPoint, setVelocity)
{
    StrandPoint p;
    p.setVelocity({0.0f, -0.2f, 0.0f});
    auto vel = p.getVelocity();
    EXPECT_FLOAT_EQ(vel.x, 0.0f);
    EXPECT_FLOAT_EQ(vel.y, -0.2f);
    EXPECT_FLOAT_EQ(vel.z, 0.0f);
}

TEST(StrandPoint, setMass)
{
    StrandPoint p;
    p.setMass(1.0f);
    auto mass = p.getMass();
    EXPECT_FLOAT_EQ(mass, 1.0f);
}

TEST(StrandPoint, setRadius)
{
    StrandPoint p;
    p.setRadius(1.0f);
    auto radius = p.getRadius();
    EXPECT_FLOAT_EQ(radius, 1.0f);
}

TEST(StrandPoint, setRegionWidth)
{
    StrandPoint p;
    p.setRegionWidth(3);
    auto region = p.getRegionWidth();
    EXPECT_EQ(region, 3);
}

TEST(StrandPoint, setPointId)
{
    StrandPoint p;
    p.setPointId(10);
    auto id = p.getPointId();
    EXPECT_EQ(id, 10);
}

// ----------- STRAND ------------

TEST(Strand, setStrandId)
{
    Strand s;
    s.setStrandId(20);
    auto s_id = s.getStrandId();
    EXPECT_EQ(s_id, 20);
}

TEST(Strand, getNumOfPointsInStrand)
{
    Strand s;
    auto n_p = s.getNumberOfPointInStrand();
    EXPECT_EQ(n_p, 0);
}

