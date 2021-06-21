#include "signinwindow.h"
#include "ui_signinwindow.h"


// external variables from mainWindow;
extern bool toggle;
extern bool menu;
extern bool minimized;
extern bool maximized;
extern bool normal;
extern int count;


// global variables;
extern QString username;
extern QString userPassword;
extern QString userPasswordConfirmed;

extern bool echoModeActive;
extern QSqlDatabase db;


SignInWindow::SignInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);

    if (minimized) {
        this->showMinimized();
    } else if (maximized) {
        this->showMaximized();
    } else if (normal) {
        this->showNormal();
    }

    this->setWindowIcon(QIcon(":/images/images/c-logo-icon.ico"));
    this->setWindowTitle("Sign In");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // echomode is initialy active;
    echoModeActive = true;

    if (!toggle) {
        ui->centralwidget->setStyleSheet("border-radius: 10px; background-color: #ffffff");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_blue.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu_blue.svg); padding: 5px;");

        ui->title->setStyleSheet("font: 20pt 'MS Shell Dlg 2'; background-color: rgba(0, 0, 0, 0); color: #00427e; font-weight: 600;");

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
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible_blue.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible_blue.svg);");
        }

        // signupBox components;
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
    }
    else {
        ui->centralwidget->setStyleSheet("border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0.477169, y1:0.505, x2:0.753, y2:0.608091, stop:0 rgba(0, 66, 126, 255), stop:1 rgba(0, 86, 151, 255));");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_white.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu.svg); padding: 5px;");

        ui->title->setStyleSheet("font: 20pt 'MS Shell Dlg 2'; background-color: rgba(0, 0, 0, 0); color: #ffffff; font-weight: 600;");

        // bar components;
        ui->minimizeButton->setStyleSheet("image: url(:/images/images/minus_white.svg); padding: 5px;");
        ui->maximizaButton->setStyleSheet("image: url(:/images/images/maximize_white.svg); padding: 5px;");
        ui->normalButton->setStyleSheet("image: url(:/images/images/normal_white.svg); padding: 5px;");
        ui->closeButton->setStyleSheet("image: url(:/images/images/cancel_white.svg); padding: 5px;");

        // menulist components;
        ui->homeOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible.svg);");
        }

        // signupBox components;
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
    }
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

// top bar configuration;
void SignInWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
    minimized = true;
    maximized = false;
    normal = false;
}

void SignInWindow::on_maximizaButton_clicked()
{
    this->showMaximized();
    minimized = false;
    maximized = true;
    normal = false;
}

void SignInWindow::on_normalButton_clicked()
{
    showNormal();
    minimized = false;
    maximized = false;
    normal = true;
}

void SignInWindow::on_closeButton_clicked()
{
    db.close();
    close();
}


// head options configuration;
void SignInWindow::on_menuButton_clicked()
{
    if (menu) {
        menu = false;
        ui->menuList->setStyleSheet("min-width: 150%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    }
    else {
        menu = true;
        ui->menuList->setStyleSheet("max-width: 0%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    }
}

void SignInWindow::on_toggleButton_clicked()
{
    if (!toggle) {
        toggle = true;
        ui->centralwidget->setStyleSheet("border-radius: 10px; background-color: qlineargradient(spread:pad, x1:0.477169, y1:0.505, x2:0.753, y2:0.608091, stop:0 rgba(0, 66, 126, 255), stop:1 rgba(0, 86, 151, 255));");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_white.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu.svg); padding: 5px;");

        ui->title->setStyleSheet("font: 20pt 'MS Shell Dlg 2'; background-color: rgba(0, 0, 0, 0); color: #ffffff; font-weight: 600;");

        // bar components;
        ui->minimizeButton->setStyleSheet("image: url(:/images/images/minus_white.svg); padding: 5px;");
        ui->maximizaButton->setStyleSheet("image: url(:/images/images/maximize_white.svg); padding: 5px;");
        ui->normalButton->setStyleSheet("image: url(:/images/images/normal_white.svg); padding: 5px;");
        ui->closeButton->setStyleSheet("image: url(:/images/images/cancel_white.svg); padding: 5px;");

        // menulist components;
        ui->homeOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible.svg);");
        }

        // signupBox components;
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");

    }
    else {
        toggle = false;
        ui->centralwidget->setStyleSheet("border-radius: 10px; background-color: #ffffff");

        // head components;
        ui->toggleButton->setStyleSheet("image: url(:/images/images/toggle_blue.svg); padding: 10px;");
        ui->menuButton->setStyleSheet("image: url(:/images/images/menu_blue.svg); padding: 5px;");

        ui->title->setStyleSheet("font: 20pt 'MS Shell Dlg 2'; background-color: rgba(0, 0, 0, 0); color: #00427e; font-weight: 600;");

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
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible_blue.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible_blue.svg);");
        }

        // signupBox components;
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
    }
}


