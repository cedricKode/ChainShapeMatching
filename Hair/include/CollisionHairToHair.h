#ifndef COLLISION_H_
#define COLLISION_H_
#include "ngl/Vec3.h"
#include "StrandPoint.h"
#include <iostream>

// This Class is just for calculating point to point collision,
// becuase point ot head collision will be implemented differently (like loop
// throught all hair points and checking: does it collide with head according
// to it's radius or not). It WON'T have separated class.

// It have to be mention, that collision for one point may occure with some number of points
// (more than two). So in this situation, penlty force have to be calculated with each
// "neigbour-collision" point. After that all penalty forces must be summed up, and divided by
// observing point mass

// Also, to make collision not "conserving", 'multiply const' may be added.This will decreace
// penalty force

class CollisionHairToHairDetection
{
public:
    // Constructor will check -- does there exist collision between two observing points
    // Radius of points taken into account
    // This CollisionDetection Constructor will be called just for neigbour points
    // This loop according to 3DTexture(Uniform grid) will be made in update() in Hair.cpp
    CollisionHairToHairDetection(StrandPoint *_pointToCollide1, StrandPoint *_pointToCollide2);

    bool checkCollisionHairToHair() const;

    // If collision exist -- calculate new force (collision force)
    ngl::Vec3 penaltyForceCalculation(float &multconst);

private:
    bool m_collisionExistance;

    float m_multconst;

    StrandPoint *m_pointToCollide1;
    StrandPoint *m_pointToCollide2;
};

#endif
