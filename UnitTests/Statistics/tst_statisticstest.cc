#include "statistics.hh"
#include "gamewindow.hh"
#include "actoritem.hh"
#include "city.hh"
#include "engine/engine.hh"
#include <QtTest>
#include <QString>
#include <QKeyEvent>
#include <QString>

class Statisticstest : public QObject
{
    Q_OBJECT

public:
    Statisticstest();
    ~Statisticstest();

private slots:

    void accuracyTest();
    void accuracyTest_data();

    void scoreTest();
    void scoreTest_data();
};

Statisticstest::Statisticstest()
{

}

Statisticstest::~Statisticstest()
{

}

void Statisticstest::accuracyTest()
{
    QFETCH(double, total_shots);
    QFETCH(double, hit_shots);
    QFETCH(int, accuracy);

    StudentSide::Statistics statistics;
    for ( int i = 0; i < total_shots; ++i )
    {
        statistics.shotFired();
    }
    for ( int i = 0; i < hit_shots; ++i )
    {
        statistics.shotHit();
    }
    QVERIFY2(statistics.accuracy() == accuracy, "Error, accuracy value wrong");
}

void Statisticstest::accuracyTest_data()
{
    QTest::addColumn<double>("total_shots");
    QTest::addColumn<double>("hit_shots");
    QTest::addColumn<int>("accuracy");

    QTest::newRow("100% accuracy") << 7.0 << 7.0 << 100;
    QTest::newRow("50% accuracy") << 20.0 << 10.0 << 50;
    QTest::newRow("0% accuracy") << 10.0 << 0.0 << 0;
}

void Statisticstest::scoreTest()
{
    QFETCH(int, destroyed_buses);
    QFETCH(int, destroyed_enemies);
    QFETCH(int, score);

    StudentSide::Statistics statistics;
    for ( int i = 0; i < destroyed_buses; ++i )
    {
        statistics.busDestroyed();
    }
    statistics.enemyDestroyed(destroyed_enemies);

    QVERIFY2(statistics.score() == score, "Error, score value wrong");
}

void Statisticstest::scoreTest_data()
{
    QTest::addColumn<int>("destroyed_buses");
    QTest::addColumn<int>("destroyed_enemies");
    QTest::addColumn<int>("score");

    QTest::newRow("High score") << 50 << 240 << 390;
    QTest::newRow("Small score") << 10 << 60 << 90;
    QTest::newRow("Zero score") << 0 << 0 << 0;
}


QTEST_APPLESS_MAIN(Statisticstest)

#include "tst_statisticstest.moc"


