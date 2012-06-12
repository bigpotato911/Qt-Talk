#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QTcpSocket>
#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{

    ui->setupUi(this);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    blockSize = 0;

    connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(this,SIGNAL(verified()),this,SLOT(processVerified()));
    connect(this,SIGNAL(unverified()),this,SLOT(processUnverified()));

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::login()
{
    userName = ui->userNameEdit->text();
    password = ui->pwdEdit->text();
    connectToServer();

}

//Connect to specified server ,wait for reply
void LoginDialog::connectToServer()
{
    client = new QTcpSocket(this);
    client->abort();
    client->connectToHost("127.0.0.1",9999);
    connect(client,SIGNAL(connected()),this,SLOT(verify()));
    connect(client,SIGNAL(readyRead()),this,SLOT(readMessage()));

}

//Analysis the info read from the server and make decision
void LoginDialog::readMessage()
{

    QString result;
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_4_7);
    if(blockSize == 0) {
        if(client->bytesAvailable() < (int)sizeof(quint16))
            return;
        else
            in >> blockSize;

    }
    if(client->bytesAvailable() < blockSize)
        return;
    in >> result;
    if(result == "true")
        emit verified();
    else if(result == "false")
        emit unverified();

}

void LoginDialog::processVerified()
{
    accept();
}

//Tell the user to retry
void LoginDialog::processUnverified()
{
    QMessageBox::warning(this,"Warning","Wrong user name or password",QMessageBox::Yes);
    ui->userNameEdit->clear();
    ui->pwdEdit->clear();
    ui->userNameEdit->setFocus();
}

 //Write to the server to verify the user infomation
void LoginDialog::verify()
{
    ui->loginButton->setDisabled(true);

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << quint16(0) << "Verify" << userName << password;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    client->write(block);

}

