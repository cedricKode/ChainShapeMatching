#include <Hair.h>

std::vector<Strand> Hair::getAllStrandsInHair() const
{
    return m_strandsInHair;
}

void Hair::addStrandsToTheHair(const Strand _strandtoadd)
{
    m_strandsInHair.push_back(_strandtoadd);
}

int Hair::getNumberOfStrandsInHair() const
{
    return m_strandsInHair.size();
}
