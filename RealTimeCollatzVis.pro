QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# best change to (if lboost system exists.)
unix:!macx {
    LIBS+= -lboost_system
}

INCLUDEPATH += "$$PWD/include"

SOURCES += \
    src/messageParser.cpp \
    src/SequenceHolder.cpp \
    src/DataUpdater.cpp \
    src/serverReceiverParse.cpp

macx {
    INCLUDEPATH += /usr/local/include
}

 HEADERS += \
    include/messageParser.h \
    include/SequenceHolder.h \
    include/DataUpdater.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
