#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::subdisp_slot(QStringList &info)
{
    int size= info.size();
    QString msg=info.at(0);

    this->show();
    if(size==2)
    {
        QString type = info.at(1);
        this->setWindowTitle(type);
        if(type.compare("正在升级")==0)
        {
            ui->textBrowser->clear();
        }
    }
    ui->textBrowser->append(msg);
}

