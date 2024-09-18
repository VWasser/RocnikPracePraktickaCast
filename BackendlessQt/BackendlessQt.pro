CONFIG += c++20 warn_on

QT += core network

TEMPLATE = lib

DEFINES += MAKE_BACKENDLESS_LIB \
    BACKENDLESS_VARIANT_RESPONSE___

TARGET = BackendlessQt

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

!android {
    CONFIG += staticlib
}
