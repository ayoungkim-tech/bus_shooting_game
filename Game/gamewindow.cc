#include "gamewindow.hh"
#include "ui_gamewindow.h"
#include "startdialog.hh"
#include "ui_startdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QKeyEvent>

const int PADDING = 40;
const int SIZE_SCALE = 3;

namespace StudentSide
{

GameWindow::GameWindow(QWidget *parent, std::shared_ptr<City> game_city) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    game_city_(game_city)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_+SIZE_SCALE, height_+SIZE_SCALE);
    ui->centralwidget->setFixedSize(width_ + 4 * PADDING, height_ + PADDING);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    resize(minimumSizeHint());

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayLeftTime()));

    dialog_ = new StartDialog;
    connect(dialog_, &StartDialog::signal_send, this, &GameWindow::readInputTime);
    dialog_->exec();
    timer->start(1000);

    ui->score->setText(QString::number(0));
    ui->score->setReadOnly(true);
    ui->accuracy->setText(QString::number(0));
    ui->accuracy->setReadOnly(true);
    ui->buses->setText(QString::number(0));
    ui->buses->setReadOnly(true);
    ui->enemies->setText(QString::number(0));
    ui->enemies->setReadOnly(true);
    ui->hit_shots->setText(QString::number(0));
    ui->hit_shots->setReadOnly(true);
    ui->tot_shots->setText(QString::number(0));
    ui->tot_shots->setReadOnly(true);
}

GameWindow::~GameWindow()
{
    delete ui;
}

ActorItem* GameWindow::addActor(int locX, int locY, int type)
{
    ActorItem* n_actor = new ActorItem(X_SCALE + locX, Y_SCALE - locY, type);
    if ( type == CHARACTER || type == MISSILE )
    {
        n_actor->setZValue(1); // used to keep on top of other items
    }
    map->addItem(n_actor);
    return n_actor;
}

void GameWindow::moveActor(ActorItem* item, int locX, int locY)
{
    if ( item != nullptr)
    {
        item->setCoord( X_SCALE + locX, Y_SCALE - locY);
    }
}

void GameWindow::deleteActor(ActorItem* item)
{
    if ( item != nullptr )
    {
        map->removeItem(item);
        delete item;
    }
}

bool GameWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
    if ( map->backgroundBrush() == Qt::NoBrush )
    {
        return false;
    }
    return true;
}

void GameWindow::displayLeftTime()
{
    ++spent_time_;
    int left_time = total_time_ - spent_time_;
    left_min_ =  left_time / 60;
    left_sec_ =  left_time % 60;
    ui->left_m->display(left_min_);
    ui->left_s->display(left_sec_);

    if (left_min_ == 0 && left_sec_ == 0)
    {
        gameOver(false);
    }
}

void GameWindow::gameOver(bool killed)
{
    timer->stop();
    QMessageBox msgBox;
    if (killed)
    {
        status_ = QString("GAME OVER :( \n You were killed by the enemy.");
    }
    else
    {
        status_ = QString("GAME OVER :) Times up! \n Your score is %1. \n Your accuracy is %2%. ").arg(score_).arg(accuracy_);
    }
    QMessageBox::information(this, tr("Info"), status_);
    this->close();
}

void GameWindow::updateScore(int score, int destroyed_buses, int destroyed_enemies)
{
    score_ = score;
    ui->score->setText(QString::number(score_));
    destroyed_buses_ = destroyed_buses;
    ui->buses->setText(QString::number(destroyed_buses_));
    destroyed_enemies_ = destroyed_enemies;
    ui->enemies->setText(QString::number(destroyed_enemies_));

}

void GameWindow::updateAccuracy(int accuracy, int hit_shots, int tot_shots)
{
    accuracy_ = accuracy;
    ui->accuracy->setText(QString::number((accuracy)));
    hit_shots_ = hit_shots;
    ui->hit_shots->setText(QString::number(hit_shots_));
    tot_shots_ = tot_shots;
    ui->tot_shots->setText(QString::number(tot_shots_));
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    game_city_->executeUserCommand(event);
}

bool GameWindow::isStarted()
{
    if ( dialog_->result() == 0 )
    {
        return false;
    }
    return true;
}

void GameWindow::readInputTime(int input_min)
{
    ui->left_m->display(input_min);
    total_time_ = input_min * 60; //s
}
} //namespace

