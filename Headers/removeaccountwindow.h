#ifndef REMOVEACCOUNTWINDOW_H
#define REMOVEACCOUNTWINDOW_H

#include <QDialog>
#include <QIcon>
#include <QMessageBox>

#include "mainwindow.h"
#include "signupwindow.h"
#include "signinwindow.h"

namespace Ui {
class RemoveAccountWindow;
}

class RemoveAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveAccountWindow(QWidget *parent = nullptr);
    ~RemoveAccountWindow();

private slots:
    void on_minimizeButton_clicked();

    void on_maximizaButton_clicked();

    void on_normalButton_clicked();

    void on_closeButton_clicked();

    void on_menuButton_clicked();

    void on_toggleButton_clicked();

    void on_removeAccountButton_clicked();

    void on_aboutOption_clicked();

    void on_exitOption_clicked();

    void on_signupOption_clicked();

    void on_signinOption_clicked();

    void on_visibilityButton_clicked();

private:
    Ui::RemoveAccountWindow *ui;
};

#endif // REMOVEACCOUNTWINDOW_H
