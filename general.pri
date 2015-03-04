################################################################################
deploybin = ../../SBDeploy/bin
CONFIG (debug, debug|release){
    inputbin = bin/debug
    destination = ./bin/debug
}
else{
    inputbin = bin/release
    destination = ./bin/release    
}

################################################################################
OBJECTS_DIR = $$destination/obj
UI_DIR = $$destination/ui
MOC_DIR = $$destination/moc
RCC_DIR = $$destination/rcc
DESTDIR = $$destination

################################################################################
INCLUDEPATH += \
    ./include \
    ./src/private \
    $$UI_DIR

################################################################################
win32-msvc2013:{
    QMAKE_CXXFLAGS_RELEASE += -Zi
    QMAKE_CXXFLAGS += /WX
    QMAKE_LFLAGS_RELEASE += /DEBUG
    DEFINES += _CRT_SECURE_NO_WARNINGS NOMINMAX /MACHINE:X86
    DLLDESTDIR = $$deploybin
}

################################################################################
