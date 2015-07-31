/**************************************************************************
 * Copyright (c) 2012-2015 Raffaele Pertile <raffarti@zoho.com>
 * This file is part of touchegg-gce.
 *
 * touchegg-gce is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * touchegg-gce is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with touchegg-gce.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

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
