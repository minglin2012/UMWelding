#ifndef CURVEVIEW_H
#define CURVEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QGridLayout>

class CurveView : public QGraphicsView
{
    Q_OBJECT
public:
public:
    enum EGenAlgorithm
    {
        GEN_POLYNOMINAL,//y = a0+a1*x+a2*x^2+a3*x^3+...+an*x^n
        GEN_POWER,//y = x^a
        GEN_EXP,//y = a^x
        GEN_LOG,//y = log_a(x)
        GEN_SIN,//y = a0(sin(a1*x+a2)
        GEN_LAGRANGE_INTER, //已知n+1个互异点的函数值，唯一确定一个n次多项式，作为插值多项式。实际中使用lagrange插值法。
        GEN_BINOMIAL_DISTRIBUTION,   //二项分布，n次独立随机实验，每次事件发生的概率为P，则事件发生K次的样本子集数量。A(ξ=K) = C(n, k) = n!/(k! * (n-k)!)
        GEN_POISSON_DISTRIBUTION,
        GEN_NORMAL_DISTRIBUTION,
        GEN_RANDOM  //随机数,平均值为param[0],最大偏差为 param[1]

    };
    explicit CurveView(QWidget *parent = 0);
    void addPoint(const QPoint &);
    void addPoint(int x, int y);
    void addPoints(const QPoint*,int amount);
    void addPoints(const QList<QPoint> &);
    void readArray(const unsigned short *addr,int len=1000);
    bool generateY(EGenAlgorithm algo, double *param, int paramAmount);
    bool generateY(EGenAlgorithm algo, QPointF  *points,int pointAmount, int lagrangeFactor=1);
    bool generateY(EGenAlgorithm algo, const QList<QPointF> &points, int lagrangeFactor=1);

    void getData(QList<double> &data);
    void applyData(const QList<double> &data);

    void draw();
    void resizeEvent(QResizeEvent *event);
    QGridLayout* getLayout(){return viewLayout;}
    void updateAxisVLayout(double min,double max);
signals:

public slots:
private:
    QGraphicsScene *m_pScene;
    QPainterPath m_path;
    double pointsY[1000];
    double pointsYmax;
    double pointsYmin;
    QSize viewSize;
    QGridLayout *viewLayout;
    QHBoxLayout *axisHLayout;
    QVBoxLayout *axisVLayout;

};

#endif // CURVEVIEW_H
