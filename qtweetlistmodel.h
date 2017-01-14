#ifndef QTWEETLISTMODEL_H
#define QTWEETLISTMODEL_H

#include <QAbstractListModel>

#include "tweet.h"

class QTweetListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        UserName = 1,
        TweetContent
    };

    explicit QTweetListModel(QObject *parent = 0);
    explicit QTweetListModel(const QList<Tweet> &tweetList, QObject *parent = 0);

    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
//    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void setTweetList(const QList<Tweet> &tweetList);

private:
    QList<Tweet> tweetList;
};

#endif // QTWEETLISTMODEL_H
