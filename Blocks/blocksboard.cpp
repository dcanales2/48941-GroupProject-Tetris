#include "blocksboard.h"
#include <QtGui>
#include <iostream>

using namespace std;

Qt::Key BlocksBoard::leftButton = Qt::Key_A;
Qt::Key BlocksBoard::rightButton = Qt::Key_D;
Qt::Key BlocksBoard::downButton = Qt::Key_S;
Qt::Key BlocksBoard::dropButton = Qt::Key_Space;
Qt::Key BlocksBoard::rotateCWButton = Qt::Key_K;
Qt::Key BlocksBoard::rotateCCWButton = Qt::Key_J;

/*******************************************************************************
 * Default constructor. Config widget and initialize gamestate. Inherits QFrame
 * @param parent widget
 ******************************************************************************/
BlocksBoard::BlocksBoard(QWidget *parent)
    :QFrame(parent)
{

    setFrameStyle(QFrame::Panel | QFrame::Sunken);//sunken panel style
    //StrongFocus ensures this widget gets Keyboard input
    setFocusPolicy(Qt::StrongFocus);



    //init gamestates
    isStarted = false;
    isPaused = false;
    clearBoard();

    //set nextPiece
    nextPiece.setRandomShape();
    curX = 0;
    curY = BoardHeight;
}

/*******************************************************************************
 * assign nexPieceLabel with constructed label
 * @param label for nextPiece
 ******************************************************************************/
void BlocksBoard::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}


/*******************************************************************************
 * Provice size hints based on play area
 * @return propritional size hint
*******************************************************************************/
QSize BlocksBoard::sizeHint() const
{
    return QSize(BoardWidth * 15 + frameWidth() *2,
                 BoardHeight * 15 + frameWidth()*2 );

}

/*******************************************************************************
 * Provice minimum size hints based on play area
 * @return propritional minimum size hint
*******************************************************************************/
QSize BlocksBoard::minimunSizeHint() const
{
    return QSize (BoardWidth * 5 + frameWidth() * 2,
                  BoardHeight * 5 + frameWidth() *2);

}


/*******************************************************************************
 * Reset gameState, clear board and start game
*******************************************************************************/
void BlocksBoard::start()
{
    if(isPaused){//do nothing if game is paused
        return;
    }

    isStarted = true;//set started to true
    isWaitingAfterLine = false;//set waiting to false

    //reset score values and clear board
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    clearBoard();

    //emit signals
    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    //create new piece
    newPiece();

    //start timer
    timer.start(timeoutTime(), this);

}

/*******************************************************************************
 * pause or unpause the game
*******************************************************************************/
void BlocksBoard::pause()
{
    //do nothing if game hasn't started yet
    if(!isStarted){
        return;
    }

    //inverse pause status (True to false: False to True)
    isPaused = !isPaused;


    if(isPaused){
        timer.stop();//stop timer if paused
    }else{
        timer.start(timeoutTime(), this);//continue timer if unpaused
    }
    //update and redraw board widget
    update();
}




/*******************************************************************************
 * paint board and board contents
 * @param QPaintEvent
*******************************************************************************/
void BlocksBoard::paintEvent(QPaintEvent *event)
{
   //pass event to parent class
    QFrame::paintEvent(event);

    //instantiate painter object
    QPainter painter(this);
    QRect rect = contentsRect();

    //show pause text if paused
    if(isPaused){
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }

    //determine top of board by subtracting the BoardHeight from the bottom
    //coordinate
    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    //draw blocks on the board
    for (int i = 0; i < BoardHeight; ++i) {//for each row
        for (int j = 0; j < BoardWidth; ++j) {//for each col
            //check cell contents
            BlockShape shape = shapeAt(j, BoardHeight - i - 1);
            //if cell is not empty, or diretly under current piece

            if (shape != NoShape ||//if not NoShape or
                    //within the xCoords of piece
                    (j >= curX + curPiece.minX() &&
                     j <= curX + curPiece.maxX() &&
                     isStarted
                     )){
                //helper column
                if(shape == NoShape){//if NoShape
                    //get the maximum value in column occupied by current piece
                    int yMax = 0;
                    for(int k=0; k<4; ++k){
                        if(curX + curPiece.x(k) == j){
                            yMax = qMax(yMax, curY - curPiece.y(k));
                        }
                    }
                    //continue loop is NoShape is above max coord for current
                    //piece
                    if(i < -yMax + BoardHeight ) continue;

                }
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape);
            }//draw square in cell
        }
    }

    //draw current piece
    if(curPiece.shape() != NoShape){
        for (int i = 0; i< 4; ++i){
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.shape());//draw each peice cell
        }
    }

}


