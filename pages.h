/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PAGES_H
#define PAGES_H

#include <QWidget>

class ConfigPage : public QWidget
{
public:
    ConfigPage(QWidget *parent = 0);
};

class QueryPage : public QWidget
{
public:
    QueryPage(QWidget *parent = 0);
};

class GroupPage : public QWidget
{
public:
    enum EGenAlgorithm
    {
        GEN_POLYNOMINAL,//y = a0+a1*x+a2*x^2+a3*x^3+...+an*x^n
        GEN_POWER,//y = x^a
        GEN_EXP,//y = a^x
        GEN_LOG,//y = log_a(x)
        GEN_SIN,//y = a0(sin(a1*x+a2)
        GEN_LAGRANGE_INTER //已知n+1个互异点的函数值，唯一确定一个n次多项式，作为插值多项式。实际中使用lagrange插值法。

    };

public:
    GroupPage(QWidget *parent = 0);
    GroupPage(bool bEnable, QWidget *parent = 0);
//    void addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column);
    void addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column,int rowSpan=1,int columnSpan=1);
    void addItem(QGridLayout *layout,  const int * pointsY, int row, int column, int rowSpan, int columnSpan);
    bool generateY(EGenAlgorithm algo, double *param, int paramAmount);
    bool generateY(EGenAlgorithm algo, QPoint  *points,int pointAmount, int lagrangeFactor=1);
private:
    int pointsY[1000];
    bool m_bEnable;
};


class WorkPage : public QWidget
{
public:
    enum EGenAlgorithm
    {
        GEN_POLYNOMINAL,//y = a0+a1*x+a2*x^2+a3*x^3+...+an*x^n
        GEN_POWER,//y = x^a
        GEN_EXP,//y = a^x
        GEN_LOG,//y = log_a(x)
        GEN_SIN,//y = a0(sin(a1*x+a2)
        GEN_LAGRANGE_INTER //已知n+1个互异点的函数值，唯一确定一个n次多项式，作为插值多项式。实际中使用lagrange插值法。

    };

public:
    WorkPage(QWidget *parent = 0);
    void addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column);
    void addItem(QGridLayout *layout,  const int * pointsY, int row, int column, int rowSpan, int columnSpan);
    bool generateY(EGenAlgorithm algo, double *param, int paramAmount);
    bool generateY(EGenAlgorithm algo, QPoint  *points,int pointAmount, int lagrangeFactor=1);
private:
    int pointsY[1000];
};

class DebugPage : public QWidget
{
public:
    DebugPage(QWidget *parent = 0);
    void addItem(QGridLayout *layout, const QString &title, int addr,int row,int column,int rowSpan=1,int columnSpan=1);
    void addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column);
};

class CurvePage : public QWidget
{
public:
    CurvePage(QWidget *parent = 0);
};

class AboutPage : public QWidget
{
public:
    AboutPage(QWidget *parent = 0);
};

#endif
