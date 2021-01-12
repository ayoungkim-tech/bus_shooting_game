#include "engine.hh"
#include "creategame.hh"

namespace StudentSide
{

Engine::Engine() :
    city_(new City),
    game_character_(new GameCharacter),
    window_(new GameWindow(nullptr, city_)),
    game_logic_(new CourseSide::Logic),
    statistics_(new Statistics),
    missile_(new Missile)
{
}

int Engine::start()
{
    try
    {
        if ( window_->isStarted() )
        {
            game_character_->createCharacter();
            missile_->createMissile();

            city_->initializeCity(window_, false, statistics_);
            city_->setBackground(basic_, big_);
            city_->addActor(game_character_);
            city_->addActor(missile_);
            city_->startGame();

            game_logic_->setTime(DEFAULT_HOUR, DEFAULT_MIN);
            game_logic_->takeCity(city_);
            game_logic_->fileConfig();
            game_logic_->finalizeGameStart();
            return GAME_STARTED;
        }
        return GAME_NOT_STARTED;
    }
    catch ( Interface::GameError const& error )
    {
        qDebug() << "Game error: " << error.giveMessage();
        return EXCEPTION;
    }
    catch ( Interface::InitError const& error)
    {
        qDebug() << "Initialization error: " << error.giveMessage();
        return EXCEPTION;
    }
}

}
