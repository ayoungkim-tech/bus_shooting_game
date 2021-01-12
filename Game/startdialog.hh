#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

namespace Ui
{
class StartDialog;
}

namespace StudentSide
{

/**
 * @brief defines the dialog for the starting game.
 */
class StartDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief constructor of the dialog for starting game
     * @param parent points the parent class
     */
    explicit StartDialog(QWidget *parent = nullptr);

    /**
     * @brief destructor of the dialog for starting game
     */
    ~StartDialog();

signals:
    /**
     * @brief send the signal from dialog to game window
     */
    void signal_send(int);

private slots:
    /**
     * @brief game time value is choosed by user.
     * @param input_min given by the user.
     */
    void on_game_time_valueChanged(int input_min);

    /**
     * @brief when user press the game start button, then the signal is accepted.
     */
    void accept() override;

private:
    Ui::StartDialog *ui;
    int game_time_ = 1;
};

} //namespace
#endif // STARTDIALOG_HH
