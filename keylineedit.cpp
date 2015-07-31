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

#include "keylineedit.h"
#include "keylinguist.h"
#include <QKeyEvent>

KeyLineEdit::KeyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}
//this is my implementation of a QLineEdit for catching key events!

bool KeyLineEdit::event(QEvent *event){
    if (QEvent::KeyPress == event->type()) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        //modifiers are handled with checkboxes. Filtering them.
        if (ke->key() != Qt::Key_Alt && ke->key() != Qt::Key_AltGr && ke->key() != Qt::Key_Super_L && ke->key() != Qt::Key_Super_R && ke->key() != Qt::Key_Shift && ke->key() != Qt::Key_Control){
            if (!text().isEmpty()) setText(text().append("+"));
            QString key = KeyLinguist::toString((uint)ke->nativeScanCode());
            setText(text().append(key));
            emit keyCatched(key);
            return true;
        }
    }
    return QWidget::event(event);
}
