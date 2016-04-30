#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QtGui>
#include <QtCore>

#define DELT_POS_X 90
#define DELT_POS_Y 20
#define BLOCK_SIZE 60

class MyLabel : public QLabel{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent=0);
    int getsideNum(){return sideNum;}
    void setsideNum(int sideNum){this->sideNum = sideNum;}
    std::vector<std::vector<int>> getColors(){return colors;}
    void setColors(std::vector<std::vector<int>> colors);

private:
    std::vector<std::vector<int>> colors;
    int sideNum;
    QPoint mousePos;
    int int_pos_x;
    int int_pos_y;
    std::vector<QRectF> face;
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    QColor colorsMap(int color);
    int inWhichFace(QPoint point);
};
#endif
