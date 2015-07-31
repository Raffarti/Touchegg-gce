#-------------------------------------------------
#
# Project created by QtCreator 2012-09-22T01:24:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = touchegg-gce
TEMPLATE = app

LIBS        += -lX11

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
    translatorhandler.cpp \
    settings.cpp

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
    translatorhandler.h \
    settings.h

FORMS    += gui.ui \
    button.ui \
    editdialog.ui \
    sendkeys.ui \
    newgroupdialog.ui

OTHER_FILES += \
    default.conf \
    Changelog \
    README \
    COPYING

TRANSLATIONS = Dictionaries/it.ts \
    Dictionaries/de.ts \
    Dictionaries/en.ts \
    Dictionaries/zh_CN.ts

!isEmpty(standalone){
    RESOURCES += resources.qrc
}else:{

    isEmpty(PREFIX){
        PREFIX = /usr/local
    }

    isEmpty(BIN_PATH){
        BIN_PATH = "$$PREFIX/bin"
    }

    isEmpty(SLIB_PATH){
        SLIB_PATH = "$$PREFIX/share"
    }

    isEmpty(TLIB_PATH){
        TLIB_PATH = "$$SLIB_PATH/touchegg-gce"
    }

    isEmpty(DICTS_PATH){
        DICTS_PATH = "$$TLIB_PATH/Dictionaries"
    }

    isEmpty(ICONS_PATH){
        ICONS_PATH = "$$SLIB_PATH/icons"
    }


    default_config.files = default.conf
    default_config.path = $$TLIB_PATH

    icons.files = $$system('find icons -type f')
    icons.path = $$SLIB_PATH/icons

    target.path = $$BIN_PATH
    translations.path = $$PREFIX/share/touchegg-gce/Dictionaries
    translations.files = Dictionaries/*.qm

    isEmpty(CONFIG_PATH){
        CONFIG_PATH = $$PREFIX/etc
    }

    message("Installation Directories:")
    message("   prefix:    $$PREFIX")
    message("   bin:       $$BIN_PATH")
    message("   config:    $$CONFIG_PATH")
    message("   shared:    $$SLIB_PATH")

    message("See README for details.")

    conf.path = $$CONFIG_PATH
    conf.files = touchegg-gce.conf

    desktop.files = touchegg-gce.desktop
    desktop.path = $$PREFIX/share/applications

    INSTALLS = target default_config translations desktop icons conf
    INSTALLS -= $$SKIP
}

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
else: QMAKE_CXXFLAGS += -std=c++11
