QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# best change to (if lboost system exists.)
unix:!macx {
    LIBS+= -lboost_system
}

macx {
    INCLUDEPATH += /usr/local/include
}

INCLUDEPATH += "$$PWD/include"

SOURCES += \
    src/messageParser.cpp \
    src/SequenceHolder.cpp \
    src/DataUpdater.cpp \
    src/qcustomplot.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/messageParser.h \
    include/SequenceHolder.h \
    include/DataUpdater.h \
    include/qcustomplot.h \
    include/mainwindow.h

FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
