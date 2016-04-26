#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define NB_CAPTURE 6
#define ROBOT_DEBUG 1

using namespace std;
using namespace cv;

namespace Ui {
class Dialog1;
}


class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void readFrame();

    void on_openCamera_clicked();

    void on_closeCamera_clicked();

    void on_lastStep_clicked();

private:
    Ui::Dialog1 *ui;
    VideoCapture capture;
    Mat cvframe;
    //QImage *img;
    QTimer *timer;

};

#endif // DIALOG1_H
