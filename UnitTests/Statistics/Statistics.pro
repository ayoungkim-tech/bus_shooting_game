QT += testlib
QT -= gui
QT += core widgets gui

TARGET = tst_statisticstest.cc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES +=  tst_statisticstest.cc \
        ../../Game/statistics.cc \
        ../../Game/gamewindow.cc \
        ../../Game/actoritem.cc \
        ../../Game/startdialog.cc \
        ../../Game/city.cc \
        ../../Game/creategame.cc \
        ../../Game/gamecharacter.cc \
        ../../Game/missile.cc \
        ../../Game/engine/engine.cc \
        ../../Course/CourseLib/actors/nysse.cc \
        ../../Course/CourseLib/actors/passenger.cc \
        ../../Course/CourseLib/actors/stop.cc \
        ../../Course/CourseLib/core/location.cc \
        ../../Course/CourseLib/core/logic.cc \
        ../../Course/CourseLib/errors/gameerror.cc \
        ../../Course/CourseLib/errors/initerror.cc \
        ../../Course/CourseLib/graphics/simpleactoritem.cpp \
        ../../Course/CourseLib/graphics/simplemainwindow.cpp \
        ../../Course/CourseLib/offlinereader.cc \

HEADERS += \
            ../../Game/statistics.hh \
            ../../Game/gamewindow.hh \
            ../../Game/actoritem.hh \
            ../../Game/startdialog.hh \
            ../../Game/city.hh \
            ../../Game/gamecharacter.hh \
            ../../Game/missile.hh \
            ../../Game/engine/engine.hh \
            ../../Course/CourseLib/actors/nysse.hh \
            ../../Course/CourseLib/actors/passenger.hh \
            ../../Course/CourseLib/actors/stop.hh \
            ../../Course/CourseLib/core/location.hh \
            ../../Course/CourseLib/core/logic.hh \
            ../../Course/CourseLib/creategame.hh \
            ../../Course/CourseLib/doxygeninfo.hh \
            ../../Course/CourseLib/errors/gameerror.hh \
            ../../Course/CourseLib/errors/initerror.hh \
            ../../Course/CourseLib/graphics/simpleactoritem.hh \
            ../../Course/CourseLib/graphics/simplemainwindow.hh \
            ../../Course/CourseLib/interfaces/iactor.hh \
            ../../Course/CourseLib/interfaces/icity.hh \
            ../../Course/CourseLib/interfaces/ipassenger.hh \
            ../../Course/CourseLib/interfaces/istatistics.hh \
            ../../Course/CourseLib/interfaces/istop.hh \
            ../../Course/CourseLib/interfaces/ivehicle.hh \
            ../../Course/CourseLib/offlinereader.hh \

FORMS += \
            ../../Game/gamewindow.ui \
            ../../Game/startdialog.ui \
            ../../Course/CourseLib/graphics/simplemainwindow.ui \

RESOURCES += \
            ../../Course/CourseLib/offlinedata.qrc

INCLUDEPATH += \
            ../../Course/CourseLib/ \
            ../../Game/

