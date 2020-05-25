#include "mlist.h"

mlist::mlist(QWidget *parent)
    :QWidget(parent)
{
    this->item =new QListWidgetItem("book");
}

mlist::~mlist()
{
    delete this->item;
}
