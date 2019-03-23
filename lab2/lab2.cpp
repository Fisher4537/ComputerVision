#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
using namespace cv;
using namespace std;

int main(int argn, char** argv) {
    Mat img = imread(argv[1]); //source image
    cv::resize(img, img, cv::Size(), 0.75, 0.75);
    
    Size patternsize(12,8); //interior number of corners
    vector<Point2f> corners; //this will be filled by the detected corners

    //CALIB_CB_FAST_CHECK saves a lot of time on images
    //that do not contain any chessboard corners
    bool patternfound = findChessboardCorners(img, patternsize, corners,
            CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
            + CALIB_CB_FAST_CHECK);

    if(patternfound) {
        cout << "found corners..." << endl;
        //cornerSubPix(img, corners, Size(11, 11), Size(-1, -1),
        //        TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    } else {
        cout << "pattern not found..." << endl;
    }

    drawChessboardCorners(img, patternsize, Mat(corners), patternfound);
    namedWindow("Example 1");
    //setMouseCallback("Example 1", MouseFunc, void *userdata);
    imshow ("Example 1", img);
    waitKey(0);
    return 0;
}