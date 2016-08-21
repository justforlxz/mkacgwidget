TEMPLATE = app

QT += qml quick
QT += widgets
QT += multimedia
QT += dbus
CONFIG += c++11


HEADERS += \
    headers/player.h \
    headers/Voice.h \
    headers/JasonQt/JasonQt_Net.h \
    headers/JasonQt/JasonQt_Vop.h \
    headers/hpbar.h \
    headers/dbusaudiosource.h \
    headers/dbuspower.h \
    headers/settings.h \
    headers/core.h

SOURCES += \
    sources/main.cpp \
    sources/player.cpp \
    sources/Voice.cpp \
    sources/hpbar.cpp \
    sources/JasonQt/JasonQt_Net.cpp \
    sources/JasonQt/JasonQt_Vop.cpp \
    sources/dbusaudiosource.cpp \
    sources/dbuspower.cpp \
    sources/settings.cpp \
    sources/core.cpp


RESOURCES += QML/qml.qrc

# Additional import path usd to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

