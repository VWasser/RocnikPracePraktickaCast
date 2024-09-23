QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    registerscreen.cpp \
    schedule.cpp \
    signinscreen.cpp \
    editmodescreen.cpp \
    BackendlessQt/BasicAPI.cpp \
    BackendlessQt/BackendlessAPI.cpp \
    BackendlessQt/BackendlessUserAPI.cpp \
    BackendlessQt/BackendlessUser.cpp

HEADERS += \
    registerscreen.hpp \
    schedule.hpp \
    signinscreen.hpp \
    editmodescreen.hpp \
    BackendlessQt/BasicAPI.hpp \
    BackendlessQt/BackendlessAPI.hpp \
    BackendlessQt/BackendlessUserAPI.hpp \
    BackendlessQt/BackendlessUser.hpp \

ios {
    QMAKE_TARGET_BUNDLE_PREFIX = com.bachelor
    QMAKE_DEVELOPMENT_TEAM = 96D9Q2BEQH
}

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

RESOURCES += \
    bachelorresources.qrc

TRANSLATIONS += \
    MyBachelor_cs_CZ.ts \
    MyBachelor_en_GB.ts
