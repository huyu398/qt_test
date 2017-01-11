#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qstringlistmodel.h>

#include "twitter.h"
#include "listdelegate.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settings = new QSettings(
                QSettings::IniFormat, QSettings::UserScope,
                "huyu", "qt_test");

    Twitter t;
    std::string accessTokenKey = this->settings->
            value("Twitter/ACCESS_TOKEN_KEY", "").toString().toStdString();
    std::string accessTokenSecret = this->settings->
            value("Twitter/ACCESS_TOKEN_SECRET", "").toString().toStdString();
    std::string userName, passWord;
    if (accessTokenKey.empty() || accessTokenSecret.empty()) {
        LoginDialog *l = new LoginDialog(this);
        while (!t.login(accessTokenKey, accessTokenSecret, userName, passWord)) {
            int r = l->exec();
            if (r == QDialog::Accepted) {
                userName = l->getUserName();
                passWord = l->getPassWord();
            } else if (r == QDialog::Rejected) {
                delete l;
                QCoreApplication::quit();
            }
        }
        delete l;

        this->settings->setValue("Twitter/ACCESS_TOKEN_KEY",
                                 QString::fromStdString(accessTokenKey));
        this->settings->setValue("Twitter/ACCESS_TOKEN_SECRET",
                                 QString::fromStdString(accessTokenSecret));
    }

    QStringListModel *model = new QStringListModel();
    QStringList qlist;
    qlist << "hoge";
    qlist << "huga";
    qlist << "foo";
    qlist << "bar";

    model->setStringList(qlist);

    ui->listView->setModel(model);
    ui->listView->setItemDelegate(new ListDelegate(ui->listWidget));
//    QListWidgetItem *item = new QListWidgetItem();
//    item->setData(Qt::DisplayRole, "Title");
//    item->setData(Qt::UserRole + 1, "Description");
//    ui->listWidget->addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    QCoreApplication::quit();
}
