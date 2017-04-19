#include "myellipseitem.h"
#include <QDebug>
#include <QGraphicsScene>

myEllipseItem::myEllipseItem(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

myEllipseItem::myEllipseItem(const QPointF &point, QGraphicsItem *parent) :
    QGraphicsEllipseItem(point.x()-5,point.y()-5,10,10,parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

myEllipseItem::myEllipseItem(qreal x, qreal y, QGraphicsItem *parent):
    QGraphicsEllipseItem(x-5,y-5,10,10,parent)
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
        QVariant var_xFactor = this->data(1);
        QVariant var_yFactor = this->data(2);
        QVariant var_HEIGHT = this->data(3);
        QVariant var_rry = this->data(4);
        QVariant var_max = this->data(5);
        if(var_pY.isValid())
        {
            void *pY = var_pY.value<void*>();
            double xFactor = var_xFactor.value<double>();
            double yFactor= var_yFactor.value<double>();
            int HEIGHT = var_HEIGHT.value<int>();
            double rr_y = var_rry.value<double>();
            double max = var_max.value<double>();

            //*(double*)pY = *(double*)pY+10;
            int x = rect.x();
            int y = ( rect.y()+pos().y()-rr_y);
            qDebug()<<"HEIGHT="<<HEIGHT<<",rect.y="<<rect.y()<<",y="<<pos().y();
            qDebug()<<"POS:["<<x/xFactor<<","<<max-y/yFactor<<"]";
            *(double*)pY = max-y/yFactor;
        }

        return value;
    }

    return QGraphicsItem::itemChange(change,value);
}
