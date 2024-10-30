QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    registerscreen.cpp \
    schedule.cpp \
    signinscreen.cpp \
    editmodescreen.cpp \
    httpclient.cpp \
    # client.cpp \
    # Backendless
    BackendlessQt/BasicAPI.cpp \
    BackendlessQt/BackendlessAPI.cpp \
    BackendlessQt/BackendlessUserAPI.cpp \
    BackendlessQt/BackendlessUser.cpp \
    BackendlessQt/StandardNetworkManager.cpp

HEADERS += \
    registerscreen.hpp \
    schedule.hpp \
    signinscreen.hpp \
    editmodescreen.hpp \
    httpclient.hpp \
    # client.hpp \
    # Backendless
    BackendlessQt/BasicAPI.hpp \
    BackendlessQt/BackendlessAPI.hpp \
    BackendlessQt/BackendlessUserAPI.hpp \
    BackendlessQt/BackendlessUser.hpp \
    BackendlessQt/StandardNetworkManager.hpp

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
    MyBachelor_en_GB.ts \
    MyBachelor_cs_CZ.qm \
    MyBachelor_en_GB.qm
