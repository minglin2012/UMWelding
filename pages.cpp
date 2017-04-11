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

#include <QtWidgets>
#include "umwelding.h"
#include "pages.h"
#include "math.h"
#include <iostream>
using namespace std;


QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(QStringLiteral("Look for packages"));

    QLabel *nameLabel = new QLabel(QStringLiteral("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(QStringLiteral("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(QStringLiteral("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(QStringLiteral("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(QStringLiteral("Return up to "));
    hitsSpinBox->setSuffix(QStringLiteral(" results"));
    hitsSpinBox->setSpecialValueText(QStringLiteral("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(QStringLiteral("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}



GroupPage::GroupPage(QWidget *parent)
    : QWidget(parent)
{

    QGroupBox *paramGroup = new QGroupBox(QStringLiteral("工作参数"));
    QGroupBox *curveGroup = new QGroupBox(QStringLiteral("曲线参数"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(paramGroup,0,0);
    QGridLayout *paramLayout = new QGridLayout;
    paramGroup->setLayout(paramLayout);
    addItem(paramLayout,QStringLiteral("下降时间"),QStringLiteral("ms"),0,0);
    addItem(paramLayout,QStringLiteral("上升时间"),QStringLiteral("ms"),1,0);
    addItem(paramLayout,QStringLiteral("震落振幅"),QStringLiteral("%"),2,0);
    addItem(paramLayout,QStringLiteral("焊接能量"),QStringLiteral("J"),3,0);
    addItem(paramLayout,QStringLiteral("初始驱动"),QStringLiteral(""),4,0);
    addItem(paramLayout,QStringLiteral("工作模式"),QStringLiteral("" ),0,1);
    addItem(paramLayout,QStringLiteral("工作组号"),QStringLiteral("" ),6,1,1,1);
    addItem(paramLayout,QStringLiteral("保压时间"),QStringLiteral("ms"),1,1);
    addItem(paramLayout,QStringLiteral("震落时间"),QStringLiteral("ms"),2,1);
    addItem(paramLayout,QStringLiteral("冷却时间"),QStringLiteral("ms"),3,1);
    addItem(paramLayout,QStringLiteral("测试振幅"),QStringLiteral("%"),4,1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *btnLoadGroup = new QPushButton(QStringLiteral("读取"));
    hLayout->addStretch();
    hLayout->addWidget(btnLoadGroup);
 //   hLayout->addStretch();
    paramLayout->addLayout(hLayout,6,0,1,1);

//    double params[ ] = {20,1};
//    generateY(GEN_POLYNOMINAL,params,2);

//    double params[] = {100,2*3.14/200,0 };
//    generateY(GEN_SIN,params,3);
//    addItem(paramLayout,pointsY ,4,1,3,1);
//    QPoint points[] = {QPoint(0,100),QPoint(100,200),QPoint(200,0),QPoint(300,80),QPoint(500,100),QPoint(600,50),QPoint(700,100),QPoint(800,0),QPoint(999,50)};
//    QPoint points[] = {QPoint(1,50) };
//    generateY(GEN_LAGRANGE_INTER,points,9,8);



//    mainLayout->addSpacing(12);
    mainLayout->addWidget(curveGroup,0,1);

    QGridLayout *curveLayout = new QGridLayout;
    curveGroup->setLayout(curveLayout);
    curveLayout->setSpacing(30);
    QWidget *pSpace2 = new QWidget;
    curveLayout->addWidget(pSpace2);
    addItem(curveLayout,pointsY ,1,0,1,1);

    setLayout(mainLayout);
}

GroupPage::GroupPage(bool bEnable, QWidget *parent)

    : QWidget(parent)
    , m_bEnable(bEnable)
{

    QGroupBox *paramGroup = new QGroupBox(QStringLiteral("工作参数"));
    QGroupBox *curveGroup = new QGroupBox(QStringLiteral("曲线参数"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(paramGroup,0,0);
    mainLayout->setColumnStretch(0,1);
    QGridLayout *paramLayout = new QGridLayout;
    paramGroup->setLayout(paramLayout);
    addItem(paramLayout,QStringLiteral("下降时间"),QStringLiteral("ms"),0,0);
    addItem(paramLayout,QStringLiteral("上升时间"),QStringLiteral("ms"),1,0);
    addItem(paramLayout,QStringLiteral("震落振幅"),QStringLiteral("%"),2,0);
    addItem(paramLayout,QStringLiteral("焊接能量"),QStringLiteral("J"),3,0);
    addItem(paramLayout,QStringLiteral("初始驱动"),QStringLiteral(""),4,0);
    addItem(paramLayout,QStringLiteral("工作模式"),QStringLiteral("" ),0,1);
    addItem(paramLayout,QStringLiteral("保压时间"),QStringLiteral("ms"),1,1);
    addItem(paramLayout,QStringLiteral("震落时间"),QStringLiteral("ms"),2,1);
    addItem(paramLayout,QStringLiteral("冷却时间"),QStringLiteral("ms"),3,1);
    addItem(paramLayout,QStringLiteral("测试振幅"),QStringLiteral("%"),4,1);


    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *btnLoadGroup = new QPushButton(QStringLiteral("读取"));
    QPushButton *btnSaveGroup = new QPushButton(QStringLiteral("保存"));
    QLabel *labelGroup = new QLabel(QStringLiteral("工作组号:"));
    QLineEdit *editGroup = new QLineEdit;
    QPushButton *btnDownloadGroup = new QPushButton(QStringLiteral("下载"));
    btnDownloadGroup->setStyleSheet("background-color:green");

    hLayout->addStretch();
    if(!bEnable)
    {
        hLayout->addWidget(btnLoadGroup);
    }
    else
    {
        hLayout->addWidget(btnSaveGroup);
    }
    hLayout->addWidget(labelGroup);
    hLayout->addWidget(editGroup);
    if(!bEnable)
    {
        hLayout->addWidget(btnDownloadGroup);
    }
    hLayout->addStretch();
    paramLayout->addLayout(hLayout,5,0,1,2);
    paramLayout->setRowStretch(5,1);
 //   hLayout->addStretch();

//    double params[ ] = {20,1};
//    generateY(GEN_POLYNOMINAL,params,2);

//    double params[] = {100,2*3.14/200,0 };
//    generateY(GEN_SIN,params,3);
//    addItem(paramLayout,pointsY ,4,1,3,1);
//    QPoint points[] = {QPoint(0,100),QPoint(100,200),QPoint(200,0),QPoint(300,80),QPoint(500,100),QPoint(600,50),QPoint(700,100),QPoint(800,0),QPoint(999,50)};
//    QPoint points[] = {QPoint(1,50) };
//    generateY(GEN_LAGRANGE_INTER,points,9,8);



//    mainLayout->addSpacing(12);
    mainLayout->addWidget(curveGroup,0,1);
    mainLayout->setColumnStretch(1,1);

    QGridLayout *curveLayout = new QGridLayout;
    curveGroup->setLayout(curveLayout);
    curveLayout->setSpacing(30);
    QWidget *pSpace2 = new QWidget;
    curveLayout->addWidget(pSpace2);
    addItem(curveLayout,pointsY ,1,0,1,1);

    setLayout(mainLayout);
}

void GroupPage::addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column,int rowSpan,int columnSpan)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *titleLabel = new QLabel(title+QStringLiteral(":"));
    QLineEdit *contentEdit = new QLineEdit;
    QLabel *unitLabel = new QLabel(unit);
    QPushButton *downloadBtn = new QPushButton(QStringLiteral("下载"));
    downloadBtn->setStyleSheet("background-color:green");
    if(!m_bEnable)
    {
        downloadBtn->hide();
    }

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentEdit,1,Qt::AlignLeft);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    hLayout->addWidget(downloadBtn,1,Qt::AlignLeft);
    layout->addLayout(hLayout,row,column,rowSpan,columnSpan);
    layout->setRowStretch(row,1);
}

void GroupPage::addItem(QGridLayout *layout, const int * pointsY, int row, int column, int rowSpan, int columnSpan)
{
    QGraphicsScene *scene = new QGraphicsScene;
    //scene->addLine(10, 10, 150, 300);
    QPainterPath axispath;
    int WIDTH=200;
    int HEIGHT=200;
    double xFactor = WIDTH/1000.0;
    double yFactor = 1.0;
    axispath.addRect(0,0,WIDTH,HEIGHT);
     scene->addPath(axispath );

//    QPainterPath curvePath;
//    curvePath.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
//    for(int i=1;i<1000;i+=1)
//    {
//        curvePath.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
//    }
//    scene->addPath(curvePath);

    QGraphicsView *curveView = new QGraphicsView(scene);
    curveView->setScene(scene);
    curveView->setAttribute(Qt::WA_TranslucentBackground,true);
    QPalette  myPalette;
    QColor  myColor(100,100,0);
    myColor.setAlphaF(0.5);
    myPalette.setBrush(curveView->backgroundRole(),myColor);
    curveView->setPalette(myPalette);
    curveView->setStyleSheet("border:0px");//无边框，背景透明
    curveView->setAutoFillBackground(true);//这个的话就不会了，只有view透明
    layout->addWidget(curveView,row,column,rowSpan,columnSpan);
}



WorkPage::WorkPage(QWidget *parent)
    : QWidget(parent)
{

//    QGroupBox *paramGroup = new QGroupBox(QStringLiteral("工作参数"));
    QGroupBox *paramGroup = new QGroupBox(QString::fromLocal8Bit("工作参数"));
//    QGroupBox *statusGroup = new QGroupBox(QStringLiteral("实时数据"));
    QGroupBox *statusGroup = new QGroupBox(QStringLiteral("实时数据"));
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(paramGroup);
    QGridLayout *paramLayout = new QGridLayout;
    paramGroup->setLayout(paramLayout);
    addItem(paramLayout,QStringLiteral("下降时间"),QStringLiteral("ms"),0,0);
    addItem(paramLayout,QStringLiteral("上升时间"),QStringLiteral("ms"),1,0);
    addItem(paramLayout,QStringLiteral("震落振幅"),QStringLiteral("%"),2,0);
    addItem(paramLayout,QStringLiteral("焊接能量"),QStringLiteral("J"),3,0);
    addItem(paramLayout,QStringLiteral("初始驱动"),QStringLiteral(""),4,0);
    addItem(paramLayout,QStringLiteral("工作模式"),QStringLiteral("" ),5,0);
    addItem(paramLayout,QStringLiteral("工作组号"),QStringLiteral("" ),6,0);
    addItem(paramLayout,QStringLiteral("保压时间"),QStringLiteral("ms"),0,1);
    addItem(paramLayout,QStringLiteral("震落时间"),QStringLiteral("ms"),1,1);
    addItem(paramLayout,QStringLiteral("冷却时间"),QStringLiteral("ms"),2,1);
    addItem(paramLayout,QStringLiteral("测试振幅"),QStringLiteral("%"),3,1);
//    double params[ ] = {20,1};
//    generateY(GEN_POLYNOMINAL,params,2);

//    double params[] = {100,2*3.14/200,0 };
//    generateY(GEN_SIN,params,3);
//    addItem(paramLayout,pointsY ,4,1,3,1);
    QPoint points[] = {QPoint(0,100),QPoint(100,200),QPoint(200,0),QPoint(300,80),QPoint(500,100),QPoint(600,50),QPoint(700,100),QPoint(800,0),QPoint(999,50)};
//    QPoint points[] = {QPoint(1,50) };
    generateY(GEN_LAGRANGE_INTER,points,9,8);

     addItem(paramLayout,pointsY ,4,1,3,1);


    mainLayout->addSpacing(12);
    mainLayout->addWidget(statusGroup);
    QGridLayout *statusLayout = new QGridLayout;
    statusGroup->setLayout(statusLayout);
    addItem(statusLayout,QStringLiteral("功  率 "),QStringLiteral("ms"),0,0);
    addItem(statusLayout,QStringLiteral("峰  值 "),QStringLiteral("ms"),1,0);
    addItem(statusLayout,QStringLiteral("频  率 "),QStringLiteral("%"),2,0);
    addItem(statusLayout,QStringLiteral("焊接能量"),QStringLiteral("J"),3,0);
    addItem(statusLayout,QStringLiteral("焊接时间"),QStringLiteral(""),4,0);
    addItem(statusLayout,QStringLiteral("工件计数"),QStringLiteral("" ),5,0);
    addItem(statusLayout,QStringLiteral("错误类型"),QStringLiteral("ms"),6,0);
    addItem(statusLayout,QStringLiteral("上传数据数量"),QStringLiteral("ms"),0,1);


    setLayout(mainLayout);
}

void WorkPage::addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *titleLabel = new QLabel(title+QStringLiteral(":"));
    QLineEdit *contentEdit = new QLineEdit;
    QLabel *unitLabel = new QLabel(unit);

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentEdit,2,Qt::AlignLeft);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    layout->addLayout(hLayout,row,column);
    layout->setRowStretch(row,1);
}

void WorkPage::addItem(QGridLayout *layout, const int * pointsY, int row, int column, int rowSpan, int columnSpan)
{
    QGraphicsScene *scene = new QGraphicsScene;
    //scene->addLine(10, 10, 150, 300);
    QPainterPath axispath;
    int WIDTH=200;
    int HEIGHT=200;
    double xFactor = WIDTH/1000.0;
    double yFactor = 1.0;
    axispath.addRect(0,0,WIDTH,HEIGHT);
//    scene->addPath(axispath );

    QPainterPath curvePath;
    curvePath.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
    for(int i=1;i<1000;i+=1)
    {
//        cout<<"line To :"<<i<<":"<<i*xFactor<<","<<HEIGHT-(pointsY[i]*yFactor)<<endl;
        curvePath.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
    }
    scene->addPath(curvePath);

    QGraphicsView *curveView = new QGraphicsView(scene);
    curveView->setScene(scene);
//    curveView->setFixedSize();
    curveView->setAttribute(Qt::WA_TranslucentBackground,true);
    QPalette  myPalette;
    QColor  myColor(100,100,0);
    myColor.setAlphaF(0.5);
    myPalette.setBrush(curveView->backgroundRole(),myColor);
    curveView->setPalette(myPalette);
    curveView->setStyleSheet("border:0px");//无边框，背景透明
    curveView->setAutoFillBackground(true);//这个的话就不会了，只有view透明
    layout->addWidget(curveView,row,column,rowSpan,columnSpan);
}


bool WorkPage::generateY(EGenAlgorithm algo, double *param, int paramAmount)
{
    for(int i=0;i<1000;i++)
    {
        switch(algo)
        {
        case GEN_POLYNOMINAL:
        {
            pointsY[i] = 0;
            for(int j=0;j<paramAmount;j++)
                pointsY[i] += param[j]*pow(i,j);
        }
            break;
        case GEN_SIN:
        {
            pointsY[i] = param[0]*sin(param[1]*i+param[2]);
        }
            break;
        default:
            pointsY[i] = i;
            break;
        }
    }
    return true;
}

bool WorkPage::generateY(EGenAlgorithm algo, QPoint  *points, int pointAmount, int lagrangeFactor)
{
    //lagrangeFactor  拉格朗日插值次数系数，1代表线性插值，2代表抛物线插值
    //依据lagrange插值多项式 ：
    //Ln(x) = sigma(j=0,n)(y[i]*l[j](x));sigma表示累加 ，lj称为lagrange插值基函数
    //l[j](x) = pai(k=0,n)(x-x[j])/(x[j]-x[k]) ；pai表示累乘

    //    QPoint *basePoints = new QPoints[lagrangeFactor];
    qDebug()<<" pointAmount = "<<pointAmount<<endl;
    switch (algo)
    {
    case GEN_LAGRANGE_INTER:
    {
        QPoint *basePoints = NULL;
        double *baseLagrange = new double[lagrangeFactor];

        if(pointAmount <=0) {return false;}
        if(pointAmount ==1) {
            double param[ ]={points[0].y()*1.0};
            generateY(GEN_POLYNOMINAL,param,sizeof(param));
            return true;
        }
        // 1 <= 插值次数 <= pointAmount-1
        if(lagrangeFactor>pointAmount-1)
        {
            lagrangeFactor = pointAmount-1;
        }
        else if(lagrangeFactor < 1)
        {
            lagrangeFactor = 1;
        }

        //依次插值
        for(int i=0;i<1000;i++)
        {

            //计算第一个基点x索引，数目等于lagrangeFacotr+1, 例如一次线性插值依赖两个基点。
            int index = 0;

            //如果第一个点的横坐标已经大于插值点x了，此时是左外插值
            if(points[0].x() > i)
            {
                index=0;
            }
            //如果最后一个点的横坐标小于等于插值点x，此时是右外插值
            else if(points[pointAmount-1].x() <= i)
            {
                index = pointAmount - 1 - lagrangeFactor;
            }
            //其他情况属于内插值，插值点两边的点尽量平均
            else
            {
                for(int j=0;j<pointAmount-1;j++)
                {
                    if(points[j].x()<=i && points[j+1].x() > i)
                    {
                        //找到最近点points[j]作为求基点的参考
                        index =j;
                        break;
                    }
                    index = pointAmount-1;
                }
                index = index - (lagrangeFactor )/2;
                if(index<0) index=0;
                if(index+lagrangeFactor >pointAmount-1) index= pointAmount-lagrangeFactor-1;
            }
            basePoints =&points[index];

            //求n次插值的n+1个基函数值
            for(int j=0;j<lagrangeFactor+1;j++)
            {
                baseLagrange[j] = 1;
                for(int k=0;k<lagrangeFactor+1;k++)
                {
                    if(k!=j)
                    {
                        baseLagrange[j] *= 1.0*(i-basePoints[k].x());
                        baseLagrange[j] /= 1.0*(basePoints[j].x()-basePoints[k].x());
                    }
                }
            }

            //计算插值L(n) = l0*y0+l1*y1+l2*y2+...+ln*yn
            pointsY[i] = 0;
            for(int j=0;j<lagrangeFactor+1;j++)
            {
                pointsY[i] += basePoints[j].y()*baseLagrange[j];
            }

//             cout<<"inter pointsY ["<<i<<"]="<<pointsY[i]<<endl;
        }
    }
        break;
    default :
        return false;
    }
    return true;
}

DebugPage::DebugPage(QWidget *parent)
    : QWidget(parent)
{

    QGroupBox *cmdGroup = new QGroupBox(QStringLiteral("调试命令"));
    QGroupBox *statusGroup = new QGroupBox(QStringLiteral("实时数据"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(cmdGroup,0,0);
    mainLayout->setColumnStretch(0,1);
    mainLayout->addWidget(statusGroup,0,1);
    mainLayout->setColumnStretch(1,1);

    QGridLayout *cmdLayout = new QGridLayout;
    cmdGroup->setLayout(cmdLayout);
    addItem(cmdLayout,QStringLiteral("机器测试"),0,0,0);
    addItem(cmdLayout,QStringLiteral("清除错误"),2,1,0);
    addItem(cmdLayout,QStringLiteral("焊头上升"),3,2,0);
    addItem(cmdLayout,QStringLiteral("冷却阀开启"),4,3,0);
    addItem(cmdLayout,QStringLiteral("成功信号\n测试开启"),0,4,0);
    addItem(cmdLayout,QStringLiteral("错误信号\n测试开启"),0,5,0);
    addItem(cmdLayout,QStringLiteral("机器工作"),5,0,1);
    addItem(cmdLayout,QStringLiteral("紧急停止"),6,1,1);
    addItem(cmdLayout,QStringLiteral("焊头下降"),7,2,1);
    addItem(cmdLayout,QStringLiteral("冷却阀关闭"),8,3,1);
    addItem(cmdLayout,QStringLiteral("成功信号\n测试关闭"),9,4,1);
    addItem(cmdLayout,QStringLiteral("错误信号\n测试关闭"),10,5,1);


    QGridLayout *statusLayout = new QGridLayout;
    statusGroup->setLayout(statusLayout);
    addItem(statusLayout,QStringLiteral("功  率"),QStringLiteral("ms"),0,0);
    addItem(statusLayout,QStringLiteral("峰  值"),QStringLiteral("ms"),1,0);
    addItem(statusLayout,QStringLiteral("频  率"),QStringLiteral("%"),2,0);
    addItem(statusLayout,QStringLiteral("焊接能量"),QStringLiteral("J"),3,0);
    addItem(statusLayout,QStringLiteral("焊接时间"),QStringLiteral(""),4,0);
    addItem(statusLayout,QStringLiteral("工件计数"),QStringLiteral("" ),5,0);
    addItem(statusLayout,QStringLiteral("错误类型"),QStringLiteral("ms"),6,0);
    addItem(statusLayout,QStringLiteral("上传数据数量"),QStringLiteral("ms"),7,0);


    setLayout(mainLayout);
}

void DebugPage::addItem(QGridLayout *layout, const QString &title, int addr, int row,int column,int rowSpan,int columnSpan)
{
    QPushButton *downloadBtn = new QPushButton(title);
    downloadBtn->setProperty("addr",addr);
 //   downloadBtn->setProperty("data",data);
    downloadBtn->setStyleSheet("background-color:green");
    connect(downloadBtn,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_pushButton_clicked);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(downloadBtn);
    hLayout->addStretch();
    layout->addLayout(hLayout,row,column,rowSpan,columnSpan);
}

void DebugPage::addItem(QGridLayout *layout, const QString &title, const QString &unit,int row,int column)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *titleLabel = new QLabel(title+QStringLiteral(":"));
    QLineEdit *contentEdit = new QLineEdit;
    QLabel *unitLabel = new QLabel(unit);

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentEdit,1);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    hLayout->addStretch();
    layout->addLayout(hLayout,row,column);
}


CurvePage::CurvePage(QWidget *parent)
    : QWidget(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(0,0,1000,1000);
    scene->addRect(0,0,1000,1000);
    QGraphicsView *curveView = new QGraphicsView;
    curveView->setScene(scene);
    curveView->setAttribute(Qt::WA_TranslucentBackground,true);
    QPalette  myPalette;
    QColor  myColor(100,100,0);
    myColor.setAlphaF(0.5);
    myPalette.setBrush(curveView->backgroundRole(),myColor);
    curveView->setPalette(myPalette);
    curveView->setStyleSheet("border:0px");//无边框，背景透明
    curveView->setAutoFillBackground(true);//这个的话就不会了，只有view透明

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(curveView);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(new QPushButton(QStringLiteral("振幅")));
    hLayout->addWidget(new QPushButton(QStringLiteral("相位")));
    hLayout->addWidget(new QPushButton(QStringLiteral("电压")));
    hLayout->addWidget(new QPushButton(QStringLiteral("功率")));
    hLayout->addWidget(new QPushButton(QStringLiteral("频率")));


    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);
    QPushButton *btnUpload = new QPushButton(QStringLiteral("上传数据"));
    btnUpload->setStyleSheet("background-color:green");
    hLayout->addWidget(btnUpload);

    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);


}


AboutPage::AboutPage(QWidget *parent)
    : QWidget(parent)
{

    QGroupBox *aboutGroup = new QGroupBox(QStringLiteral("关于软件"));
    QVBoxLayout *aboutLayout = new QVBoxLayout;
    QLabel *aboutLabel = new QLabel(QStringLiteral("\n\
                                       版本：UMWelding-1.0.1 \n\
                                       公司：暨通信息科技有限公司@ 保留所有权利\n\
                                       地址：广州市越秀区天河路") );
    aboutLayout->addWidget(aboutLabel);
    aboutGroup->setLayout(aboutLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(aboutGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

}
