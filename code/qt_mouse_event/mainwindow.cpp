#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "m_mouse_event.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText("start...");
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "mouse move...";
    //QPoint m = event->globalPos();
    //ui->textBrowser->append(QString("(%1,%2)").arg(m.x()).arg(m.y()));
    QPoint n = QCursor::pos();
    ui->textBrowser->append(QString("(%1,%2)").arg(n.x()).arg(n.y()));
    // 鼠标左键单击
    if (ev->button() == Qt::LeftButton)
    {
        qDebug() << "left button down...";
    }
    // 鼠标右键单击
    else if (ev->button() == Qt::RightButton)
    {
        qDebug() << "right button down...";
    }

    // 判断是否按下了 alt 键
    if (ev->modifiers() == Qt::AltModifier)
    {
        qDebug() << "alt is down...";
    }
    // 判断是否按下了 CTRL 键
    if (ev->modifiers() == Qt::CTRL)
    {
        qDebug() << "ctrl is down...";
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    // 鼠标左键单击弹起
    if (ev->button() == Qt::LeftButton)
    {
        qDebug() << "left button up...";
    }
    // 鼠标右键单击弹起
    else if (ev->button() == Qt::RightButton)
    {
        qDebug() << "right button up...";
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    // 双击消息，会产生一次 mousePressEvent
    qDebug() << "doubleClick...";
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动
    qDebug() << "mouse move...";
    QPoint m = event->globalPos();
    ui->textBrowser->append(QString("(%1,%2)").arg(m.x()).arg(m.y()));
    QPoint n = QCursor::pos();
    ui->textBrowser->append(QString("(%1,%2)").arg(n.x()).arg(n.y()));
}

void MainWindow::enterEvent(QEvent *)
{
    qDebug() << "mouse enter...";
}

void MainWindow::leaveEvent(QEvent *)
{
    qDebug() << "mouse leave...";
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
     qDebug() << "wheel move...";
     if(event->delta() > 0){                    // 当滚轮远离使用者时
         ui->textBrowser->zoomIn();                // 进行放大
     }else{                                     // 当滚轮向使用者方向旋转时
         ui->textBrowser->zoomOut();               // 进行缩小
     }
}