/*******************************************************************************
 * Key event handler. Manages keyevents
 * @oaram keyEvent
*******************************************************************************/
void BlocksBoard::keyPressEvent(QKeyEvent *event)
{

    //pass event to parent if gamestate has not started
    if(!isStarted || isPaused || curPiece.shape() == NoShape){
        QFrame::keyPressEvent(event);
        return;
    }

    if(event->key() == leftButton){
        tryMove(curPiece, curX - 1, curY);
    }else if(event->key() == rightButton){
        tryMove(curPiece, curX + 1, curY);
    }else if(event->key() == rotateCWButton){
        tryMove(curPiece.rotatedRight(), curX, curY);
    }else if(event->key() == rotateCCWButton){
        tryMove(curPiece.rotatedRight(), curX, curY);
    }else if(event->key() == downButton){
        oneLineDown();
    }else if(event->key() == dropButton){
        dropDown();
    }else{
        QFrame::keyPressEvent(event);
    }



    //associate keyCode with appropriate method call
//    switch(event->key()){
//    case leftButton:
//        tryMove(curPiece, curX - 1, curY);
//        break;
//    case rightButton:
//        tryMove(curPiece, curX + 1, curY);
//        break;
//    case rotateCWButton:
//        tryMove(curPiece.rotatedRight(), curX, curY);
//        break;
//    case rotateCCWButton:
//        tryMove(curPiece.rotatedLeft(), curX, curY);
//        break;
//    case dropButton:
//        dropDown();
//        break;
//    case downButton:
//        oneLineDown();
//        break;
//    default:
//        //pass to parent class
//        QFrame::keyPressEvent(event);
//    }

}

/*******************************************************************************
 * TimerEvent method.
 * @param QTimerEvent
*******************************************************************************/
void BlocksBoard::timerEvent(QTimerEvent *event){

    //if event is triggered by game timer
    if(event->timerId() == timer.timerId()){
        //do game logic
        if (isWaitingAfterLine){
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        }else{
            oneLineDown();
        }
    }else{
        //pass event to parent class
        QFrame::timerEvent(event);
    }
}


/*******************************************************************************
 * ShapeAt method returns shape enum value at board coordinate
 * @return BlockShape value
*******************************************************************************/
BlockShape & BlocksBoard::shapeAt(int x, int y)
{
    return board[(y * BoardWidth) + x];
}


/*******************************************************************************
 *  timeoutTime method calculates the time until the next game timer event,
 * valued at 1000/(1 + level)
 * @return miliseconds till next time event
*******************************************************************************/
int BlocksBoard::timeoutTime()
{
//    return 1000/ (1+level);
    return 1000;
}

/*******************************************************************************
 * @return square width
*******************************************************************************/
int BlocksBoard::squareWidth(){
    return contentsRect().width() / BoardWidth;
}

/*******************************************************************************
 * @return square height
*******************************************************************************/
int BlocksBoard::squareHeight()
{
    return contentsRect().height() / BoardHeight;
}


/*******************************************************************************
 * clear board grid
*******************************************************************************/
void BlocksBoard::clearBoard()
{
    //set each coordinate in board array to NoShape
    for (int i = 0; i < BoardHeight * BoardWidth; ++i){
        board[i] = NoShape;
    }
}

/*******************************************************************************
 * drop current piece as far down as it will go
*******************************************************************************/
void BlocksBoard::dropDown()
{

    int dropHeight = 0;
    int newY = curY;
    //try to move piece down until it wont move anymore
    while (newY > 0){
        //break loop on move down collision
        if (!tryMove(curPiece, curX, newY - 1)){
            break;
        }

        --newY;
        ++dropHeight;

    }
    pieceDropped(dropHeight);
}


/*******************************************************************************
 * move current piece down one line
*******************************************************************************/
void BlocksBoard::oneLineDown()
{
    if(!tryMove(curPiece, curX, curY -1)){
        pieceDropped(0);
    }
}

/*******************************************************************************
 * Check for full rows and award points accordingly
*******************************************************************************/
void BlocksBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i){
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt (x,y) = curPiece.shape();

    }

    ++numPiecesDropped;
    if(numPiecesDropped % 25 == 0){
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight +7;
    emit scoreChanged(score);
    removeFullLines();

    if(!isWaitingAfterLine){
        newPiece();
    }
}



