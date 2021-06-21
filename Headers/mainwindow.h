#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>

#include "signupwindow.h"
#include "signinwindow.h"
#include "removeaccountwindow.h"
#include "databasecenter.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_minimizeButton_clicked();

    void on_closeButton_clicked();

    void on_maximizaButton_clicked();

    void on_normalButton_clicked();

    void on_toggleButton_clicked();

    void on_menuButton_clicked();

    void on_signupOption_clicked();

    void on_extiOption_clicked();

    void on_aboutOption_clicked();

    void on_signinOption_clicked();

    void on_removeAccountOption_clicked();

    void on_copyrightLabel_clicked();

    void on_homeOption_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
