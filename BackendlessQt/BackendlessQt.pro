CONFIG += c++20 warn_on staticlib

QT += core network

TEMPLATE = lib

SOURCES += \
    BasicAPI.cpp \
    BackendlessAPI.cpp \
    BackendlessUserAPI.cpp \
    BackendlessUser.cpp

HEADERS += \
    BasicAPI.hpp \
    BackendlessAPI.hpp \
    BackendlessUserAPI.hpp \
    BackendlessUser.hpp
