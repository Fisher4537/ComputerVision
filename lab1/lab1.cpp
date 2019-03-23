#include <opencv2/highgui.hpp>
using namespace cv;
//void MouseFunc(int event, int x, int y, int flags, void* userdata);

int blue_shirt = 25;
int green_shirt = 125;
int red_shirt = 175;
int bias = 95;
bool check_range(int value, int mean, int range);
bool change_condition(Vec3b v3b, int bias);

int main(int argc, char** argv) {
    Mat img = imread(argv[1]);
    int tmp;
    Vec3b intensity;
    intensity = img.at<Vec3b> (Point(0, 0));
    // std::printf("change_condition: %i (%i %i %i)\n", change_condition(intensity, 35), intensity.val[0], intensity.val[1], intensity.val[2]);
    // return 0; 
    for (int i = 0; i < img.size().width; ++i)
        for (int j = 0; j < img.size().height; ++j) {
            intensity = img.at<Vec3b> (Point(i, j));
            if (change_condition(intensity, bias)) {
                //std::printf("change value of (%i, %i) (%i %i %i)\n", i, j, intensity.val[0], intensity.val[1], intensity.val[2]);
                tmp = intensity.val[0];
                intensity.val[0] = intensity.val[2];
                intensity.val[2] = tmp;
                img.at<Vec3b>(Point(i,j)) = intensity;
            } else {
                //std::printf("change value of (%i, %i) (%i %i %i)\n", i, j, intensity.val[0], intensity.val[1], intensity.val[2]);
            }
        }
    namedWindow("Example 2");
    //setMouseCallback("Example 2", MouseFunc, void *userdata);
    imshow ("Example 2", img);
    waitKey(0);
    return 0;
}

bool change_condition(Vec3b v3b, int bias) {
    if ( check_range(v3b.val[0], ::blue_shirt, bias) && check_range(v3b.val[1], ::green_shirt, bias) && check_range(v3b.val[2], ::red_shirt, bias) ) {
        return true;
    }
    return false;
}

bool check_range(int value, int mean, int range) {
    //std::printf("value, mean, range = %i %i %i, condition = %i\n", value, mean, range, value < min(mean + range, 255) && value > max(mean - range, 0));
    return value < min(mean + range, 255) && value > max(mean - range, 0);
} 
/*
void MouseFunc(int event, int x, int y, int flags, void* userdata) {
    if ( event == EVENT_LBUTTONDOWN ) {
        cout << "Left button clicked - position (" << x << ", " << y << ")" << endl;
    }
}*/
