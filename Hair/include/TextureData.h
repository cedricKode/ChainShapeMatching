#ifndef TEXTUREDATA_H_
#define TEXTUREDATA_H_
#include "ngl/Vec4.h"
#include "ngl/Vec3.h"
#include "Hair.h"
#include <Eigen/Jacobi>
#include <iostream>

typedef std::vector<StrandPoint*> listOfPoints;
//         rows(x)   columns(y)   depth(z)
typedef std::vector<std::vector<std::vector<listOfPoints>>> Texture3D;
// in this realisation Vec4 == ' R G B A '
typedef std::vector<std::vector<ngl::Vec4>> Texture2D;

class textureData
{
public:

    // not to forget after initialisation -- set dimensions for all Textures
    // it will be better to create another textureData object (in code) for 3d Texture,
    // because it may have another dimensions
    // Let's just predefine number of levels (depth) to 0; 2d textures do not have depth (z) coordinate
    textureData(const int _numOfRow, const int _numOfColumns, const int _numOfLevels = 0);

    ngl::Vec3 getTextureDimensions() const;

    ~textureData()=default;
    textureData(const textureData &)=default;

    // Main data was made public
    Texture2D m_oldPositionTex;
    Texture2D m_newPositionTex;
    Texture2D m_oldVelocityTex;
    Texture2D m_newVelocityTex;
    Texture2D m_widthIdStrandIdRestLengthTex;
    Texture2D m_initialPositionTex;
    Texture2D m_optimalTransformationTex;
    Texture2D m_optimalRotation1RowTex;
    Texture2D m_optimalRotation2RowTex;
    Texture2D m_optimalRotation3RowTex;

    // in each "voxel" we will list of pointers to strandPoints
    Texture3D m_voxeledUniformGridTex;

    void setPointInOldPositionTex(const int _row, const int _column);
    void setPointInNewPositionTex(const int _row, const int _column);
    void setPointInOldVelocityTex(const int _row, const int _column);
    void setPointInNewVelocityTex(const int _row, const int _column);
    void setPointInWidthIdStrandIdRestLengthTex(const int _row, const int _column);
    void setPointInInitialPositionTex(const int _row, const int _column);
    void setPointInOptimalTransformationTex(const int _row, const int _column);
    void setPointInOptimalRotation1RowTex(const int _row, const int _column);
    void setPointInOptimalRotation2RowTex(const int _row, const int _column);
    void setPointInOptimalRotation3RowTex(const int _row, const int _column);

    StrandPoint getPointFromTex (const Texture2D _texture, const int _row, const int _column);

private:

    int m_numOfRow;
    int m_numOfColumns;
    int m_numOfLevels;

};

#endif
