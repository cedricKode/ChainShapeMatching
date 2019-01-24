#include "MainWindow.h"
#include "ui_MainWindow.h"

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{


	// setup the user interface
	m_ui->setupUi(this);

    m_gl=new  NGLScene(this);
	// add the glWindow to the UI
	m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,4,1);

    // Take position of head from parameters
    ngl::Vec3 _headPosition(float(m_ui->m_aX->value()),
                            float(m_ui->m_aY->value()),
                            float(m_ui->m_aZ->value()));

    // Create Hair Simulation
    m_hair = new Hair (_headPosition,
                       float(m_ui->m_radius->value()),
                       size_t(m_ui->m_numStrands->value()),
                       size_t(m_ui->m_halfRegionWidth->value()));

    // Assign hair simulation in NGLScene file
    m_gl->setHair(m_hair);

    // Connect all UI elements with functions
    // Number of strands
    connect(m_ui->m_numStrands,SIGNAL(valueChanged(int)),this,SLOT(setNumberOfStrands()));

    // Position of the head
    connect(m_ui->m_aX,SIGNAL(valueChanged(double)),this,SLOT(setHeadPosition()));
    connect(m_ui->m_aY,SIGNAL(valueChanged(double)),this,SLOT(setHeadPosition()));
    connect(m_ui->m_aZ,SIGNAL(valueChanged(double)),this,SLOT(setHeadPosition()));

    // Radius of the head
    connect(m_ui->m_radius,SIGNAL(valueChanged(double)),this,SLOT(setHeadRadius()));

    // Half region width
    connect(m_ui->m_halfRegionWidth,SIGNAL(valueChanged(int)),this,SLOT(setHalfRegionWidth()));

    // Gravity force
    connect(m_ui->m_gravityX,SIGNAL(valueChanged(double)),this,SLOT(setGravity()));
    connect(m_ui->m_gravityY,SIGNAL(valueChanged(double)),this,SLOT(setGravity()));
    connect(m_ui->m_gravityZ,SIGNAL(valueChanged(double)),this,SLOT(setGravity()));

    // Self collision toggle
    connect(m_ui->m_selfCollision,SIGNAL(clicked(bool)),this,SLOT(setSelfCollision()));

    // Simulation button
	connect(m_ui->m_sim,SIGNAL(clicked(bool)),this,SLOT(toggleSim(bool)));
}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_hair;
    delete m_ui;
}

//---------------------------------------------------------------------------------------
void MainWindow::setNumberOfStrands()
{
    size_t numStrands = size_t(m_ui->m_numStrands->value());
    m_hair->setNumberOfStrandsInHair(numStrands);
    m_hair->clear();
    m_hair->createStrands();

    m_hair->originalCentersOfMass();
    m_hair->restLength();
}
//---------------------------------------------------------------------------------------
void MainWindow::setHeadPosition()
{
    ngl::Vec3 position(float(m_ui->m_aX->value()),
                       float(m_ui->m_aY->value()),
                       float(m_ui->m_aZ->value()));
    m_hair->setPosition(position);
    m_hair->clear();
    m_hair->createStrands();

    m_hair->originalCentersOfMass();
    m_hair->restLength();
}
//---------------------------------------------------------------------------------------
void MainWindow::setHeadRadius()
{
    float headRadius = float(m_ui->m_radius->value());
    m_hair->setRadius(headRadius);
    m_hair->clear();
    m_hair->createStrands();

    m_hair->originalCentersOfMass();
    m_hair->restLength();
}
//---------------------------------------------------------------------------------------
void MainWindow::setGravity()
{
    ngl::Vec3 gravity(float(m_ui->m_gravityX->value()),
                       float(m_ui->m_gravityY->value()),
                       float(m_ui->m_gravityZ->value()));
    m_hair->setGravityForce(gravity);
}
//---------------------------------------------------------------------------------------
void MainWindow::setHalfRegionWidth()
{
    // Half region width may be just odd integer value from 1 to 7

    size_t halfRegionWidth = size_t(m_ui->m_halfRegionWidth->value());
    if (halfRegionWidth % 2 == 0)
    {
        halfRegionWidth += 1;
        m_ui->m_halfRegionWidth->setValue(int(halfRegionWidth));
    }
    if (halfRegionWidth > 7)
    {
        m_ui->m_halfRegionWidth->setValue(7);
        halfRegionWidth = 7;
    }
    m_hair->setHalfRegionWidth(halfRegionWidth);
}
//---------------------------------------------------------------------------------------
void MainWindow::setSelfCollision()
{
    // Due to the fact, that self collision is very computationally expensive operation,
    // there is pop up message, which asks user about his confidence in performed action
    if (m_ui->m_selfCollision->isChecked())
    {
        QMessageBox::StandardButton selfCollisionWarning;
        selfCollisionWarning = QMessageBox::question(this, "Self Collision",
                               "Are you sure want to enable Self Collision? \n"
                               "This will significantly slow down simulation.",
                               QMessageBox::Yes|QMessageBox::No);
          if (selfCollisionWarning == QMessageBox::Yes)
          {
            m_ui->m_selfCollision->setChecked(true);
            m_hair->setSelfCollision(true);
          }
          else
          {
            m_ui->m_selfCollision->setChecked(false);
            m_hair->setSelfCollision(false);
          }
    }
    else
    {
        m_hair->setSelfCollision(false);
    }
}
//---------------------------------------------------------------------------------------
void MainWindow::toggleSim(bool _s)
{
    if(_s == false)
    {
        m_gl->startSimulation();
        m_ui->m_sim->setText("reset");
        // Hide all other parameters. It is done because user do not have to able
        // to change any parameter during the simulation
        m_ui->m_aX->setEnabled(false);
        m_ui->m_aY->setEnabled(false);
        m_ui->m_aZ->setEnabled(false);
        m_ui->m_radius->setEnabled(false);
        m_ui->m_halfRegionWidth->setEnabled(false);
        m_ui->m_gravityX->setEnabled(false);
        m_ui->m_gravityY->setEnabled(false);
        m_ui->m_gravityZ->setEnabled(false);
        m_ui->m_selfCollision->setEnabled(false);
        m_ui->m_numStrands->setEnabled(false);
    }
    else
    {
        m_gl->stopSimulation();
        m_hair->updateSimulation();
        m_ui->m_sim->setText("sim");
        // Unhide all other parameters. Because simulation was reseted, user may be able
        // to change any parameter.
        m_ui->m_aX->setEnabled(true);
        m_ui->m_aY->setEnabled(true);
        m_ui->m_aZ->setEnabled(true);
        m_ui->m_radius->setEnabled(true);
        m_ui->m_halfRegionWidth->setEnabled(true);
        m_ui->m_gravityX->setEnabled(true);
        m_ui->m_gravityY->setEnabled(true);
        m_ui->m_gravityZ->setEnabled(true);
        m_ui->m_selfCollision->setEnabled(true);
        m_ui->m_numStrands->setEnabled(true);
    }
}
