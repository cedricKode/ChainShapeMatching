TARGET=HairTests
SOURCES += main.cpp \
           ../Hair/src/Hair.cpp \
           ../Hair/src/Strand.cpp \
           ../Hair/src/StrandPoint.cpp

CONFIG+=c++11

INCLUDEPATH += /usr/local/include/

LIBS += -L/usr/local/lib -lgtest

INCLUDEPATH += ../Hair/include

cache()

CONFIG-=app_bundle
