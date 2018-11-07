#ifndef STRAND_H_
#define STRAND_H_
#include <vector>
#include "StrandPoint.h"

class Strand
{
public:

    Strand()=default;
    ~Strand()=default;
    Strand(const Strand &)=default;
    Strand(Strand &&)=default;
    Strand & operator =(const Strand &)=default;
    Strand & operator =(Strand &&)=default;

    std::vector<StrandPoint> getAllPointsInStrand() const;
    void addPointToTheStrand(const StrandPoint _pointtoadd);
    int getNumberOfPointInStrand();

    int getStrandId() const;
    void setStrandId(int _strandid);

private:
    std::vector<StrandPoint> m_pointsInStrand;

    int m_strandid;
};

#endif
