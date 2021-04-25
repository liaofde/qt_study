#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <checkdelegate.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tb;
    QStandardItemModel *md = new QStandardItemModel(/*&tb*/);
    md->setRowCount(5);
    md->setColumnCount(5);
    for(int i = 0;i<4;i++){
        md->setData(md->index(1,i),QString("1"),Qt::EditRole);
    }
    CheckBoxDelegate *ck = new CheckBoxDelegate(/*&tb*/);

    tb.setModel(md);
    tb.setItemDelegate(ck);
    tb.show();

    return a.exec();

}
