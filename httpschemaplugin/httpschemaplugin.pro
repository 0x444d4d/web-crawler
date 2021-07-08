CONFIG -= qt

TEMPLATE = lib
DEFINES += HTTPSCHEMAPLUGIN_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../rastreador_web/include
SOURCES += \
    httpschemaplugin.cpp

HEADERS += \
    httpschemaplugin.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libcurl

unix:!macx: LIBS += -L$$PWD/../libs/GumboQuery/lib/ -lgq

INCLUDEPATH += $$PWD/../libs/GumboQuery/src
DEPENDPATH += $$PWD/../libs/GumboQuery/src

unix:!macx: PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/libgq.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/GumboQuery/lib/release/ -lgq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/GumboQuery/lib/debug/ -lgq
else:unix: LIBS += -L$$PWD/../libs/GumboQuery/lib/ -lgq

INCLUDEPATH += $$PWD/../libs/GumboQuery
DEPENDPATH += $$PWD/../libs/GumboQuery

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/release/libgq.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/debug/libgq.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/release/gq.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/debug/gq.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libs/GumboQuery/lib/libgq.a
