#ifndef MLIST_H
#define MLIST_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QListWidget>
#include <QWidgetItem>

class mlist:public QWidget
{
    Q_OBJECT
public:
    mlist(QWidget *parent=0);
    ~mlist();
public:
    QListWidgetItem  *item;
};

#endif // MLIST_H
