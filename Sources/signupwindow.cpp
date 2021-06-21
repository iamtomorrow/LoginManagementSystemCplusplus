#include "signupwindow.h"
#include "ui_signupwindow.h"

#include "signupwindow.h"

// external variables from mainWindow;
extern bool toggle;
extern bool menu;
extern bool minimized;
extern bool maximized;
extern bool normal;


// global variables;
QString userName;
QString userCountry;
QString userPhone;
QString userEmail;
QString username;
QString userPassword;
QString userPasswordConfirmed;

bool echoModeActive;

extern QSqlDatabase db;

// functions;
bool nameConfirmation(QString name);
bool countryConfirmation(QString country);
bool phoneConfirmation(QString phone);
bool emailConfirmation(QString email);
bool usernameConfirmation(QString un);
bool passwordConfirmation(QString password);
bool passwordReconfirmation(QString password, QString passwordAgain);


// database functions;
QString newUserID();
bool findUsername(QString newUsername);
bool findEmail(QString newEmail);


// program setup;
SignUpWindow::SignUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow)
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
    this->setWindowTitle("Sign Up");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // echomode is initialy active;
    echoModeActive = true;

    // color theme setup;
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

        // menuList components;
        ui->homeOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #00427e; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: rgb(0, 65, 126); padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        // signupBox components;
        ui->textName->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textCountry->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPhone->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textEmail->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");

        ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible_blue.svg);");

        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->labelTermsAndConditions->setStyleSheet("color: #00427e; font: 8pt 'MS Shell Dlg 2'; padding: 0px;");


    } else {
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
        ui->signinOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->removeAccountOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left; padding-left: 5px; } QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->signupOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->aboutOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");
        ui->exitOption->setStyleSheet("QPushButton {border-radius: 0px; background-color: rgba(0, 0, 0, 0); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: left ; padding-left: 5px;} QPushButton:hover { border-radius: 0px; background-color: rgba(0, 0, 0, 0.2); color: #ffffff; font: 8pt 'MS Shell Dlg 2'; font-weight: bold; text-align: center }");

        ui->copyrightLabel->setStyleSheet("color: #ffffff; padding: 0px; border-radius: 0px; background-color: rgba(0, 0, 0, 0); font-weight: bold;");

        // signupBox components;
        ui->textName->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textCountry->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPhone->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textEmail->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");

        ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg);");

        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->labelTermsAndConditions->setStyleSheet("color: #ffffff; font: 8pt 'MS Shell Dlg 2'; padding: 0px;");
    }

}


SignUpWindow::~SignUpWindow()
{
    delete ui;
}


// top bar configuration;
void SignUpWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
    minimized = true;
    maximized = false;
    normal = false;
}

void SignUpWindow::on_maximizaButton_clicked()
{
    this->showMaximized();
    minimized = false;
    maximized = true;
    normal = false;
}

void SignUpWindow::on_normalButton_clicked()
{
    this->showNormal();
    minimized = false;
    maximized = false;
    normal = true;
}

void SignUpWindow::on_closeButton_clicked()
{
    db.close();
    this->close();
}


// head option configuration;
void SignUpWindow::on_menuButton_clicked()
{
    if (menu) {
        menu = false;
        ui->menuList->setStyleSheet("min-width: 150%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    } else {
        menu = true;
        ui->menuList->setStyleSheet("max-width: 0%; background-color: rgba(0, 0, 0, 0.2); border-radius: 0px;");
    }
}

void SignUpWindow::on_toggleButton_clicked()
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

        // signupBox components;
        ui->textName->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textCountry->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPhone->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textEmail->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible.svg);");
        }


        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #ffffff; border-radius: 3px;");
        ui->labelTermsAndConditions->setStyleSheet("color: #ffffff; font: 8pt 'MS Shell Dlg 2'; padding: 0px;");

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

        // signupBox components;
        ui->textName->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textCountry->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPhone->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textEmail->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textUsername->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->textPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");

        if (echoModeActive) {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible_blue.svg);");
        }
        else {
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/visible_blue.svg);");
        }

        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 0, 0, 0.2); color: #00427e; border-radius: 3px;");
        ui->labelTermsAndConditions->setStyleSheet("color: #00427e; font: 8pt 'MS Shell Dlg 2'; padding: 0px;");

    }

}


