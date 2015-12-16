#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    linesRemoved = 0;
    score = 0;
    level = 1;
    userName = "";
}

