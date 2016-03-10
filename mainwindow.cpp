#include "mainwindow.h"
#include "ui_mainwindow.h"

cv::Mat convertToRubiks(cv::Mat img, cv::Mat palette);
cv::Vec3b closestPaletteColor(cv::Vec3b color, cv::Mat palette);
cv::Mat changeRubixColor(cv::Mat _image);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pathLabel->setWordWrap(true);
    ui->pathLabel->setAlignment(Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFile_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("Open File"),"D:",tr("Image(*.jpg *.jpeg *.png *.gif *.bmp *.tiff)"));
    qDebug()<<"filename:"<<filename;filename.toLocal8Bit().data();
    ui->pathLabel->setText(filename);
    if(!filename.isEmpty())
    {
        image_origin = cv::imread(filename.toLocal8Bit().data());
        cv::cvtColor(image_origin, image, CV_BGR2RGB);
        Qimage = new QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
        QImage imgScaled = Qimage->scaled(ui->picLabel->size(),Qt::KeepAspectRatio);//图像自适应label大小
        ui->picLabel->setPixmap(QPixmap::fromImage(imgScaled));//图像插入label
    }
}

void MainWindow::on_divideButton_clicked()
{
    cubeRow = ui->cubeRow->value();
    cubeCol = ui->cubeCol->value();
    if(cubeRow*cubeCol >= 4 && !filename.isEmpty())
    {
        //I. divide image
        //1.prepare
        //int largeSquare = (int)floor(sqrt(cubeNum));//get the largest square that can be made
        //qDebug() << "largeSquare:" <<largeSquare;
        float picRatio = (float)image_origin.rows / (float)image_origin.cols;//row行数col列数
        //qDebug() << "picRatio:" <<picRatio;
        float cubeRatio = (float)cubeRow / (float)cubeCol;
        int scale, fixedCol, fixedRow;
        if(picRatio >= cubeRatio)//row long
        {
            scale = image_origin.cols/(cubeCol*3);//图像大小和魔方之比,整除
            fixedRow = scale*cubeRow*3;//为了获得魔方列整数倍
            fixedCol = scale*cubeCol*3;
        }
        else//col long
        {
            scale = image_origin.rows/(cubeRow*3);
            fixedRow = scale*cubeRow*3;
            fixedCol = scale*cubeCol*3;
        }
        int removeRows = image_origin.rows - fixedRow;
        int removeCols = image_origin.cols - fixedCol;

        qDebug()<<"scale:"<<scale<<" row:"<<fixedRow<<" col:"<<fixedCol<<" Original resolution:"<<image_origin.rows<<image_origin.cols<<" remove:"<<removeRows<<removeCols;

        int removeRows_top,removeRows_down,removeCols_left,removeCols_right;
        if(removeRows%2 != 0)//行删除量不是偶数
        {
            //上比下多删1
            removeRows_top = removeRows/2 + 1;
            removeRows_down = removeRows/2;
        }
        else
            removeRows_top = removeRows_down = removeRows/2;
        if(removeCols%2 != 0)//列删除量不是偶数
        {
            //左比右多删1
            removeCols_left = removeCols/2 + 1;
            removeCols_right = removeCols/2;
        }
        else
            removeCols_left = removeCols_right = removeCols/2;

        qDebug()<<"removeRow_fixed:"<<removeRows_top<<removeRows_down<<"removeCol_fixed:"<<removeCols_left<<removeCols_right;
        cv::Mat fixedImage = image_origin(Rect(removeCols_left,removeRows_top,fixedCol,fixedRow));//改好大小的图片

        //resize the image
        cv::Size dsize = cv::Size(cubeCol*3,cubeRow*3);//Image resolution of the match cube ratio
        //cv::Mat image_resize = fixedImage;
        cv::Mat image_resize;
        cv::resize(fixedImage, image_resize, dsize);
        image_resize = changeRubixColor(image_resize);
        cv::cvtColor(image_resize, image_resize, CV_BGR2RGB);
        Qimage= new QImage((const unsigned char*)(image_resize.data), image_resize.cols, image_resize.rows, QImage::Format_RGB888);
        QImage imgScaled = Qimage->scaled(ui->picLabel->size(),Qt::KeepAspectRatio);//图像自适应label大小
        ui->picLabel->setPixmap(QPixmap::fromImage(imgScaled));//图像插入label
    }
    else if(cubeRow*cubeCol < 4)
    {
        int ret1 = QMessageBox::warning(this, "Warning", "The number of cubes is at least four!", QMessageBox::Abort);
        if (ret1 == QMessageBox::Abort)
            qDebug() << "WARNING!!";
    }
    else if(filename.isEmpty())
    {
        int ret2 = QMessageBox::warning(this, "Warning", "You need choose an image file!", QMessageBox::Abort);
        if (ret2 == QMessageBox::Abort)
            qDebug() << "WARNING!!";
    }
}

