#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <mainwindow.h>
#include "mainwindow.h"

#include <QDialog>
#include <QIcon>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPixmap>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include "signinwindow.h"
#include "removeaccountwindow.h"


namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();

private slots:
    void on_minimizeButton_clicked();

    void on_maximizaButton_clicked();

    void on_normalButton_clicked();

    void on_closeButton_clicked();

    void on_menuButton_clicked();

    void on_toggleButton_clicked();

    void on_homeOption_clicked();

    void on_exitOption_clicked();

    void on_aboutOption_clicked();

    void on_signupButton_clicked();

    void on_signinOption_clicked();

    void on_visibilityButton_clicked();

    void on_removeAccountOption_clicked();

private:
    Ui::SignUpWindow *ui;
};

#endif // SIGNUPWINDOW_H