/*******************************************************************************
 * scan board grid and remove full lines
*******************************************************************************/
void BlocksBoard::removeFullLines()
{
    int numFullLines = 0;//line counter

    for (int i= BoardHeight -1; i >=0; --i){//for each row
        bool lineIsFull = true;//set flag

        for (int j = 0; j< BoardWidth; ++j){//for each cell in row
            if (shapeAt(j,i)  == NoShape){//if cell is empty
                lineIsFull = false;//clear flag
                break;//break loop
            }
        }


        if(lineIsFull){//in line is full
            ++numFullLines; //increment full lines
            //for each row starting at active row
            for( int k = i; k < BoardHeight - 1; ++k){
                //for cell in row
                for(int j = 0; j < BoardWidth ; ++j){
                    //copy row above to active row
                    shapeAt(j, k) = shapeAt(j, k + 1);
                }
            }
            for (int j= 0; j < BoardWidth; ++j){//for each column
                shapeAt(j, BoardHeight - 1) = NoShape;//clear cell
            }
        }
    }

    if(numFullLines > 0){//if any lines are are removed
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        if (numFullLines == 4){//if max lines removed
            score += 60;//bonus points
        }

        //emit signals
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        //update and redraw Board widget
        update();
    }

}

/*******************************************************************************
 * cycle next peice to current peice and generate new piece
*******************************************************************************/
void BlocksBoard::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth/2+1;
    curY = BoardHeight -1 + curPiece.minY();
    
    if(!tryMove(curPiece, curX, curY)){//if grid is full
        curPiece.setShape(NoShape);//end game
        timer.stop();
        isStarted = false;
    }
}


/*******************************************************************************
 * update label for next piece
*******************************************************************************/
void BlocksBoard::showNextPiece()
{
    if(!nextPieceLabel){
        return;
    }
    
    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;
    
    QPixmap pixMap (dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixMap);
    painter.fillRect(pixMap.rect(),nextPieceLabel->palette().background());
    
    
    for(int i = 0; i< 4; ++i ){
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter,
                   x * squareWidth(),
                   y * squareHeight(),
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixMap);
}


/*******************************************************************************
 * tryMove method, attempt to move peice.
 * @return true if successfull, false if not
*******************************************************************************/
bool BlocksBoard::tryMove(const BlocksPiece &newPiece, int newX, int newY)
{
    for(int i = 0; i < 4; ++i){
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);

        //return false if out of bounds
        if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight){
            return false;
        }

        //false if candidate cell is occupied
        if (shapeAt( x,y) !=NoShape){
            return false;
        }

    }
    //if all candidate cells are clear (NoShape)
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    //update and redraw board widget
    update();
    return true;
}


/*******************************************************************************
 * draw blocks on the grid
*******************************************************************************/
void BlocksBoard::drawSquare(QPainter &painter, int x, int y, BlockShape shape)
{
    static const QRgb colorTable[8] = {
        0xDDDDDD,
        0xCC6666,
        0x66CC66,
        0x6666CC,
        0xCCCC66,
        0xCC66CC,
        0x66CCCC,
        0xDAAA00

    };

    QColor color = colorTable[shape];//set color according to shape


    if(shape != NoShape){
        painter.fillRect(x + 1, y + 1, squareWidth() - 2,
                         squareHeight() -2, color);
        painter.setPen(color.light());
        painter.drawLine(x, y + squareHeight() - 1, x, y);
        painter.drawLine(x, y, x + squareWidth() - 1, y);

        painter.setPen(color.dark());
        painter.drawLine(x + 1, y + squareHeight() - 1,
                         x + squareWidth() - 1, y + squareHeight() - 1);
        painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                         x + squareWidth() - 1, y + 1);
    }else{
        painter.fillRect(x , y , squareWidth(), squareHeight(), color);
    }
}

Qt::Key BlocksBoard::getRotateCCWButton()
{
    return rotateCCWButton;
}

void BlocksBoard::setRotateCCWButton(const Qt::Key &key)
{
    rotateCCWButton = key;
}

Qt::Key BlocksBoard::getRotateCWButton()
{
    return rotateCWButton;
}

void BlocksBoard::setRotateCWButton(const Qt::Key &key)
{
    rotateCWButton = key;
}

Qt::Key BlocksBoard::getDropButton()
{
    return dropButton;
}

void BlocksBoard::setDropButton(const Qt::Key &key)
{
    dropButton = key;
}

Qt::Key BlocksBoard::getDownButton()
{
    return downButton;
}

void BlocksBoard::setDownButton(const Qt::Key &value)
{
    downButton = value;
}

Qt::Key BlocksBoard::getRightButton()
{
    return rightButton;
}

void BlocksBoard::setRightButton(const Qt::Key &key)
{
    rightButton = key;
}

Qt::Key BlocksBoard::getLeftButton()
{
    return leftButton;
}

void BlocksBoard::setLeftButton(const Qt::Key &key)
{
    leftButton = key;
}
