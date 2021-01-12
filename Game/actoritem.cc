#include "actoritem.hh"

namespace StudentSide
{
ActorItem::ActorItem(int x, int y, int type):x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_ ));
}

ActorItem::~ActorItem()
{

}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (type_ == 1) // Bus stop drawing
    {
        painter->setBrush(Qt::black);
        painter->drawRect(7, 8, 4, 20); // stick
        painter->setBrush(Qt::blue);
        painter->drawEllipse(0, 0, 17, 17); // number board
        painter->setPen(Qt::white);
        QString str_waiting_passenger_num = QString::number(waiting_passenger_num_);
        painter->drawText(4, 13, str_waiting_passenger_num); // display waiting_passenger_num_ (4,12)
    }

    if (type_ == 2) // Bus drawing
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::yellow);
        painter->drawRect(0, 0, 30, 15); // body
        painter->setBrush(Qt::white);
        painter->drawRect(0, 0, 8, 6); // window
        painter->setBrush(Qt::black);
        painter->drawEllipse(4, 13, 8, 8); // left wheel
        painter->drawEllipse(17, 13, 8, 8); // right wheel
        painter->setPen(Qt::black);
        QString str_passenger_num = QString::number(passenger_num_);
        painter->drawText(15, 13, str_passenger_num); // display passenger_num_
        painter->setBrush(Qt::black);
        painter->drawEllipse(1, 1, 1, 1); //left eye
        painter->drawEllipse(5, 1, 1, 1); //right eye
        painter->drawRect(2, 3, 3, 1); // driver mouth
    }

    if (type_ == 3) // Tower drawing
    {
        painter->setBrush(Qt::red);
        painter->drawRect(10, 0, 3, 14); // tower pin
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);
        static const QPointF points[4] =
        {
            QPointF(0, 14),
            QPointF(24, 14),
            QPointF(4, 22),
            QPointF(20, 22)
        };
        painter->drawPolygon(points, 4); // middle
        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);
        painter->drawRect(7, 22, 9, 55); // tower body
    }

    if (type_ == 4) // Shooting target drawing
    {
        painter->setPen(Qt::red);
        painter->drawEllipse(50, 50, 30, 30); // outer circle
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);
        painter->drawEllipse(63, 63, 5, 5); // inner circle
        painter->drawRect(63, 0, 5, 50); // north line
        painter->drawRect(0, 63, 50, 5); // east line
        painter->drawRect(80, 63, 50, 5); // west line
        painter->drawRect(63, 80, 5, 50); // south line
    }

    if (type_ == 5) // missile drawing
    {
        painter->setBrush(Qt::black);
        static const QPointF l_wing[3] =
        {
            QPointF(10, 0),
            QPointF(10, 7),
            QPointF(25, 7)
        };
        painter->drawPolygon(l_wing, 3); // left wing
        painter->setBrush(Qt::red);
        painter->drawRect(10, 7, 40, 15); // body
        // fire
        painter->setBrush(Qt::yellow);
        static const QPointF u_fire[3] =
        {
            QPointF(0, 9),
            QPointF(10, 7),
            QPointF(10, 13)
        };
        painter->drawPolygon(u_fire, 3); // upper fire
        static const QPointF m_fire[3] =
        {
            QPointF(0, 15),
            QPointF(10, 13),
            QPointF(10, 18)
        };
        painter->drawPolygon(m_fire, 3); // middle fire
        static const QPointF l_fire[3] =
        {
            QPointF(0, 20),
            QPointF(10, 18),
            QPointF(10, 23)
        };
        painter->drawPolygon(l_fire, 3); // lower fire
        painter->setBrush(Qt::black);
        static const QPointF r_wing[3] =
        {
            QPointF(10, 23),
            QPointF(10, 30),
            QPointF(25, 23)
        };
        painter->drawPolygon(r_wing, 3); // right wing
        static const QPointF head[3] =
        {
            QPointF(50, 7),
            QPointF(65, 14),
            QPointF(50, 23)
        };
        painter->drawPolygon(head, 3); // head
    }
}

void ActorItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

void ActorItem::updateBusPassengerNum(int amount)
{
    passenger_num_ = amount;
}

void ActorItem::updateStopPassengerNum(int amount)
{
    waiting_passenger_num_ = amount;
}

} //namespace
