#ifndef COLLISION_H_
#define COLLISION_H_
#include "Vector.h"
#include "StrandPoint.h"
#include <iostream>

// the same description as in Hair.h
typedef std::vector<StrandPoint*> listOfPoints;

class CollisionDetection
{
public:
    CollisionDetection()=default;
    ~CollisionDetection()=default;
    CollisionDetection(const CollisionDetection &)=default;

    // let's decite, that each voxel is 3x3x3
    listOfPoints detactingPointsToCollide(Vector3 _observingVoxel);
    void collisionForse(const StrandPoint *_observingPoint, const listOfPoints _neigbourPoints);
};

#endif
