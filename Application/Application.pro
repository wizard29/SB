################################################################################
include (../general.pri)

################################################################################
QT += core gui

################################################################################
TARGET = sb
TEMPLATE = app

################################################################################
DEFINES +=

################################################################################
QMAKE_LIBDIR += \
    ../Core/$$inputbin

################################################################################
INCLUDEPATH += \
    ../Core/include

################################################################################
HEADERS +=

################################################################################
SOURCES += \
    src/main.cpp

################################################################################
QMAKE_LIBS += \
    -lcore

################################################################################
