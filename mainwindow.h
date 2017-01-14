#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "twitter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool loginTwitter();
    void prepare();

private slots:
    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    QSettings *settings;
    Twitter twitterClient;
};

#endif // MAINWINDOW_H
