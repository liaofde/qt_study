#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//content << "姓名" << "性别" << "年龄" << "民族";
#include <QMainWindow>
#include<QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public:
    QStandardItemModel * modal;
    QModelIndex mindex;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
