QT += core gui widgets network

CONFIG += c++20 ordered

TEMPLATE = subdirs

SUBDIRS = \
    BackendlessQt \
    App

App.depends = BackendlessQt

android {
    ANDROID_EXTRA_LIBS += \
        /Users/romanpodymov/RocnikPracePraktickaCast/BackendlessQt/build/Android_Qt_6_8_0_Clang-Vydu00e1nu00ed/libBackendlessQt_arm64-v8a.so
}
