QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    registerscreen.cpp \
    signinscreen.cpp \
    BackendlessQt/BasicAPI.cpp \
    BackendlessQt/BackendlessAPI.cpp \
    BackendlessQt/BackendlessUserAPI.cpp

HEADERS += \
    registerscreen.hpp \
    signinscreen.hpp \
    BackendlessQt/BasicAPI.hpp \
    BackendlessQt/BackendlessAPI.hpp \
    BackendlessQt/BackendlessUserAPI.hpp \
    BackendlessQt/BackendlessUser.hpp \

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/res/values/libs.xml \
        android/gradle.properties \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat
}
