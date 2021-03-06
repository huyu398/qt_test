#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qstringlistmodel.h>

#include "twitter.h"
#include "tweet.h"
#include "listdelegate.h"
#include "qtweetlistmodel.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settings = new QSettings(
                QSettings::IniFormat, QSettings::UserScope,
                "huyu", "qt_test");

//    std::list<Tweet> *_tweetList = t.getTimeLine();
//    QList<Tweet> tweetList;
//    for (std::list<Tweet>::iterator it = _tweetList->begin(); it != _tweetList->end(); it++) {
//        tweetList << *it;
//    }

//    QTweetListModel *tweetListModel = new QTweetListModel;
//    tweetListModel->setTweetList(tweetList);

//    QStringListModel *model = new QStringListModel();
//    QStringList qlist;
//    for (int i = 0; i < 20; i++) {
//        qlist << QString(QString::number(i));
//    }

//    model->setStringList(qlist);

//    ui->listView->setModel(tweetListModel);
//    ui->listView->setItemDelegate(new ListDelegate(ui->listWidget));
//    ui->listView->scrollTo(tweetListModel->index(10));

//    QListWidgetItem *item = new QListWidgetItem();
//    item->setData(Qt::DisplayRole, "Title");
//    item->setData(Qt::UserRole + 1, "Description");
//    ui->listWidget->addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loginTwitter()
{
    std::string accessTokenKey = this->settings->
            value("Twitter/ACCESS_TOKEN_KEY", "").toString().toStdString();
    std::string accessTokenSecret = this->settings->
            value("Twitter/ACCESS_TOKEN_SECRET", "").toString().toStdString();
    if (!this->twitterClient.login(accessTokenKey, accessTokenSecret)) {
        LoginDialog l(this);
        std::string userName, passWord;
        while (!this->twitterClient.login(accessTokenKey, accessTokenSecret, userName, passWord)) {
            int r = l.exec();
            if (r == QDialog::Accepted) {
                userName = l.getUserName();
                passWord = l.getPassWord();
            } else if (r == QDialog::Rejected) {
                return false;
            }
        }

        this->settings->setValue("Twitter/ACCESS_TOKEN_KEY",
                                 QString::fromStdString(accessTokenKey));
        this->settings->setValue("Twitter/ACCESS_TOKEN_SECRET",
                                 QString::fromStdString(accessTokenSecret));
    }

    return true;
}

void MainWindow::prepare()
{
    this->twitterClient.setupStreaming();
    bool tmp = this->twitterClient.callStreamingAPI();
}

void MainWindow::on_quitButton_clicked()
{
    QCoreApplication::quit();
//    static int i = 0;
//    QStringListModel *model = (QStringListModel*)ui->listView->model();
//    ui->listView->scrollTo(model->index(i++));
}
