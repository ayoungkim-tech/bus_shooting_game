#ifndef GAMECHARACTER_HH
#define GAMECHARACTER_HH

#include "interfaces/iactor.hh"
#include "core/location.hh"

namespace StudentSide
{

/**
 * \brief The GameCharacter class defines operations for the gamecharacter that user
 *  uses in the game.
 */
class GameCharacter : public Interface::IActor
{
public:
    /**
     * \brief GameCharacter constructor
     */
    GameCharacter();

    /**
     * \brief GameCharacter destructor
     */
    virtual ~GameCharacter();

    /**
     * \brief createCharacter creates game character with default location
     * \return Location object of the character
     */
    Interface::Location createCharacter();

    /**
     * \brief giveLocation returns the character's location
     * \return Location object of the character
     */
    Interface::Location giveLocation() const;

    /**
     * \brief move sets character a new location
     * \param loc Character's new location
     */
    void move(Interface::Location loc);

    /**
     * \brief isRemoved tells if the character is removed from the game
     * \return true if removed, false if not
     */
    bool isRemoved() const;

    /**
     * \brief remove sets the character as removed
     */
    void remove();

private:
    Interface::Location character_location_;

    int default_x_ = 200;
    int default_y_ = 200;

    bool removed_ = false;
};

}
#endif // GAMECHARACTER_HH
