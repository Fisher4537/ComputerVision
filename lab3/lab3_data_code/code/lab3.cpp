
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "filter.cpp"

using namespace cv;
using namespace std;

Mat currentImage;       // image to be filter
string currentTitle;    // title of the dispayed window
//Filter currentFilter;

// max value applied to the filter
const int sizeMaxValue = 100;
const int sigmaMaxValue = 10;
const int colorMaxValue = 255;
const int spaceMaxValue = 100;

// max value in the trackbar
const int sizeSliderMax = sizeMaxValue;
const int sigmaSliderMax = 100;
const int colorSliderMax = 255;
const int spaceSliderMax = 100;

// current value of slider in the trackbar
int sizeSlider = 0;
int colorSlider = 0;
int spaceSlider = 0;
int sigmaSlider = 0;

// title of the trackbar
const string spaceBarTitle = "space";
const string colorBarTitle = "color";
const string sizeBarTitle = "ker size";
const string sigmaBarTitle = "sigma";

// list of different filters
enum Filters { NOFILTER, MEDIAN, GAUSSIAN, BILATERAL};

// new methods
void showHistogram(std::vector<cv::Mat>& );
void computeHistograms(Mat &img, vector<Mat> &hists);
void showHistAndImg(Mat &img, string title);
void showHistAndImg(Mat &img, Filters filterType, string title);
void cvtAndEq(Mat &img, Mat &out, int codeConv, int invCodeConv, int chSize, vector<int> chToEq);

// callback functions
static void colorCallback(int iCurrentColor, void* userData);
static void spaceCallback(int iCurrentSpace, void* userData);
//static void sigmaCallback(int iCurrentSigma, void* userData);
static void sizeCallback(int iCurrentSize, void* userData);

