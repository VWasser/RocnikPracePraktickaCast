TEMPLATE = app

QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    signinscreen.cpp

HEADERS += \
    signinscreen.hpp

INCLUDEPATH += \
    ../BackendlessQt

LIBS += \
    -L../BackendlessQt -lBackendlessQt