cv::Mat convertToRubiks(cv::Mat imgOrig, cv::Mat palette)
{
    cv::Mat img = imgOrig.clone();
    cv::Mat resImg = img.clone();
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
        {
            cv::Vec3b newpixel = closestPaletteColor(img.at<Vec3b>(i, j), palette);
            resImg.at<Vec3b>(i, j) = newpixel;

            for (int k = 0; k<3; k++)
            {
                int quant_error = (int)img.at<cv::Vec3b>(i, j)[k] - newpixel[k];
                if (j + 1<img.cols)
                    img.at<cv::Vec3b>(i, j + 1)[k] = fmin(255, fmax(0, (int)img.at<cv::Vec3b>(i, j + 1)[k] + (7 * quant_error) / 16));
                if (i + 1 < img.rows && j - 1 >= 0)
                    img.at<cv::Vec3b>(i + 1, j - 1)[k] = fmin(255, fmax(0, (int)img.at<cv::Vec3b>(i + 1, j - 1)[k] + (3 * quant_error) / 16));
                if (i + 1 < img.rows)
                    img.at<cv::Vec3b>(i + 1, j)[k] = fmin(255, fmax(0, (int)img.at<cv::Vec3b>(i + 1, j)[k] + (5 * quant_error) / 16));
                if (i + 1 < img.rows && j + 1 < img.cols)
                    img.at<cv::Vec3b>(i + 1, j + 1)[k] = fmin(255, fmax(0, (int)img.at<cv::Vec3b>(i + 1, j + 1)[k] + (1 * quant_error) / 16));
            }
        }
    return resImg;
}

float vec3bDist(cv::Vec3b a, cv::Vec3b b)
{
    return sqrt(pow((float)a[0] - b[0], 2) + pow((float)a[1] - b[1], 2) + pow((float)a[2] - b[2], 2));
}

cv::Vec3b closestPaletteColor(cv::Vec3b color, cv::Mat palette)
{
    int i = 0;
    int minI = 0;
    cv::Vec3b diff = color - palette.at<Vec3b>(0);
    float minDistance = vec3bDist(color, palette.at<Vec3b>(0));
    for (int i = 0; i<palette.rows; i++)
    {
        float distance = vec3bDist(color, palette.at<Vec3b>(i));
        if (distance < minDistance)
        {
            minDistance = distance;
            minI = i;
        }
    }
    return palette.at<Vec3b>(minI);
}

cv::Mat changeRubixColor(cv::Mat _image)
{
    int nrColors = 6;

    cv::Mat imgBGR = _image;
    cv::Mat img;
    cvtColor(imgBGR, img, CV_BGR2Lab);
    cv::Mat colVec = img.reshape(1, img.rows*img.cols);
    cv::Mat colVecD;
    colVec.convertTo(colVecD, CV_32FC3, 1.0);
    cv::Mat labels, centers;
    cv::kmeans(colVecD, nrColors, labels,
        cv::TermCriteria(CV_TERMCRIT_ITER, 100, 0.1),
        3, cv::KMEANS_PP_CENTERS, centers);
    cv::Mat imgPosterized = img.clone();
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
            for (int k = 0; k < 3; k++)
                imgPosterized.at<Vec3b>(i, j)[k] = centers.at<float>(labels.at<int>(j + img.cols*i), k);

    cv::Mat palette;
    centers.convertTo(palette, CV_8UC3, 1.0);
    palette.row(0).col(0) = 96 ;
    palette.row(0).col(1) = 194;
    palette.row(0).col(2) = 29;
    palette.row(1).col(0) = 255;
    palette.row(1).col(1) = 128;
    palette.row(1).col(2) = 128;
    palette.row(2).col(0) = 176;
    palette.row(2).col(1) =  68;
    palette.row(2).col(2) = 177;
    palette.row(3).col(0) = 140;
    palette.row(3).col(1) = 204;
    palette.row(3).col(2) = 196;
    palette.row(4).col(0) = 190;
    palette.row(4).col(1) = 154;
    palette.row(4).col(2) = 196;
    palette.row(5).col(0) = 245;
    palette.row(5).col(1) = 109;
    palette.row(5).col(2) = 221;

    cv::Mat fs = convertToRubiks(img, palette);

    cv::Mat imgPosterizedBGR, fsBGR;
    cvtColor(imgPosterized, imgPosterizedBGR, CV_Lab2BGR);
    cvtColor(fs, fsBGR, CV_Lab2BGR);
    return fsBGR;
}
