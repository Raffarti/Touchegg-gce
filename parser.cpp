/**
 *This work is licensed under the
 *Creative Commons Attribuzione 3.0
 *Unported License. To view a copy
 *of this license, visit
 *http://creativecommons.org/licenses/by/3.0/
 *
 *Please note that this is not Touchégg nor Touchégg-gui,
 *which author is Jos� Exp�sito <jose.exposito89@gmail.com>.
 *This is a gui interface to edit
 *Touchégg configuration file alternative to Touchégg-gui.
 *
 *@author Raffaele Pertile <raffarti@yahoo.it>
 */
#include "parser.h"
#include "general.h"

#include <QDebug>

Parser::Parser(QString file){
    input = new QFile(file);
}

Parser::~Parser(){
    input->close();
    delete input;
}

int Parser::init(){
    int ret = input->open(QIODevice::ReadOnly);
    if (!ret) qDebug() << "Errore nell'apertura del file.";
    in = new QTextStream(input);
    in->setCodec("UTF-8"); //out of ascii, see below-.-
    return ret;
}

void Parser::close(){
    input->close();
}

QChar Parser::peek(){
    if (!peeked.isNull()) return peeked;
    peeked = in->read(sizeof(char))[0];//it works!
    return peeked;
}

QChar Parser::poll(){
    QChar ret;
    if (!peeked.isNull()){
        ret = peeked;
        peeked = QChar::Null;
    }
    else ret = in->read(sizeof(char))[0];
    if (ret == '\n'){
        error.line++;
        error.pos = 0;
    } else error.pos++;
    return ret;
}

void Parser::eat(QString s){
    while (s.contains(peek())) poll();//skip all chars till found one not in string
}

QString Parser::getVarName(){
    QString ret("");
    eat(" \t\n");
    while(peek().isLetterOrNumber() || peek() == '_'){
        ret.append(poll());
    }
    if (ret.isEmpty()) return NULL;
    return ret;
}

QString Parser::getParam(){
    QString ret("");
    eat(" \t\n");
    while(peek() != ':' && peek() != '<' && peek() != '='){
        ret.append(poll());
    }
    if (ret.isEmpty()) return NULL;
    return ret;
}

int Parser::getInt(){
    QString ret("");
    eat(" \t\n");
    while(peek().isNumber()){
        ret.append(poll());
    }
    if (ret.isEmpty()) return 0;
    return ret.toInt();
}

QString Parser::getString(){
    QString ret("");
    eat(" \t\n");
    if (poll() != '"') return NULL;
    while(peek() != '"'){
        ret.append(poll());
    } poll();
    return ret;
}

void Parser::throwError(){
    state.append("ERROR");
}

void Parser::sStart(){
    eat(" \t\n");
    if (peek() == '\0'){
        state.append("EOF");
        return;
    }
    if (poll() != '<'){
        throwError();
        return;
    }
    if (getVarName() != QString::fromUtf8("touchégg")){
        throwError();
        return;
    }
    eat(" \t\n");
    if (poll() != '>'){
        throwError();
        return;
    }
    state.append("TOUCHEGG");
}

void Parser::sTouchegg(){
    eat(" \t\n");
    if (poll() != '<'){
        throwError();
        return;
    }
    eat(" \t\n");
    if (peek() == '/'){
        poll();
        if (getVarName() != QString::fromUtf8("touchégg")){
            throwError();
            return;
        }
        eat("\n\t ");
            if (poll() != '>'){
                throwError();
            }
        state.removeLast();
        return;
    }
    QString nextState;
    QString var = getVarName();
    if (!var.compare("settings")) nextState = "SETTINGS";
    else if (!var.compare("application")) nextState = "APPLICATION";
    else{
        throwError();
        return;
    }
    eat(" \t\n");
    if (!nextState.compare("APPLICATION")){
        if (getVarName().compare("name") || poll() != '='){
            throwError();
            return;
        }
        QString key = getString();
        if (key.isNull()){
            throwError();
            return;
        }

        appKey = key;
        appKey = Memory::addGroup(appKey);
        eat(" \t\n");
    }
    if (poll() != '>'){
        throwError();
        return;
    }
    state.append(nextState);
}

void Parser::sSettings(){
    eat(" \t\n");
    if (poll() != '<'){
        throwError();
        return;
    }
    eat(" \t\n");
    if (peek() == '/'){
        poll();
        if (getVarName().compare("settings")){
            throwError();
            return;
        }
        eat(" \t\n");
        if (poll() != '>'){
            throwError();
            return;
        }
        state.removeLast();
        return;
    }
    if (!getVarName().compare("property"));
    else{
        throwError();
        return;
    }
    eat(" \t\n");
    if (getVarName().compare("name")){
        throwError();
        return;
    }
    if (poll() != '='){
        throwError();
        return;
    }
    QString key = getString();
    if (key == NULL){
        throwError();
        return;
    }
    eat(" \t\n");
    if (poll() != '>'){
        throwError();
        return;
    }
    state.append("PROPERTY");
    sProperty(key);
}

