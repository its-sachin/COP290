// #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat im = imread("empty.jpg");
    double xDimen = stod(argv[1]);
    double yDimen = stod(argv[2]);

    cout << "image size before " << im.size() << endl;
    resize(im, im, Size(xDimen,yDimen));
    cout << "image size after " << im.size() << endl;
    
    while (true) {
        // imshow("Image", im);
        Mat gray;
        cvtColor(im, gray, COLOR_BGR2GRAY);
        // im = gray;
        imshow("GrayImage", gray);
        if (waitKey(10) == 27){
            break;
        }
    }
    return 0;

}