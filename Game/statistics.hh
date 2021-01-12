#ifndef STATISTICS_HH
#define STATISTICS_HH

namespace StudentSide
{
/**
 * @brief Statistics class contains operations for handling statistics data.
 */
class Statistics
{
public:
    /**
     * @brief constructor of Statistics
     * @param window is pointer of the game window.
     */
    Statistics();

    /**
     * @brief score new score is calculated and updated at game window.
     * @return new score value
     */
    int score();

    /**
     * @brief accuracy new accuracy is calculated and updated at game window.
     * @return new accuracy value
     */
    int accuracy();

    /**
     * @brief shotFired counts how many shot is fired.
     * @return number of shot fired
     */
    int shotFired();

    /**
     * @brief shotHit counts how many shot is hit the bus.
     * @return number of shot hit the bus
     */
    double shotHit();

    /**
     * @brief getHitShotNum gets how many times shot hits the buses until now
     * @return the current number of shots hit the bus
     */
    double getHitShotNum();

    /**
     * @brief busDestroyed counts how many buses are destroyed.
     * @return number of destroyed buses
     */
    int busDestroyed();

    /**
     * @brief enemyDestroyed counts how many enemies are destroyed.
     * @param enemy_num killed by the lastest shot.
     * @return number of destroyed enemies
     */
    int enemyDestroyed(int enemy_num);

private:
    int score_ = 0;
    int accuracy_ = 0; //%
    int destroyed_buses_ = 0;
    int destroyed_enemies_ = 0;
    double total_shots_ = 0;
    double hit_shots_ = 0;
};

} //namespace
#endif // STATISTICS_HH
