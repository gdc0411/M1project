#ifndef UTILS_HEADER
#define UTILS_HEADER	

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

enum ColorRubik{
	white = 0,
	green = 1,
	red = 2,
	blue = 3,
	orange = 4,
	yellow = 5
};

struct SquareRubik{
	Point2f position;
	ColorRubik color;

	SquareRubik(Point2f point, ColorRubik col) : position(point), color(col) {}
};

#endif
