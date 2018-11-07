#ifndef HAIR_H_
#define HAIR_H_
#include "Strand.h"
//#include <Eigen/Jacobi>
#include <iostream>

typedef std::vector<StrandPoint*> listOfPoints;
//         rows(x)   columns(y)   depth(z)
typedef std::vector<std::vector<std::vector<listOfPoints>>> Texture3D;
// in this realisation Vec4 == ' R G B A '
typedef std::vector<std::vector<Vector4>> Texture2D;

class Hair
{
public:

    Hair()=default;
    ~Hair()=default;
    Hair(const Hair &)=default;
    Hair(Hair &&)=default;
    Hair & operator =(const Hair &)=default;
    Hair & operator =(Hair &&)=default;

    std::vector<Strand> getAllStrandsInHair() const;
    void addStrandsToTheHair(const Strand _strandtoadd);
    int getNumberOfStrandsInHair() const;

    void render() const;

    // ---------BEGIN TEXTURE DATA------------

    // initially we do not know dimensions of Textures. It have to be calculated from
    // number of all points (in all strands)
    // So this stage must be called just after creation of all points
    void set2DTextureDimensions(const int _nrow, const int _ncollumn);
    // 3d texture represent uniform grid, so it may have another dimensions
    // collision may be calulated just inside this "grid"
    void set3DTextureDimension(const int _nrow, const int _ncollumn, const int _nlevel);

    // Main data was made public
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

    // in each "voxel" we will list of pointers to strandPoints
    Texture3D m_voxeledUniformGridTex;

    // In this function will be implemented loop throught all voxels,
    // checking if voxel is not emplty -> goint to collision class for points in observing voxel
    // So Collision Library may have to be added later
    void runThrough3DTexture();

    // In this function will be implemented loop throught all textures (1st and 2nd )
    // and setting data to 7th to 10th Textures
    // Because of this we need Eigen (SVL calculation will take place)
    void calculationOfOptiomalTranslationAndRotation();

    // Other functions (for adding all info to widthIdStrandIdRestLengthTex etc) is still unknown
    // I am not sure, do I need to add them or not

     // ---------END TEXTURE DATA------------

private:
    std::vector<Strand> m_strandsInHair;

    int m_numOfRow2D;
    int m_numOfColumns2D;

    int m_numOfRow3D;
    int m_numOfColumns3D;
    int m_numOfLevels3D;
};

#endif
