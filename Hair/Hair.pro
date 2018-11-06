TARGET=Particle
SOURCES += src/main.cpp \
           src/Hair.cpp \
           src/Strand.cpp \
           src/StrandPoint.cpp \
           src/Collision.cpp

HEADERS += include/Hair.h \
           include/Strand.h \
           include/StrandPoint.h \
           include/Collision.h \
           include/Vector.h

INCLUDEPATH += ./include

QMAKE_CXXFLAGS += $$system(pkg-config --cflags eigen3)
INCLUDEPATH += /usr/local/include/eigen3

include($(HOME)/NGL/UseNGL.pri)

CONFIG += c++11

QT += opengl

cache()
