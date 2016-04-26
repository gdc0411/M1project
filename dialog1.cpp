#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    //set signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));
    //timer->start();
}

Dialog1::~Dialog1()
{
    delete ui;
    timer->stop();
    capture.release();
}

void Dialog1::closeEvent(QCloseEvent *event)
{
    timer->stop();
    capture.release();
    ui->camFrameView->clear();
}

void Dialog1::readFrame()
{
    capture >> cvframe;

    //@TODO ANALYSE

    //*************************************//
    //change the color channel
    cv::cvtColor(cvframe, cvframe, CV_BGR2RGB);
    //Mat->QImage
    QImage qimage = QImage((const uchar*)(cvframe.data), cvframe.cols, cvframe.rows, QImage::Format_RGB888);
    qimage = qimage.scaled(ui->camFrameView->size(),Qt::KeepAspectRatio);
    //put qimage to label
    ui->camFrameView->setPixmap(QPixmap::fromImage(qimage));
}

void Dialog1::on_openCamera_clicked()
{
    capture = VideoCapture(0);
    capture.set(CV_CAP_PROP_SETTINGS, 1);
    timer->start(33);
    if (!capture.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video file" << std::endl;
        return;
    }
}

void Dialog1::on_closeCamera_clicked()
{
    timer->stop();
    capture.release();
    ui->camFrameView->clear();
}

void Dialog1::on_lastStep_clicked()
{
    timer->stop();
    capture.release();
    ui->camFrameView->clear();
    this->close();

}
