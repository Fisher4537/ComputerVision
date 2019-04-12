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
        cout << "usage: ./lab2 <path_of_directory_within_images>" << endl;
        return EXIT_FAILURE;
    }

    // check if dir exists else
    const cv::String path(argc>1 ? argv[1] : ".");    // path of directory with images
    if (!cv::utils::fs::exists(path)) {
        cout << "specified path does not exist: " << path << endl;
        return EXIT_FAILURE;
    } else {
        cout << "looking for images in " << path << endl;
    }
    vector<cv::String> fn;                      // path list
    cv::glob(path,fn,false);                    // get files list false = recursive,
    int numBoards = fn.size();                  // number of boards is the number of file in the specified dir
    int numCornersHor;                          // number of corners per column
    int numCornersVer;                          // number of corners per row

    // get input params
    printf("Enter number of corners along width: ");
    scanf("%d", &numCornersHor);

    printf("Enter number of corners along height: ");
    scanf("%d", &numCornersVer);

    int numSquares = numCornersHor * numCornersVer; // number of corners in each images

    vector<vector<Point2f>> corners;            // this will be filled by the detected corners
    vector<vector<Point3f>> objectPoints;       // 3D relative position of the points in the space
    vector<Size> imgs_size;                     // size of the images

    // set relative points position in the space.
    vector<Point3f> obj;
    for(int j=0;j<numSquares;j++)
        obj.push_back(Point3f(j/numCornersHor, j%numCornersHor, 0.0f));

    /**
     * for each image, save:
     * the relative point position in the space,
     * the founded corners,
     * the image size.
    */
    for (int i = 0; i < numBoards; i++) {
        objectPoints.push_back(obj);
        corners.push_back(get_corners(fn[i]));
        Mat img = cv::imread(fn[i]);
        imgs_size.push_back(img.size());
    }

    // calibrate camera
    Mat intrinsic = Mat(3, 3, CV_32FC1); // filled by calibrateCamera, rapresents intrinsic parameters 
    intrinsic.ptr<float>(0)[0] = 1;      // initialization value if no changes are required
    intrinsic.ptr<float>(1)[1] = 1;

    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);      // filled by calibrateCamera, 
    Size board_sz = Size(numCornersHor, numCornersVer); // size of the board
    vector<Mat> rvecs;          // Output vector of rotation vectors estimated for each pattern view
    vector<Mat> tvecs;          // Output vector of translation vectors estimated for each pattern view

    double rms = cv::calibrateCamera(objectPoints, corners, imgs_size[0], intrinsic, distCoeffs, rvecs, tvecs);

    // print  the output
    cout << "calibrateCamera return: " << rms << endl;
    cout << "intrinsicFactor = "<< endl << " "  << intrinsic << endl << endl;
    cout << "distCoeffs = "<< endl << " "  << distCoeffs << endl << endl;

}
// cmake . && make && ./lab2 D3300 >> D3300_ouput.txt 