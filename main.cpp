#include "mainwindow.h"
#include "tetris.h"

#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //std::unique_ptr<Tetris> tetris=std::make_unique<Tetris>();
    //tetris->show();
    return a.exec();
}
