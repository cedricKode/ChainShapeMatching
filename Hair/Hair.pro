TARGET=Hair
SOURCES += src/main.cpp \
           src/Hair.cpp \
           src/Strand.cpp \
           src/StrandPoint.cpp \
    src/CollisionHairToHair.cpp

HEADERS += include/Hair.h \
           include/Strand.h \
           include/StrandPoint.h \
    include/CollisionHairToHair.h

INCLUDEPATH += ./include

QMAKE_CXXFLAGS += $$system(pkg-config --cflags eigen3)
INCLUDEPATH += /usr/local/include/eigen3/

include($(HOME)/NGL/UseNGL.pri)

CONFIG += c++11

QT += opengl

cache()

CONFIG-=app_bundle
