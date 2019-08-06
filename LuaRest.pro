#-------------------------------------------------
#
# Project created by QtCreator 2019-08-01T23:36:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuaRest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 console

SOURCES += \
        AssistLogic/AssistThreadLogic.cpp \
        Data/DirectoryData.cpp \
        Data/ProjectTreeData.cpp \
        ParserMachine/Parser.cpp \
        View/CodeSpace.cpp \
        View/ProjectTreeSpace.cpp \
        main.cpp \
        View/MainWindow.cpp

HEADERS += \
        AssistLogic/AssistThreadLogic.h \
        AssistLogic/ExecuteThread.h \
        AssistLogic/ThreadMutex.h \
        Data/DirectoryData.h \
        Data/ProjectTreeData.h \
        ParserMachine/Parser.h \
        View/MainWindow.h \
        View/CodeSpace.h \
        View/ProjectTreeSpace.h

FORMS += \
        View/UI/ProjectTreeSpace.ui \
        View/UI/CodeSpace.ui \
        View/UI/MainWindow.ui

RESOURCES += \
    Resource.qrc
