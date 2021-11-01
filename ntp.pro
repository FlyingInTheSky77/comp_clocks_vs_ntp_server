QT += core

QT += quick

CONFIG += c++11

TARGET = ntp
#CONFIG   += console
#CONFIG   -= app_bundle

#TEMPLATE = app

include (qntp/qntp.pri)

RESOURCES += qml.qrc


SOURCES += main.cpp \
    ntptest.cpp

HEADERS += \
    ntptest.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
