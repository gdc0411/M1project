#include "mylabel.h"
/* White - Green - Red - Blue - Orange - Yellow */
std::vector<QColor> colorTable{ Qt::white, Qt::green, Qt::red, Qt::blue, QColor(255,88,0), Qt::yellow };
//define rubic area
QRectF face0 = QRectF(DELT_POS_X+BLOCK_SIZE*3,DELT_POS_Y,BLOCK_SIZE*3,BLOCK_SIZE*3);
QRectF face1 = QRectF(DELT_POS_X,DELT_POS_Y+BLOCK_SIZE*3,BLOCK_SIZE*3,BLOCK_SIZE*3);
QRectF face2 = QRectF(DELT_POS_X+BLOCK_SIZE*3,DELT_POS_Y+BLOCK_SIZE*3,BLOCK_SIZE*3,BLOCK_SIZE*3);
QRectF face3 = QRectF(DELT_POS_X+BLOCK_SIZE*3*2,DELT_POS_Y+BLOCK_SIZE*3,BLOCK_SIZE*3,BLOCK_SIZE*3);
QRectF face4 = QRectF(DELT_POS_X+BLOCK_SIZE*3*3,DELT_POS_Y+BLOCK_SIZE*3,BLOCK_SIZE*3,BLOCK_SIZE*3);
QRectF face5 = QRectF(DELT_POS_X+BLOCK_SIZE*3,DELT_POS_Y+BLOCK_SIZE*3*2,BLOCK_SIZE*3,BLOCK_SIZE*3);

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{ 
    face.push_back(face0);
    face.push_back(face1);
    face.push_back(face2);
    face.push_back(face3);
    face.push_back(face4);
    face.push_back(face5);

    std::vector<int> col;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<9;j++)
            col.push_back(i);
        colors.push_back(col);
        col.clear();
    }
//    for(int i=0;i<colors.size();i++)
//    {
//        for(int j=0; j<colors.size();j++)
//        {
//            qDebug() << colors.at(i).at(j);
//            if((j+1)%3 == 0)
//            {
//                qDebug() << "\n";
//            }
//        }
//    }

}

QColor MyLabel::colorsMap(int color)
{
    QColor c;
    if(color != -1)
        c = colorTable.at(color);
    else
        c = Qt::lightGray;
    return c;
}

void MyLabel::setColors(std::vector<std::vector<int>> colors)
{
    this->colors = colors;
    update();
}

void MyLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    QBrush brush(Qt::SolidPattern);

    //face 0
    int_pos_x = BLOCK_SIZE*3 + DELT_POS_X;
    int_pos_y = 0 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(0).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }
    //face 1
    int_pos_x = 0 + DELT_POS_X;
    int_pos_y = BLOCK_SIZE*3 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(1).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }
    //face 2
    int_pos_x = BLOCK_SIZE*3 + DELT_POS_X;
    int_pos_y = BLOCK_SIZE*3 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(2).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }
    //face 3
    int_pos_x = BLOCK_SIZE*6 + DELT_POS_X;
    int_pos_y = BLOCK_SIZE*3 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(3).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }
    //face 4
    int_pos_x = BLOCK_SIZE*9 + DELT_POS_X;
    int_pos_y = BLOCK_SIZE*3 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(4).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }
    //face 5
    int_pos_x = BLOCK_SIZE*3 + DELT_POS_X;
    int_pos_y = BLOCK_SIZE*6 + DELT_POS_Y;
    for(int i = 0; i < 9; i++)
    {
        brush.setColor(colorsMap(colors.at(5).at(i)));
        painter.setBrush(brush);
        painter.drawRoundRect(QRect(BLOCK_SIZE*i%(BLOCK_SIZE*3)+int_pos_x,BLOCK_SIZE*(i/3)+int_pos_y,BLOCK_SIZE,BLOCK_SIZE));
    }

}

void MyLabel::mousePressEvent(QMouseEvent *e)
{
    mousePos = e->pos();
}

void MyLabel::mouseReleaseEvent(QMouseEvent *e)
{
    mousePos = e->pos();
    int num_face = inWhichFace(mousePos);
    qDebug()<<num_face;
    if(num_face != -1)
    {
        QPointF posInFace = QPointF(mousePos) - face[num_face].topLeft();
        int num_x = posInFace.x() / BLOCK_SIZE;
        int num_y = posInFace.y() / BLOCK_SIZE;
        int numBlockInFace = num_x + num_y * 3;
        colors[num_face][numBlockInFace] = (colors[num_face][numBlockInFace] + 1) % 6;
        update();
    }

}

int MyLabel::inWhichFace(QPoint point)
{
    if(face[0].contains(point))
        return 0;
    else if(face[1].contains(point))
        return 1;
    else if(face[2].contains(point))
        return 2;
    else if(face[3].contains(point))
        return 3;
    else if(face[4].contains(point))
        return 4;
    else if(face[5].contains(point))
        return 5;
    else
        return -1;
}

