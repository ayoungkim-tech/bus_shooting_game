#include <QApplication>
#include "engine/engine.hh"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    StudentSide::Engine e;
    int game_status = e.start();

    if ( game_status == GAME_STARTED )
    {
        return a.exec();

    }
    else if ( game_status == GAME_NOT_STARTED )
    {
        return 0;
    }
    else
    {
        return 1; // exception occurred
    }
}


