#ifndef ACTORITEM_HH
#define ACTORITEM_HH

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QtGlobal>

const int WIDTH = 130;
const int HEIGHT = 130;

namespace StudentSide
{
/**
 * @brief defines drawing and setting the actor item (= an object acting in the game).
 */
class ActorItem : public QGraphicsItem
{
public:
    /**
     * @brief actor item constructor
     * @param x axis of character.
     * @param y axis of character.
     * @param type of the character that is drawing.
     */
    ActorItem(int x, int y, int type = 0);

    /**
     * @brief virtual destructor of ActorItem.
     */
    virtual ~ActorItem();

    /**
     * @brief boundingRect for actor item to group the item.
     * @return rectangle boundry.
     */
    QRectF boundingRect() const;

    /**
     * @brief provide the actor item's painting implementation.
     * @param painter is used for paining implementation.
     * @param option provides style options for the actor item.
     * @param widget (optional) points to the widget that is being painted on.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief set coordinates of actor item.
     * @param x axis of actor item.
     * @param y axis of actor item.
     */
    void setCoord(int x, int y);

    /**
     * \brief updateBusPassengerNum updates the amount of passengers in the bus
     * \param amount The new amount of passengers
     */
    void updateBusPassengerNum(int amount);

    /**
     * \brief updateStopPassengerNum updates the amount of passengers in the bus stop
     * \param amount The new amount of passengers
     */
    void updateStopPassengerNum(int amount);

private:
    int x_;
    int y_;
    int type_;
    int passenger_num_ = 0;
    int waiting_passenger_num_ = 0;
};

}

#endif // ACTORITEM_HH
