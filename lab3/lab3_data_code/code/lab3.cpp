#include <stdio.h>
#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/utils/filesystem.hpp>

using namespace cv;
using namespace std;

void showHistogram(std::vector<cv::Mat>& );

/**
 * show image with a title, can be resize.
*/
void show_img(Mat &img, 
                const string TITLE="Image", 
                const float IMG_WIDTH=1092.0,   // 80% of my screen width
                const float IMG_HEIGHT=614.0);  // 80% of my screen height


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        throw "usage: ./lab3 <img_path>";
    }
    Mat img = cv::imread(argv[1]);  // load the image
    vector<Mat> bgr;                // destination vector
    split(img,bgr);                 // split source in B, G and R channel

    const int channels[] = {0, 1, 2};    // channels to analize

    Mat b_hist, g_hist, r_hist;      // histograms

    int histSize = 256;   //histograms size

    float range[] = {0, 256};
    const float* ranges = {range};   // blue, green and red ranges

    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &ranges, true, false);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &ranges, true, false);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &ranges, true, false);

    std::vector<cv::Mat> hists{b_hist,g_hist,r_hist};

    // show original image and histograms
    showHistogram(hists);
    namedWindow("image", WINDOW_NORMAL);
    imshow("image", img);
    namedWindow("blue_histogram", WINDOW_NORMAL);
    imshow("blue_histogram", b_hist);
    namedWindow("green_histogram", WINDOW_NORMAL);
    imshow("green_histogram", g_hist);
    namedWindow("red_histogram", WINDOW_NORMAL);
    imshow("red_histogram", r_hist);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

// hists = vector of 3 cv::mat of size nbins=256 with the 3 histograms
// e.g.: hists[0] = cv:mat of size 256 with the red histogram
//       hists[1] = cv:mat of size 256 with the green histogram
//       hists[2] = cv:mat of size 256 with the blue histogram
void showHistogram(std::vector<cv::Mat>& hists)
{
    // Min/Max computation
    double hmax[3] = {0,0,0};
    double min;
    cv::minMaxLoc(hists[0], &min, &hmax[0]);
    cv::minMaxLoc(hists[1], &min, &hmax[1]);
    cv::minMaxLoc(hists[2], &min, &hmax[2]);

    std::string wname[3] = { "blue", "green", "red" };
    cv::Scalar colors[3] = { cv::Scalar(255,0,0), cv::Scalar(0,255,0),
                            cv::Scalar(0,0,255) };

    std::vector<cv::Mat> canvas(hists.size());

    // Display each histogram in a canvas
    for (int i = 0, end = hists.size(); i < end; i++)
    {
        canvas[i] = cv::Mat::ones(125, hists[0].rows, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < hists[0].rows-1; j++)
        {
            cv::line(
                    canvas[i],
                    cv::Point(j, rows),
                    cv::Point(j, rows - (hists[i].at<float>(j) * rows/hmax[i])),
                    hists.size() == 1 ? cv::Scalar(200,200,200) : colors[i],
                    1, 8, 0
                    );
        }

        cv::imshow(hists.size() == 1 ? "value" : wname[i], canvas[i]);
    }
}

void show_img(Mat &img, const string TITLE, const float IMG_WIDTH, const float IMG_HEIGHT) {
    if (IMG_WIDTH <= 0 || IMG_HEIGHT <=0 ) {
        throw "width and height of the output images must be grater than 0";
    }
    const float resize_factor = min(IMG_WIDTH/img.cols, IMG_HEIGHT/img.rows);
    Mat resized_img;
    // debug cout<<TITLE<<" (img.cols, img.rows) = ("<<img.cols<<", "<<img.rows<<")"<<endl;
    resize(img, resized_img, Size(), resize_factor, resize_factor);
    namedWindow(TITLE);
    imshow (TITLE, resized_img);
    waitKey(0);
    destroyWindow(TITLE);
}