int main(int argc, char** argv)
{
    // Check input param
    if (argc != 2)
    {
        throw "usage: ./lab3 <img_path>";
    }
    currentImage = cv::imread(argv[1]);     // analyzed image

    // show original image and histograms for each channel
    showHistAndImg(currentImage, MEDIAN,  "Original image and histograms MEDIAN filter");
    showHistAndImg(currentImage, GAUSSIAN,  "Original image and histograms GAUSSIAN filter");
    showHistAndImg(currentImage, BILATERAL,  "Original image and histograms BILATERAL filter");
    

    // show BGR equalized image and histograms for each channel
    vector<Mat> splitImg;
    vector<Mat> eqSplitImg(3);

    cv::split(currentImage, splitImg);
    cv::equalizeHist(splitImg[0], eqSplitImg[0]);
    cv::equalizeHist(splitImg[1], eqSplitImg[1]);
    cv::equalizeHist(splitImg[2], eqSplitImg[2]);

    Mat eqImg;
    cv::merge(eqSplitImg, eqImg);
    showHistAndImg(eqImg, MEDIAN, "BGR colorspace equalization");
    showHistAndImg(eqImg, GAUSSIAN, "BGR colorspace equalization");
    showHistAndImg(eqImg, BILATERAL, "BGR colorspace equalization");

    // show Lab equalized image and histograms for each channel
    Mat labEqImg;
    vector<int> chToEq{0};  // equalize only channel 0 (Lightness)
    cvtAndEq(currentImage, labEqImg, COLOR_BGR2Lab, COLOR_Lab2BGR, 3, chToEq);
    showHistAndImg(labEqImg, GAUSSIAN, "Lab colorspace equalization");

    // show HSV equalized image and histograms for each channel
    Mat hsvEqImg;
    vector<int> chToEq_{2};  // equalize only channel 2 (Value)
    cvtAndEq(currentImage, hsvEqImg, COLOR_BGR2HSV, COLOR_HSV2BGR, 3, chToEq_);
    showHistAndImg(hsvEqImg, GAUSSIAN, "HSV colorspace equalization");

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

static void colorCallback(int iCurrentColor, void* userData)
{
    colorSlider = iCurrentColor;
    double dCurrentColor = (double)iCurrentColor;
    double dCurrentSpace = spaceMaxValue*(double)*(static_cast<int*>(userData))/(double)spaceSliderMax;
    cout << "dCurrentColor=" << dCurrentColor << " dCurrentSpace=" << dCurrentSpace << " currentSize=" << sizeSlider << endl;
    BilateralFilter currentFilter(currentImage, sizeSlider, dCurrentColor, dCurrentSpace);
    currentFilter.doFilter();
    Mat outImg = currentFilter.getResult();
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(outImg, hists);  
    showHistogram(hists);
    imshow(currentTitle, outImg);
}

static void spaceCallback(int iCurrentSpace, void* userData)
{
    spaceSlider = iCurrentSpace;
    double dCurrentSpace = spaceMaxValue*(double)iCurrentSpace/(double)spaceSliderMax;
    double dCurrentColor = (double)*(static_cast<int*>(userData));
    cout << "dCurrentColor=" << dCurrentColor << " dCurrentSpace=" << dCurrentSpace << " currentSize=" << sizeSlider << endl;
    BilateralFilter currentFilter(currentImage, sizeSlider, dCurrentColor, dCurrentSpace);
    currentFilter.doFilter();
    Mat outImg = currentFilter.getResult();
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(outImg, hists);  
    showHistogram(hists);
    imshow(currentTitle, outImg);
}


static void sigmaCallback(int iCurrentSigma, void* userData)
{
    sigmaSlider = iCurrentSigma;
    double dCurrentSigma = sigmaMaxValue * (double)iCurrentSigma / (double)sigmaSliderMax;
    cout << "dCurrentSize=" << sizeSlider << " dCurrentSigma=" << dCurrentSigma << endl;
    GaussianFilter currentFilter(currentImage, sizeSlider, dCurrentSigma);
    currentFilter.doFilter();
    Mat outImg = currentFilter.getResult();
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(outImg, hists);
    showHistogram(hists);
    cv::imshow(currentTitle, outImg);
}

static void sizeCallback(int iCurrentSize, void* userData)
{
    sizeSlider = iCurrentSize;
    Filters filterType = * (static_cast<Filters*>(userData));
    Mat outImg;
    switch (filterType)
    {
        case MEDIAN:
        {
            cout << "dCurrentSize=" << sizeSlider << endl;
            MedianFilter mf(currentImage, iCurrentSize);
            mf.doFilter();
            outImg = mf.getResult();
            break;
        }
        case GAUSSIAN:
        {
            cout << "dCurrentSize=" << sizeSlider << " dCurrentSigma=" << sigmaSlider << endl;
            double dcurrentSigma = sigmaMaxValue * (double)sigmaSlider / (double)sigmaSliderMax;
            GaussianFilter gf(currentImage, iCurrentSize, dcurrentSigma);
            gf.doFilter();
            outImg = gf.getResult();
            break;
        }
        case BILATERAL:
        {
            double dCurrentSpace = (double)spaceMaxValue * (double)spaceSlider / (double)spaceSliderMax;
            double dCurrentColor = (double)(colorSlider);
            cout << "dCurrentColor=" << dCurrentColor << " dCurrentSpace=" << dCurrentSpace << " currentSize=" << iCurrentSize << endl;
            BilateralFilter bf(currentImage, iCurrentSize, dCurrentColor, dCurrentSpace);
            bf.doFilter();
            outImg = bf.getResult();
            break;
        }
        default:
        {
            outImg = currentImage;
            break;
        }
    }
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(outImg, hists);  
    showHistogram(hists);
    cv::imshow(currentTitle, outImg);
}

void showHistAndImg(Mat &img, string title="img") {
    currentTitle = title;              // set title of the current image
    enum Filters test_filter = BILATERAL;
    namedWindow(currentTitle, WINDOW_NORMAL);
    cv::createTrackbar(spaceBarTitle, title, &spaceSlider, spaceSliderMax, spaceCallback, &colorSlider);
    cv::createTrackbar(colorBarTitle, title, &colorSlider, colorSliderMax, colorCallback, &spaceSlider);
    cv::createTrackbar(sizeBarTitle, title, &sizeSlider, sizeSliderMax, sizeCallback, &test_filter);
    //createTrackbar(colorBarTitle, title, &colorSlider, spaceSliderMax, colorCallback, &spaceSlider);
    cv::imshow(title, img);    
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(img, hists);  
    showHistogram(hists);
    cv::waitKey(0);

    cv::destroyAllWindows();
}

void showHistAndImg(Mat &img, Filters filterType, string title="img") {
    currentTitle = title;              // set title of the current image
    currentImage = img;
    namedWindow(currentTitle, WINDOW_NORMAL);
    switch (filterType)
    {
        case NOFILTER:
            /* no code */
            break;
        case MEDIAN:
        {
            createTrackbar(sizeBarTitle, title, &sizeSlider, sizeSliderMax, sizeCallback, &filterType);
            break;
        }
        case GAUSSIAN:
        {
            createTrackbar(sizeBarTitle, title, &sizeSlider, sizeSliderMax, sizeCallback, &filterType);
            createTrackbar(sigmaBarTitle, title, &sigmaSlider, sigmaSliderMax, sigmaCallback);
            break;
        }
        case BILATERAL:
        {
            createTrackbar(spaceBarTitle, title, &spaceSlider, spaceSliderMax, spaceCallback, &colorSlider);
            createTrackbar(colorBarTitle, title, &colorSlider, colorSliderMax, colorCallback, &spaceSlider);
            createTrackbar(sizeBarTitle, title, &sizeSlider, sizeSliderMax, sizeCallback, &filterType);
            break;
        }
        default:
            break;
    }
    
    vector<Mat> hists;                  // histograms of the image
    computeHistograms(currentImage, hists);  
    showHistogram(hists);
    imshow(currentTitle, currentImage);
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