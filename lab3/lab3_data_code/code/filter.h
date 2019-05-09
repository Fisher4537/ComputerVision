#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef FILTER
#define FILTER

/**
 * @brief Generic class implementing a filter with the input and output
 * image data and the parameters
 * 
 */
class Filter{

    public:

        /**
         * @brief Construct a new Filter object
         * 
         * @param input_img image to be filtered
         * @param filter_size size of the kernel/window of the filter
         */
        Filter(cv::Mat input_img, int filter_size);

        /**
         * @brief perform filtering (in base class do nothing, to be 
         * reimplemented in the derived filters)
         * 
         */
        void doFilter();

        /**
         * @brief get the output of the filter
         * 
         * @return cv::Mat filtered image. 
         */
        cv::Mat getResult();

        /**
         * @brief set the window size (square window of dimensions size x size)
         * 
         * @param size 
         */
        void setSize(int size);
        
        /**
         * @brief get the Window Size
         * 
         * @return int 
         */
        int getSize();

    protected:

        /**
         * @brief input image
         */
        cv::Mat input_image;

        /**
         * @brief output image (filter result)
         */
        cv::Mat result_image;

        /**
         * @brief window size
         */
        int filter_size;

};

class MedianFilter : public Filter {

public: 
    
    MedianFilter(cv::Mat img, int size);

    // perform filtering (in base class do nothing, to be reimplemented in the derived filters)
    void doFilter();

// place constructor
// re-implement  doFilter()
// no additional parameters

};

// Gaussian Filter
class GaussianFilter : public Filter  {

// write here your code
public:
    GaussianFilter(cv::Mat img, int size, double std);

    // perform filtering (in base class do nothing, to be reimplemented in the derived filters)
    void doFilter();

    void setSTD(double std);

// place constructor
// re-implement  doFilter()
// additional parameter: standard deviation (sigma)
protected:

    double sigma;

};


class BilateralFilter : public Filter {
public:

    BilateralFilter(cv::Mat img, int size, double sr, double ss);
    
    // perform filtering (in base class do nothing, to be reimplemented in the derived filters)
    void doFilter();

// place constructor
// re-implement  doFilter()
// additional parameters: sigma_range, sigma_space

protected:

    double sigma_range, sigma_space;

};

#endif