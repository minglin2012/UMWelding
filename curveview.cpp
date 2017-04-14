#include "curveview.h"
#include <QGraphicsItem>
#include <cmath>
#include <QDebug>

CurveView::CurveView(QWidget *parent) :
    QGraphicsView(parent)
{

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

bool CurveView::generateY(EGenAlgorithm algo, QPoint  *points, int pointAmount, int lagrangeFactor)
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
void CurveView::draw()
{

    //    QPoint points[] = {QPoint(0,100),QPoint(100,200),QPoint(200,0),QPoint(300,80),QPoint(500,100),QPoint(600,50),QPoint(700,100),QPoint(800,0),QPoint(999,50)};
    //    QPoint points[] = {QPoint(1,50) };
    //    generateY(GEN_LAGRANGE_INTER,points,9,8);
    //    QPainterPath curvePath;
//        curvePath.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
//    for(int i=1;i<1000;i+=1)
//    {
//          cout<<"line To :"<<i<<":"<<i*xFactor<<","<<HEIGHT-(pointsY[i]*yFactor)<<endl;
//        curvePath.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
//    }
    int WIDTH=200;
    int HEIGHT=200;
    double xFactor = WIDTH/1000.0;
    double yFactor = 1.0;
    m_path.moveTo(0,HEIGHT-(pointsY[0]*yFactor));
        for(int i=1;i<1000;i+=1)
        {
            qDebug()<<"line To :"<<i<<":"<<i*xFactor<<","<<HEIGHT-(pointsY[i]*yFactor)<<endl;
            m_path.lineTo(int(i*xFactor),int(HEIGHT-(pointsY[i]*yFactor)));
        }
        m_pScene->addPath(m_path);
}

