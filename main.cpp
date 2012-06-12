#include <QtGui/QApplication>
#include <QDialog>
#include "logindialog.h"
#include "chatdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login;
    ChatDialog chatDialog;
    if(login.exec()==QDialog::Accepted){

        chatDialog.show();
        return a.exec();
    }

}
