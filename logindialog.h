#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    std::string getUserName();
    std::string getPassWord();

private slots:
    void onAccept();
    void onReject();

private:
    Ui::LoginDialog *ui;

    std::string userName;
    std::string passWord;
};

#endif // LOGINDIALOG_H
