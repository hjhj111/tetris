#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tetris=new Tetris(this);
    ui->horizontalLayout->insertWidget(0,tetris);
    setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    tetris->newGame();
    ui->label->setText(QString::number(tetris->maxScore));
    ui->label_2->setText(QString::number(tetris->score));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"main key";
    tetris->keyPressEvent(event);
}
