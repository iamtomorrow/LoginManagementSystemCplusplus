#include "mainwindow.h"

#include <QApplication>

#include <QSplashScreen>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *image = new QSplashScreen;

    image->setPixmap(QPixmap(":/images/images/splash_screen_2.png"));
    image->show();

    MainWindow w;

    QTimer::singleShot(5000, image, SLOT(close()));
    QTimer::singleShot(5000, &w, SLOT(show()));
    // w.show();

    return a.exec();
}
