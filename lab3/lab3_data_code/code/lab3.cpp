
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void showHistogram(std::vector<cv::Mat>& );
void computeHistograms(Mat &img, vector<Mat> &hists);
void showHistAndImg(Mat &img, string title);
void cvtAndEq(Mat &img, Mat &out, int codeConv, int invCodeConv, int chSize, vector<int> chToEq);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        throw "usage: ./lab3 <img_path>";
    }
    Mat img = cv::imread(argv[1]);  // load the image
    
    // show original image and histograms for each channel
    showHistAndImg(img, "Original image and histograms");

    // show BGR equalized image and histograms for each channel
    vector<Mat> splitImg;
    vector<Mat> eqSplitImg(3);

    split(img, splitImg);
    equalizeHist(splitImg[0], eqSplitImg[0]);
    equalizeHist(splitImg[1], eqSplitImg[1]);
    equalizeHist(splitImg[2], eqSplitImg[2]);

    Mat eqImg;
    merge(eqSplitImg, eqImg);
    showHistAndImg(eqImg, "BGR colorspace equalization");

    // show Lab equalized image and histograms for each channel
    Mat labEqImg;
    vector<int> chToEq{0};  // equalize only channel 0 (Lightness)
    cvtAndEq(img, labEqImg, COLOR_BGR2Lab, COLOR_Lab2BGR, 3, chToEq);
    showHistAndImg(labEqImg, "Lab colorspace equalization");

    // show HSV equalized image and histograms for each channel
    Mat hsvEqImg;
    vector<int> chToEq_{2};  // equalize only channel 2 (Value)
    cvtAndEq(img, hsvEqImg, COLOR_BGR2HSV, COLOR_HSV2BGR, 3, chToEq_);
    showHistAndImg(hsvEqImg, "HSV colorspace equalization");

    return 0;
}

void cvtAndEq(Mat &img, Mat &out, int codeConv, int invCodeConv, int chSize, vector<int> chToEq) {
    Mat cvtImg;  // color converted image
    cvtColor(img, cvtImg, codeConv);    
    vector<Mat> splitImg;  // splitted image
    split(cvtImg, splitImg);
    
    // equalize only specified channels
    vector<Mat> eqSplitImg(3);  // vector with eq channels
    for (int i = 0; i < chSize; i++) 
        if ( find(chToEq.begin(), chToEq.end(), i) != chToEq.end() )
            equalizeHist(splitImg[i], eqSplitImg[i]);
        else
            eqSplitImg[i] = splitImg[i];
    
    Mat eqImg;  // equalized image in color converted space
    merge(eqSplitImg, eqImg);
    cvtColor(eqImg, out, invCodeConv);
    
}

void showHistAndImg(Mat &img, string title="img") {
    vector<Mat> hists;
    computeHistograms(img, hists);
    showHistogram(hists);
    namedWindow(title, WINDOW_NORMAL);
    string barTitle = "bar title";
    int initBarValue = 10;
    int maxBarValue = 100;
    createTrackbar(barTitle, title, &initBarValue, maxBarValue);
    imshow(title, img);
    waitKey(0);
    destroyAllWindows();
}

void computeHistograms(Mat &img, vector<Mat> &hists) {
    vector<Mat> bgr;  // destination vector
    split(img,bgr);  // split source in B, G and R channel

    const int channels[] = {0, 1, 2};  // channels to analize

    Mat b_hist, g_hist, r_hist;  // histograms

    int histSize = 256;  // histograms size

    float range[] = {0, 256};
    const float* ranges = {range};  // blue, green and red ranges

    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &ranges, true, false);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &ranges, true, false);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &ranges, true, false);

    hists = {b_hist,g_hist,r_hist};
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