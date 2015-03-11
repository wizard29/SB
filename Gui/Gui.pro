################################################################################
include (../general.pri)

################################################################################
QT += widgets

################################################################################
TARGET = gui
TEMPLATE = lib

################################################################################
DEFINES += GUI_BUILD

################################################################################
QMAKE_LIBDIR += \
    ../Core/$$inputbin

################################################################################
QMAKE_LIBS += \
    -lcore

################################################################################
HEADERS += \
    include/guidef.h \
    include/SBMDIManager.h \
    src/private/SBMDIManager_p.h \
    include/SBApplication.h \
    src/private/SBApplication_p.h \
    include/SBWidget.h \
    src/private/SBWidget_p.h \
    include/SBTitleBar.h \
    src/private/SBTitleBar_p.h \
    include/SBPanel.h \
    src/private/SBPanel_p.h \
    include/SBToolBar.h \
    src/private/SBToolBar_p.h \
    include/SBToolBarContent.h \
    src/private/SBToolBarContent_p.h

################################################################################
SOURCES += \
    src/SBMDIManager.cpp \
    src/private/SBMDIManager_p.cpp \
    src/private/SBApplication_p.cpp \
    src/SBApplication.cpp \
    src/private/SBWidget_p.cpp \
    src/SBWidget.cpp \
    src/SBTitleBar.cpp \
    src/private/SBTitleBar_p.cpp \
    src/SBPanel.cpp \
    src/private/SBPanel_p.cpp \
    src/SBToolBar.cpp \
    src/private/SBToolBar_p.cpp \
    src/SBToolBarContent.cpp \
    src/private/SBToolBarContent_p.cpp

################################################################################
win32-msvc2013:{
    RESOURCES += \
        resources/windows/gui.qrc
}
################################################################################
