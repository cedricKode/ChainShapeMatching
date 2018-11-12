#include <Hair.h>
#include <random>
#include <math.h>

size_t Hair::getNumberOfStrandsInHair() const
{
    return m_numStrands;
}

Hair::Hair(const ngl::Vec3 &_headPosition, float _radiusOfHead,
           size_t _numStrands)
{

    m_position = _headPosition;
    m_numStrands = _numStrands;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angle1(0.0f, 360.0f);
    std::uniform_real_distribution<float> angle2(0.0f, 360.0f);

    std::uniform_real_distribution<float> distanceInsideStrand(0.4f, 0.5f);

    std::uniform_real_distribution<> numOfPointsInStrand(8, 10);


    for (size_t i = 0; i < _numStrands; i++)
    {
        // Creating some number of root points on head (which equals to sphere in this implementation)
        // Root point equals to direction (vector from head center to root point)
        float angle1Num = angle1(gen);
        float angle2Num = angle2(gen);
        float x = _headPosition.m_x + _radiusOfHead * std::sin(angle1Num) * std::cos(angle2Num);
        float y = _headPosition.m_y + _radiusOfHead * std::sin(angle1Num) * std::sin(angle2Num);
        float z = _headPosition.m_z + _radiusOfHead *  std::cos(angle1Num);

        ngl::Vec3 firstPoint(x,y,z);
        ngl::Vec3 strandDirection = firstPoint - _headPosition;

        Strand s(firstPoint, strandDirection, numOfPointsInStrand(gen), distanceInsideStrand(gen));
        s.setStrandId(i);
        m_strandsInHair.push_back(s);
    }

}

void Hair::render()
{
    for (auto s : m_strandsInHair)
        s.render();
}
