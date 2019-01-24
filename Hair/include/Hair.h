//---------------------------------------------------------------------------------------
/// @file Hair.h
/// @brief This is the main class of hair simulation and all other classes inherit
/// form this
/// @author Daria Kozlova
/// @version 1.0
/// @date 15/01/19
/// @class Hair
//---------------------------------------------------------------------------------------

#ifndef HAIR_H_
#define HAIR_H_

#include <cstring>

#include <ngl/Vec3.h>

#include "Strand.h"

class Hair
{
  public:

    Hair()=default;
    //-----------------------------------------------------------------------------------
    /// @brief ctor for Hair simulation class
    /// @param _headPosition original position of the sphere root
    /// @param _radiusOfHed radius of the sphere root
    /// @param _numStrands number of strands in hair simulation
    /// @param _halfRegionWidth integer odd number of half width of region of each point
    //-----------------------------------------------------------------------------------
    Hair(const ngl::Vec3 &_headPosition, float _radiusOfHead,
         size_t _numStrands, size_t _halfRegionWidth);
    //-----------------------------------------------------------------------------------
    Hair(const Hair &)=default;
    //-----------------------------------------------------------------------------------
    /// @brief copy ctor for Hair simulation class
    //-----------------------------------------------------------------------------------
    Hair& operator =(Hair &other)
    {
        m_numStrands = other.m_numStrands;
        m_strandsInHair = other.m_strandsInHair;
        m_allPoints = other.m_allPoints;
        m_position = other.m_position;
        m_radiusOfHead = other.m_radiusOfHead;
        return *this;
    }

    //-----------------------------------------------------------------------------------
    /// @brief method to get total number of strands in Hair simulation
    /// @return integer number of strands in Hair simulation
    //-----------------------------------------------------------------------------------
    size_t getNumberOfStrandsInHair() const;   
    //-----------------------------------------------------------------------------------
    /// @brief method to set total number of strands in Hair simulation
    /// @param _numStrands integer number of strands in Hair simulation
    //-----------------------------------------------------------------------------------
    void setNumberOfStrandsInHair(size_t &_numStrands);
    //-----------------------------------------------------------------------------------
    /// @brief method to get position of the sphere root
    /// @return vector of position of the head
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getPosition() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set position of the sphere root
    /// @param _pos vector of position of the head
    //-----------------------------------------------------------------------------------
    void setPosition(ngl::Vec3 _pos);
    //-----------------------------------------------------------------------------------
    /// @brief method to get radius of the sphere root
    /// @return float value of radius of the head
    //-----------------------------------------------------------------------------------
    float getRadius() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set radius of the sphere root
    /// @param _radius float value of radius of the head
    //-----------------------------------------------------------------------------------
    void setRadius(float &_radius);

    //-----------------------------------------------------------------------------------
    /// @brief method to create number of strands with random number of points in it.
    //-----------------------------------------------------------------------------------
    void createStrands();
    //-----------------------------------------------------------------------------------
    /// @brief method to calculate original centers of mass for all regions, which will
    /// take part in Chain Shape Matching algorithm
    //-----------------------------------------------------------------------------------
    void originalCentersOfMass();
    //-----------------------------------------------------------------------------------
    /// @brief method to calculate distance between point and the next point in the
    /// initial step of simulation
    //-----------------------------------------------------------------------------------
    void restLength();
    //-----------------------------------------------------------------------------------
    /// @brief method to set gravity force to Hair simulation
    /// @param _gravity vector of gravity direction
    //-----------------------------------------------------------------------------------
    void setGravityForce(ngl::Vec3 &_gravity);
    //-----------------------------------------------------------------------------------
    /// @brief method to get gravity force in Hair simulation
    /// @return vector of gravity direction
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getGravityForce() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to enable or disable self collision in Hair simulation
    /// @param _selfCollisionToggle switcher to enable or disable self collision in
    /// Hair simulation
    //-----------------------------------------------------------------------------------
    void setSelfCollision(bool _selfCollisionToggle);
    //-----------------------------------------------------------------------------------
    /// @brief method to set half region width for each point in Hair simulation
    /// @param _halfRegionWidth odd integer number between 1 and 7
    //-----------------------------------------------------------------------------------
    void setHalfRegionWidth(size_t _halfRegionWidth);

    //-----------------------------------------------------------------------------------
    /// @brief method to reset Hair Simulation
    //-----------------------------------------------------------------------------------
    void updateSimulation();
    //-----------------------------------------------------------------------------------
    /// @brief main function for updating all points' position
    /// @param _timeStep delta time in Hair Simulation
    //-----------------------------------------------------------------------------------
    void update(float _timeStep);
    //-----------------------------------------------------------------------------------
    /// @brief method to print position of all points in all strands in Hair Simulation
    //-----------------------------------------------------------------------------------
    void render();
    //-----------------------------------------------------------------------------------
    /// @brief method to clear all vector parameters in Hair Simulation
    //-----------------------------------------------------------------------------------
    void clear();

    //-----------------------------------------------------------------------------------
    /// @brief vector of all strands in Hair Simulation
    //-----------------------------------------------------------------------------------
    std::vector<Strand> m_strandsInHair;
    //-----------------------------------------------------------------------------------
    /// @brief vector of all points in Hair Simulation
    //-----------------------------------------------------------------------------------
    std::vector<StrandPoint> m_allPoints;
    //-----------------------------------------------------------------------------------
    /// @brief vector of pointers to all points in Hair Simulation
    //-----------------------------------------------------------------------------------
    std::vector<StrandPoint *> m_allPointsToDraw;

private:

    //-----------------------------------------------------------------------------------
    /// @brief total number of strands in Hair Simulation
    //-----------------------------------------------------------------------------------
    size_t m_numStrands = 0;

    //-----------------------------------------------------------------------------------
    /// @brief radius of the root sphere
    //-----------------------------------------------------------------------------------
    float m_radiusOfHead = 0;
    //-----------------------------------------------------------------------------------
    /// @brief position of the root sphere
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_position;
    //-----------------------------------------------------------------------------------
    /// @brief switcher to enable or disable collision between strands
    //-----------------------------------------------------------------------------------
    bool m_enableSelfCollision = false;
    //-----------------------------------------------------------------------------------
    /// @brief size of the half region width of each point in hair simulation
    //-----------------------------------------------------------------------------------
    size_t m_halfRegionWidth = 3;

    //-----------------------------------------------------------------------------------
    /// @brief constant gravity force, which influence to all points in Hair simulation
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_gravity = {0.0f, -9.8f, 0.0f};
};

#endif
