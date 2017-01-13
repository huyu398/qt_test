#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T05:12:01
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_test
TEMPLATE = app

INCLUDEPATH += /usr \
            /home/huyu/git/picojson

win32:INCLUDEPATH +=  $$PWD/../picojson

SOURCES += main.cpp\
        mainwindow.cpp \
    twitter.cpp \
    customdelegate.cpp \
    listdelegate.cpp \
    logindialog.cpp \
    tweet.cpp

HEADERS  += mainwindow.h \
    twitter.h \
    customdelegate.h \
    listdelegate.h \
    logindialog.h \
    tweet.h

FORMS    += mainwindow.ui \
    logindialog.ui

unix:!macx: LIBS += -ltwitcurl

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../twitcurl/libtwitcurl/release/ -ltwitcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../twitcurl/libtwitcurl/debug/ -ltwitcurl
LIBS += -L$$PWD/../twitcurl/libtwitcurl/lib/ -llibcurl

INCLUDEPATH += $$PWD/../twitcurl/libtwitcurl
DEPENDPATH += $$PWD/../twitcurl/libtwitcurl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../twitcurl/libtwitcurl/release/libtwitcurl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../twitcurl/libtwitcurl/debug/libtwitcurl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../twitcurl/libtwitcurl/release/twitcurl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../twitcurl/libtwitcurl/debug/twitcurl.lib
