#ifndef CONTROL_H
#define CONTROL_H

#include "QTextStream"
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QString>
#include <iostream>
#include <QFrame>
#include <QKeyEvent>

using namespace std;

enum buttonSelect{none,moveLeft,moveRight,down,drop,ccw,cw,hold};

class Control : public QWidget
{
    Q_OBJECT
public:
    explicit Control(QWidget *parent = 0);
    QGridLayout *layout;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;

    QPushButton *dropButton;
    QPushButton *dropRowButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *rotateCCWButton;
    QPushButton *rotateCWButton;
    QPushButton *holdButton;

    QLabel *dropButtonLabel;
    QLabel *dropRowButtonLabel;
    QLabel *leftButtonLabel;
    QLabel *rightButtonLabel;
    QLabel *rotateCCWButtonLabel;
    QLabel *rotateCWButtonLabel;
    QLabel *holdButtonLabel;


    bool settingDown;
    bool settingDropRow;
    bool settingLeft;
    bool settingRight;
    bool settingCCW;
    bool settingCW;
    bool settingHold;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    signals:

private:
    buttonSelect selected;

public slots:
    void dropControl();
    void dropRowControl();
    void leftControl();
    void rightControl();
    void rotateControlCCW();
    void rotateControlCW();
    void holdControl();

};

#endif // CONTROL_H
