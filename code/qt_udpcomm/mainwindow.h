#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    quint64 rxcnt=0;
    quint64 txcnt=0;
public slots:
    void disp_slot(QByteArray &);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void send_signal(QString &ip, quint16 port, QByteArray &msg);
};
#endif // MAINWINDOW_H
