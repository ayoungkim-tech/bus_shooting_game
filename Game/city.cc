#include "city.hh"
#include <QDebug>

namespace StudentSide
{

City::City()
{

}

City::~City()
{

}

void City::setBackground(QImage &basic_, QImage &big_)
{
    QImage background;
    if ( basic_backround_ == false )
    {
        background = big_;
    }
    else
    {
        background = basic_;
    }
    if ( window_->setPicture(background) == false )
    {
        throw Interface::InitError("Setting the background picture was unsuccesful or the picture was invalid");
    }
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    Interface::Location stop_location = stop->getLocation();
    if ( locationIsValid(stop_location) )
    {
        ActorItem* actor_item = window_->addActor(stop_location.giveX(),stop_location.giveY(), BUS_STOP);
        bus_stops_.insert({stop, actor_item});
    }
}

void City::startGame()
{
    window_->show();
}

void City::addActor(std::shared_ptr<Interface::IActor> new_actor)
{
    if ( game_actors_.find(new_actor) != game_actors_.end() )
    {
        throw Interface::GameError("Actor is already in the city");
    }
    ActorItem* actor_item = nullptr;
    Interface::Location actor_location = new_actor->giveLocation();
    if ( std::dynamic_pointer_cast<Interface::IVehicle>(new_actor) != nullptr )
    {
        actor_item = window_->addActor(actor_location.giveX(), actor_location.giveY(), BUS);
        game_actors_.insert({new_actor, actor_item});
    }
    else if ( std::dynamic_pointer_cast<GameCharacter>(new_actor) != nullptr)
    {
        actor_item = window_->addActor(actor_location.giveX(), actor_location.giveY(), CHARACTER);
        actor_location.setXY(actor_location.giveX() + SCALE, actor_location.giveY() - SCALE);
        new_actor->move(actor_location);
        character_item_ = actor_item;
        character_ = new_actor;
    }
    else if ( std::dynamic_pointer_cast<Missile>(new_actor) != nullptr )
    {
        actor_item = window_->addActor(actor_location.giveX(), actor_location.giveY(), MISSILE);
        missile_item_ = actor_item;
        missile_ = std::dynamic_pointer_cast<Missile>(new_actor);
    }
    else
    {   // passengers are not drawed to the gamewindow
        game_actors_.insert({new_actor, actor_item});
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if ( game_actors_.find(actor) != game_actors_.end() )
    {
        actor->remove();
        actorRemoved(actor);
        game_actors_.erase(actor);
    }
    else
    {
        throw Interface::GameError("Actor not found in the city");
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    ActorItem* actor_item = game_actors_.at(actor);
    window_->deleteActor(actor_item);
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    if ( game_actors_.find(actor) != game_actors_.end() )
    {
        return true;
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    if ( not game_over_ )
    {
        ActorItem* item = game_actors_.at(actor);
        Interface::Location new_location = actor->giveLocation();
        window_->moveActor(item, new_location.giveX(), new_location.giveY());
        if ( std::dynamic_pointer_cast<Interface::IVehicle>(actor) != nullptr )
        {
            std::shared_ptr<CourseSide::Nysse> bus = nullptr;
            bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
            item->updateBusPassengerNum(bus->getPassengers().size());
        }
        updateBusStops();
        updateMissilePosition();
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor> > nearby_actors = {};
    for ( auto& actor : game_actors_ )
    {
        if ( std::dynamic_pointer_cast<Interface::IVehicle>(actor.first) != nullptr )
        {
            Interface::Location location = actor.first->giveLocation();
            if ( location.isClose(loc, SHOT_RANGE) )
            {
                nearby_actors.push_back(actor.first);
            }
        }
    }
    return nearby_actors;
}

bool City::isGameOver() const
{
    return game_over_;
}

void City::initializeCity(std::shared_ptr<GameWindow> window, bool basic, std::shared_ptr<Statistics> statistics)
{
    window_ = window;
    basic_backround_ = basic;
    statistics_ = statistics;
    window_->addActor(TOWER_X, TOWER_Y, TOWER);
}

void City::executeUserCommand(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_D )
    {
        moveHorizontal(STEP);
    }
    if ( event->key() == Qt::Key_A )
    {
        moveHorizontal(-STEP);
    }
    if ( event->key() == Qt::Key_W )
    {
        moveVertical(-STEP);
    }
    if ( event->key() == Qt::Key_S )
    {
        moveVertical(STEP);
    }
    if ( event->key() == Qt::Key_L )
    {
        shoot();
    }
}

void City::moveVertical(qreal amount)
{
    Interface::Location loc = character_->giveLocation();
    qreal next_pos = character_item_->y() + amount;
    if ( next_pos < LIMIT_Y && next_pos > 0 )
    {
        character_item_->moveBy(0, amount);
        loc.setXY(loc.giveX(), loc.giveY() - amount);
        character_->move(loc);
    }
}

void City::moveHorizontal(qreal amount)
{
    Interface::Location loc = character_->giveLocation();
    qreal next_pos = character_item_->x() + amount;
    if ( next_pos < LIMIT_X && next_pos > 0 )
    {
        character_item_->moveBy(amount,0);
        loc.setXY(loc.giveX() + amount, loc.giveY());
        character_->move(loc);
    }
}

void City::missileHit()
{
    int missile_x = missile_item_->x() + MISSILE_HEAD_X;
    int missile_y = missile_item_->y() + MISSILE_HEAD_Y;
    int character_x = character_item_->x() + SCALE;
    int character_y = character_item_->y() + SCALE;
    if ( ( missile_x < character_x + RANGE && missile_x > character_x - RANGE )
         && ( missile_y < character_y + RANGE && missile_y > character_y - RANGE ) )
    {
        window_->gameOver(true);
        game_over_ = true;
    }
}

void City::updateBusStops()
{
    for ( auto stop : bus_stops_ )
    {
        stop.second->updateStopPassengerNum(stop.first->getPassengers().size());
    }
}

bool City::locationIsValid(Interface::Location loc)
{
    if ( loc.giveX() < CITY_EAST && loc.giveX() > CITY_WEST &&
         loc.giveY() < CITY_NORTH && loc.giveY() > CITY_SOUTH )
    {
        return true;
    }
    return false;
}

void City::updateMissilePosition()
{
    missile_->updatePosition(missile_item_);
    missileHit();
}

void City::shoot()
{
    Interface::Location loc = character_->giveLocation();
    int destroyed_buses = 0;
    int destroyed_enemies = 0;
    double hit_shots = statistics_->getHitShotNum();
    double total_shots = statistics_->shotFired();
    std::vector<std::shared_ptr<Interface::IActor>> actors = getNearbyActors(loc);

    if ( actors.size() != 0 )
    {
        hit_shots = statistics_->shotHit();
        for ( auto actor : actors )
        {
            destroyed_buses = statistics_->busDestroyed();
            std::shared_ptr<CourseSide::Nysse> bus = nullptr;
            bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
            destroyed_enemies = statistics_->enemyDestroyed(bus->getPassengers().size());
            bus->remove();
        }
        int score = statistics_->score();
        window_->updateScore(score, destroyed_buses, destroyed_enemies);
    }
    int accuracy = statistics_->accuracy();
    window_->updateAccuracy(accuracy, hit_shots, total_shots);
}

}
