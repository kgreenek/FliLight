#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T20:25:41
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

TARGET = FliLight
TEMPLATE = app

INCLUDEPATH = pm_common/ porttime/ qextserialport/src/

win32 {
	INCLUDEPATH += pm_win/
	LIBS += -lwinmm
	SOURCES += pm_win/pmwinmm.c \
	    pm_win/pmwin.c
	HEADERS += pm_win/pmwinmm.h
}

# this build hasn't been tested on Linux yet
unix {
	DEFINES += PMALSA
	INCLUDEPATH += pm_linux/
	LIBS += -lasound
	SOURCES += pm_linux/finddefault.c \
	    pm_linux/pmlinux.c \
	    pm_linux/pmlinuxalsa.c
	HEADERS += pm_linux/pmlinux.h pm_linux/pmlinuxalsa.h
}

DEFINES -= UNICODE

SOURCES += main.cpp\
    mainwindow.cpp \
    pm_common/portmidi.c \
    pm_common/pmutil.c \
    porttime/porttime.c \
    porttime/ptwinmm.c \
    midibeatdetector.cpp \
    flanimation.cpp \
    cubemanager.cpp \
    animations/beatsnakeanimation.cpp \
    animations/updownsweepanimation.cpp \
    beatdispenser.cpp \
    animations/diamondanimation.cpp \
    animations/strobeanimation.cpp \
    animations/precipitationanimation.cpp \
    animations/onanimation.cpp \
    animations/planeanimation.cpp

HEADERS += mainwindow.h \
    pm_common/pmutil.h \
    pm_common/pminternal.h \
    pm_common/portmidi.h \
    porttime/porttime.h \
    midibeatdetector.h \
    flanimation.h \
    cubemanager.h \
    cubeframe.h \
    animations/beatsnakeanimation.h \
    animations/updownsweepanimation.h \
    beatdispenser.h \
    animations/diamondanimation.h \
    animations/strobeanimation.h \
    animations/precipitationanimation.h \
    animations/onanimation.h \
    animations/planeanimation.h

FORMS   += mainwindow.ui

include(qextserialport/src/qextserialport.pri)














