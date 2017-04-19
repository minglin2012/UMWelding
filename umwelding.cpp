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
#include <QMessageBox>
#include "umwelding.h"
#include "pages.h"

ConfigDialog::ConfigDialog()
    : m_pModbusCtx(NULL)
    , contentsWidget(NULL)
    , pagesWidget(NULL)
    , m_cboSetGroups(NULL)
    , statusBar(NULL)
    , statusLabel(NULL)
    , serialBox(NULL)
    , serialRatio(NULL)
    , statusTimer(NULL)
    , serialDevCombo(NULL)
{
}

void ConfigDialog::Initialize()
{

//     setWindowFlags(Qt::FramelessWindowHint);
//    setWindowState(Qt::WindowMaximized);
    setObjectName("umwelding");
     setStyleSheet("#umwelding{border-image:url(:/images/frame.png);}");

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
     contentsWidget->setMaximumWidth(160);
//    contentsWidget->setMaximumHeight(1000);
    contentsWidget->setSpacing(12);
//    setStyleSheet("contentsWidget{color:gray;font-size:12px;background:#FAFAFD;}\
//                QScrollBar{width:0;height:0}");
//     contentsWidget->setResizeMode(QListView::Adjust);
//    contentsWidget->resize();

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new WorkPage);
    pagesWidget->addWidget(new GroupPage(false));
    pagesWidget->addWidget(new GroupPage(true));
    pagesWidget->addWidget(new CurvePage);
    pagesWidget->addWidget(new DebugPage);
    pagesWidget->addWidget(new AboutPage);

    QPushButton *closeButton = new QPushButton(QStringLiteral("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    createIcons();
    contentsWidget->setCurrentRow(0);
    contentsWidget->setStyleSheet("background-color:transparent");


    QHBoxLayout *horizontalLayout = new QHBoxLayout;
     horizontalLayout->addWidget(contentsWidget,1 );
     horizontalLayout->addWidget(pagesWidget,1 );

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    QLabel *msgLabel = new QLabel;
    statusLabel = msgLabel;
    msgLabel->setStyleSheet(" QLabel{ color: green }");
//    msgLabel->setText("Ready :");
    QStatusBar *status = new QStatusBar;
    statusBar = status;
    status->addWidget(msgLabel);

    QRadioButton *serialRadio = new QRadioButton(QStringLiteral("开启端口"));
    this->serialRatio = serialRadio;

    QComboBox *serialDevCombo = new QComboBox;
    serialDevCombo->addItem("COM");
    serialDevCombo->addItem("/dev/ttyS");
    serialDevCombo->addItem("/dev/ttyUSB");
    serialDevCombo->addItem("/dev/pts/");
    this->serialDevCombo =serialDevCombo;

    QComboBox *serialCombo = new QComboBox;
    serialBox = serialCombo;
    serialCombo->addItem("0");
    serialCombo->addItem("1");
    serialCombo->addItem("2");
    serialCombo->addItem("3");
    connect(serialRadio,&QRadioButton::clicked,this,&ConfigDialog::on_serialButton_clicked);

#ifdef WIN32
    serialDevCombo->setCurrentIndex(0);
    serialCombo->setCurrentIndex(0);
#else
    serialDevCombo->setCurrentIndex(3);
    serialCombo->setCurrentIndex(1);
#endif


    buttonsLayout->addWidget(status);
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(serialRadio);
    buttonsLayout->addWidget(serialDevCombo);
    buttonsLayout->addWidget(serialCombo);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout,10);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    readParamList();
    updatePages();

    serialRadio->click();

    statusTimer = new QTimer(this);
    connect( statusTimer, SIGNAL(timeout()),this, SLOT(on_statusTimer_out()) );
    statusTimer->start();

}

