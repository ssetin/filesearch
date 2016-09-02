QT -= core
QT -= gui

TARGET = filesearch
CONFIG += console static-runtime
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.c \
    btreeindex.c

HEADERS += \
    btreeindex.h