void Parser::sProperty(QString key = QString::null){
    if (key != NULL){
        eat("\t\n ");
        int val = getInt();
        Memory::addProp(key,QString::number(val));
        return;
    }
    eat("\t\n ");
    if (poll() != '<'){
        throwError();
        return;
    }
    eat("\t\n ");
    if (poll() != '/'){
        throwError();
        return;
    }
    if (getVarName().compare("property")){
        throwError();
        return;
    }
    eat("\t\n ");
    if (poll() != '>'){
        throwError();
        return;
    }
    state.removeLast();

}

void Parser::sApplication(){
    eat(" \t\n");
    if (poll() != '<'){
        throwError();
        return;
    }
    eat(" \t\n");
    if (peek() == '/'){
        poll();
        if (getVarName().compare("application")){
            throwError();
            return;
        }
        eat(" \t\n");
        if (poll() != '>'){
            throwError();
            return;
        }
        state.removeLast();
        return;
    }
    if (!getVarName().compare("gesture"));
    else{
        throwError();
        return;
    }
    ges = new gesture;
    ges->type = QString::null;
    ges->num = 0;
    ges->direction = QString::null;
    while(peek() != '>'){
        eat(" \t\n");
        QString var = getVarName();
        if (!var.compare("type")){
            if (poll() != '='){
                throwError();
                return;
            }
            ges->type = getString();

        }
        else if (!var.compare("fingers")){
            if (poll() != '='){
                throwError();
                return;
            }
            ges->num = getString().toInt();

        }
        else if (!var.compare("direction")){
            if (poll() != '='){
                throwError();
                return;
            }
            ges->direction = getString();

        }
        else{
            throwError();
            return;
        }
        eat(" \t\n");
    }
    poll();
    if (ges->direction.isNull() || ges->type.isEmpty() || ges->num == 0){
        throwError();
        return;
    }
    state.append("GESTURE");
}

void Parser::sGesture(){
    eat(" \t\n");
    if (poll() != '<'){
        throwError();
        return;
    }
    eat(" \t\n");
    if (!getVarName().compare("action"));
    else{
        throwError();
        return;
    }
    eat(" \t\n");
    if (getVarName().compare("type")){
        throwError();
        return;
    }
    if (poll() != '='){
        throwError();
        return;
    }
    QString type = getString();
    Group *g = Memory::getGroup(appKey);
    g->addGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction));
    g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction))->setAction(Lists::aT(type));
    eat(" \t\n");
    if (poll() != '>'){
        throwError();
        return;
    }
    state.append("ACTION");
    sAction(g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction))->getAction());
    if (state.endsWith(QString("E"))){
        qDebug() << "E";
        return;
    }
    if (poll() != '<' || poll() != '/' || getVarName() != "action" || poll() != '>'){
        throwError();
        return;
    }
    state.removeLast();
    eat("\n\t ");
    if (poll() != '<' || poll() != '/' || getVarName() != "gesture" || poll() != '>'){
        throwError();
        return;
    }
    state.removeLast();
}

void Parser::sAction(Action *act){
    eat(" \t\n");
    while(peek() != '<'){
        eat(" \t\n");
        QString key = getParam();
        if (key.isEmpty()){
            throwError();
            return;
        }
        if (peek() == '='){
            poll();
            QString tmp = getParam();
            act->addParam(key,tmp);
        }
        else
            act->addParam(key);
        eat(" \t\n");
        if (peek() == ':') poll();
    }
}


bool Parser::loadAll(){
    state = QStringList();
    state.append("START");
    error.ch = 0;
    error.line = 1;
    error.pos = 0;
    error.msg = QString::null;
    Memory();
    while(true){
        if (!state.last().compare("EOF")){
            qDebug() << "Config file loaded.";
            return true;
        }
        else if (!state.last().compare("START")) sStart();
        else if (!state.last().compare("TOUCHEGG")) sTouchegg();
        else if (!state.last().compare("SETTINGS")) sSettings();
        else if (!state.last().compare("PROPERTY")) sProperty();
        else if (!state.last().compare("APPLICATION")) sApplication();
        else if (!state.last().compare("GESTURE")) sGesture();
        else throwError();
        if (!state.last().compare("ERROR")){
            qDebug() << QString("Error while parsing:%1:%2\nstate:\t"+state.at(state.length()-2)).arg(error.line).arg(error.pos);
            return false;
        }
    }
}