void ConfigDialog::addButton(QListWidget *widget,const QString &icon, const QString &text )
{

    QListWidgetItem *configButton = new QListWidgetItem(widget);
    configButton->setIcon(QIcon(icon));
    configButton->setText(text);
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

bool ConfigDialog::write(int addr, int nb, const uint16_t *data)
{
    //03命令
    //modbus_read_registers(m_pModbusCtx,m_nAddr,m_nNumber,m_pDest);
    //10命令
    //modbus_write_registers(m_pModbusCtx,m_nAddr,m_nNumber,m_pSrc);
    if(NULL == m_pModbusCtx) return false;
    return (-1 != modbus_write_registers(m_pModbusCtx,addr,nb,data));
}

bool ConfigDialog::read(int addr, int nb, uint16_t *dest)
{
    if(NULL == m_pModbusCtx) return false;
    return (-1 != modbus_read_registers(m_pModbusCtx,addr,nb,dest));
}


void ConfigDialog::createIcons()
{
    addButton(contentsWidget,QStringLiteral(":/images/work.png"),QStringLiteral("工作"));
    addButton(contentsWidget,QStringLiteral(":/images/group.png"),QStringLiteral("分组"));
    addButton(contentsWidget,QStringLiteral(":/images/config.png"),QStringLiteral("设置"));
    addButton(contentsWidget,QStringLiteral(":/images/curve.png"),QStringLiteral("曲线"));
    addButton(contentsWidget,QStringLiteral(":/images/debug.png"),QStringLiteral("调试"));
    addButton(contentsWidget,QStringLiteral(":/images/about.png"),QStringLiteral("关于"));
//    contentsWidget->adjustSize();

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));

    setWindowTitle(pagesWidget->currentWidget()->objectName());
}

void ConfigDialog::on_downloadButton_clicked()
{
    QPushButton *btn=(QPushButton*)sender();
    QVariant var_addr = btn->property("addr");
    QVariant var_data = btn->property("data");
    QVariant var_lineedit = btn->property("lineedit");
    QVariant var_combobox = btn->property("combobox");
    if(!var_addr.isValid()) { return ;}
    int addr = var_addr.toInt();
    uint16_t data;
    if(var_data.isValid()) {
        data = var_data.toUInt();
    }
    else if(var_lineedit.isValid()){
        data = var_lineedit.value<QLineEdit*>()->text().toInt();
    }
    else if(var_combobox.isValid()) {
        data = var_combobox.value<QComboBox*>()->currentIndex();
    }
    else {
        return;
    }

    qDebug()<<"modbus_write_registers:addr["<<(void*)addr<<"],data["<<data<<"]";
    QString text;
    text += QStringLiteral("地址[%1H],数据[%2H]" ).arg(QString::number(addr,16),4,QChar('0')).arg(QString::number(data,16),4,QChar('0') );
    QMessageBox::information(NULL,QStringLiteral("下载信息"),text);
    bool flag = write(addr,1,&data);
    if(flag)
    {
        statusLabel->setStyleSheet(" QLabel{ color: green }");
        statusLabel->setText(QStringLiteral("下载成功"));
    }
    else
    {
        statusLabel->setStyleSheet(" QLabel{ color: red }");
        statusLabel->setText(QStringLiteral("下载失败"));
        if(var_data.isValid())
        {
            btn->setStyleSheet("background-color:rgba(255,0,0,255)");
        }
        else if(var_lineedit.isValid())
        {
            var_lineedit.value<QLineEdit*>()->setStyleSheet("background-color:rgba(255,0,0,255)");
        }
//        else if(var_combobox.isValid())
//        {
//            var_combobox.value<QLineEdit*>()->setStyleSheet("background-color:rgba(255,0,0,255)");
//        }
    }
    statusTimer->start( 3000 ); // 2秒单触发定时器

}
void ConfigDialog::on_uploadButton_clicked()
{
    QPushButton *btn=(QPushButton*)sender();
    QVariant var_addr[5];
    QVariant var_check[5];
    var_addr[0] = btn->property("addr1");
    var_addr[1] = btn->property("addr2");
    var_addr[2] = btn->property("addr3");
    var_addr[3] = btn->property("addr4");
    var_addr[4] = btn->property("addr5");
    var_check[0] = btn->property("check1");
    var_check[1] = btn->property("check2");
    var_check[2] = btn->property("check3");
    var_check[3] = btn->property("check4");
    var_check[4] = btn->property("check5");


//    if(!var_addr.isValid()) { return ;}
    int addr[5];
    addr[0] = var_addr[0].toInt();
    addr[1] = var_addr[1].toInt();
    addr[2] = var_addr[2].toInt();
    addr[3] = var_addr[3].toInt();
    addr[4] = var_addr[4].toInt();


    for(int i=0;i<5;i++)
    {
        if(var_check[i].value<QCheckBox*>()->isChecked())
        {
            int j;
            for(j=0;j+50<1024;j+=50)
            {
                if(!read(addr[i]+j,50,&registerAddr[i][j]))
                {
                    QString text;
                    text += QStringLiteral("地址[%1H],长度[%2H]" ).arg(QString::number(addr[i]+j,16),4,QChar('0')).arg(QString::number(50,16),4,QChar('0') );
                    QMessageBox::information(NULL,QStringLiteral("下载信息"),text);
                    continue;
                    return ;
                }
            }
            if(!read(addr[i]+j,1024-j,&registerAddr[i][j]))
            {
                QString text;
                text += QStringLiteral("地址[%1H],长度[%2H]" ).arg(QString::number(addr[i]+j,16),4,QChar('0')).arg(QString::number(1024-j,16),4,QChar('0') );
                QMessageBox::information(NULL,QStringLiteral("下载信息"),text);
                continue;
                return ;
            }
        }
    }

//    qDebug()<<"modbus_write_registers:addr["<<(void*)addr<<"],data["<<dstdata<<"],len["<<len;
//    QMessageBox::information(NULL,QStringLiteral("下载信息"),text);

//    if(flag)
//    {
//        statusLabel->setStyleSheet(" QLabel{ color: green }");
//        statusLabel->setText(QStringLiteral("下载成功"));
//    }
//    else
//    {
//        statusLabel->setStyleSheet(" QLabel{ color: red }");
//        statusLabel->setText(QStringLiteral("下载失败"));
//    }
    statusTimer->start( 3000 ); // 2秒单触发定时器
}


