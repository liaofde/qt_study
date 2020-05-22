#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QWidget"
#include "QMouseEvent"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 鼠标按下消息
    void mousePressEvent(QMouseEvent *);
    // 鼠标松开消息
    void mouseReleaseEvent(QMouseEvent *);
    // 鼠标双击消息，有bug，会产生一次 mousePressEvent
    void mouseDoubleClickEvent(QMouseEvent *);
    // 鼠标移动消息，默认要在触发了mousePressEvent后才生效
    // 需要在构造函数中调用 this->setAttribute(Qt::WA_MouseTracking);
    void mouseMoveEvent(QMouseEvent *);

    // 鼠标进入窗口范围内消息
    void enterEvent(QEvent *);
    // 鼠标离开窗口范围内消息
    void leaveEvent(QEvent *);
    // 鼠标滚轮消息
    void wheelEvent(QWheelEvent  *);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
