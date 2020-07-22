/**
 *Please note that this is not Touchégg nor Touchégg-gui,
 *which author is José Expósito <jose.exposito89@gmail.com>.
 *This is a gui interface to edit Touchégg configuration file
 *alternative to Touchégg-gui.
 *
 *@author Raffaele Pertile <raffarti@zoho.com>
 */
 
Dependencies:
sudo apt-get install build-essential libqt4-dev libx11-6 libx11-dev

_________________________________________________________________________________________________
BUILD & INSTALLATION:

Build and install in /usr/local (default prefix):

    mkdir build && cd build
    qmake ..
    make && make install

Build and install in user's home:

    mkdir build && cd build
    qmake PREFIX=~/.local ..
    make && make install


=================================================================================================
ADVANCED HELP
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_________________________________________________________________________________________________
To customize installation directories use:

    qmake VARIABLE=value

_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
variables and defaults:
    PREFIX=/usr/local
    BIN_PATH=$$PREFIX/bin
    CONFIG_PATH=$$PREFIX/etc
    SLIB_PATH=$$PREFIX/share
    ICONS_PATH=$$SLIB/icons
    TLIB_PATH=$$SLIB_PATH/touchegg-gce
    DICTS_PATH=$$TLIB_PATH/Dictionaries

NOTE:
relative paths will be refered to .pro file location.

_________________________________________________________________________________________________
To customize installation use:

    qmake INSTALLS="part1 part2 ..." (e.g. qmake INSTALLS="target translations")

or
    qmake SKIP="part1 part2 ..." (e.g. qmake SKIP="icons desktop")
_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
parts list:
    target          executable file
    translations    translation files
    default_config  default configuration for touchégg
    conf            default configuration file
    desktop         .desktop file (application shortcut)
    icons           icons files

_________________________________________________________________________________________________
To create an executable with compressed resources use
    qmake standalone=y; make
