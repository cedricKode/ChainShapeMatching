//---------------------------------------------------------------------------------------
/// @file Strand.h
/// @brief This class inherits from Strand class. It contains the smallest element
/// (point) of hair simulation.
/// @author Daria Kozlova
/// @version 1.0
/// @date 15/01/19
/// @class StrandPoint
//---------------------------------------------------------------------------------------

#ifndef STRANDPOINT_H_
#define STRANDPOINT_H_

#include <iostream>

#include <Eigen/Jacobi>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <Eigen/Dense>

#include "ngl/Vec3.h"

class StrandPoint
{
  public:

    StrandPoint()=default;
    //-----------------------------------------------------------------------------------
    /// @brief ctor for Point class
    /// @param _position original position of the point
    /// @param _velocity original velocity of the point
    /// @param _mass mass of the point
    /// @param _regionWidth half width of the region of the point
    //-----------------------------------------------------------------------------------
    StrandPoint(ngl::Vec3 &_position,
                ngl::Vec3 &_velocity,
                float _mass,
                size_t _regionWidth);

    ~StrandPoint()=default;
    StrandPoint(const StrandPoint &)=default;
    StrandPoint(StrandPoint &&)=default;
    StrandPoint & operator =(const StrandPoint &)=default;
    StrandPoint & operator =(StrandPoint &&)=default;

    //-----------------------------------------------------------------------------------
    /// @brief method to get position of the point
    /// @return vector of position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getPosition() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get old position of the point (from previous step of simulation)
    /// @return vector of old position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getOldPosition() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get initial position of the point (from the first step of
    /// simulation)
    /// @return vector of initial position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getOriginalPosition() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set position of the point
    /// @param _pos vector of current position of the point
    //-----------------------------------------------------------------------------------
    void setPosition(const ngl::Vec3  &_pos);
    //-----------------------------------------------------------------------------------
    /// @brief method to get goal position of the point
    /// @return vector of goal position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getGoalPosition() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set goal position of the point
    /// @param _goalPos vector of goal position of the point
    //-----------------------------------------------------------------------------------
    void setGoalPosition(const ngl::Vec3  &_goalPos);

    //-----------------------------------------------------------------------------------
    /// @brief method to get velocity of the point
    /// @return vector of velocity of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getVelocity() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set velocity of the point
    /// @param _vel vector of velocity of the point
    //-----------------------------------------------------------------------------------
    void setVelocity(const ngl::Vec3  &_vel);

    size_t getPointId() const;
    size_t getPointIdInVector() const;
    size_t getStrandId() const;
    void setPointId(size_t _pointid, size_t _strandid);
    void setPointIdInVector(size_t _pointidinvector);

    //-----------------------------------------------------------------------------------
    /// @brief method to get mass of the point
    /// @return float value of mass of the point
    //-----------------------------------------------------------------------------------
    float getMass() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get distance from the point to the next point in the same strand
    /// at initial step of simulation
    /// @return float value of distance to the next point from the same strand
    //-----------------------------------------------------------------------------------
    float getRestLength() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set distance from the point to the next point in the same strand
    /// at initial step of simulation
    /// @param _length float value of distance to the next point from the same strand
    //-----------------------------------------------------------------------------------
    void setRestLength(float _length);
    //-----------------------------------------------------------------------------------
    /// @brief method to get half width of the region of the neigbour points from the
    /// same strand
    /// @return integer value of half width of the region of the point
    //-----------------------------------------------------------------------------------
    size_t getRegionWidth() const;

    //-----------------------------------------------------------------------------------
    /// @brief method to find indices of the points, which belong to the region of the
    /// observed point; and to calculate initial center of the mass of the region
    /// @param _regionOfPoints indices of the points, which belong to the region of the
    /// observed point
    /// @param _centerOfMass initial center of the mass of the region
    //-----------------------------------------------------------------------------------
    void setRegionOfPointsAndCenterOfMass(std::vector <size_t> _regionOfPoints,
                                          ngl::Vec3 _centerOfMass);
    //-----------------------------------------------------------------------------------
    /// @brief method to get vector of indices of the points, which belong to the region
    /// of the observed point
    /// @return vector of indices of the points, which belong to the region of the
    /// observed point
    //-----------------------------------------------------------------------------------
    std::vector <size_t> getIndiciesOfRegionOfPointstor() const;

    //-----------------------------------------------------------------------------------
    /// @brief method to clear value of external forces
    //-----------------------------------------------------------------------------------
    void clearExtForce();
    //-----------------------------------------------------------------------------------
    /// @brief method to add gravity force to the external forces
    /// @param _gravityForce vector of direction of the gravity
    //-----------------------------------------------------------------------------------
    void addGravityForce(ngl::Vec3 &_gravityForce);
    //-----------------------------------------------------------------------------------
    /// @brief method to add collision (with the head) force to the external forces
    /// @param _headPosition position of the head
    /// @param _headRadius radius of the head
    //-----------------------------------------------------------------------------------
    void addCollisionWithHeadForce(ngl::Vec3 _headPosition,
                                   float _headRadius);
    //-----------------------------------------------------------------------------------
    /// @brief method to add collision (between strands) force to the external forces
    /// @param _pointToCollideWith another point to check collision (between observed
    /// point and another point)
    //-----------------------------------------------------------------------------------
    void addSelfCollision(StrandPoint _pointToCollideWith);

    //-----------------------------------------------------------------------------------
    /// @brief method to update position and velocity of the point according to external
    /// forces
    /// @param _timeStep delta time of simulation
    /// @param _headPosition position of the head
    /// @param _headRadius radius of the head
    //-----------------------------------------------------------------------------------
    void updatePositionAndVelocity(float _timeStep, ngl::Vec3 _headPosition,
                                   float _headRadius);

