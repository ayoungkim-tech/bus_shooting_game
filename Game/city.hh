#ifndef CITY_HH
#define CITY_HH

#include "gamewindow.hh"
#include "interfaces/icity.hh"
#include "gamecharacter.hh"
#include "statistics.hh"
#include "actors/nysse.hh"
#include "missile.hh"
#include "errors/initerror.hh"
#include "errors/gameerror.hh"

#include <QTime>
#include <QKeyEvent>
#include <unordered_map>

const int BUS_STOP = 1;
const int BUS = 2;
const int TOWER = 3;
const int CHARACTER = 4;
const int MISSILE = 5;

const int RANGE = 12;
const int SCALE = 65;
const int SHOT_RANGE = 7;

const int MISSILE_HEAD_X = 65;
const int MISSILE_HEAD_Y = 14;

const int TOWER_X = -110;
const int TOWER_Y = 550;

const qreal STEP = 5;
const qreal LIMIT_X = 963;
const qreal LIMIT_Y = 373;

const int CITY_NORTH = 550;
const int CITY_SOUTH = 85;
const int CITY_WEST = -350;
const int CITY_EAST = 700;

namespace StudentSide
{
class GameWindow;

/**
 * @brief City class contains operations for handling game characters in the game.
 */
class City : public Interface::ICity
{
public:
    /**
     * \brief City constructor
     */
    City();

    /** @copydoc Interface::ICity::setBackround(QImage& basicbackground,QImage& bigbackground)
     */
    void setBackground(QImage& basic_, QImage& big_);

    /** @copydoc Interface::ICity::setClock(QTime clock)
     */
    void setClock(QTime clock);

    /** @copydoc Interface::ICity::addStop(std::shared_ptr<IStop> stop)
     */
    void addStop(std::shared_ptr<Interface::IStop> stop);

    /** @copydoc Interface::ICity::startGame()
     */
    void startGame();

    /** @copydoc Interface::ICity::addActor(std::shared_ptr<IActor> newactor)
     */
    void addActor(std::shared_ptr<Interface::IActor> newactor);

    /** @copydoc Interface::ICity::removeActor(std::shared_ptr<IActor> actor)
     */
    void removeActor(std::shared_ptr<Interface::IActor> actor);

    /** @copydoc Interface::ICity::actorRemoved(std::shared_ptr<IActor> actor)
     */
    void actorRemoved(std::shared_ptr<Interface::IActor> actor);

    /** @copydoc Interface::ICity::findActor(std::shared_ptr<IActor> actor) const
     */
    bool findActor(std::shared_ptr<Interface::IActor> actor) const;

    /** @copydoc Interface::ICity::actorMoved(std::shared_ptr<IActor> actor)
     */
    void actorMoved(std::shared_ptr<Interface::IActor> actor);

    /** @copydoc Interface::ICity::getNearbyActors(Location loc) const
     */
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const;

    /** @copydoc Interface::ICity::isGameOver() const
     */
    bool isGameOver() const;

    /**
     * \brief initializeCity gets the initialization information for the city.
     * \param window A pointer to a gamewindow used in the game
     * \param basic Game's background type
     * \param statistics A pointer to city's statistics class
     */
    void initializeCity(std::shared_ptr<GameWindow> window, bool basic, std::shared_ptr<Statistics> statistics);

    /**
     * \brief executeUserCommand executes the command that user wants
     * \param event A pointer that contains information of pressed key on the keyboard.
     */
    void executeUserCommand(QKeyEvent* event);

    /**
     * \brief City destructor
     */
    virtual ~City();

private:

    /**
     * \brief moveVertical moves game character in vertical direction in the gamewindow
     * \param amount The amount of movement
     */
    void moveVertical(qreal amount);

    /**
     * \brief moveHorizontal moves game character in horizontal direction in the gamewindow
     * \param amount The amount of movement
     */
    void moveHorizontal(qreal amount);

    /**
     * \brief missileHit checks if the missile hits the game character
     */
    void missileHit();

    /**
     * \brief updateBusStops Updates the amount of passengers in the bus stop
     */
    void updateBusStops();

    /**
     * \brief locationIsValid Checks whether the given location is valid
     * \param loc A Location whose position is checked
     * \return True if valid, false otherwise
     */
    bool locationIsValid(Interface::Location loc);

    /**
     * \brief updateMissilePosition updates the missile position on the screen
     */
    void updateMissilePosition();

    /**
     * \brief shoot executes operations when user shoots the gun
     */
    void shoot();

    QTime clock_;

    bool basic_backround_ = false;
    bool game_over_ = false;

    std::unordered_map<std::shared_ptr<Interface::IStop>, ActorItem*> bus_stops_;
    std::unordered_map<std::shared_ptr<Interface::IActor>, ActorItem*> game_actors_;

    ActorItem* missile_item_ = nullptr;
    ActorItem* character_item_ = nullptr;

    std::shared_ptr<GameWindow> window_ = nullptr;
    std::shared_ptr<Interface::IActor> character_ = nullptr;
    std::shared_ptr<Statistics> statistics_ = nullptr;
    std::shared_ptr<Missile> missile_ = nullptr;
};

}
#endif // CITY_HH
