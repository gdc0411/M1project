#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));
    //ui->nextLoop->setVisible(false);
    ui->openCamera_2->setVisible(false);
    ui->camFrameView->setVisible(false);
}

Dialog1::~Dialog1()
{
    delete ui;
//    timer->stop();
//    capture.release();

}

void Dialog1::setRubikColor(RubikColor colors[])
{
    for(int i = 0; i < 9; i++)
        col[i] = colors[i];
}

void Dialog1::closeEvent(QCloseEvent *event)
{
    timer->stop();
    if(capture.isOpened())
        capture.release();
}

void Dialog1::readFrame()
{
    capture >> cvframe;
    cv::cvtColor(cvframe, cvframe, CV_BGR2RGB);
    //Mat->QImage
    QImage qimage = QImage((const uchar*)(cvframe.data), cvframe.cols, cvframe.rows, QImage::Format_RGB888);
    qimage = qimage.scaled(ui->camFrameView->size(),Qt::KeepAspectRatio);
    //put qimage to label
    ui->camFrameView->setPixmap(QPixmap::fromImage(qimage));
}

void Dialog1::on_openCamera_clicked()
{
    colors = rob.launchCapture();
    ui->currentSideLabel->setColors(colors);
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

void Dialog1::on_lastStep_clicked()
{
    ui->camFrameView->setVisible(false);
    //ui->nextLoop->setVisible(false);
    ui->openCamera_2->setVisible(false);
    ui->currentSideLabel->setVisible(true);
    ui->openCamera->setVisible(true);
    ui->nextStep->setVisible(true);
    if(capture.isOpened())
    {
        capture.release();
        timer->stop();
        ui->camFrameView->clear();
    }
    this->close();
}

void Dialog1::on_nextStep_clicked()
{
    ui->camFrameView->setVisible(false);
    //ui->nextLoop->setVisible(true);
    ui->openCamera_2->setVisible(false);
    ui->currentSideLabel->setVisible(false);
    ui->openCamera->setVisible(false);
    ui->nextStep->setVisible(false);

}

void Dialog1::on_openCamera_2_clicked()
{
    capture = VideoCapture(0);
    //capture.set(CV_CAP_PROP_SETTINGS, 1);
    if (!capture.isOpened())  // if not success, exit program
    {
        qDebug() << "Cannot open the video file";
        return;
    }
    timer->start(33);

}

void Dialog1::on_runRobot_clicked()
{
    Rubik r(colors);

    r.resolve(col, &rob);

    rob.sendRubikMoves(r.getMoves());

    rob.printSimplifiedSentRobotMoves();
}
