#include "Strand.h"

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
    return m_pointsInStrand.size();
}

std::vector<StrandPoint> Strand::getAllPointsInStrand() const
{
    return m_pointsInStrand;
}

void Strand::addPointToTheStrand(const StrandPoint _pointtoadd)
{
    m_pointsInStrand.push_back(_pointtoadd);
}
