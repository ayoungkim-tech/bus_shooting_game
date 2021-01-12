#include "startdialog.hh"
#include "ui_startdialog.h"

#include <QMessageBox>

namespace StudentSide
{

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    ui->game_time->setValue(1);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::on_game_time_valueChanged(int input_min)
{
    game_time_ = input_min;
}

void StartDialog::accept()
{
    emit signal_send(game_time_);
    QDialog::accept();
}

} //namespace
