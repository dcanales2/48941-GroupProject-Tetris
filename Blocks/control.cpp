#include "control.h"
#include "blocksboard.h"
#include <QDebug>

Control::Control(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    selected = none;

    dropButton = new QPushButton(QKeySequence(BlocksBoard::getDropButton()).toString() );
    QObject::connect(dropButton,SIGNAL(clicked()),this,SLOT(dropControl()));

    leftButton = new QPushButton(QKeySequence(BlocksBoard::getLeftButton()).toString() );
    QObject::connect(leftButton,SIGNAL(clicked()),this,SLOT(leftControl()));

    rightButton = new QPushButton(QKeySequence(BlocksBoard::getRightButton()).toString() );
    QObject::connect(rightButton,SIGNAL(clicked()),this,SLOT(rightControl()));

    rotateCCWButton = new QPushButton(QKeySequence(BlocksBoard::getRotateCCWButton()).toString() );
    QObject::connect(rotateCCWButton,SIGNAL(clicked()),this,SLOT(rotateControlCCW()));

    rotateCWButton = new QPushButton(QKeySequence(BlocksBoard::getRotateCWButton()).toString( ));
    QObject::connect(rotateCWButton,SIGNAL(clicked()),this,SLOT(rotateControlCW()));

    dropRowButton = new QPushButton(QKeySequence(BlocksBoard::getDownButton()).toString( ));
    QObject::connect(dropRowButton,SIGNAL(clicked()),this,SLOT(dropRowControl()));

    dropButtonLabel = new QLabel("DROP");
    dropRowButtonLabel = new QLabel("DOWN");
    leftButtonLabel = new QLabel("MOVE LEFT");
    rightButtonLabel = new QLabel("MOVE RIGHT");
    rotateCCWButtonLabel = new QLabel("ROTATE COUNTER CLOCKWISE");
    rotateCWButtonLabel = new QLabel("ROTATE CLOCKWISE");


    layout = new QGridLayout();
    vboxLayout1 = new QVBoxLayout();
    vboxLayout2 = new QVBoxLayout();

    vboxLayout1->addWidget(dropButton);
    vboxLayout1->addSpacing(50);
    vboxLayout1->addWidget(dropRowButton);
    vboxLayout1->addSpacing(50);
    vboxLayout1->addWidget(leftButton);
    vboxLayout1->addSpacing(50);
    vboxLayout1->addWidget(rightButton);
    vboxLayout1->addSpacing(50);
    vboxLayout1->addWidget(rotateCCWButton);
    vboxLayout1->addSpacing(50);
    vboxLayout1->addWidget(rotateCWButton);

    vboxLayout2->addWidget(dropButtonLabel);
    vboxLayout2->addSpacing(50);
    vboxLayout2->addWidget(dropRowButtonLabel);
    vboxLayout2->addSpacing(50);
    vboxLayout2->addWidget(leftButtonLabel);
    vboxLayout2->addSpacing(50);
    vboxLayout2->addWidget(rightButtonLabel);
    vboxLayout2->addSpacing(50);
    vboxLayout2->addWidget(rotateCCWButtonLabel);
    vboxLayout2->addSpacing(50);
    vboxLayout2->addWidget(rotateCWButtonLabel);

    layout->addLayout(vboxLayout2,0,0,1,1,0);
    layout->addLayout(vboxLayout1,0,1,1,1,0);


    setWindowTitle("Controller");
    setFixedSize(300,300);
    setLayout(layout);
    show();
}

void Control::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = static_cast<Qt::Key>(event->key());
    switch (selected)
    {
    case none:
        break;
    case moveLeft:

        BlocksBoard::setLeftButton(key);
        leftButton->setText(QKeySequence(BlocksBoard::getLeftButton()).toString());
        selected = none;
        leftButton->setEnabled(true);

        break;
    case moveRight:
        BlocksBoard::setRightButton(key);
        rightButton->setText(QKeySequence(BlocksBoard::getRightButton()).toString());
        selected = none;
        rightButton->setEnabled(true);

         break;
    case down:
        BlocksBoard::setDownButton(key);
        dropRowButton->setText(QKeySequence(BlocksBoard::getDownButton()).toString());
        selected = none;
        dropRowButton->setEnabled(true);

         break;
    case drop:
        BlocksBoard::setDropButton(key);
        dropButton->setText(QKeySequence(BlocksBoard::getDropButton()).toString());

        dropButton->setEnabled(true);
        selected = none;

         break;
    case ccw:
        BlocksBoard::setRotateCCWButton(key);
        rotateCCWButton->setText(QKeySequence(BlocksBoard::getRotateCCWButton()).toString());
        selected = none;
        rotateCCWButton->setEnabled(true);

         break;
    case cw:
        BlocksBoard::setRotateCWButton(key);
        rotateCWButton->setText(QKeySequence(BlocksBoard::getRotateCWButton()).toString());
        selected = none;
        rotateCWButton->setEnabled(true);

         break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Control::dropControl()
{
    if(selected == none)
    {
        dropButton->setEnabled(false);
        selected = drop;

    }
    this->setFocus();

}

void Control::dropRowControl()
{
    if(selected == none)
    {
        dropRowButton->setEnabled(false);
        selected = down;
    }
    this->setFocus();
}

void Control::leftControl()
{
    if(selected == none)
    {
        leftButton->setEnabled(false);
        selected = moveLeft;
    }
    this->setFocus();

}

void Control::rightControl()
{
    if(selected == none)
    {
        rightButton->setEnabled(false);
        selected = moveRight;
    }
    this->setFocus();
}

void Control::rotateControlCCW()
{
    if(selected == none)
    {
        rotateCCWButton->setEnabled(false);
        selected = ccw;
    }
    this->setFocus();
}

void Control::rotateControlCW()
{
    if(selected == none)
    {
        rotateCWButton->setEnabled(false);
        selected = cw;
    }
    this->setFocus();
}
