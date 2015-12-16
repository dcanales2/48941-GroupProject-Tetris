#include "blockswindow.h"
#include "blocksboard.h"


#include <QGridLayout>
#include <QMenuBar>
#include <QtGui>



struct Connection{
    QSqlDatabase db;
    bool connected;
};
Connection createConnection();

/*******************************************************************************
 * Default constructor. Setsup interface
 ******************************************************************************/
BlocksWindow::BlocksWindow()
{
   // create a dialog for new username or load profile
    saveDialog = new QFileDialog(this);
    loadProfile =new QPushButton("LOAD PROFILE");
    newProfile = new QPushButton("NEW GAME");
    QObject::connect(newProfile,SIGNAL(clicked()),this,SLOT(newProfileDialog()));
    QObject::connect(loadProfile,SIGNAL(clicked()),this,SLOT(loadFileDialog()));

    profileLayout = new QHBoxLayout();
    profileWindow = new QWidget();
    profileLayout->addWidget(newProfile);
    profileLayout->addWidget(loadProfile);
    profileWindow->setLayout(profileLayout);
    profileWindow->setGeometry(650,400,200,50);
    profileWindow->show();
    profileWindow->raise();
    //board->lower();

    //create a player
    player = new Player();
    userLabel = new QLabel();

    //create new board instance
    board = new BlocksBoard;
    board->setStyleSheet("border: 3px solid #c1c1a4;");

    //create and config nextPieceLabel
    nextPieceLabel = new QLabel();
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    nextPieceLabel->setFrameStyle(QFrame::Box);
    nextPieceLabel->setStyleSheet("background-color:black;border: 3px solid  #c1c1a4;");
    //nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);

    holdPieceLabel = new QLabel();
    //holdPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    holdPieceLabel->setAlignment(Qt::AlignCenter);
    holdPieceLabel->setStyleSheet("background-color:black;border: 3px solid  #c1c1a4;");

    //set nextPieceLael to board
    board->setNextPieceLabel(nextPieceLabel);
    board->setHoldPieceLabel(holdPieceLabel);

    backGroundLabel = new QLabel();
    backGroundLabel->setPixmap(QPixmap(":/Images/startBackground.jpg"));
    backGroundLabel->setScaledContents(true);
    backGroundLabel->lower();

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
    fileMenu = new QMenu("File");
    optionsMenu = new QMenu("Options");
    submenu[0] = new QAction("Controls",this);
    fileSubmenu[0] = new QAction("New User",this);
    fileSubmenu[1] = new QAction("Load",this);
    fileSubmenu[2] = new QAction("Save",this);
    fileSubmenu[3] = new QAction("Close",this);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(optionsMenu);
    fileMenu->addAction(fileSubmenu[0]);
    fileMenu->addAction(fileSubmenu[1]);
    fileMenu->addAction(fileSubmenu[2]);
    fileMenu->addAction(fileSubmenu[3]);
    optionsMenu->addAction(submenu[0]);

    connect(submenu[0], SIGNAL(triggered(bool)), this, SLOT(controllsSetup()));
    connect(fileSubmenu[0], SIGNAL(triggered(bool)),this,SLOT(newProfileDialog()));
    connect(fileSubmenu[1], SIGNAL(triggered(bool)),this,SLOT(loadFileDialog()));
    connect(fileSubmenu[2], SIGNAL(triggered(bool)),this,SLOT(saveFileDialog()));
    connect(fileSubmenu[3], SIGNAL(triggered(bool)),this,SLOT(close()));

    layout->setMenuBar(menuBar);

    layout->addWidget(backGroundLabel,0,0,0,0,0);
    layout->addWidget(createLabel(tr(" <font color=red>NEXT</font>")),1,0,1,1,0);
    layout->addWidget(nextPieceLabel, 0, 0);
    layout->addWidget(createLabel(tr(" <font color=red>LEVEL</font>")), 3, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(userLabel,5,0);
    layout->addWidget(board, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr(" <font color=red>HOLD PIECE</font>")),1,2);
    layout->addWidget(holdPieceLabel,0,2);
    layout->addWidget(createLabel(tr(" <font color=red>SCORE</font>")), 2, 2);
    layout->addWidget(scoreLcd, 2, 2);
    layout->addWidget(createLabel(tr(" <font color=red>LINES REMOVED</font>")), 3, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);

    setLayout(layout);

    //set widget title and size
    setWindowTitle(tr("Blocks"));
    resize(550, 370);

    //let buttons be disabled until the user loads or creates a new profile
    startButton->setEnabled(false);
    pauseButton->setEnabled(false);
    quitButton->setEnabled(false);

    this->lower();
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
    QLabel *lbl = new QLabel("_" + text);
    //set allignment
    lbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //return label
    lbl->raise();
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

void BlocksWindow::newProfileDialog()
{
    player->linesRemoved = 0;
    player->level = 0;
    player->score = 0;

    bool ok;
    QString text = QInputDialog::getText(this, tr("USERNAME"),
                                         tr("User name:"), QLineEdit::Normal
                                         );
    if (ok && !text.isEmpty())

        player->userName = text;

    userLabel->setText(player->userName);
    profileWindow->hide();

    startButton->setEnabled(true);
    pauseButton->setEnabled(true);
    quitButton->setEnabled(true);

}

void BlocksWindow::saveFileDialog()
{
    saveDialog->setFileMode(QFileDialog::AnyFile);
    QString testNameDir = saveDialog->getSaveFileName();

    file = new QFile(testNameDir);

    player->score = board->score;
    player->level = board->level;
    player->linesRemoved = board->numLinesRemoved;

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(file);
    out << player->userName + "\n";
    out <<QString::number(player->score) + "\n";
    out <<QString::number(player->level) + "\n";
    out <<QString::number(player->linesRemoved);
    file->close();


    //server connection
    Connection connection = createConnection();
        if ( !connection.connected ){
            qDebug() << "Not connected!";
            //return 1;
            return;
        }
        else{
            qDebug() << "Connected!";
            QSqlQuery query;
            query.prepare("SELECT Blocks FROM Tables");
            query.prepare("INSERT INTO Blocks (userName, score, level, linesCleared) "
                            "VALUES (:user, :score, :userLevel, :linesRemoved)");
            cout<<player->userName.toStdString()<<endl;
            cout<<player->score<<endl;
            cout<<player->level<<endl;
            cout<<player->linesRemoved<<endl;
              query.bindValue(":user", player->userName);
              query.bindValue(":score", player->score);
              query.bindValue(":userLevel", player->level);
              query.bindValue(":linesRemoved", player->linesRemoved);

            query.exec();
            connection.db.close();
            }
}

void BlocksWindow::loadFileDialog()
{
    saveDialog->setFileMode(QFileDialog::ExistingFile);
    QString testNameDir = saveDialog->getOpenFileName();
    file2 = new QFile(testNameDir);

    if (!file2->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(file2);
    QString line = in.readLine();
    player->userName = line;
    userLabel->setText(player->userName);

    line = in.readLine();

    player->score = line.toInt();
    board->score = player->score;

    line = in.readLine();
    player->level = line.toInt();
    board->level = player->level;

    line = in.readLine();
    player->linesRemoved = line.toInt();
    board->numLinesRemoved = player->linesRemoved;

    file2->close();
    profileWindow->hide();

    startButton->setEnabled(true);
    pauseButton->setEnabled(true);
    quitButton->setEnabled(true);
}

Connection createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("209.129.8.2");
    db.setDatabaseName("48941");
    db.setUserName("48941");
    db.setPassword("48941cis17b");

    Connection connection;
    connection.db = db;
    if (!db.open()) {
        qDebug() << "Database error occurred";
        connection.connected = false;
        return connection;
    }
    connection.connected = true;

    return connection;
}


/*******************************************************************************
 *
*******************************************************************************/
//int BlocksWindow::heightForWidth(int w) const
//{
//    return static_cast<int>(w/(550.0f/370.0f));
//}
