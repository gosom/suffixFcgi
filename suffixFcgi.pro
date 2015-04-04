TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp
INCLUDEPATH += $$PWD/../libs
INCLUDEPATH += "/home/giorgos/include"

LIBS += -L$$PWD/../libs/ -lcSuffixSearch
LIBS += -lfcgi
LIBS += -ljsoncpp


