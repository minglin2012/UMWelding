#include "myellipseitem.h"
#include <QDebug>
#include <QGraphicsScene>

myEllipseItem::myEllipseItem(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

myEllipseItem::myEllipseItem(const QPointF &point, QGraphicsItem *parent) :
    QGraphicsEllipseItem(QRectF(point,QSize(10,10)),parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

myEllipseItem::myEllipseItem(qreal x, qreal y, QGraphicsItem *parent):
    QGraphicsEllipseItem(x,y,10,10,parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant myEllipseItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene())
    {
//        qDebug()<<"x="<<value.toPointF().x()<<",y="<<value.toPointF().y();
        return QPointF(pos().x(),value.toPointF().y());
    }
    else if(change == ItemPositionHasChanged && scene())
    {
        QPointF pointF = mapToScene(pos());
        QRectF rect = this->rect();

        QVariant var_pY = this->data(0);
        if(var_pY.isValid())
        {
            void *pY = var_pY.value<void*>();

            *(double*)pY = *(double*)pY+10;
//            scene()->getSceneRect();
            qDebug()<<"scene1="<<rect<<",pos="<<pos();
        }

        return value;
    }

    return QGraphicsItem::itemChange(change,value);
}
