#ifndef TETRIS_H
#define TETRIS_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QQueue>
#include <QTimer>
#include "item.h"
#include "iteml.h"
class Tetris : public QWidget
{
    Q_OBJECT

public:
    friend class Item;
    explicit Tetris(QWidget *parent = nullptr);
    int row;
    int col;
    int d;
    int time;
    int score;
    int maxScore;

    QVector<QVector<int>> board;
    QVector<QVector<int>> _board;
    QVector<QVector<int>> tmp_board;
    QQueue<Item> items;
    QPainter* painter;
    QTimer* timer;
    Item item;
    void drawWall();
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void drawBoard();
    void draw_Board();
    void updateBoard();
    void update_Board();
    void undo_Board();
    void clear();
    void clearOne(int _row);
    bool canMoveDown();
    bool canMoveLeft();
    bool canMoveRight();
    bool canTurn();
    bool canClear(int _row);
    bool gameOver();
    void addRandItem();
    void newGame();

public slots:
    void autoMove();

signals:

};

#endif // TETRIS_H
