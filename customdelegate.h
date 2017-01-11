#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QAbstractItemDelegate>

class CustomDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject *parent = 0);

signals:

public slots:

};

#endif // CUSTOMDELEGATE_H
