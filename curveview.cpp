#include "curveview.h"
#include <QGraphicsItem>
#include <cmath>
#include <QDebug>
#include <QTime>
#include <QLabel>
#include <QPushButton>

#include "myellipseitem.h"
__int64_t factorial(int  x )
{
    return x ? ( factorial(x-1)*x) : 1;
}

CurveView::CurveView(QWidget *parent) :
    QGraphicsView(parent)
{
    viewLayout = new QGridLayout;

    setAttribute(Qt::WA_TranslucentBackground,true);
    QPalette  myPalette;
    QColor  myColor(100,100,0);
    myColor.setAlphaF(0.5);
    myPalette.setBrush( backgroundRole(),myColor);
    setPalette(myPalette);
    setStyleSheet("border:0px");//无边框，背景透明
    setAutoFillBackground(true);//这个的话就不会了，只有view透明
    m_pScene = new QGraphicsScene;

//    QPainterPath curvePath;
//    curvePath.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
//    for(int i=1;i<1000;i+=1)
//    {
//          cout<<"line To :"<<i<<":"<<i*xFactor<<","<<HEIGHT-(pointsY[i]*yFactor)<<endl;
//        curvePath.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
//    }

    // a white semi-transparent foreground
    m_pScene->setBackgroundBrush(QColor(0, 255, 0, 130));

    // a grid foreground
    m_pScene->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    setScene(m_pScene);

    axisHLayout = new QHBoxLayout;
    axisVLayout = new QVBoxLayout;
    QFont font = this->font();
    font.setPixelSize(12);
    font.setBold(true);
    for(int i=0;i<1000;i+=200)
    {
        QString str("%1");
        QLabel *label = new QLabel(str.arg(i));
        label->setFont(font);
        axisHLayout->addWidget(label);
    }
    double interval=200;
    for(int i=0;i<5;i++)
    {
        QLabel *label = new QLabel(QString::number(800-i*interval,10,0));
        label->setFont(font);
        axisVLayout->addWidget(label,0,Qt::AlignBottom);
    }
    viewLayout->addLayout(axisVLayout,0,0,1,1);
    QPushButton *pBtn = new QPushButton(tr("R"));
    viewLayout->addWidget(pBtn,1,0,1,1);
    connect(pBtn,&QPushButton::clicked,this,&CurveView::on_runButton_clicked);
    viewLayout->addWidget(this,0,1,1,1);
    viewLayout->addLayout(axisHLayout,1,1,1,1);

}

void CurveView::addPoint(const QPoint &)
{

}

void CurveView::addPoint(int x, int y)
{

}

void CurveView::addPoints(const QPoint*,int amount)
{

}

void CurveView::addPoints(const QList<QPoint> &)
{}

bool CurveView::generateY(EGenAlgorithm algo, double *param, int paramAmount)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    pointsYmax = -1e10;
    pointsYmin = 1e10;
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
        case GEN_BINOMIAL_DISTRIBUTION:
        {
            //P(ξ=K) = C(n,k) * p^k * (1-p)^(n-k), 其中C(n, k) = n!/(k! * (n-k)!)
            //A(ξ=K) = C(n,k)
            pointsY[i] =0;
            int k=i;
            int n=param[0]+0.5;
            double p=param[1];
            Q_ASSERT(n>1);
            Q_ASSERT(p<1 && p>0);
            Q_ASSERT(paramAmount==2);

            if(k<=n)
            {
                double c_n_k=1.0;
                for(int j=k+1;j<=n;j++)
                {
                    c_n_k *= j*1.0/(j-k);
                }
                pointsY[i] =  c_n_k * pow(p,k) *pow(1-p,n-k)  ;
            }

        }
            break;
        case GEN_POISSON_DISTRIBUTION:
        {
            //P(X=k) = pow(λ,k)*exp(-λ)/k!,k=0,1,2,...
            double lamda = param[0];

            double poisson=1.0;
            poisson *= exp(-lamda);
            for(int j=1;j<i;j++)
            {
                poisson *=lamda/j;
            }
            pointsY[i] = poisson;
        }
            break;
        case GEN_NORMAL_DISTRIBUTION:
        {
            //P(X=k) =
        }
            break;
        case GEN_RANDOM:
        {
            Q_ASSERT(paramAmount==3);
            QList<QPointF> listPoints;

            for(int i=0;i+param[2]<1000;i+=param[2])
            {
                listPoints.append(QPointF(i,qrand()%(int)(2*param[1])+param[0]-param[1]));
            }
            listPoints.append(QPointF(999,qrand()%(int)(2*param[1])+param[0]-param[1]));
            return generateY(GEN_POLYNOMINAL,listPoints,1);
        }
            break;
        default:
            pointsY[i] = i;
            break;
        }
        pointsYmax = qMax(pointsYmax,pointsY[i]);
        pointsYmin = qMin(pointsYmin,pointsY[i]);
    }
    qDebug()<<"max="<<pointsYmax<<",min="<<pointsYmin;
    return true;
}