void ConfigDialog::on_downloadGroupButton_clicked()
{
    QMessageBox::information(NULL,tr("info"),tr("download group"));

}

void ConfigDialog::on_serialButton_clicked()
{
    QRadioButton *btn=(QRadioButton*)sender();
    if(btn->isChecked())
    {
        int index = serialBox->currentIndex();
//#ifdef WIN32
//        QString dev = QString("%1%2").arg(QString("COM")).arg(index+1);
//#else
//        QString dev = QString("%1%2").arg(QString("/dev/ttyUSB")).arg(index);
//#endif
        QString dev = QString("%1%2").arg(serialDevCombo->currentText()).arg(index);

        if(NULL == (m_pModbusCtx = modbus_new_rtu(dev.toStdString().c_str(),38400,'N',8,1)))
        {
            btn->setChecked(false);
            return;
        }
        modbus_set_slave(m_pModbusCtx,1);
        if( -1 == modbus_connect(m_pModbusCtx))
        {
            btn->setChecked(false);
            return;
        }
    }
    else
    {
        modbus_close(m_pModbusCtx);
    }
    if(NULL != statusTimer)
    {
        statusTimer->start();
    }

}

void ConfigDialog::on_statusTimer_out()
{
    statusTimer->stop();
    if(serialRatio->isChecked())
    {
        statusLabel->setStyleSheet(" QLabel{ color: green }");
        statusLabel->setText(QStringLiteral("就绪:"));
    }
    else
    {
        statusLabel->setStyleSheet(" QLabel{ color: red }");
        statusLabel->setText(QStringLiteral("未就绪:"));
    }
}


ConfigDialog * ConfigDialog::getInstance()
{
    static ConfigDialog *pInstance = NULL;
    if(NULL == pInstance)
    {
        pInstance = new ConfigDialog;
    }
    return pInstance;

}


bool ConfigDialog::readParamList()
{

    QFile file("file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);    // read the data serialized from the file
    in >> umweldingParamList;           // extract "the answer is" and 42
}


bool ConfigDialog::writeParamList()
{
    QFile file("file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << umweldingParamList;
}


bool ConfigDialog::addGroup(const QString &name, const QList<quint32> &value, const QList<double> &data)
{
    UmweldingParams param;
    param.name = name;
    param.value = value;
    param.data  = data;
    umweldingParamList.push_back(param);
    return true;
}


void ConfigDialog::updatePages()
{
    ConfigDialog::getInstance()->m_cboSetGroups->clear();
    ConfigDialog::getInstance()->m_cboGroupGroups->clear();
    for(QList<UmweldingParams>::iterator iter=umweldingParamList.begin();iter != umweldingParamList.end();++iter)
    {
        ConfigDialog::getInstance()->m_cboSetGroups->addItem(iter->name);
        ConfigDialog::getInstance()->m_cboGroupGroups->addItem(iter->name);
    }

}
