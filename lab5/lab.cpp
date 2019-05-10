#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include <iostream>

#include "panoramic_utils.h"

using namespace cv;
using namespace std;


Stitcher::Mode mode = Stitcher::PANORAMA;
vector<cv::Mat> img_vector;

vector<cv::Mat> loadSetOfImg(cv::String path)
{
    cout << "loading images from: " << path << endl;
    vector<cv::String> fn;
    vector<cv::Mat> data;
    cv::glob(path, fn, false); // non recursive
    for (size_t k=0; k<fn.size(); ++k)
    {
        cout << fn[k] << endl;
        cv::Mat im = cv::imread(fn[k]);
        if (im.empty()) continue; //only proceed if sucsessful
        // you probably want to do some preprocessing
        data.push_back(im);
    }
    return data;
}

int main(int argc, char** argv)
{
    // Check input param
    if (argc != 2)
    {
        cout << "usage: ./lab <img_folder_path>" << endl;
        return -1;
    }
    cv:String path = argv[1]; // pattern string of the images
    img_vector = loadSetOfImg(path);

        // Define object to store the stitched image 
    Mat pano; 
      
    // Create a Stitcher class object with mode panoroma 
    Ptr<Stitcher> stitcher = Stitcher::create(mode); 
      
    // Command to stitch all the images present in the image array 
    Stitcher::Status status = stitcher->stitch(img_vector, pano);
  
    if (status != Stitcher::OK) 
    { 
        // Check if images could not be stiched 
        // status is OK if images are stiched successfully 
        cout << "Can't stitch images\n"; 
        return -1; 
    } 
      
    // Store a new image stiched from the given  
    //set of images as "result.jpg" 
    imwrite("result.jpg", pano); 
      
    // Show the result 
    imshow("Result", pano); 
      
    waitKey(0); 
    return 0; 
}
