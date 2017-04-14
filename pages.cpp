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
#include "curveview.h"
#include <iostream>
using namespace std;





GroupPage::GroupPage(bool bEnable, QWidget *parent)

    : QWidget(parent)
    , m_bEnable(bEnable)
{
    if(!m_bEnable)
        setObjectName(QStringLiteral("分组"));
    else
        setObjectName(QStringLiteral("设置"));

    QGroupBox *paramGroup = new QGroupBox(QStringLiteral("工作参数"));
    QGroupBox *curveGroup = new QGroupBox(QStringLiteral("曲线参数"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(paramGroup,0,0);
    mainLayout->setColumnStretch(0,1);
    mainLayout->setSpacing(20);
    QGridLayout *paramLayout = new QGridLayout;
    paramGroup->setLayout(paramLayout);

    addItem(paramLayout,QStringLiteral("下降时间"),QStringLiteral("ms"),QStringLiteral("20"),0x256E,0,0);
    addItem(paramLayout,QStringLiteral("上升时间"),QStringLiteral("ms"),QStringLiteral("100"),0x2570,1,0);
    addItem(paramLayout,QStringLiteral("震落振幅"),QStringLiteral("%") ,QStringLiteral("60"),0x2572,2,0);
    addItem(paramLayout,QStringLiteral("焊接能量"),QStringLiteral("J") ,QStringLiteral("2000"),0x2574,3,0);
    addItem(paramLayout,QStringLiteral("初始驱动"),QStringLiteral("")  ,QStringLiteral("30"),0x2576,4,0);

//    addItem(paramLayout,QStringLiteral("工作模式"),QStringLiteral("" ),0,1);
    QStringList list;
    list<<QStringLiteral("智能模式")<<QStringLiteral("能量模式")<<QStringLiteral("时间模式")<<QStringLiteral("高度模式");
    addItem(paramLayout,QStringLiteral("工作模式"),list,QStringLiteral(""),0x2577 ,0,1);

    addItem(paramLayout,QStringLiteral("保压时间"),QStringLiteral("ms") ,QStringLiteral("100"),0x256F,1,1);
    addItem(paramLayout,QStringLiteral("震落时间"),QStringLiteral("ms") ,QStringLiteral("500"),0x2571,2,1);
    addItem(paramLayout,QStringLiteral("冷却时间"),QStringLiteral("ms") ,QStringLiteral("3000"),0x2573,3,1);
    addItem(paramLayout,QStringLiteral("测试振幅"),QStringLiteral("%")  ,QStringLiteral("50"),0x2575,4,1);


    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *btnLoadGroup = new QPushButton(QStringLiteral("读取"));
    QPushButton *btnSaveGroup = new QPushButton(QStringLiteral("保存"));

    QLabel *labelGroup = new QLabel(QStringLiteral("工作组号:"));
//    QLineEdit *editGroup = new QLineEdit;
    QComboBox *comboGroup = new QComboBox;
    QPushButton *btnDownloadGroup = new QPushButton(QStringLiteral("下载"));
    btnDownloadGroup->setStyleSheet("background-color:green");

    hLayout->addStretch();
    if(!bEnable)
    {
        hLayout->addWidget(btnLoadGroup);
        connect(btnLoadGroup,&QPushButton::clicked,this,&GroupPage::on_loadButton_clicked);
    }
    else
    {
        hLayout->addWidget(btnSaveGroup);
        connect(btnSaveGroup,&QPushButton::clicked,this,&GroupPage::on_saveButton_clicked);
    }
    if(!bEnable)
    {
        hLayout->addWidget(labelGroup);
        hLayout->addWidget(comboGroup);
        ConfigDialog::getInstance()->groupBox = comboGroup;
        hLayout->addWidget(btnDownloadGroup);
        connect(btnDownloadGroup,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_downloadGroupButton_clicked);
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
//    QPointF points[] = {QPointF(0,100),QPointF(100,200),QPointF(200,0),QPointF(300,80),QPointF(500,100),QPointF(600,50),QPointF(700,100),QPointF(800,0),QPointF(999,50)};
//    QPointF points[] = {QPointF(1,50) };
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

void GroupPage::addItem(QGridLayout *layout, const QString &title, const QString &unit,const QString &initValue,int addr,int row,int column,int rowSpan,int columnSpan)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *titleLabel = new QLabel(title+QStringLiteral(":"));
    QLineEdit *contentEdit = new QLineEdit;
    contentEdit->setValidator(new QIntValidator(0,1000,this));
    contentEdit->setText(initValue);
    contentEdit->setMinimumWidth(80);
    QLabel *unitLabel = new QLabel(unit);
    QPushButton *downloadBtn = new QPushButton(QStringLiteral("下载"));
    downloadBtn->setStyleSheet("background-color:green");
    downloadBtn->setProperty("addr",addr);
    downloadBtn->setProperty("lineedit",QVariant::fromValue(contentEdit))  ;
    if(!m_bEnable)
    {
        downloadBtn->hide();
    }

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentEdit,1,Qt::AlignLeft);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    hLayout->addWidget(downloadBtn,1,Qt::AlignLeft);
    connect(downloadBtn,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_downloadButton_clicked);
    layout->addLayout(hLayout,row,column,rowSpan,columnSpan);
    layout->setRowStretch(row,1);
}

void GroupPage::addItem(QGridLayout *layout, const QString &title, const QStringList &contents, const QString &unit,int addr,int row,int column,int rowSpan,int columnSpan)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *titleLabel = new QLabel(title+QStringLiteral(":"));
    QComboBox *contentCbb = new QComboBox;
    contentCbb->addItems(contents);
//    contentEdit->setValidator(new QIntValidator(0,1000,this));
    QLabel *unitLabel = new QLabel(unit);
    QPushButton *downloadBtn = new QPushButton(QStringLiteral("下载"));
    downloadBtn->setStyleSheet("background-color:green");
    downloadBtn->setProperty("addr",addr);
    downloadBtn->setProperty("combobox",QVariant::fromValue(contentCbb))  ;
    if(!m_bEnable)
    {
        downloadBtn->hide();
    }

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentCbb,1,Qt::AlignLeft);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    hLayout->addWidget(downloadBtn,1,Qt::AlignLeft);
    connect(downloadBtn,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_downloadButton_clicked);
    layout->addLayout(hLayout,row,column,rowSpan,columnSpan);
    layout->setRowStretch(row,1);
}

