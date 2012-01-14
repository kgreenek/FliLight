#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T20:25:41
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

TARGET = FliLight
TEMPLATE = app

INCLUDEPATH = pm_common/ porttime/

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
    audiomanager.cpp \
    audiobuffer.cpp \
    pm_common/portmidi.c \
    pm_common/pmutil.c \
    porttime/porttime.c \
    porttime/ptwinmm.c \
    midibeatdetector.cpp \
    flanimation.cpp \
    beatsnakeanimation.cpp \
    cubemanager.cpp

HEADERS  += mainwindow.h \
    audiomanager.h \
    audiobuffer.h \
    pm_common/pmutil.h \
    pm_common/pminternal.h \
    pm_common/portmidi.h \
    porttime/porttime.h \
    midibeatdetector.h \
    flanimation.h \
    beatsnakeanimation.h \
    cubemanager.h \
    cubeframe.h

FORMS    += mainwindow.ui
















































