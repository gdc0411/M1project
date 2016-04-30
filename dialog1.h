#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Robot.h"
#include "Rubik.h"
#include "RubikColor.h"


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
    void setRubikColor(RubikColor colors[]);


protected:
     void closeEvent(QCloseEvent *event);

private slots:

    void on_openCamera_clicked();

    void on_lastStep_clicked();

    void on_nextStep_clicked();

    void on_openCamera_2_clicked();

    void readFrame();

    void on_runRobot_clicked();

private:
    Ui::Dialog1 *ui;
    Robot rob;
    std::vector<std::vector<int>> colors;
    cv::VideoCapture capture;
    cv::Mat cvframe;
    QTimer *timer;
    RubikColor col[9];


};

#endif // DIALOG1_H
