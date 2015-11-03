#include "frame.h"
#include <QtWidgets>
#include <iostream>

using namespace std;

Frame::Frame(QWidget *parent)
    :QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
}
