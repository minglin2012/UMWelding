#ifndef CURVEVIEW_H
#define CURVEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>

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
        GEN_LAGRANGE_INTER //已知n+1个互异点的函数值，唯一确定一个n次多项式，作为插值多项式。实际中使用lagrange插值法。

    };
    explicit CurveView(QWidget *parent = 0);
    void addPoint(const QPoint &);
    void addPoint(int x, int y);
    void addPoints(const QPoint*,int amount);
    void addPoints(const QList<QPoint> &);
    bool generateY(EGenAlgorithm algo, double *param, int paramAmount);
    bool generateY(EGenAlgorithm algo, QPoint  *points,int pointAmount, int lagrangeFactor=1);
    void draw();
signals:

public slots:
private:
    QGraphicsScene *m_pScene;
    QPainterPath m_path;
    int pointsY[1000];

};

#endif // CURVEVIEW_H
