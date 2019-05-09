#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filter.h"

// constructor
Filter::Filter(cv::Mat input_img, int size) {

    input_image = input_img;
    if (size % 2 == 0)
        size++;
    filter_size = size;
}

// for base class do nothing (in derived classes it performs the corresponding filter)
void Filter::doFilter() {

    // it just returns a copy of the input image
    result_image = input_image.clone();

}

// get output of the filter
cv::Mat Filter::getResult() {

    return result_image;
}

//set window size (it needs to be odd)
void Filter::setSize(int size) {

    if (size % 2 == 0)
        size++;
    filter_size = size;
}

//get window size 
int Filter::getSize() {

    return filter_size;
}

/**
 * @brief Construct a new Median Filter:: Median Filter object
 * call of cv::medianBlur() method. 
 * 
 * @param img 
 * @param size 
 */
MedianFilter::MedianFilter(cv::Mat img, int size)
: Filter(img, size) 
{}

void MedianFilter::doFilter()
{
    cv::medianBlur(input_image, result_image, filter_size);
}

/**
 * @brief Construct a new Gaussian Filter:: Gaussian Filter object
 * call of cv::GaussianBlur() method. 
 * 
 * @param img 
 * @param size 
 * @param std 
 */
GaussianFilter::GaussianFilter(cv::Mat img, int size, double std)
: Filter(img, size), sigma(std)
{}

void GaussianFilter::doFilter()
{
    cv::GaussianBlur(input_image, result_image, cv::Size(filter_size, filter_size), sigma, sigma);
}

/**
 * @brief Construct a new Bilateral Filter:: Bilateral Filter object
 * call of cv::bilateralFilter() method. 
 * 
 * @param img 
 * @param size 
 * @param sr 
 * @param ss 
 */
BilateralFilter::BilateralFilter(cv::Mat img, int size, double sr, double ss)
: Filter(img, size), sigma_range(sr), sigma_space(ss)
{}

void BilateralFilter::doFilter()
{
    cv::bilateralFilter(input_image, result_image, filter_size, sigma_range, sigma_space);
}

/**
int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        throw "usage: ./filter <img_path>";
    }
    cv::Mat img = cv::imread(argv[1]);

    MedianFilter mf(img, 3);
    mf.doFilter();
    cv::namedWindow("original img", cv::WINDOW_NORMAL);
    cv::imshow("original img", img);
    cv::namedWindow("result img", cv::WINDOW_NORMAL);
    cv::imshow("result img", mf.getResult());
    cv::waitKey(0);

    GaussianFilter gf(img, 3, 0.5);
    gf.doFilter();
    // cv::namedWindow("original img", cv::WINDOW_NORMAL);
    // cv::imshow("original img", img);
    cv::namedWindow("gaussian img", cv::WINDOW_NORMAL);
    cv::imshow("gaussian img", gf.getResult());

    cv::waitKey(0);

    BilateralFilter bf(img, 3, 12, 60);
    bf.doFilter();
    // cv::namedWindow("original img", cv::WINDOW_NORMAL);
    // cv::imshow("original img", img);
    cv::namedWindow("BilateralFilter img", cv::WINDOW_NORMAL);
    cv::imshow("BilateralFilter img", bf.getResult());

    cv::waitKey(0);
    return 0;
}
*/
