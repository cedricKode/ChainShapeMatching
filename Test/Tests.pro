TARGET=HairTests
SOURCES += main.cpp \
           ../Hair/src/Hair.cpp \
           ../Hair/src/Strand.cpp \
           ../Hair/src/StrandPoint.cpp

CONFIG+=c++11

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/eigen3

LIBS += -L/usr/local/lib -lgtest

INCLUDEPATH += ../Hair/include

cache()

NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}


CONFIG-=app_bundle
