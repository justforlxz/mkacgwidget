TEMPLATE = app

QT += qml quick
QT += widgets
QT += multimedia
CONFIG += c++11


HEADERS += \
    player.h \
    Voice.h \
    JasonQt/JasonQt_Net.h \
    JasonQt/JasonQt_Vop.h

SOURCES +=main.cpp \
    player.cpp \
    Voice.cpp \
    JasonQt/JasonQt_Net.cpp \
    JasonQt/JasonQt_Vop.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

