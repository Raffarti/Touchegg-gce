#-------------------------------------------------
#
# Project created by QtCreator 2012-09-22T01:24:22
#
#-------------------------------------------------

QT       += core gui

TARGET = touchegg-gce
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    parser.cpp \
    button.cpp \
    lists.cpp \
    editdialog.cpp \
    memory.cpp \
    sendkeys.cpp \
    keylineedit.cpp \
    keylinguist.cpp \
    scribe.cpp \
    newgroupdialog.cpp \
    dictionary.cpp \
    langselector.cpp

HEADERS  += gui.h \
    parser.h \
    general.h \
    button.h \
    lists.h \
    editdialog.h \
    memory.h \
    sendkeys.h \
    keylineedit.h \
    keylinguist.h \
    scribe.h \
    newgroupdialog.h \
    dictionary.h \
    langselector.h

FORMS    += gui.ui \
    button.ui \
    editdialog.ui \
    sendkeys.ui \
    newgroupdialog.ui

OTHER_FILES += \
    default.conf \
    README.md

TRANSLATIONS = Dictionaries/it.ts \
    Dictionaries/en.ts
