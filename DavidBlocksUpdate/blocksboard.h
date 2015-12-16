#ifndef BLOCKSBOARD_H
#define BLOCKSBOARD_H

#include "blockspiece.h"

#include <QBasicTimer>
#include <QFrame>
#include <QLabel>
#include <QPointer>



class BlocksBoard: public QFrame
{
    Q_OBJECT

public:
    //default constructor
    BlocksBoard(QWidget *parent = 0);

    void setNextPieceLabel(QLabel *label);
    void setHoldPieceLabel(QLabel *label);
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimunSizeHint() const Q_DECL_OVERRIDE;

    //keep track of score
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;


    static Qt::Key getLeftButton();
    static void setLeftButton(const Qt::Key &key);

    static Qt::Key getRightButton();
    static void setRightButton(const Qt::Key &key);

    static Qt::Key getDownButton();
    static void setDownButton(const Qt::Key &key);

    static Qt::Key getDropButton();
    static void setDropButton(const Qt::Key &key);

    static Qt::Key getRotateCWButton();
    static void setRotateCWButton(const Qt::Key &key);

    static Qt::Key getRotateCCWButton();
    static void setRotateCCWButton(const Qt::Key &key);

    static Qt::Key getHoldButton();
    static void setHoldButton(const Qt::Key &key);

public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    //board array size enum constants
    enum {BoardWidth = 10, BoardHeight = 22};

    //game control methods
    BlockShape &shapeAt(int x, int y);
    int timeoutTime();
    int squareWidth();
    int squareHeight();
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const BlocksPiece &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, BlockShape shape);

    //hold piece function
    void changeCurrentPiece();
    //-----------------------


    //game variables
    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    QPointer<QLabel> holdPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    BlocksPiece curPiece;
    BlocksPiece nextPiece;
    //new---------------
    BlocksPiece holdPiece;
    bool held;
    //------------------
    int curX;
    int curY;
    //board array contains PieceShape enum value for each grid coordinate
    BlockShape board[BoardHeight * BoardWidth];

    static Qt::Key leftButton;
    static Qt::Key rightButton;
    static Qt::Key downButton;
    static Qt::Key dropButton;
    static Qt::Key rotateCWButton;
    static Qt::Key rotateCCWButton;
    static Qt::Key holdButton;


 };

#endif // BLOCKSBOARD_H
