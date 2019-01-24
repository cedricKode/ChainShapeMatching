#include <QMouseEvent>
#include "NGLScene.h"
#include <iostream>
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/ShaderLib.h>


//---------------------------------------------------------------------------------------
NGLScene::NGLScene(QWidget *_parent ) : QOpenGLWidget(_parent )
{
  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on
  // construction)
  this->resize(_parent->size());
  m_timerValue = 10;
  startTimer(m_timerValue);
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags,
// defining display lists, etc.

//---------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{
    ngl::NGLInit::instance();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);

    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from( 0.0f, 20.0f, 20.0f );
    ngl::Vec3 to( 0.0f, 0.0f, 0.0f );
    ngl::Vec3 up( 0.0f, 1.0f, 0.0f );
    ngl::NGLInit::instance();
    m_view=ngl::lookAt(from,to,up);

    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_project=ngl::perspective(45.0f,720.0f/576.0f,0.5f,150.0f);

    //ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    //prim->createSphere("sphere",m_hair->getRadius(), 40);

    auto *shader=ngl::ShaderLib::instance();
    shader->use(ngl::nglDiffuseShader);
    shader->setUniform("Colour",1.0f,1.0f,0.0f,1.0f);
    shader->setUniform("lightPos",1.0f,1.0f,1.0f);
    shader->setUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);
}

//---------------------------------------------------------------------------------------
//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective(45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

//---------------------------------------------------------------------------------------
void NGLScene::loadMatricesToShader()
{
  auto *shader=ngl::ShaderLib::instance();
  (*shader)[ngl::nglDiffuseShader]->use();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;

  M=m_transform.getMatrix();
  MV=m_view *m_mouseGlobalTX*M;
  MVP=m_project*MV;
  normalMatrix=MV;
  normalMatrix.inverse().transpose();
  shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  shader->setUniform("normalMatrix",normalMatrix);
  shader->setUniform("M",M);
}

//---------------------------------------------------------------------------------------
void NGLScene::loadMatricesToColourShader()
{
  auto *shader=ngl::ShaderLib::instance();
  (*shader)[ngl::nglColourShader]->use();
  ngl::Mat4 MVP;
  MVP = m_project*m_view *
        m_mouseGlobalTX*
        m_transform.getMatrix();
  shader->setUniform("MVP",MVP);
}

//---------------------------------------------------------------------------------------
void NGLScene::setHair(Hair *_h)
{
    m_hair = _h;
    m_hair->createStrands();
    m_hair->originalCentersOfMass();
    m_hair->restLength();
}


//---------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void NGLScene::paintGL()
{
  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // clear the screen and depth buffer

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Rotation based on the mouse position for our global
  // transform
  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;

  // draw lines
  shader->use(ngl::nglColourShader);
  // get our position values and put in a vector
  shader->setUniform("Colour",1.0f,0.97f,0.86f,1.0f);
  m_transform.reset();
  loadMatricesToColourShader();
  // load transform stack
  std::unique_ptr<ngl::AbstractVAO> vao(ngl::VAOFactory::createVAO("simpleVAO",GL_LINES));

  // drawing lines of hair simulation
  std::vector<ngl::Vec3> allPointsPositionVector;
  for (auto s : m_hair->m_allPointsToDraw)
      allPointsPositionVector.push_back(s->getPosition());

  vao -> bind();
  vao -> setData(ngl::SimpleVAO::VertexData(allPointsPositionVector.size() *
                                            sizeof (ngl::Vec3),
                                            allPointsPositionVector[0].m_x));
  vao -> setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
  vao -> setNumIndices(allPointsPositionVector.size());
  vao -> draw();
  vao -> unbind();


  // get an instance of the VBO primitives for drawing
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  shader->use(ngl::nglDiffuseShader);
  // draw the head sphere
  shader->setUniform("Colour",0.8f,0.52f,0.24f,1.0f);
  m_transform.setScale(1.0f,1.0f,1.0f);
  m_transform.setPosition(m_hair->getPosition());
  loadMatricesToShader();
  prim->createSphere("sphere",m_hair->getRadius(), 40);
  prim->draw("sphere");
}
//---------------------------------------------------------------------------------------
void NGLScene::timerEvent( QTimerEvent *)
{
    float deltaTime = 0.1f;
    if (enableSimulation == true)
        m_hair->update(deltaTime);

    update();
}
//---------------------------------------------------------------------------------------
NGLScene::~NGLScene()
{

}
//---------------------------------------------------------------------------------------
void NGLScene::startSimulation()
{
    enableSimulation = true;
}
//---------------------------------------------------------------------------------------
void NGLScene::stopSimulation()
{
    enableSimulation = false;
}

