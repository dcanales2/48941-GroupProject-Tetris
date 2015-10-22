#ifndef BLOCKSWINDOW_H
#define BLOCKSWINDOW_H




#include <QWidget>
#include <QFrame>

#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>

#include "blocksboard.h"

class BlocksWindow : public QWidget
{
    Q_OBJECT

public:
    BlocksWindow();


private:
    //QLabel constructor method
   QLabel *createLabel(const QString &text);

   //BlocksBoard instance manages game logic, controls, and display
   BlocksBoard *board;
   
   //label contains an image of the next piece
   QLabel *nextPieceLabel;

   //LCD label displays the score, level and lines removed
   QLCDNumber *scoreLcd;
   QLCDNumber *levelLcd;
   QLCDNumber *linesLcd;
   
   //command buttons
   QPushButton *startButton;
   QPushButton *quitButton;
   QPushButton *pauseButton;

   void resizeEvent(QResizeEvent*);
//   int heightForWidth(int) const;

};

#endif // BLOCKSWINDOW_H
