# Hair simulation by Chain Shape Matching

This is the basic hair simulation based on an algorithm of Chain Shape Matching. For graphical visualization were used NCCA NGL library and Qt User Interface. Testing of project was done with usage "Test Driven Developments" (TDD).

![alt tag](HairSimulation.gif)

## Requirements:

- NCCA NGL (https://github.com/NCCA/NGL)
- Eigen3 (https://eigen.tuxfamily.org/dox/)
- OpenGL (https://www.opengl.org/sdk/)
- QtCreator (https://www.qt.io/download)
- Google Tests for TDD (https://github.com/google/googletest)

## Running the system:

This project was build with usage QTCreator (5.11.2). To launch program, run the project file.

## Using the system:

The GUI can be navigated with usage the mouse. Also there is a number of parameters in User Interface which may affect simulation.

### Head Parameters

- *Position of Head*. This parameter changes position of the sphere, which is used as root of hair simulation.

- *Radius of Head*. This parameter changes radius of the sphere, which is used as root of hair simulation.

- *Number of Strands*. This parameter allows to change total number of strands, which take part in hair simulation. This parameter was limited between 1 and 2000, due to computational cost. 

- *Half Region Width*. This parameter changes the width of the region of each point. The region of each point consists of some number of neigbour points from the same strand. This parameter may be just an odd number integer from 1 to 7. It is possible to make this parameter bigger, but it will lead to the fact that the hair will become stiffer. Moreover, in observing the situation, when the distance between points in one strand is very small and there is no other obstacles except root sphere, it is hard to visually notice the difference in the simulation when this parameter changes.

### Forces

- *Gravity*. This parameter changes direction of gravity force.

- *Self Collision*. This parameter allows to enable or disable collision between hair strands. However, computational cost of this action is very high, so there is pop up warning message, which asks user again about his confidence in the perfect action. 

### Simulation
- *Sim* and *Reset*. This button allows to perform two types of actions: start simulation and reset simulation. After starting simulation, all other parameters are blocked. User may change initial parameters of simulation just after resetting simulation. 

## Test Driven Developments (TDD):

Test Driven Development was implemented with usage Google Tests. There were written some number of tests for various functions from various classes. Some of tests checks interaction within a class, e.g. setting and getting private parameters; some of them checks implementation of an algorythm. For example in a situation, when gravity force equals to zero, tests check that:
1. Matrix of Optimal Rotation between previous position and current position of each region of each point has to be identity. 
2. Goal position of each point, which computes on the basis of centers of mass and matrices of optimal rotation of regions to which belongs observing point, has to be equal to old position.
