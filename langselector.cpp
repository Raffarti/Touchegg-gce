#include "langselector.h"

//I can't belive Qt really forced me to do  2 method file class....

LangSelector::LangSelector(QObject *parent) :
    QObject(parent)
{
    value = 0;
}

void LangSelector::set(int val){
    value = val;
}
