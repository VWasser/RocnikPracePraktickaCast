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

#LIBS += \
#   -L../BackendlessQt -lBackendlessQt

android {
    QMAKE_LINK += -nostdlib++

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        $$PWD/android/AndroidManifest.xml \
        $$PWD/android/build.gradle \
        $$PWD/android/res/values/libs.xml \
        $$PWD/android/gradle.properties \
        $$PWD/android/gradle/wrapper/gradle-wrapper.jar \
        $$PWD/android/gradle/wrapper/gradle-wrapper.properties \
        $$PWD/android/gradlew \
        $$PWD/android/gradlew.bat
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../BackendlessQt/build/Android_Qt_6_8_0_Clang_arm64_v8a-Vydu00e1nu00ed/libBackendlessQt_arm64-v8a.so
}
