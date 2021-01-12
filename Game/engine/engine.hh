#ifndef ENGINE_HH
#define ENGINE_HH

#include "gamewindow.hh"
#include "core/logic.hh"
#include "city.hh"
#include "gamecharacter.hh"
#include "statistics.hh"
#include "missile.hh"

#include <QDebug>

const QString BACKROUND_SMALL = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
const QString BACKROUND_BIG = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";

const int DEFAULT_HOUR = 16;
const int DEFAULT_MIN = 0;

const int GAME_STARTED = 0;
const int GAME_NOT_STARTED = -1;
const int EXCEPTION = 1;

namespace StudentSide
{

/**
 * \brief The Engine class provides necessary resources for the game
 */
class Engine
{

public:
    /**
     * \brief Engine constructor
     */
    Engine();

    /**
     * \brief start calls methods to initialize game and catches exceptions
     * \return 0 if user started the game, -1 if user did not start the game, 1 if exception caught
     */
    int start();

private:

    std::shared_ptr<City> city_ = nullptr;
    std::shared_ptr<GameCharacter> game_character_ = nullptr;
    std::shared_ptr<GameWindow> window_ = nullptr;
    std::shared_ptr<CourseSide::Logic> game_logic_ = nullptr;
    std::shared_ptr<Statistics> statistics_ = nullptr;
    std::shared_ptr<Missile> missile_ = nullptr;

    QImage basic_ = QImage(BACKROUND_SMALL);
    QImage big_ = QImage(BACKROUND_BIG);
};

}
#endif // ENGINE_HH
