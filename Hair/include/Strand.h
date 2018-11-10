#ifndef STRAND_H_
#define STRAND_H_
#include <vector>
#include "StrandPoint.h"
#include <cstring>

class Strand
{
public:

    Strand()=default;
    // Let's think, for begging, that each strand is a line;
    // So all points of strand are located on one line, with
    // fixed distance between points
    Strand(ngl::Vec3 &_directionToPlacingPoints, size_t _numPoints, float _distance);
    ~Strand()=default;
    Strand(const Strand &)=default;
    Strand(Strand &&)=default;
    Strand & operator =(const Strand &)=default;
    Strand & operator =(Strand &&)=default;

    std::vector<StrandPoint> getAllPointsInStrand() const;
    int getNumberOfPointInStrand();

    int getStrandId() const;
    void setStrandId(int _strandid);

    // this function will update points position according to their new goal position
    // and rest length. Also, velocity may be needed to update.
    // This method will update goalPosition -> method setGoalPosition from StrandPoint will
    // be used
    void preserveStretching();

private:
    std::vector<StrandPoint> m_pointsInStrand;
    size_t m_numPoints = 0;

    float m_distance;
    int m_strandid;
};

#endif
