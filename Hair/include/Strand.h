//---------------------------------------------------------------------------------------
/// @file Strand.h
/// @brief This class inherits from Hair class and inherits by StrandPoint class
/// @author Daria Kozlova
/// @version 1.0
/// @date 15/01/19
/// @class Strand
//---------------------------------------------------------------------------------------

#ifndef STRAND_H_
#define STRAND_H_

#include <cstring>
#include <vector>

#include "StrandPoint.h"

class Hair;

class Strand
{
  public:

    Strand()=default;
    //-----------------------------------------------------------------------------------
    /// @brief ctor for one Strand
    /// @param _hair reference to the whole Hair simulation
    //-----------------------------------------------------------------------------------
    Strand(Hair *_hair) : m_hair(_hair){}

    ~Strand()=default;
    Strand(const Strand &)=default;
    Strand(Strand &&)=default;
    Strand & operator =(const Strand &)=default;
    Strand & operator =(Strand &&)=default;

    //-----------------------------------------------------------------------------------
    /// @brief method to add reference of one point to the vector of all points, which
    /// belong to observed strand
    /// @param _p points to add to the vector
    //-----------------------------------------------------------------------------------
    void addPointToStrand(StrandPoint *_p) {m_pointsInStrandRef.push_back(_p);}
    //-----------------------------------------------------------------------------------
    /// @brief method to get the vector of all points, which belong to observed strand
    /// @return vector of references to points, which belong to observed strand
    //-----------------------------------------------------------------------------------
    std::vector<StrandPoint *> getAllRefPointsInStrand() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get number of points, which belong to observed strand
    /// @return integer number of points, which belong to observed strand
    //-----------------------------------------------------------------------------------
    size_t getNumberOfPointInStrand();
    //-----------------------------------------------------------------------------------
    /// @brief method to get strand id number
    /// @return integer number of strand id
    //-----------------------------------------------------------------------------------
    size_t getStrandId() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set strand id number
    /// @param _strandid integer number of strand id
    //-----------------------------------------------------------------------------------
    void setStrandId(size_t _strandid);

    //-----------------------------------------------------------------------------------
    /// @brief method to calculate original centers of mass for all regions of points,
    /// which belong to observed strand
    //-----------------------------------------------------------------------------------
    void originalCentersOfMass();
    //-----------------------------------------------------------------------------------
    /// @brief method to calculate current centers of mass for all regions of points,
    /// which belong to observed strand
    //-----------------------------------------------------------------------------------
    void currentCenterOfTheMass();

    //-----------------------------------------------------------------------------------
    /// @brief method to calculate optimal rotation and optimal translation between
    /// old and current position for all regions of points, which belong to observed
    /// strand
    //-----------------------------------------------------------------------------------
    void optimalTransformation();
    //-----------------------------------------------------------------------------------
    /// @brief method to calculate goal position for all points which belong to observed
    /// strand
    //-----------------------------------------------------------------------------------
    void goalPosition();

    //-----------------------------------------------------------------------------------
    /// @brief method to preserve stretching of the goal positions of points in observed
    /// strand
    //-----------------------------------------------------------------------------------
    void strainLimitingGoalPosition();
    //-----------------------------------------------------------------------------------
    /// @brief method to preserve stretching of the final positions of points in
    /// observed strand
    //-----------------------------------------------------------------------------------
    void strainLimitingPosition();

    //-----------------------------------------------------------------------------------
    /// @brief method to print position of all points from observed strand
    //-----------------------------------------------------------------------------------
    void render();

    //-----------------------------------------------------------------------------------
    /// @brief reference to whole Hair simulation
    //-----------------------------------------------------------------------------------
    Hair *m_hair;

private:
    //-----------------------------------------------------------------------------------
    /// @brief vector of references to points, which belong to observed strand
    //-----------------------------------------------------------------------------------
    std::vector<StrandPoint *> m_pointsInStrandRef;
    //-----------------------------------------------------------------------------------
    /// @brief strand id number
    //-----------------------------------------------------------------------------------
    size_t m_strandid;
};

#endif