// menu list configuration;
void SignInWindow::on_aboutOption_clicked()
{
    QMessageBox::about(this, "About C++ Login Management System", "This program uses Qt Version 6.1.0.\n"
                                                                    "\n"
                                                                    "C++ Login Management System (C++LMS) is a based C++ program that allows users to login in a MySQL database using a very friendly graphical user interface created in Qt.\n"
                                                                    "\n"
                                                                    "C++LMS code is available on GitHub where developers can use, test and eventually contribute improving the performance of the project.\n"
                                                                    "\n"
                                                                    "Please access https://github.com/iamtomorrow for more about this and other programs in development.\n"
                                                                    "\n"
                                                                    "Copyright (C) 2021 Tomorrow.\n"
                                                                    "\n"
                                                                    "Qt is The Company Ltd product developed as an open source project. See qt.io for more information.\n");
}

void SignInWindow::on_exitOption_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Exit", "Are you sure?", QMessageBox::Yes | QMessageBox::No );
    if (ans == QMessageBox::Yes) {
        this->close();
    }
}

void SignInWindow::on_signupOption_clicked()
{
    SignUpWindow SignUp;
    this->close();
    SignUp.exec();
}

void SignInWindow::on_removeAccountOption_clicked()
{
    RemoveAccountWindow rmvAccount;
    this->close();
    rmvAccount.exec();
}


// SignIn setup;
void SignInWindow::on_visibilityButton_clicked()
{
    if (echoModeActive) {
        echoModeActive = false;
        ui->textPassword->setEchoMode(QLineEdit::Normal);
        ui->textConfirmPassword->setEchoMode(QLineEdit::Normal);
        if (!toggle) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible_blue.svg)");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible.svg)");
        }
    }
    else {
        echoModeActive = true;
        ui->textPassword->setEchoMode(QLineEdit::Password);
        ui->textConfirmPassword->setEchoMode(QLineEdit::Password);
        if (!toggle) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible_blue.svg)");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg)");
        }
    }
}

void SignInWindow::on_signInButton_clicked()
{
    username = ui->textUsername->text();
    userPassword = ui->textPassword->text();
    userPasswordConfirmed = ui->textConfirmPassword->text();

    if (db.open()) {
        qDebug() << "Database is OPEN!";

        count = 0;
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE username = '"+username+"' AND user_password = '"+userPassword+"'");
        if (query.exec()) {
            while (query.next()) {
                count++;
            }

            qDebug() << count;
            if (count == 1) {
                QMessageBox::warning(this, "SUCCESSFUL Sign In", "User SUCCESSFUL signed in!");
                ui->textUsername->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
                ui->textPassword->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
                ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
            }
            else {
                // 002 sign in error;
                QMessageBox::warning(this, "Sign In ERROR", "ERROR trying to find user in our database! It looks like your user is not a current real user or some information is wrong! Consider review it and try again.");
                ui->textUsername->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
                ui->textPassword->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
                ui->textConfirmPassword->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
            }
            db.close();
        }
        else {
            // 001 execution error;
            QMessageBox::warning(this, "Execution ERROR", "ERROR trying to execute the search for the user! Please consider contact us for possible solutions, since this problem does not belong to expected errors.");
            qDebug() << "ERROR trying to find user in our database!";
            qDebug() << query.lastError();
        }
    }
    else {
        // 000 connection error;
        QMessageBox::warning(this, "Connection ERROR", "Sorry it looks like our database was not open properly! Please contact us for possible solutions.");
        qDebug() << "Database NOT open!";
    }
}
