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

ConfigDialog::ConfigDialog()
{

     setWindowFlags(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowMaximized);
    setObjectName("ConfigDialog");
     setStyleSheet("#ConfigDialog{border-image:url(:/images/frame.png);}");

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

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    createIcons();
    contentsWidget->setCurrentRow(0);
    contentsWidget->setStyleSheet("background-color:transparent");


    QHBoxLayout *horizontalLayout = new QHBoxLayout;
     horizontalLayout->addWidget(contentsWidget,1 );
     horizontalLayout->addWidget(pagesWidget,1 );

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout,10);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
}

void ConfigDialog::addButton(QListWidget *widget,const QString &icon, const QString &text )
{

    QListWidgetItem *configButton = new QListWidgetItem(widget);
    configButton->setIcon(QIcon(icon));
    configButton->setText(text);
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}


void ConfigDialog::createIcons()
{
    addButton(contentsWidget,tr(":/images/work.png"),tr("工作"));
    addButton(contentsWidget,tr(":/images/group.png"),tr("分组"));
    addButton(contentsWidget,tr(":/images/config.png"),tr("设置"));
    addButton(contentsWidget,tr(":/images/curve.png"),tr("曲线"));
    addButton(contentsWidget,tr(":/images/debug.png"),tr("调试"));
    addButton(contentsWidget,tr(":/images/about.png"),tr("关于"));
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
}
