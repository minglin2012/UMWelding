#ifndef MYELLIPSEITEM_H
#define MYELLIPSEITEM_H

#include <QGraphicsEllipseItem>

class myEllipseItem : public QGraphicsEllipseItem
{
//    Q_OBJECT
public:
    explicit myEllipseItem(QGraphicsItem *parent = 0);
    explicit myEllipseItem(const QPointF &rect, QGraphicsItem *parent = 0);
    explicit myEllipseItem(qreal x, qreal y, QGraphicsItem *parent = 0);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
signals:

public slots:

};

#endif // MYELLIPSEITEM_H
