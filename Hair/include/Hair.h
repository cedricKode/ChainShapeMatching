#ifndef HAIR_H_
#define HAIR_H_
#include "Strand.h"

//#include <Eigen/Jacobi>

#include <iostream>
#include "ngl/Vec3.h"
#include <cstring>

// This will be used later
#include "CollisionHairToHair.h"


// Data Storage -- 3D Texture, where width, hight and depth are not pre-defined
// Each cell (voxel) may store unknow number of points, so it was decided to
// use array(vector) with dynamic size
// Rows -> Collumns -> Depth
typedef std::vector<StrandPoint*> listOfPoints;
typedef std::unique_ptr<listOfPoints> Texture3D;

// Data Storage -- 2D Texture, where width and hight are not pre-defined
// PixelDepth == 4 (RGBA)
// Rows -> Collumns
typedef std::unique_ptr<float []> Texture2D;


class Hair
{
public:

    // ---------- HAIR INITIALIZING PART -----------------

    Hair()=default;
    Hair(const ngl::Vec3 &_headPosition, float _radiusOfHead,
         size_t _numStrands);
    Hair(const Hair &)=default;

    size_t getNumberOfStrandsInHair() const;

    void render() const;
    // Main function for executing updation of all points position
    void update();

    // ----------- HAIR TEXTURE DATA PART ----------------

    // This function is planning to be a creation of [0] matrixes, according to
    // number of strands and number of points. We are not able to make matrixes in advance,
    // because we do not know this values
    void set2DTextures();
    // This function is planning to be a creation of [0] matrix, according to
    // head position. We are not able to make matrix in advance,
    // because we do not know this value
    void set3DTexture();

    Texture2D m_oldPositionTex; //1st
    Texture2D m_newPositionTex; // 2nd
    Texture2D m_oldVelocityTex;
    Texture2D m_newVelocityTex;
    Texture2D m_widthIdStrandIdRestLengthTex;
    Texture2D m_initialPositionTex;
    Texture2D m_optimalTransformationTex; //7th
    Texture2D m_optimalRotation1RowTex; // 8th
    Texture2D m_optimalRotation2RowTex; // 9th
    Texture2D m_optimalRotation3RowTex; // 10th

    Texture3D m_voxeledUniformGridTex;

    // Next to functions are planning to be used in update() method

    // In this function will be implemented loop throught 1st and 2nd textures
    // and setting data to 7th to 10th Textures
    // Because of this we need Eigen (SVL calculation will take place)
    void calculationOfOptiomalTranslationAndRotation();

    // In this function loop throught all voxels will be implemented.
    // If voxel is not emplty -> go to collision class for points
    // inside observing voxel
    void runThrough3DTexture();

    // Output data for all strands in hair simulation
    void render();

     // ---------END TEXTURE DATA------------

private:

    size_t m_numStrands = 0;

    std::vector<Strand> m_strandsInHair;
    ngl::Vec3 m_position;
};

#endif
