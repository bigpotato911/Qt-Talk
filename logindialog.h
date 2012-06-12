#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class QTcpSocket;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
signals:
    void verified();
    void unverified();
private slots:
    void login();
    void connectToServer();
    void readMessage();
    void processVerified();
    void processUnverified();
    void verify();
private:


    int blockSize;
    QString userName;
    QString password;
    Ui::LoginDialog *ui;
    QTcpSocket *client;
};

#endif // LOGINDIALOG_H
