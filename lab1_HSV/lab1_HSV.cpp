#include <opencv2/highgui.hpp>
#include <iostream>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

/**
 * @brief check if value is in (mean-range, mean+range)
 * 
 * @param value the int to evaluate
 * @param mean int, the mean of the interval
 * @param range int the distance from the mean to define the interval
 * @return true if value is value from 0 to 255 included and in (mean-range, mean+range)
 * @return false the other way
 */
bool check_range(int value, int mean, int range);

/**
 * @brief verify if the v3b pixel has a color that must be changed
 * 
 * @param v3b pixel value
 * @param bias distance from the mean
 */
bool change_condition(Vec3b v3b, int bias);

int main(int argc, char** argv) {
    if (argc != 2)
    {
        std::cout << "usage: ./lab1_HSV <img_path>" << std::endl;
    }

    Mat img = imread(argv[1]);
    const float IMG_WIDTH=1092.0;
    const float IMG_HEIGHT=614.0;
    const float resize_factor = min(IMG_WIDTH/img.cols, IMG_HEIGHT/img.rows);
    resize(img, img, Size(), resize_factor, resize_factor);

	Mat hsv;
    Vec3b intensity;
	cv::cvtColor(img, hsv, COLOR_BGR2HSV);

    for (int i = 0; i < hsv.size().width; ++i)
        for (int j = 0; j < hsv.size().height; ++j) {
            intensity = hsv.at<Vec3b> (Point(i, j));
            if (change_condition(intensity, 4)) {
                std::printf("change value of (%i, %i) (%i %i %i) ", i, j, intensity.val[0], intensity.val[1], intensity.val[2]);
                intensity.val[0] = (intensity.val[0] + 880);
                std::printf("to (%i %i %i)\n", intensity.val[0], intensity.val[1], intensity.val[2]);
                hsv.at<Vec3b>(Point(i,j)) = intensity;
            } else {
                //std::printf("change value of (%i, %i) (%i %i %i)\n", i, j, intensity.val[0], intensity.val[1], intensity.val[2]);
            }
        }
    
	cv::cvtColor(hsv, img, COLOR_HSV2BGR);
    namedWindow("Example 2");
    //setMouseCallback("Example 2", MouseFunc, void *userdata);
    imshow ("Example 2", img);
    waitKey(0);
    return 0;
}

bool change_condition(Vec3b v3b, int bias) {
    int h = 18;
    return check_range(v3b.val[0], h, bias);
}

bool check_range(int value, int mean, int range) {
    //std::printf("value, mean, range = %i %i %i, condition = %i\n", value, mean, range, value < min(mean + range, 255) && value > max(mean - range, 0));
    return value <= (mean + range) % 360 && value >= (mean - range) % 360;
}