bool CurveView::generateY(EGenAlgorithm algo, QPointF  *points, int pointAmount, int lagrangeFactor)
{
    //lagrangeFactor  拉格朗日插值次数系数，1代表线性插值，2代表抛物线插值
    //依据lagrange插值多项式 ：
    //Ln(x) = sigma(j=0,n)(y[i]*l[j](x));sigma表示累加 ，lj称为lagrange插值基函数
    //l[j](x) = pai(k=0,n)(x-x[j])/(x[j]-x[k]) ；pai表示累乘

    //    QPoint *basePoints = new QPoints[lagrangeFactor];
    qDebug()<<" pointAmount = "<<pointAmount<<endl;
    pointsYmax = -1e100;
    pointsYmin = 1e100;
    switch (algo)
    {
    case GEN_LAGRANGE_INTER:
    {
        QPointF *basePoints = NULL;
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
            pointsYmax = qMax(pointsYmax,pointsY[i]);
            pointsYmin = qMin(pointsYmin,pointsY[i]);

        }
        qDebug()<<"*********"<<pointsYmax<<","<<pointsYmin;
    }
        break;
    default :
        return false;
    }
    return true;
}

bool CurveView::generateY(EGenAlgorithm algo, const QList<QPointF> &pointList, int lagrangeFactor)
{
    QPointF *points = new QPointF[pointList.size()];
    int i=0;
    for(QList<QPointF>::const_iterator iter=pointList.begin();iter!=pointList.end();++iter,++i)
    {
        points[i] = *iter;
    }
    return generateY(GEN_LAGRANGE_INTER,points,pointList.size(),lagrangeFactor);
}

void CurveView::readArray(const unsigned short *addr,int len)
{
    Q_ASSERT(len<=1000);
    for(int i=0;i<len;i++)
    {
        pointsY[i] = addr[i];
    }
}

void CurveView::draw()
{
    qDebug()<<"DRAW["<<this<<"]";
    int WIDTH=200;
    int HEIGHT=200;
    WIDTH=rect().width();
    HEIGHT=rect().height();
    double xFactor = WIDTH/1000.0 ;
    double yFactor = HEIGHT/(pointsYmax-pointsYmin);
    qDebug()<<"xFactor"<<xFactor<<",yFactor"<<yFactor;

    QRect rr = rect();
    rr.moveTop(HEIGHT-pointsYmax*yFactor);
    qDebug()<<"setSceneRect="<<rr<<",min:"<<pointsYmin<<",max:"<<pointsYmax;
    setSceneRect(rr);
    QPainterPath path;
    path.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
    m_pScene->clear();
    for(int i=1;i<1000;i+=1)
    {
//        qDebug()<<"line To :"<<i<<":"<<i*xFactor<<","<<HEIGHT-(pointsY[i]*yFactor)<<endl;
        path.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
        if(i%100 == 0)
        {
            myEllipseItem *item = new myEllipseItem(QPointF(i*xFactor,HEIGHT-(pointsY[i]*yFactor)));
            item->setData(0,QVariant::fromValue((void*)&pointsY[i]));
            m_pScene->addItem(item);
//            m_pScene->addItem(i*xFactor,HEIGHT-(pointsY[i]*yFactor),10,10);
        }
    }
    m_pScene->addPath(path);
    updateAxisVLayout(pointsYmin,pointsYmax);
}


void CurveView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event) ;
    draw();
}



void CurveView::updateAxisVLayout(double min,double max)
{
    double interval = (max-min)/5;
    for (int cc = axisVLayout->count()-1; cc >= 0; --cc)//4,3,2,1,0
       {
           QLayoutItem *it = axisVLayout->layout()->itemAt(cc);
           QLabel *label = qobject_cast<QLabel *>(it->widget());
           if (label != 0)
           {
               //doing something for orderHistory
               int prec = 2;
               if(max>100 || min < -100) prec=0;
               label->setText(QString::number(max - (cc+1)*interval,10,prec));
           }
       }
}


void CurveView::getData(QList<double> &data)
{
    data.clear();
    for(int i=0;i<1000;i++)
    {
        data.push_back(pointsY[i]);
    }
}

void CurveView::applyData(const QList<double> &data)
{
    pointsYmax = -1e10;
    pointsYmin = 1e10;
    for(int i=0;i<1000;i++)
    {
        pointsY[i] = data[i] ;
        pointsYmax = qMax(pointsYmax,pointsY[i]);
        pointsYmin = qMin(pointsYmin,pointsY[i]);
    }
    draw();
}


void CurveView::on_runButton_clicked()
{
    qDebug()<<"on_runButton_clicked()";
    reSimulate();
}


void CurveView::reSimulate()
{
    QList<QPointF> pointList;
    for(int i=0;i<1000;i+=100)
    {
        pointList.append(QPointF(i,pointsY[i]));
    }
    generateY(CurveView::GEN_LAGRANGE_INTER,pointList,1);
    draw();
}

void CurveView::on_myEllipse_ychanged()
{
    qDebug()<<"on_myEllipse_ychanged()";
}
