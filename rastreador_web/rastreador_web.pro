QT -= gui
QT += remoteobjects network

QT += widgets
CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/crawlserver.cpp \
        src/dynamiclibrary.cpp \
        src/httpgetter.cpp \
        src/indexingservice.cpp \
        src/linkchecker.cpp \
        src/main.cpp \
        src/schemapluginmanager.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../actors/release/ -lactors
else:win32:CONFIG(debug,  debug|release): LIBS += L$$OUT_PWD/../actors/debug/ -lactors
else:unix: LIBS += -L$$OUT_PWD/../actors/ -lactors


# INCLUDEPATH += $$PWD/../actors/include
DEPENDPATH += $$PWD/../actors

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/schemaplugin.h \
    src/crawlserver.h \
    src/dynamiclibrary.h \
    src/httpgetter.h \
    src/indexingservice.h \
    src/linkchecker.h \
    src/schemapluginmanager.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../actors/release/ -lactors
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../actors/debug/ -lactors
else:unix: LIBS += -L$$OUT_PWD/../actors/ -lactors -ldl

INCLUDEPATH += $$PWD/../actors/include
DEPENDPATH += $$PWD/../actors

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libcurl


REPC_SOURCE = src/remoteObject.rep


DISTFILES += \

    src/remoteObject.rep

unix:!macx: LIBS += -L$$PWD/../libs/GumboQuery/lib/ -lgq

INCLUDEPATH += $$PWD/../libs/GumboQuery/src
DEPENDPATH += $$PWD/../libs/GumboQuery/src

unix:!macx: PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/libgq.a