void GroupPage::addItem(QGridLayout *layout, const int * pointsY, int row, int column, int rowSpan, int columnSpan)
{
    QGraphicsScene *scene = new QGraphicsScene;
    QPainterPath axispath;
    int WIDTH=200;
    int HEIGHT=200;
    double xFactor = WIDTH/1000.0;
    double yFactor = 1.0;
    axispath.addRect(0,0,WIDTH,HEIGHT);
     scene->addPath(axispath );


    CurveView *curveView = new CurveView;
    QPointF points[] = {QPointF(0,100),QPointF(100,200),QPointF(200,0),QPointF(300,80),QPointF(500,100),QPointF(600,50),QPointF(700,100),QPointF(800,0),QPointF(999,50)};
    curveView-> generateY(CurveView::GEN_LAGRANGE_INTER,points,9,6);
//    curveView->draw();
//    layout->addWidget(curveView,row,column,rowSpan,columnSpan);
    layout->addLayout(curveView->getLayout(),row,column,rowSpan,columnSpan);
}

void GroupPage::on_saveButton_clicked()
{
    QMessageBox::information(NULL,tr("info"),tr("save group"));

    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        ConfigDialog::getInstance()->groupBox->addItem(text );
    }
        //textLabel->setText(text);
}

void GroupPage::on_loadButton_clicked()
{
    QMessageBox::information(NULL,tr("info"),tr("load group"));
}


WorkPage::WorkPage(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("工作"));
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
    CurveView *curveView =new CurveView ;
    QPointF points[] = {QPointF(0,100),QPointF(100,200),QPointF(200,0),QPointF(300,80),QPointF(500,100),QPointF(600,50),QPointF(700,100),QPointF(800,0),QPointF(999,50)};
    curveView-> generateY(CurveView::GEN_LAGRANGE_INTER,points,9,4);
//    curveView->draw();
//    paramLayout->addWidget(curveView,4,1,3,1);
    paramLayout->addLayout(curveView->getLayout(),4,1,3,1);
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
    contentEdit->setMinimumWidth(80);
    QLabel *unitLabel = new QLabel(unit);

    hLayout->addWidget(titleLabel,1,Qt::AlignRight);
    hLayout->addWidget(contentEdit,2,Qt::AlignLeft);
    hLayout->addWidget(unitLabel,1,Qt::AlignLeft);
    layout->addLayout(hLayout,row,column);
    layout->setRowStretch(row,1);
}

void WorkPage::addItem(QGridLayout *layout, const int * pointsY, int row, int column, int rowSpan, int columnSpan)
{
    CurveView *curveView = new CurveView;
    QPointF points[] = {QPointF(0,100),QPointF(100,200),QPointF(200,0),QPointF(300,80),QPointF(500,100),QPointF(600,50),QPointF(700,100),QPointF(800,0),QPointF(999,50)};
    curveView-> generateY(CurveView::GEN_LAGRANGE_INTER,points,9,2);
//    curveView->draw();
//    layout->addWidget(curveView,row,column,rowSpan,columnSpan);
    layout->addLayout(curveView->getLayout(),row,column,rowSpan,columnSpan);
}


