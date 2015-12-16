#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    int linesRemoved;
    int score;
    int level;
    QString userName;

    explicit Player(QObject *parent = 0);

signals:

public slots:
};

#endif // PLAYER_H
