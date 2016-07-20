TEMPLATE = app

QT += qml quick
QT += widgets
QT += multimedia
CONFIG += c++11


HEADERS += \
    headers/player.h \
    headers/Voice.h \
    headers/JasonQt/JasonQt_Net.h \
    headers/JasonQt/JasonQt_Vop.h \
    headers/hpbar.h

SOURCES += \
    sources/main.cpp \
    sources/player.cpp \
    sources/Voice.cpp \
    sources/hpbar.cpp \
    sources/JasonQt/JasonQt_Net.cpp \
    sources/JasonQt/JasonQt_Vop.cpp \


RESOURCES += QML/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

