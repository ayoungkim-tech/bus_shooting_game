#ifndef MISSILE_HH
#define MISSILE_HH

#include "interfaces/iactor.hh"
#include "core/location.hh"
#include "actoritem.hh"

const int START_X = -110;
const int START_Y = 550;
const int MAX_X = 1300;
const int MIN_X = 240;
const int MAX_Y = 450;
const int MIN_Y = 5;
const int SELECT_X = 0;
const int SELECT_Y = 1;

namespace StudentSide
{

/**
 * @brief TowerItem class contains operations for handling tower item (missile) in the game.
 */
class Missile : public Interface::IActor
{
public:
    /**
     * @brief constructor of TowerItem
     */
    Missile();

    /**
     * \brief TowerItem destructor
     */
    virtual ~Missile();

    /**
     * \brief giveLocation returns the tower's location
     * \return Location object of the tower
     */
    Interface::Location giveLocation() const;

    /**
     * \brief move tower to new location
     * \param loc tower's new location
     */
    void move(Interface::Location loc);

    /**
     * \brief isRemoved tells if the tower is removed from the game
     * \return true if removed, false if not
     */
    bool isRemoved() const;

    /**
     * \brief remove the tower as removed
     */
    void remove();

    /**
     * \brief createTowerItem creates tower with default location
     * \return Location object of the tower
     */
    Interface::Location createMissile();

    /**
     * @brief updatePosition is updataing missile position
     * @param missile_item
     */
    void updatePosition(ActorItem* missile_item);

private:
    /**
     * @brief randomNumberGenerator returns random number in the range
     * @param min_val for random number
     * @param max_val for random number
     * @return return the random number between min and max value
     */
    int randomNumberGenerator(int min_val, int max_val);

    /**
     * @brief getEndPostion gets the end position of the missile randomly
     */
    void getEndPostion();

    /**
     * @brief getStepSize calculates what is the step size in x axis and y axis
     */
    void getStepSize();

    Interface::Location location_;

    bool removed_ = false;

    double step_x_ = 0.05;
    double step_y_ = 0.05;
    int end_x_ = 700;
    int end_y_ = 450;
};

} //namespace
#endif // TOWERITEM_HH
