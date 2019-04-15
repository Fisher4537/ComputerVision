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

/**
 * show image with a title, can be resize.
*/
void show_img(Mat &img, 
                const string TITLE="Image", 
                const float IMG_WIDTH=1092.0,   // 80% of my screen width
                const float IMG_HEIGHT=614.0);  // 80% of my screen height

/**
 * get the corners of the specified images
 * with default param CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK
 */
vector<Point2f> get_corners(Mat &img, Size patternsize);

/**
 * calculate the relative positions of 3D points in the checkboard images
 * with num_corners_cols columns and num_corners_rows rows,
 * the result vector can be passed like objectPoints to cv::calibrateCamers() method.
 */
vector<Point3f> get_object_points(int num_corners_cols, int num_corners_rows);

/**
 * command to compile and execute (you need CMakeLists.txt file)
 * $ cmake . && make && ./lab2 D3300 >> D3300_ouput.txt
 */
int main(int argc, char** argv) {

    //check params
    bool show_img_c = true; //default: show images
    if (argc < 2) {
        cout << "usage: ./lab2 <path_of_directory_within_images> [show_img]" << endl;
        return EXIT_FAILURE;
    } else if (argc < 3) {
        // nothing yet
    } else if (argc < 4) {
        if (strcmp(argv[2], "true") == 0) {
            show_img_c = true;
            cout << "argv[2] == " << argv[2] << endl;
        } else if (strcmp(argv[2], "false") == 0) {
            show_img_c = false;
            cout << "argv[2] == " << argv[2] << endl;
        } else {
            cout << "usage: ./lab2 <path_of_directory_within_images> [show_img]" << endl;
            return EXIT_FAILURE;
        }
    }

    // check if dir exists else
    const cv::String path(argv[1]);    // path of directory with images
    if (!cv::utils::fs::exists(path)) {
        cout << "specified path does not exist: " << path << endl;
        return EXIT_FAILURE;
    } else {
        cout << "looking for images in " << path << endl;
    }

    vector<cv::String> fn;          // path list
    cv::glob(path,fn,false);        // get files list false = recursively,
    int numBoards = fn.size();      // number of boards is the number of file in the specified dir
    int numCornersCols;              // number of corners per column
    int numCornersRows;              // number of corners per row

    // get input params
    printf("Enter number of corners along width: ");
    scanf("%d", &numCornersCols);
    printf("Enter number of corners along height: ");
    scanf("%d", &numCornersRows);

    Size pattern_size = Size(numCornersCols, numCornersRows);

    vector<vector<Point2f>> corners;            // this will be filled by the detected corners
    vector<vector<Point3f>> objectPoints;       // 3D relative position of the points in the space
    vector<Size> imgs_size;                     // size of the images

    // set relative points position in the space.
    vector<Point3f> obj = get_object_points(numCornersCols, numCornersRows);

    /**
     * for each image, get:
     * the relative point position in the space,
     * the founded corners,
     * the image size.
    */
    for (int i = 0; i < numBoards; i++) {
        objectPoints.push_back(obj);
        Mat img = cv::imread(fn[i]);    
        corners.push_back(get_corners(img, pattern_size));
        imgs_size.push_back(img.size());
    }

    // calibrate camera
    // intrinsic params are stored in a 3 by 3 matrix
    Mat intrinsic = Mat(3, 3, CV_32FC1); // filled by calibrateCamera, rapresents intrinsic params
    intrinsic.ptr<float>(0)[0] = 1;      // initialization value if no changes are required
    intrinsic.ptr<float>(1)[1] = 1;

    // distortion coefficients are 8 different vars
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);      // filled by calibrateCamera,
    Size board_sz = Size(numCornersCols, numCornersRows); // size of the board
    vector<Mat> rvecs;      // Output vector of rotation vectors estimated for each pattern view
    vector<Mat> tvecs;      // Output vector of translation vectors estimated for each pattern view

    double rms = cv::calibrateCamera(objectPoints, 
                                        corners, 
                                        imgs_size[0], 
                                        intrinsic, 
                                        distCoeffs, 
                                        rvecs, tvecs);

    // undistort each images
    for (int i = 0; i < fn.size(); i++) {
        Mat img = imread(fn[i]);
        Mat imageUndistorted;
        undistort(img, imageUndistorted, intrinsic, distCoeffs);
        if (show_img_c) {
            vector<Point2f> corners;
            bool patternfound =  findChessboardCorners(img, pattern_size, corners, 
                                                        CALIB_CB_ADAPTIVE_THRESH + 
                                                        CALIB_CB_NORMALIZE_IMAGE + 
                                                        CALIB_CB_FAST_CHECK);
            drawChessboardCorners(img, pattern_size, Mat(corners), patternfound);
            show_img(img, (string("Example ") + to_string(i)) );
            show_img(imageUndistorted, (string("Example ") + to_string(i)) );
        }
    }


    // print  the output
    cout << "calibrateCamera return: " << rms << endl;
    cout << "intrinsicFactor = " << endl << " "  << intrinsic << endl << endl;
    cout << "distCoeffs = " << endl << " "  << distCoeffs << endl << endl;

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

vector<Point2f> get_corners(Mat &img, Size patternsize) { 
    vector<Point2f> corners;
    // CALIB_CB_FAST_CHECK saves a lot of time on images
    // that do not contain any chessboard corners
    bool patternfound = findChessboardCorners(img, patternsize, corners,
                                                CALIB_CB_ADAPTIVE_THRESH + 
                                                CALIB_CB_NORMALIZE_IMAGE + 
                                                CALIB_CB_FAST_CHECK);
    return corners;
}

vector<Point3f> get_object_points(int num_corners_cols, int num_corners_rows) {
    // cols and rows must be equal or grater than 1
    if (num_corners_cols < 1 || num_corners_rows < 1){
        throw "cols and rows must be equal or grater than 1";
    }
    vector<Point3f> obj;
    int num_squares = num_corners_cols*num_corners_rows;
    for(int j=0; j<num_squares; j++)
        obj.push_back(Point3f(j/num_corners_cols, j%num_corners_cols, 0.0f));
    return obj;
 }