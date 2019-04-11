#include "mainwindow.h"
#include "ui_mainwindow.h"
#define CURL_STATICLIB
#include <curl/curl.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loops = 1;
    _emailsCurrently = 0;
    _emailsRecived = 0;
    _emailsSent = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_send_clicked()
{
    if(worker->sendEmail(ui->to->text().toStdString()))
    {
       _emailsSent++;
    ui->emailsSent->setText(QString::number(_emailsSent));
    }
}

void MainWindow::login()
{
    _username = ui->from->text();
    _password = ui->password->text();

    worker = new emailWork(_username.toStdString(), "Automated Test Email", "This is an automatic testing email.");
}


int MainWindow::countInbox()
{
    QString email;

    while(true)
    {
    email = worker->getEmail(loops, _username.toStdString(), _password.toStdString());
    if(email == "")
    {
        return loops - 1;
    }

    loops++;
    }
}

void MainWindow::on_login_clicked()
{
    login();

    if(mainthread == nullptr)
    mainthread = new std::thread(&MainWindow::proccessIncomingEmails, this);

    ui->login->setEnabled(0);
    ui->to->setEnabled(1);
    ui->send->setEnabled(1);


}

void MainWindow::proccessIncomingEmails()
{
    _emailsCurrently = countInbox();


    while(true)
    {
        ui->EmailsRecived->setText(QString::number(countInbox()));
        if(loops - 1 > _emailsCurrently)
        {
            _emailsRecived++;
            _emailsCurrently = loops - 1;

            ui->EmailsIncoming->setText(QString::number(_emailsRecived));
        }

    }

}