// menu list options configuration;
void SignUpWindow::on_homeOption_clicked()
{
    MainWindow Home;
    this->hide();
    Home.show();
}

void SignUpWindow::on_signinOption_clicked()
{
    SignInWindow SignIn;
    this->close();
    SignIn.exec();
}

void SignUpWindow::on_exitOption_clicked()
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Exit", "Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if (ans == QMessageBox::Yes) {
        this->close();
    }
}

void SignUpWindow::on_aboutOption_clicked()
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

void SignUpWindow::on_removeAccountOption_clicked()
{
    RemoveAccountWindow rmvAccount;
    this->close();
    rmvAccount.exec();
}


// SignUp setup;
void SignUpWindow::on_signupButton_clicked()
{

    userName = ui->textName->text();
    userCountry = ui->textCountry->text();
    userPhone = ui->textPhone->text();
    userEmail = ui->textEmail->text();
    username = ui->textUsername->text();
    userPassword = ui->textPassword->text();
    userPasswordConfirmed = ui->textConfirmPassword->text();

    if (nameConfirmation(userName)) {
        ui->textName->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textName->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (countryConfirmation(userCountry)) {
        ui->textCountry->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textCountry->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (phoneConfirmation(userPhone)) {
        ui->textPhone->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textPhone->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (emailConfirmation(userEmail)) {
        ui->textEmail->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textEmail->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (usernameConfirmation(username)) {
        ui->textUsername->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textUsername->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (passwordReconfirmation(userPassword, userPassword) && userPassword.length() != 0) {
        ui->textPassword->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(0, 230, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    else {
        ui->textPassword->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
        ui->textConfirmPassword->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (!findUsername(username)) {
        QMessageBox::warning(this, "Username ERROR", "Sorry it looks like this username already exists! Consider add a new and try again.");
        ui->textUsername->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }
    if (!findEmail(userEmail)) {
        QMessageBox::warning(this, "Email ERROR", "Sorry it looks like this email already exists! Consider add a new and try again.");
        ui->textEmail->setStyleSheet("background-color: rgba(230, 0, 0, 0.4); color: #ffffff; border-radius: 3px;");
    }

    if (nameConfirmation(userName) && countryConfirmation(userCountry) && phoneConfirmation(userPhone) && emailConfirmation(userEmail) && passwordConfirmation(userPassword) && findUsername(username) && findEmail(userEmail)) {

        if (db.open()) {
            qDebug() << "Database is OPEN!";
            QSqlQuery query;

            query.prepare("INSERT INTO users VALUES ('"+newUserID()+"', '"+userName+"', '"+userCountry+"', '"+userPhone+"', '"+userEmail+"', '"+username+"', '"+userPassword+"')");
            if (query.exec()) {
                QMessageBox::warning(this, "SUCCESSFUL Sign Up", "User SUCCESSFUL created! Now you can access our updates and features using this account.");
                qDebug() << "User inserted into database!";
                db.close();
            }
            else {
                // 001 execution error;
                QMessageBox::warning(this, "Execution ERROR", "ERROR trying to execute the creation of the user! Please consider contact us for possible solutions, since this problem does not belong to expected errors.");
                qDebug() << "ERROR trying to insert user to database";
                qDebug() << query.lastError();
            }
        }
        else {
            // 000 connection error;
            QMessageBox::warning(this, "Connection ERROR", "Sorry it looks like our database was not open properly! Please contact us for possible solutions.");
            qDebug() << "Database NOT open!";
        }
    }
    else {
        QMessageBox::warning(this, "User NOT confirmed", "It looks like there are some missing or wrong information.\n"
                                                        "\n"
                                                        "1. The name inserted must to be full.\n"
                                                        "\n"
                                                        "2. The username must does not match a existing username or contain spaces\n"
                                                        "\n"
                                                        "3. The country inserted must to be a valid country.\n"
                                                        "\n"
                                                        "4. The phone number inserted must to be a valid number.\n"
                                                        "\n"
                                                        "5. The email address inserted must does not match a existing email or be a invalid email.\n"
                                                        "\n"
                                                        "6. The password inserted must to have at leat one of this characters (!, @, #, $, %...)");
    }
}


void SignUpWindow::on_visibilityButton_clicked()
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
            // ui->visibilityButton->setIcon(invisibleWhiteIcon);
            ui->visibilityButton->setStyleSheet("image: url(:/images/images/invisible.svg)");
        }
    }
}


// sign up fucntions;
bool nameConfirmation(QString name) {
    int count = 0;
    // user full name confirmation;
    for (int i = 0; i < name.length(); i++) {
        if (name[i] == ' ') {
            count++;
        }
    }
    if (count >= 2) {
        return true;
    }
    else {
        return false;
    }
}

bool countryConfirmation(QString country) {
    if (country.length() > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool phoneConfirmation(QString phone) {
    if (phone.length() > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool emailConfirmation(QString email) {
    int count = 0;
    for (int i = 0; i < email.length(); i++) {
        if (email[i] == '@') {
            count++;
            for (int c = i; c < email.length(); c++) {
                if (email[c] == '.') {
                    count++;
                }
            }
        }
    }
    if (count == 2) {
        return true;
    }
    else {
        return false;
    }
}

bool usernameConfirmation(QString un) {
    int count = 0;

    if (un.length() > 0) {
        for (int i = 0; i < un.length(); i++) {
            if (un[i] == ' ') {
                count++;
            }
        }
    }
    else {
        return false;
    }

    if (count == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool passwordConfirmation(QString password) {
    int count = 0;
    char characters[] = {'!', '@', '#', '$', '&', '*', '(', ')', '-'};
    int charLength = sizeof(characters)/sizeof (characters[0]);

    if (password.length() >= 10) {
        count++;
    }

    for (int i = 0; i < password.length(); i++) {
        for (int c = 0; c < charLength; c++) {
            if (password[i] == characters[c]) {
                count++;
            }
        }
    }
    if (count > 1) {
       return true;
    }
    else {
        return false;
    }
}

bool passwordReconfirmation(QString password, QString passwordAgain) {
    if (password == passwordAgain && passwordConfirmation(password)) {
        return true;
    }
    else {
        return false;
    }
}

// database functions;
QString newUserID()
{
    int lastUserID;
    QString userID;
    QSqlQuery query;

    if (db.open()) {
        // generate new user ID;
        query.prepare("SELECT user_id "
                    "FROM users "
                    "ORDER BY user_id DESC "
                    "LIMIT 1");
        if (query.exec()) {
            while (query.next()) {
                lastUserID = query.value(0).toInt() + 1;
                userID = QString::number(lastUserID);
            }
        }
        else {
            // 001 execution error;
            qDebug() << "001 Execution ERROR!";
        }
    }
    else {
        // 000 connection error;
        userID = "-1";
    }
    return userID;
}

bool findUsername(QString newUsername)
{
    int row = 0;
    QSqlQuery query;

    if (db.open()) {
        query.prepare("SELECT * FROM users WHERE username = '"+newUsername+"'");
        if (query.exec()) {
            while (query.next()) {
                row++;
            }
            if (row > 0) {
                return false;
            }
        }
        else {
            // 001 execution error;
            qDebug() << "Execution error!";
        }
    }
    else {
        // 000 connection error;
        qDebug() << "Connection error!";
    }
    return true;
}

bool findEmail(QString newEmail)
{
    int row = 0;
    QSqlQuery query;

    if (db.open()) {
        query.prepare("SELECT * FROM users WHERE user_email = '"+newEmail+"'");
        if (query.exec()) {
            while (query.next()) {
                row++;
            }
            if (row > 0) {
                return false;
            }
        }
        else {
            // 001 execution error;
            qDebug() << "Execution error!";
        }
    }
    else {
        // 000 connection error;
        qDebug() << "Connection error!";
    }
    return true;
}
