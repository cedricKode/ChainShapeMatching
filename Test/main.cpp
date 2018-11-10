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

TEST(StrandPoint, setVelocity)
{
    StrandPoint p;
    p.setVelocity({0.0f, -0.2f, 0.0f});
    auto vel = p.getVelocity();
    EXPECT_FLOAT_EQ(vel.m_x, 0.0f);
    EXPECT_FLOAT_EQ(vel.m_y, -0.2f);
    EXPECT_FLOAT_EQ(vel.m_z, 0.0f);
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

// ----------- STRAND ------------

TEST(Hair, getNumOfStrandsInHair)
{
    Hair h;
    auto n_s = h.getNumberOfStrandsInHair();
    EXPECT_EQ(n_s, 0);
}
