QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    signinscreen.cpp \
    BackendlessQt/BasicAPI.cpp \
    BackendlessQt/BackendlessAPI.cpp \
    BackendlessQt/BackendlessUserAPI.cpp

HEADERS += \
    signinscreen.hpp \
    BackendlessQt/BasicAPI.hpp \
    BackendlessQt/BackendlessAPI.hpp \
    BackendlessQt/BackendlessUserAPI.hpp \
    BackendlessQt/BackendlessUser.hpp \
