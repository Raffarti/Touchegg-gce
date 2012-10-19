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
#include "keylineedit.h"
#include "keylinguist.h"
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
