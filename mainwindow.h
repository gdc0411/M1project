#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QMessageBox>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <list>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

struct Ratio{
    int height;
    int width;
    float _ratio;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenFile_clicked();

    void on_divideButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    int cubeRow;
    int cubeCol;
    QImage *Qimage;//image in qt
    cv::Mat image; //image during treatment in OpenCV
    cv::Mat image_origin;
};

#endif // MAINWINDOW_H
