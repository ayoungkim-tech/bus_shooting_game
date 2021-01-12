#include "missile.hh"

#include <QDebug>
#include <random>

namespace StudentSide
{

Missile::Missile()
{

}

Missile::~Missile()
{

}

Interface::Location Missile::giveLocation() const
{
    return location_;
}

void Missile::move(Interface::Location loc)
{
    location_ = loc;
}

bool Missile::isRemoved() const
{
    return removed_;
}

void Missile::remove()
{
    removed_ = true;
}

Interface::Location Missile::createMissile()
{
    location_.setXY(START_X, START_Y);
    return location_;
}

void Missile::updatePosition(ActorItem* missile_item)
{
    if ( missile_item->x()> end_x_ && missile_item->y() > end_y_)
    {
        missile_item->setCoord(MIN_X, MIN_Y);
        getEndPostion();
        getStepSize();
    }
    else
    {
        missile_item->moveBy(step_x_, step_y_);
    }
}

int Missile::randomNumberGenerator(int min_val, int max_val)
{
    return (int) (rand() % (max_val - min_val + 1)) + min_val;
}

void Missile::getEndPostion()
{
    int axis_selection = randomNumberGenerator(0, 1);
    if (axis_selection == SELECT_X)
    {
        end_x_ = MAX_X;
        end_y_ = randomNumberGenerator(MIN_Y, MAX_Y);
    }
    else
    {
        end_x_ = randomNumberGenerator(MIN_X, MAX_X);
        end_y_ = MAX_Y;
    }
}

void Missile::getStepSize()
{
    step_x_ = (end_x_ - MIN_X) * 0.00002;
    step_y_ = (end_y_ - MIN_Y) * 0.00002;
}

} // namespace
