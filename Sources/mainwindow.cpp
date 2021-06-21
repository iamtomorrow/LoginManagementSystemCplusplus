#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "signupwindow.h"
#include "mainwindow.h"

bool toggle;
bool menu;
bool minimized;

bool maximized;
bool normal;

QSqlDatabase db;
bool dbOpen;

int count;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/images/c-logo-icon.ico"));
    this->setWindowTitle("C++ Login Management System");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    toggle = false;
    menu = false;
    minimized = false;
    maximized = false;
    normal = true;

    // database connection;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("LoginManagementSystem");
    db.setHostName("localhost");
    db.setPassword("Tomorrowuser2021");
    db.setPort(3306);
    db.setUserName("root");
    dbOpen = db.open();

    if (dbOpen) {
        qDebug() << "MySQL database is open!";
    }
    else {
        qDebug() << "ERROR trying to open database! QSQLite database will be loaded.";
        db.lastError();
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
    minimized = true;
    maximized = false;
    normal = false;
}

void MainWindow::on_maximizaButton_clicked()
{
    this->showMaximized();
    minimized = false;
    maximized = true;
    normal = false;
}

void MainWindow::on_normalButton_clicked()
{
    this->showNormal();
    minimized = false;
    maximized = false;
    normal = true;
}

void MainWindow::on_closeButton_clicked()
{
    db.close();
    this->close();
}


void MainWindow::on_toggleButton_clicked()
{
    if (!toggle) {
        toggle = true;
        ui->centralwidget->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.477169, y1:0.505, x2:0.753, y2:0.608091, stop:0 rgba(0, 66, 126, 255), stop:1 rgba(0, 86, 151, 255));");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_white.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu.svg); padding: 5px;");

        // bar components;
        ui->minimizeButton->setStyleSheet("image: url(:/images/images/minus_white.svg); padding: 5px;");
        ui->maximizaButton->setStyleSheet("image: url(:/images/images/maximize_white.svg); padding: 5px;");
        ui->normalButton->setStyleSheet("image: url(:/images/images/normal_white.svg); padding: 5px;");
        ui->closeButton->setStyleSheet("image: url(:/images/images/cancel_white.svg); padding: 5px;");

        // menulist components;
        ui->homeOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->extiOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        // central frame components;
        ui->intro->setStyleSheet("background-color: rgba(0, 0, 0, 0); image: url(:/images/images/background.png); border-radius: 0px;");

        // features components;
        ui->extensionsIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/extensions.svg);");
        ui->extensionsLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->downloadIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/download.svg);");
        ui->downloadsLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->supportIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/support.svg);");
        ui->supportLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->worldIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/earth.svg);");
        ui->worldwideLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->copyrightLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

    }
    else {
        toggle = false;
        ui->centralwidget->setStyleSheet("background-color: #ffffff");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_blue.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu_blue.svg); padding: 5px;");

        // bar componemts;
        ui->minimizeButton->setStyleSheet("image: url(:/images/images/minus.svg); padding: 5px;");
        ui->maximizaButton->setStyleSheet("image: url(:/images/images/maximize.svg); padding: 5px;");
        ui->normalButton->setStyleSheet("image: url(:/images/images/normal.svg); padding: 5px;");
        ui->closeButton->setStyleSheet("image: url(:/images/images/cancel.svg); padding: 5px;");

        // menulist components;
        ui->homeOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->extiOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        // central frame components;
        ui->intro->setStyleSheet("background-color: rgba(0, 0, 0, 0); image: url(:/images/images/background_blue.png); border-radius: 0px;");

        // features components;
        ui->extensionsIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/extensions_blue.svg);");
        ui->extensionsLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->downloadIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/download_blue.svg);");
        ui->downloadsLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->supportIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/support_blue.svg);");
        ui->supportLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->worldIcon->setStyleSheet("padding: 0px; background-color: rgba(0,0,0,0); image: url(:/images/images/earth_blue.svg);");
        ui->worldwideLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        ui->copyrightLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");
    }
}


void MainWindow::on_menuButton_clicked()
{
    if (!menu) {
        menu = true;
        ui->menuList->setStyleSheet("max-width: 150%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    }
    else {
        menu = false;
        ui->menuList->setStyleSheet("max-width: 0%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    }
}



// Menu options configuration;
void MainWindow::on_homeOption_clicked()
{
    update();
}

void MainWindow::on_signupOption_clicked()
{
    SignUpWindow SignUp;
    this->close();
    SignUp.exec();
}

void MainWindow::on_signinOption_clicked()
{
    SignInWindow SignIn;
    this->close();
    SignIn.exec();
}

void MainWindow::on_extiOption_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Exit", "Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if (ans == QMessageBox::Yes) {
        this->close();
    }
}

void MainWindow::on_aboutOption_clicked()
{

    QMessageBox::about(this, "About C++ Login Management System", "This program uses Qt Version 6.1.0.\n"
                                                                    "\n"
                                                                    "C++ Login Management System (C++LMS) is a based C++ program that allows users to login in a PosgtreSQL, SQLite and MySQL database using a very friendly graphical user interface created in Qt.\n"
                                                                    "\n"
                                                                    "C++LMS code is available on GitHub where developers can use, test and eventually contribute improving the performance of the project.\n"
                                                                    "\n"
                                                                    "The users are grouped in three different sections that corresponds to the following database services PostgreSQL, SQLite and MySQL\n"
                                                                    "\n"
                                                                    "Please access https://github.com/iamtomorrow for more about this and other programs in development.\n"
                                                                    "\n"
                                                                    "Copyright (C) 2021 Tomorrow.\n"
                                                                    "\n"
                                                                    "Qt is The Company Ltd product developed as an open source project. See qt.io for more information.\n");
}

void MainWindow::on_removeAccountOption_clicked()
{
    RemoveAccountWindow rmvAccount;
    this->close();
    rmvAccount.exec();
}

void MainWindow::on_copyrightLabel_clicked()
{
    QString webLink = "https://cplusplus.netlify.app/";
    QDesktopServices::openUrl(QUrl(webLink));
}
