// cmake . && make && ./lab2 ./D3300/img10.jpg
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

int main(int argn, char** argv) {

    //check params
    if (argn != 2) {
        cout << "usage: ./lab2 <path_of_folder_within_images>" << endl;
        return EXIT_FAILURE;
    }

    vector<boost::filesystem::path> images_path;
    //const string imgs_path = argv[1];

    const boost::filesystem::path p(argv[1]);  // avoid repeated path construction below

    if (boost::filesystem::exists(p)) {    // does path p actually exist?
        if (boost::filesystem::is_regular_file(p))        // is path p a regular file?
            cout << p << " size is " << boost::filesystem::file_size(p) << '\n';
        else if (is_directory(p))      // is path p a directory?
            cout << p << " is a directory\n";
        else
            cout << p << " exists, but is not a regular file or directory\n";
    }
    else
        cout << p << " does not exist\n";

    return 0;
    //calculate images chessboard corner and save in corners_vector
    Mat img = imread(argv[1]); //source path
    resize(img, img, Size(), 0.75, 0.75);
    
    Size patternsize(12,8); //INTERIOR number of corners (y, x)
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