    //-----------------------------------------------------------------------------------
    /// @brief method to set goal position of the point
    /// @param _goalPosition vector of goal position of the point
    //-----------------------------------------------------------------------------------
    void goalPosition(ngl::Vec3 _goalPosition);

    //-----------------------------------------------------------------------------------
    /// @brief method to get matrix of optimal rotation between old and current position
    /// of region of points
    /// @return matrix of optimal rotation
    //-----------------------------------------------------------------------------------
    Eigen:: MatrixXf getOptimalRotation() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get vector of optimal translation between old and current
    /// position of region of points
    /// @return vector of optimal translation
    //-----------------------------------------------------------------------------------
    Eigen::VectorXf getOptimalTranslation() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set vector of optimal translation and matrix of optimal rotation
    /// between old and current position of region of points
    /// @param _optimalRotation vector of optimal translation
    /// @param _optimalTranslation matrix of optimal rotation
    //-----------------------------------------------------------------------------------
    void optimalTransformation(Eigen:: MatrixXf _optimalRotation,
                               Eigen::VectorXf _optimalTranslation);

    //-----------------------------------------------------------------------------------
    /// @brief method update poisition and velocity of the point according to goal
    /// position
    /// @param _timeStep delta time of simulation
    //-----------------------------------------------------------------------------------
    void updatePositionAndVelocityByGoalPosition(float _timeStep);

    //-----------------------------------------------------------------------------------
    /// @brief method to get original center of the mass of the region of observed point
    /// @return original center of the mass of the region
    //-----------------------------------------------------------------------------------
    Eigen::Vector3f getOriginalCenterOfMassOfRegion() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to get current center of the mass of the region of observed point
    /// @return current center of the mass of the region
    //-----------------------------------------------------------------------------------
    ngl::Vec3 getCurrentCenterOfMassOfRegion() const;
    //-----------------------------------------------------------------------------------
    /// @brief method to set current center of the mass of the region of observed point
    /// @param _currentCenterOfMass current center of the mass of the region
    //-----------------------------------------------------------------------------------
    void setCurrentCenterOfMassOfRegion(ngl::Vec3 _currentCenterOfMass);

    //-----------------------------------------------------------------------------------
    /// @brief method to print position point
    //-----------------------------------------------------------------------------------
    void render();
    //-----------------------------------------------------------------------------------
    /// @brief method to reset all not initial parameters of the point
    //-----------------------------------------------------------------------------------
    void updateSimulation();

private:

    //-----------------------------------------------------------------------------------
    /// @brief id of strand to which belongs point
    //-----------------------------------------------------------------------------------
    size_t m_strandId;
    //-----------------------------------------------------------------------------------
    /// @brief point id number (regarding to the strand)
    //-----------------------------------------------------------------------------------
    size_t m_pointId;
    //-----------------------------------------------------------------------------------
    /// @brief point id number (regarding to the vector of all points in Hair simulation)
    //-----------------------------------------------------------------------------------
    size_t m_pointidInVector;

    //-----------------------------------------------------------------------------------
    /// @brief initial position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_originalPosition;   
    //-----------------------------------------------------------------------------------
    /// @brief current position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3  m_position;
    //-----------------------------------------------------------------------------------
    /// @brief old position of the point (position from the precious step of simulation)
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_oldPosition;
    //-----------------------------------------------------------------------------------
    /// @brief goal position of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3  m_goalPosition;

    //-----------------------------------------------------------------------------------
    /// @brief initial center of the mass of the region of observed point
    //-----------------------------------------------------------------------------------
    Eigen::Vector3f m_originalCenterOfMassOfRegion;
    //-----------------------------------------------------------------------------------
    /// @brief current center of the mass of the region of observed point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_currentCenterOfMassOfRegion;

    //-----------------------------------------------------------------------------------
    /// @brief current velocity of the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3  m_velocity = {0,0,0};
    //-----------------------------------------------------------------------------------
    /// @brief old velocity of the point (velocity from the precious step of simulation)
    //-----------------------------------------------------------------------------------
    ngl::Vec3  m_oldVelocity = {0,0,0};

    //-----------------------------------------------------------------------------------
    /// @brief mass of the point
    //-----------------------------------------------------------------------------------
    float m_mass;
    //-----------------------------------------------------------------------------------
    /// @brief distance from the point to the next point in the same strand at initial
    /// step of simulation
    //-----------------------------------------------------------------------------------
    float m_restLength;

    //-----------------------------------------------------------------------------------
    /// @brief half width of the region of the neigbour points from the same strand
    //-----------------------------------------------------------------------------------
    size_t m_width;
    //-----------------------------------------------------------------------------------
    /// @brief vector of IDs of points, which belong to the region of observed point
    //-----------------------------------------------------------------------------------
    std::vector <size_t> m_indiciesOfRegionOfPoints;

    //-----------------------------------------------------------------------------------
    /// @brief sum of exterior forces which influence to the point
    //-----------------------------------------------------------------------------------
    ngl::Vec3 m_forceExt = {0,0,0};

    //-----------------------------------------------------------------------------------
    /// @brief matrix of optimal rotation between old and current position of region of
    /// points
    //-----------------------------------------------------------------------------------
    Eigen:: MatrixXf m_optimalRotation;
    //-----------------------------------------------------------------------------------
    /// @brief matrix of optimal translation between old and current position of region
    /// of points
    //-----------------------------------------------------------------------------------
    Eigen::VectorXf m_optimalTranslation;
};

#endif
