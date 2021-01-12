#include "statistics.hh"
#include <cmath>
#include <QDebug>

namespace StudentSide
{

Statistics::Statistics()
{
}

int Statistics::score()
{
    score_ = destroyed_buses_ * 3 + destroyed_enemies_;
    return score_;
}

int Statistics::accuracy()
{
    accuracy_ = (int) round(hit_shots_ / total_shots_ * 100);
    return accuracy_;
}

int Statistics::shotFired()
{
    total_shots_++;
    return total_shots_;
}

double Statistics::shotHit()
{
    hit_shots_++;
    return hit_shots_;
}

double Statistics::getHitShotNum()
{
    return hit_shots_;
}

int Statistics::busDestroyed()
{
    destroyed_buses_++;
    return destroyed_buses_;
}

int Statistics::enemyDestroyed(int enemy_num)
{
    destroyed_enemies_ += enemy_num;
    return destroyed_enemies_;
}

} //namespace
