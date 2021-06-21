#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QDialog>
#include <QIcon>
#include <QMessageBox>

#include "signupwindow.h"
#include "removeaccountwindow.h"

namespace Ui {
class SignInWindow;
}

class SignInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = nullptr);
    ~SignInWindow();

private slots:
    void on_minimizeButton_clicked();

    void on_maximizaButton_clicked();

    void on_normalButton_clicked();

    void on_closeButton_clicked();

    void on_menuButton_clicked();

    void on_toggleButton_clicked();

    void on_aboutOption_clicked();

    void on_exitOption_clicked();

    void on_signupOption_clicked();

    void on_removeAccountOption_clicked();

    void on_visibilityButton_clicked();

    void on_signInButton_clicked();

private:
    Ui::SignInWindow *ui;
};

#endif // SIGNINWINDOW_H
