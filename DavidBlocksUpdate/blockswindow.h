#ifndef BLOCKSWINDOW_H
#define BLOCKSWINDOW_H




#include <QWidget>
#include <QFrame>

#include <QLCDNumber>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QPixmap>
#include <QFont>
#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QThread>
#include "player.h"
#include <QInputDialog>
#include <QFile>


#include "blocksboard.h"
#include "control.h"

class BlocksWindow : public QWidget
{
    Q_OBJECT

public:
    BlocksWindow();

public slots:
    void controllsSetup();
    void newProfileDialog();
    void saveFileDialog();
    void loadFileDialog();

private:
    Player *player;
    QFileDialog *saveDialog;
    QPushButton *loadProfile;
    QPushButton *newProfile;
    QHBoxLayout *profileLayout;
    QWidget *profileWindow;
    QFile *file;
    QFile *file2;

    //label font
    QFont *font;

    //QLabel constructor method
   QLabel *createLabel(const QString &text);

   //username label
   QLabel *userLabel;

   //BlocksBoard instance manages game logic, controls, and display
   BlocksBoard *board;
   
   //label contains an image of the next piece
   QLabel *nextPieceLabel;

   //label contains the piece user wished to hold
   QLabel *holdPieceLabel;

   //background label
   QLabel *backGroundLabel;

   //LCD label displays the score, level and lines removed
   QLCDNumber *scoreLcd;
   QLCDNumber *levelLcd;
   QLCDNumber *linesLcd;
   
   //command buttons
   QPushButton *startButton;
   QPushButton *quitButton;
   QPushButton *pauseButton;

   QMenuBar * menuBar;
   QMenu * optionsMenu;
   QMenu * fileMenu;
   QAction * fileSubmenu[4];
   QAction * submenu[1];
   Control * control;



   void resizeEvent(QResizeEvent*);
//   int heightForWidth(int) const;

};

#endif // BLOCKSWINDOW_H
