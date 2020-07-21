include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../9labProj/IKeypad.h \
        ../9labProj/ILatch.h \
        ../9labProj/lockcontroller.h \
        tst_testdivisionbyzero.h

SOURCES += \
        ../9labProj/lockcontroller.cpp \
        main.cpp

INCLUDEPATH += C:\Egor\Programming\CFU\Lab\9lab\9labProj
