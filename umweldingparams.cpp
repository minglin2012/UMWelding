#include "umweldingparams.h"

//UmweldingParams::UmweldingParams(QObject *parent) :
//    QObject(parent)
//{
//}

QDataStream &operator <<(QDataStream &output, const UmweldingParams &cls)
{
    output<<cls.name<<cls.value<<cls.data;
    return output;
}

QDataStream &operator >>(QDataStream &input, UmweldingParams &cls)
{
    input>>cls.name>>cls.value>>cls.data;
    return input;
}


