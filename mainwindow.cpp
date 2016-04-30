#include "mainwindow.h"
#include "ui_mainwindow.h"

std::vector<QColor> colorTable_main{ Qt::white, Qt::green, Qt::red, Qt::blue, QColor(255,88,0), Qt::yellow };
std::vector<QColor> colorTable_cube{ Qt::white, QColor(57,193,72), QColor(255,38,0), QColor(37,50,255), QColor(255,163,50), QColor(255,251,10) };


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
    //qDebug()<<"filename:"<<filename;filename.toLocal8Bit().data();
    ui->pathLabel->setText(filename);
    if(!filename.isEmpty())
    {
        image_origin = cv::imread(filename.toLocal8Bit().data());
        cv::cvtColor(image_origin, image, CV_BGR2RGB);
        QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows, image.cols*image.channels(),  QImage::Format_RGB888);
        QImage imgScaled = img.scaled(ui->picLabel->size(),Qt::KeepAspectRatio);//图像自适应label大小
        ui->picLabel->clear();
        ui->picLabelUp->clear();
        ui->picLabel->setPixmap(QPixmap::fromImage(imgScaled));
    }
}

void MainWindow::on_divideButton_clicked()
{
    cubeRow = ui->cubeRow->value();
    cubeCol = ui->cubeCol->value();
    if(cubeRow*cubeCol >= 4 && !filename.isEmpty() && image_origin.rows >= cubeRow*3 && image_origin.cols >= cubeCol*3)
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
            scale = image_origin.cols/(cubeCol*3);//img size devide cube's totol col
            fixedRow = scale*cubeRow*3;//set the size corresponding cube's
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

        //qDebug()<<"scale:"<<scale<<" row:"<<fixedRow<<" col:"<<fixedCol<<" Original resolution:"<<image_origin.rows<<image_origin.cols<<" remove:"<<removeRows<<removeCols;

        int removeRows_top,removeRows_down,removeCols_left,removeCols_right;
        if(removeRows%2 != 0)//the remove num of rows is not even number
        {
            //up need remove one more than down
            removeRows_top = removeRows/2 + 1;
            removeRows_down = removeRows/2;
        }
        else
            removeRows_top = removeRows_down = removeRows/2;
        if(removeCols%2 != 0)//the remove num of cols is not even number
        {
            //left need remove one more than right
            removeCols_left = removeCols/2 + 1;
            removeCols_right = removeCols/2;
        }
        else
            removeCols_left = removeCols_right = removeCols/2;

        //qDebug()<<"removeRow_fixed:"<<removeRows_top<<removeRows_down<<"removeCol_fixed:"<<removeCols_left<<removeCols_right;
        cv::Mat fixedImage = image_origin(Rect(removeCols_left,removeRows_top,fixedCol,fixedRow));//改好大小的图片

        //resize the image
        cv::Size dsize = cv::Size(cubeCol*3,cubeRow*3);//Image resolution of the match cube ratio
        //cv::Mat image_resize = fixedImage;

        cv::resize(fixedImage, image_resize, dsize);
        image_resize = changeRubixColor(image_resize);
        cv::cvtColor(image_resize, image_resize, CV_BGR2RGB);
        //image_resize---->this is what we want!!!!
        QImage QimgResize = QImage((const unsigned char*)(image_resize.data),image_resize.cols,image_resize.rows, image_resize.cols*image_resize.channels(),  QImage::Format_RGB888);
        //qDebug() << "QimgResizeRect:" << QimgResize.rect();
        ui->picLabel->clear();
        imgScaled = QimgResize.scaled(ui->picLabel->size(),Qt::KeepAspectRatio);
        //qDebug() << "imgScaledRect:" << imgScaled.rect();
        ui->picLabel->setPixmap(QPixmap::fromImage(imgScaled));//image insert into label

        /*--------------------------drawing grids----------------------------*/
        QPicture picture;
        QPainter painter;
        QPen pen_thick,pen_thin;
        pen_thick.setWidth(3);
        pen_thick.setColor(Qt::gray);
        pen_thin.setWidth(1);
        pen_thin.setColor(Qt::gray);
        painter.begin(&picture);
        picture.setBoundingRect(imgScaled.rect()); //set the boundary of painting

        //draw col line
        painter.setPen(pen_thin);
        for(int i = 0; i <= cubeCol*3; i++)
            painter.drawLine(QLineF((float)imgScaled.rect().width()/cubeCol/3.0*i, 0, (float)imgScaled.rect().width()/cubeCol/3.0*i, imgScaled.rect().height()));
        painter.setPen(pen_thick);
        for(int i = 0; i <= cubeCol; i++)
            painter.drawLine(QLineF((float)imgScaled.rect().width()/cubeCol*i, 0, (float)imgScaled.rect().width()/cubeCol*i, imgScaled.rect().height()));
        //draw row line
        painter.setPen(pen_thin);
        for(int i = 0; i <= cubeRow*3; i++)
            painter.drawLine(QLineF(0, (float)imgScaled.rect().height()/cubeRow/3.0*i, imgScaled.rect().width(), (float)imgScaled.rect().height()/cubeRow/3.0*i));
        painter.setPen(pen_thick);
        for(int i = 0; i <= cubeRow; i++)
            painter.drawLine(QLineF(0, (float)imgScaled.rect().height()/cubeRow*i, imgScaled.rect().width(), (float)imgScaled.rect().height()/cubeRow*i));

        painter.end();
        picture.save("draw_record.pic");
        ui->picLabelUp->setPicture(picture);
    }
    else if(cubeRow*cubeCol < 4)
    {
        int ret = QMessageBox::warning(this, "Warning", "The number of cubes is at least four!", QMessageBox::Abort);
        if (ret == QMessageBox::Abort)
            qDebug() << "WARNING!!";
    }
    else if(filename.isEmpty())
    {
        int ret = QMessageBox::warning(this, "Warning", "You need choose an image file!", QMessageBox::Abort);
        if (ret == QMessageBox::Abort)
            qDebug() << "WARNING!!";
    }
    else if(image_origin.rows < cubeRow*3 || image_origin.cols < cubeCol*3)
    {
        int ret = QMessageBox::warning(this, "Warning", "Too many cubes!", QMessageBox::Abort);
        if (ret == QMessageBox::Abort)
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

void MainWindow::on_scanButton_clicked()
{
    this->hide();
    dlg.show();
    dlg.exec();
    this->show();
}

void MainWindow::on_rmGridsButton_clicked()
{
    ui->picLabelUp->clear();
}

void MainWindow::on_chooseCube_editingFinished()
{
    ui->divideButton->clicked();
    ui->picLabelRoi->clear();
    int num_cube = ui->chooseCube->value();
    if(num_cube > 0 && num_cube <= cubeRow * cubeCol)
    {
        //find cube in pic
        int num_row = (num_cube - 1) / cubeCol;//start at 0
        int num_col = (num_cube - 1) % cubeCol; // start at 0
        //qDebug() << "row,col:" << num_row << num_col;
        chooseCubeColor = image_resize(cv::Rect(num_col*3,num_row*3,3,3));//cube what we choose

//        //painting roi
//        float multiple = (float)imgScaled.width() / (float)image_resize.size().width;
//        QPicture picture0;
//        QPainter painter0;
//        QPen pen_roi;
//        pen_roi.setColor(Qt::red);
//        pen_roi.setWidth(2);
//        painter0.begin(&picture0);
//        painter0.setPen(pen_roi);
//        //painting red Roi
//        painter0.drawRect(QRectF(num_col*3*multiple,num_row*3*multiple,3*multiple,3*multiple));
//        //qDebug() << QRectF(num_col*3*multiple,num_row*3*multiple,3*multiple,3*multiple);
//        painter0.end();
//        picture0.save("draw_roi.pic");
//        ui->picLabelRoi->setPicture(picture0);


        //painting cube
        QPicture picture;
        QPainter painter;
        QPen pen_cube;
        pen_cube.setColor(Qt::black);
        pen_cube.setWidth(2);
        painter.begin(&picture);
        painter.setPen(pen_cube);
        QBrush brush(Qt::SolidPattern);

        //painting choose cube
        int block_size = 40;
        for(int i = 0; i < 9; i++)
        {
            //qDebug() << "RGB:" << chooseCubeColor.at<Vec3b>(i/3,i%3).val[0]<<chooseCubeColor.at<Vec3b>(i/3,i%3).val[1]<<chooseCubeColor.at<Vec3b>(i/3,i%3).val[2];
            brush.setColor(QColor(chooseCubeColor.at<Vec3b>(i/3,i%3).val[0],chooseCubeColor.at<Vec3b>(i/3,i%3).val[1],chooseCubeColor.at<Vec3b>(i/3,i%3).val[2]));//RGB 3 channels
            painter.setBrush(brush);
            painter.drawRoundRect(QRect(block_size*i%(block_size*3),block_size*(i/3),block_size,block_size));
        }
        painter.end();
        picture.save("draw_cube.pic");
        ui->showCubeChoose->setPicture(picture);

        //store colors of cube
        for(int i = 0; i < 9; i++)
        {
            QColor qcolor = QColor(chooseCubeColor.at<Vec3b>(i/3,i%3).val[0],chooseCubeColor.at<Vec3b>(i/3,i%3).val[1],chooseCubeColor.at<Vec3b>(i/3,i%3).val[2]);//RGB 3 channels
            int color_num;
            if(qcolor == colorTable_cube[0])
                color_num = 0;
            else if(qcolor == colorTable_cube[1])
                color_num = 1;
            else if(qcolor == colorTable_cube[2])
                color_num = 2;
            else if(qcolor == colorTable_cube[3])
                color_num = 3;
            else if(qcolor == colorTable_cube[4])
                color_num = 4;
            else if(qcolor == colorTable_cube[5])
                color_num = 5;
            else
                color_num = -1;
            col[i] = RubikColor(color_num);
            //qDebug() << "color:" << color_num;
        }
        dlg.setRubikColor(col);
    }
    else
    {
        int ret = QMessageBox::warning(this, "Warning", "Please choose the cube you want to make!", QMessageBox::Abort);
        if (ret == QMessageBox::Abort)
            qDebug() << "WARNING!!";
    }

}
