#include "blockswindow.h"
#include "blocksboard.h"


#include <QGridLayout>
#include <QMenuBar>
#include <QtGui>


/*******************************************************************************
 * Default constructor. Setsup interface
 ******************************************************************************/
BlocksWindow::BlocksWindow()
{
    //create new board instance
    board = new BlocksBoard;
    
    //create and config nextPieceLabel
    nextPieceLabel = new QLabel();
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    
    //set nextPieceLael to board
    board->setNextPieceLabel(nextPieceLabel);


    //init and config LCD widgets
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    //init and config buttons
    //NoFocus prevents puttons from taking focus from game window
    startButton = new QPushButton(tr("&Start"));
    startButton ->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    //connect button signals to board an app slots
    connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
    //connect board signals to LCD slots
    connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
    connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
    connect(board, SIGNAL(linesRemovedChanged(int)),
            linesLcd, SLOT(display(int)));

    //add widgets to grid layout
    QGridLayout *layout = new QGridLayout;


    control = new Control();
    control->hide();

    //setup menubar with menus and submenus
    menuBar = new QMenuBar();
    optionsMenu = new QMenu("Options");
    submenu[0] = new QAction("Controls",this);
    menuBar->addMenu(optionsMenu);
    optionsMenu->addAction(submenu[0]);

    connect(submenu[0], SIGNAL(triggered(bool)), this, SLOT(controllsSetup()));


    layout->setMenuBar(menuBar);

    layout->addWidget(createLabel(tr("NEXT")), 0, 0);
    layout->addWidget(nextPieceLabel, 1, 0);
    layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(board, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);



    setLayout(layout);


    //set widget title and size
    setWindowTitle(tr("Blocks"));
    resize(550, 370);





}

void BlocksWindow::controllsSetup()
{
    control->show();
}

/*******************************************************************************
 * Creates and returns a QLabel object given the received QString
 * @param QString to be used in label
 ******************************************************************************/
QLabel *BlocksWindow::createLabel(const QString &text)
{
    //create instance with text string
    QLabel *lbl = new QLabel(text);
    //set allignment
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    //return label
    return lbl;
}

/*******************************************************************************
 *
*******************************************************************************/
void BlocksWindow::resizeEvent(QResizeEvent * /*none*/)
{
    float aspectRatio = 550.0f/370.0f;

    int containerWidth = this->width();
    int containerHeight = this->height();

    int contentsHeight = containerHeight;
    int contentsWidth = containerHeight * aspectRatio;

    if(contentsWidth <550){
        contentsWidth = 550;
        contentsHeight = 370;
    }else if(contentsWidth > containerWidth){
        contentsWidth = containerWidth;
        contentsHeight = containerWidth / aspectRatio;
    }
    resize(contentsWidth, contentsHeight);
}

/*******************************************************************************
 *
*******************************************************************************/
//int BlocksWindow::heightForWidth(int w) const
//{
//    return static_cast<int>(w/(550.0f/370.0f));
//}
