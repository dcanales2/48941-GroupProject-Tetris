#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QRect>
#include <QPropertyAnimation>
#include <QPixmap>

class StartWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = 0);

signals:

public slots:
};

#endif // STARTWINDOW_H
