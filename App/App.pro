TEMPLATE = app

QT += core gui widgets network

CONFIG += c++20

SOURCES += \
    main.cpp \
    #schedule.cpp \
    signinscreen.cpp \
    registerscreen.cpp

HEADERS += \
    #schedule.hpp \
    signinscreen.hpp \
    registerscreen.hpp

INCLUDEPATH += \
    ../BackendlessQt

DEPENDPATH += \
    ../BackendlessQt

#unix {
#    LIBS += \
#       -L../BackendlessQt -lBackendlessQt
#}

android {
    QMAKE_LFLAGS += -lc++

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

    ANDROID_EXTRA_LIBS += \
        $$PWD/libBackendlessQt_arm64-v8a.so
}

android: include(/Users/romanpodymov/Library/Android/sdk/android_openssl/openssl.pri)
