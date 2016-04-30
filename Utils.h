#ifndef UTILS_HEADER
#define UTILS_HEADER	

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "RubikColor.h"
#include "RobotPositionException.h"

using cv::Scalar;
using cv::String;
using cv::Rect;
using cv::VideoCapture;
using cv::Mat;
using cv::Vec4i;

struct SquareRubik{
	Rect rect;
	cv::Point2f position;
	RubikColor color;

	SquareRubik(Rect rec, cv::Point2f point, RubikColor col) : rect(rec), position(point), color(col) {}
};

#endif