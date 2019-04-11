#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <emailwork.h>
#include <atomic>
#include<iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void proccessIncomingEmails();

    void login();
    int countInbox();

private slots:
    void on_send_clicked();

    void on_login_clicked();

private:
    Ui::MainWindow *ui;
    std::thread *mainthread = nullptr;

    std::atomic<int> _emailsCurrently;
    std::atomic<int> _emailsRecived;
    std::atomic<int> _emailsSent;

    std::atomic<int> loops;


    QString _username;
    QString _password;

    emailWork *worker;
};

#endif // MAINWINDOW_H
