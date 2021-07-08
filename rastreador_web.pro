TEMPLATE = subdirs
QT += widgets
CONFIG += c++17
SUBDIRS += \
    actors \
    fileschemaplugin \
    httpschemaplugin \
    rastreador_web \
    tests

tests.depends = actors
rastreador_web.depends = actors

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/GumboQuery/lib/release/ -lgq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/GumboQuery/lib/debug/ -lgq
else:unix: LIBS += -L$$PWD/libs/GumboQuery/lib/ -lgq

INCLUDEPATH += $$PWD/libs/GumboQuery
DEPENDPATH += $$PWD/libs/GumboQuery

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/GumboQuery/lib/release/libgq.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/GumboQuery/lib/debug/libgq.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/GumboQuery/lib/release/gq.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/GumboQuery/lib/debug/gq.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/GumboQuery/lib/libgq.a
