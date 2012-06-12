#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

namespace Ui {
class ChatDialog;
}

class QTcpSocket;

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();

private:
    Ui::ChatDialog *ui;
    QTcpSocket *client;
};

#endif // CHATDIALOG_H
