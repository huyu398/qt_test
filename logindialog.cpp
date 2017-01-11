#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(onReject()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

std::string LoginDialog::getUserName()
{
    return this->userName;
}

std::string LoginDialog::getPassWord()
{
    return this->passWord;
}

void LoginDialog::onAccept()
{
    this->userName = ui->userName_lineEdit->text().toStdString();
    this->passWord = ui->passWord_lineEdit->text().toStdString();
}

void LoginDialog::onReject()
{
//    QCoreApplication::quit();
}
