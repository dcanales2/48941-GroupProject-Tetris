#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent) : QMainWindow(parent)
{
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap("c:/Qt/pic.png"));

    QLabel *label2 = new QLabel();
    label2->setPixmap(QPixmap("c:/Qt/pic.png"));

    QPropertyAnimation *animation = new QPropertyAnimation(label,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(0,0,100,60));
    animation->setEndValue(QRect(0,250,100,60));

    QPropertyAnimation *animation2 = new QPropertyAnimation(label2,"geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(QRect(0,0,100,60));
    animation2->setEndValue(QRect(0,250,100,60));


    QRect *rect = new QRect();
    rect->setRect(0,0,200,200);

    this->layout()->setGeometry(*rect);
    this->layout()->setMargin(1);

    this->layout()->addWidget(label);
    this->layout()->addWidget(label2);


    setFixedSize(600,600);

    animation->start();
    animation2->start();
    show();

}

