QT -= core
QT -= gui

TARGET = filesearch
CONFIG += console static
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CFLAGS += -std=c99

SOURCES += \
    main.c \
    btreeindex.c

HEADERS += \
    btreeindex.h
