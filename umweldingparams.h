#ifndef UMWELDINGPARAMS_H
#define UMWELDINGPARAMS_H

#include <QObject>
#include <QList>
#include <QDataStream>
class UmweldingParams
{
public:
//    explicit UmweldingParams(QObject *parent = 0);
    friend QDataStream &operator <<(QDataStream &, const UmweldingParams&);
    friend QDataStream &operator >>(QDataStream &, UmweldingParams &);
signals:

public slots:
public:
    QString name;
    QList<quint32> value ;
    QList<double> data;

};


QDataStream &operator <<(QDataStream &, const UmweldingParams&);
QDataStream &operator >>(QDataStream &, UmweldingParams &);

//class UmweldingParamList
//{
//public:
//    UmweldingParamList(const QString &file);
//    QList<UmweldingParams> list;
//};

#endif // UMWELDINGPARAMS_H