DebugPage::DebugPage(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("调试"));
    QGroupBox *cmdGroup = new QGroupBox(QStringLiteral("调试命令"));
    QGroupBox *statusGroup = new QGroupBox(QStringLiteral("实时数据"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(cmdGroup,0,0);
    mainLayout->setColumnStretch(0,1);
    mainLayout->addWidget(statusGroup,0,1);
    mainLayout->setColumnStretch(1,1);

    QGridLayout *cmdLayout = new QGridLayout;
    cmdGroup->setLayout(cmdLayout);
    addItem(cmdLayout,QStringLiteral("机器测试"),0x26FF,0x0002,0,0);
    addItem(cmdLayout,QStringLiteral("清除错误"),0x26FF,0x0001,1,0);
    addItem(cmdLayout,QStringLiteral("焊头上升"),0x26FF,0x0005,2,0);
    addItem(cmdLayout,QStringLiteral("冷却阀开启"),0x26FF,0x0007,3,0);
    addItem(cmdLayout,QStringLiteral("成功信号\n测试开启"),0x26FF,0x0009,4,0);
    addItem(cmdLayout,QStringLiteral("错误信号\n测试开启"),0x26FF,0x0011,5,0);
    addItem(cmdLayout,QStringLiteral("机器工作"),0x26FF,0x0003,0,1);
    addItem(cmdLayout,QStringLiteral("紧急停止"),0x26FF,0x0004,1,1);
    addItem(cmdLayout,QStringLiteral("焊头下降"),0x26FF,0x0006,2,1);
    addItem(cmdLayout,QStringLiteral("冷却阀关闭"),0x26FF,0x0008,3,1);
    addItem(cmdLayout,QStringLiteral("成功信号\n测试关闭"),0x26FF,0x0010,4,1);
    addItem(cmdLayout,QStringLiteral("错误信号\n测试关闭"),0x26FF,0x0012,5,1);


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

void DebugPage::addItem(QGridLayout *layout, const QString &title, int addr,int data, int row,int column,int rowSpan,int columnSpan)
{
    QPushButton *downloadBtn = new QPushButton(title);
    downloadBtn->setProperty("addr",addr);
    downloadBtn->setProperty("data",data);
    downloadBtn->setStyleSheet("background-color:green");
    connect(downloadBtn,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_downloadButton_clicked);
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
    setObjectName(QStringLiteral("曲线"));
    CurveView *curveView = new CurveView;
//    QPointF points[] = {QPointF(0,100),QPointF(100,200),QPointF(200,0),QPointF(300,80),QPointF(500,100),QPointF(600,50),QPointF(700,100),QPointF(800,0),QPointF(999,50)};
//    curveView-> generateY(CurveView::GEN_LAGRANGE_INTER,points,9,8);
//    double param[] = {1000,0.5};
//    curveView->generateY(CurveView::GEN_BINOMIAL_DISTRIBUTION,param,2);

    double param[] = {100};
    curveView->generateY(CurveView::GEN_POISSON_DISTRIBUTION,param,1);
//    double param[] = {100,30,20};
//    curveView->generateY(CurveView::GEN_RANDOM,param,3);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(curveView);
    mainLayout->addLayout(curveView->getLayout());

    QHBoxLayout *hLayout = new QHBoxLayout;
//    hLayout->addWidget(new QPushButton(QStringLiteral("振幅")));
//    hLayout->addWidget(new QPushButton(QStringLiteral("相位")));
//    hLayout->addWidget(new QPushButton(QStringLiteral("电压")));
//    hLayout->addWidget(new QPushButton(QStringLiteral("功率")));
//    hLayout->addWidget(new QPushButton(QStringLiteral("频率")));

    QCheckBox *checkBox1 = new QCheckBox(QStringLiteral("振幅"));
    QCheckBox *checkBox2 = new QCheckBox(QStringLiteral("相位"));
    QCheckBox *checkBox3 = new QCheckBox(QStringLiteral("电压"));
    QCheckBox *checkBox4 = new QCheckBox(QStringLiteral("功率"));
    QCheckBox *checkBox5 = new QCheckBox(QStringLiteral("频率"));


    hLayout->addWidget(checkBox1);
    hLayout->addWidget(checkBox2);
    hLayout->addWidget(checkBox3);
    hLayout->addWidget(checkBox4);
    hLayout->addWidget(checkBox5);


    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);
    QPushButton *btnUpload = new QPushButton(QStringLiteral("上传数据"));
    btnUpload->setProperty("addr1",0x1000);//1024个字，每次最多读50个字，最少需要读21次
    btnUpload->setProperty("addr2",0x1400);
    btnUpload->setProperty("addr3",0x1800);
    btnUpload->setProperty("addr4",0x1C00);
    btnUpload->setProperty("addr5",0x2000);

    btnUpload->setProperty("check1",QVariant::fromValue(checkBox1));//1024个字，每次最多读50个字，最少需要读21次
    btnUpload->setProperty("check2",QVariant::fromValue(checkBox2));
    btnUpload->setProperty("check3",QVariant::fromValue(checkBox3));
    btnUpload->setProperty("check4",QVariant::fromValue(checkBox4));
    btnUpload->setProperty("check5",QVariant::fromValue(checkBox5));

    connect(btnUpload,&QPushButton::clicked,ConfigDialog::getInstance(),&ConfigDialog::on_uploadButton_clicked);
    btnUpload->setStyleSheet("background-color:green");
    hLayout->addWidget(btnUpload);

    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);


}


AboutPage::AboutPage(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("关于"));
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
