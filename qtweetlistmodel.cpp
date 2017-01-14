#include "qtweetlistmodel.h"

QTweetListModel::QTweetListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QTweetListModel::QTweetListModel(const QList<Tweet> &tweetList, QObject *parent)
    : QAbstractListModel(parent), tweetList(tweetList)
{
}

//QVariant QTweetListModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

int QTweetListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return tweetList.count();
}

QVariant QTweetListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Tweet t = tweetList.at(index.row());
    switch (role) {
    case Qt::UserRole + UserName:
        return t.getUserName();
    case Qt::UserRole + TweetContent:
        return t.getTweetContent();
    default:
        return QVariant();
    }

    // FIXME: Implement me!
    return QVariant();
}

//bool QTweetListModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endInsertRows();
//}

//bool QTweetListModel::removeRows(int row, int count, const QModelIndex &parent)
//{
//    beginRemoveRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endRemoveRows();
//}

void QTweetListModel::setTweetList(const QList<Tweet> &tweetList){
    emit beginResetModel();
    this->tweetList = tweetList;
    emit endResetModel();
}
