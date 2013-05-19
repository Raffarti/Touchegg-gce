/**
 *This work is licensed under the
 *Creative Commons Attribuzione 3.0
 *Unported License. To view a copy
 *of this license, visit
 *http://creativecommons.org/licenses/by/3.0/
 *
 *Please note that this is not Touchégg nor Touchégg-gui,
 *which author is José Expósito <jose.exposito89@gmail.com>.
 *This is a gui interface to edit
 *Touchégg configuration file alternative to Touchégg-gui.
 *
 *@author Raffaele Pertile <raffarti@yahoo.it>
 */
#include "keylinguist.h"
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

///***+++---WARNING:
//DO NOT MOVE THOSE LIBRARIES TO HEADER FILE, nor add any Qt class include under them
//Seems that they hate each other, or so the compiler said.
//Oh, yeah, and don't use Qt events if you have included them, that's why they're not in keylineedit

KeyLinguist::KeyLinguist()
{
}


QString KeyLinguist::toString(uint keycode){
    return QString(XKeysymToString(XkbKeycodeToKeysym(XOpenDisplay(0),keycode,0,0)));
}
