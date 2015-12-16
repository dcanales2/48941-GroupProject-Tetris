#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>
#include <QSplashScreen>
#include <QPixMap>

class Splash : public QWidget
{
    Q_OBJECT
public:
    explicit Splash(QWidget *parent = 0);

private:
    QSplashScreen *startWindow;
    QPixMap *startBackground;

signals:

public slots:
};

#endif // SPLASH_H
