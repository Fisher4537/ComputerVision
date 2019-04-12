#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core/utils/filesystem.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

vector<Point2f> get_corners(cv::String path_to_img) { 
    Mat img = imread(path_to_img); //source path
    //resize(img, img, Size(), 0.75, 0.75);
    
    Size patternsize(12,8); //INTERIOR number of corners (y, x)
    vector<Point2f> corners; //this will be filled by the detected corners

    //CALIB_CB_FAST_CHECK saves a lot of time on images
    //that do not contain any chessboard corners
    bool patternfound = findChessboardCorners(img, patternsize, corners,
            CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
    drawChessboardCorners(img, patternsize, Mat(corners), patternfound);
    namedWindow("Example 1");
    //setMouseCallback("Example 1", MouseFunc, void *userdata);
    imshow ("Example 1", img);
    waitKey(0);
    return corners;
}

int main(int argc, char** argv) {

    //check params
    if (argc != 2) {
        cout << "usage: ./lab2 <path_of_folder_within_images>" << endl;
        return EXIT_FAILURE;
    }
    const cv::String path(argc>1 ? argv[1] : ".");    // path of directory with images
    if (!cv::utils::fs::exists(path)) {
        cout << "specified path does not exist: " << path << endl;
    }
    vector<cv::String> fn;                      // path list
    cv::glob(path,fn,false);              // get files list false1 = recursive, false2 = include directory
    vector<vector<Point2f>> corners;            // this will be filled by the detected corners

    // const boost::filesystem::path p(argc>1 ? argv[1] : ".");  // avoid repeated path construction below
    for (int i = 0; i < fn.size(); i++) {
        corners.push_back(get_corners(fn[i]));
    }
    
}
// cmake . && make && ./lab2 ./D3300/img10.jpg