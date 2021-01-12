#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "actoritem.hh"
#include "city.hh"
#include "startdialog.hh"
#include "ui_startdialog.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QPushButton>
#include <QString>

const int X_SCALE = 349;
const int Y_SCALE = 553;

namespace Ui
{
class GameWindow;
}

namespace StudentSide
{
class City;

/**
 * @brief defines operations of the game window
 */
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief game window constructor
     * @param parent is pointing the parent class.
     * @param game_city is pointer of city class for building the game environment.
     */
    explicit GameWindow(QWidget *parent = nullptr, std::shared_ptr<City> game_city = nullptr);

    /**
     * @brief virtual destructor of game window
     */
    virtual ~GameWindow();

    /**
     * @brief add actor on the map.
     * @param locX where the actor will be drawn on x axis
     * @param locY where the actor will be drawn on y axis
     * @param type of the actor
     * @return
     */
    ActorItem* addActor(int locX, int locY, int type = 0);

    /**
     * @brief move item to another location on the map
     * @param item which will be moved.
     * @param locX where the item will be moved on x axis
     * @param locY where the item will be moved on y axis
     * @param type of movement
     */
    void moveActor(ActorItem* item, int locX, int locY);

    /**
     * @brief delete item from the map
     * @param item which will be removed.
     */
    void deleteActor(ActorItem* item);

    /**
     * \brief setPicture sets the background picture of the game
     * \param img A picture for the game backround
     * \return true if setting picture was succesful, false otherwise
     */
    bool setPicture(QImage &img);

    /**
     * @brief implementation when game is over
     */
    void gameOver(bool killed);

    /**
     * @brief updateScore update score number on the line edit
     * @param score is new score for updating
     * @param destroyed_buses is new destroyed buses for updating
     * @param destroyed_enemies is new destroyed enemes for updating
     */
    void updateScore(int score = 0, int destroyed_buses = 0, int destroyed_enemies = 0);

    /**
     * @brief updateAccuracy update accuracy, hit shots, and total shots number on line edit
     * @param accuracy is new accuracy for updating
     * @param hit_shots is new shots hit the bus for updating
     * @param tot_shots is new total number of shots for updating
     */
    void updateAccuracy(int accuracy = 0, int hit_shots = 0, int tot_shots = 0);

    /**
     * @brief checking the key press event
     * @param event of key pressing
     */
    void keyPressEvent(QKeyEvent* event) override;

    /**
     * @brief checks that the game was started from the start dialog
     * @return the game is started or not
     */
    bool isStarted();

private slots:
    /**
     * @brief display the how much time left for game at lcd number
     */
    void displayLeftTime();

private:
    /**
     * @brief read input time given by user
     * @param input_min what user chose.
     */
    void readInputTime(int input_min);

    Ui::GameWindow *ui = nullptr;
    QGraphicsScene *map = nullptr;
    QTimer *timer = nullptr;
    std::shared_ptr<City> game_city_ = nullptr;
    StartDialog* dialog_ = nullptr;

    int width_ = 1095; //pxls
    int height_ = 592;
    int total_time_ = 0; //s
    int spent_time_ = 0; //s
    int left_min_ = 0;
    int left_sec_ = 0;
    int score_ = 0;
    int accuracy_ = 0;
    int destroyed_buses_ = 0;
    int destroyed_enemies_ = 0;
    int hit_shots_ = 0;
    int tot_shots_ = 0;
    QString status_ = "";
};

} //namespace
#endif // GAMEWINDOW_HH

