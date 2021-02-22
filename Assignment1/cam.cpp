#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// function to be given to set mouse callback (PROBLEM HERE)
void selectingPoints(int event, int x, int y, int flag, void* image) {

    Mat sourcImg = *reinterpret_cast<Mat*>(image);

    vector<Point2f> inPoints;

    if (event == EVENT_LBUTTONDOWN) {
        cout << x << endl;
        if (inPoints.size() < 4) {
            inPoints.push_back(Point2f(x,y));
        }

    }

    image = reinterpret_cast<void*>(&inPoints);

}


int main(int argc, char* argv[]) {

    // reading the image (grayscale) 
    Mat sourcImg = imread("empty.jpg",0);
    Mat wrapImg = Mat::zeros(sourcImg.size(),CV_8UC3);

    if (sourcImg.empty()) {
        cout << "Unable to open the source image file - Check if empty.jpg present in the folder or not." << endl;
        cin.get(); //wait for any key press
        return -1;
    }
      
    // display grayscaled source image
    imshow("Original Frame", sourcImg);

    // maping points given on course website
    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472,52));
    mapPoints.push_back(Point2f(472,830));
    mapPoints.push_back(Point2f(800,830));
    mapPoints.push_back(Point2f(800,52));

    void* data = reinterpret_cast<void*>(&sourcImg);
    
    setMouseCallback("Original Frame", selectingPoints, data);
    waitKey(0); // ---> to be changed.

    vector<Point2f> inPoints = *reinterpret_cast<Mat*>(data);

    // do homography
    Mat wrapedMatrix = findHomography(mapPoints, mapPoints);
    warpPerspective(sourcImg, wrapImg, wrapedMatrix, sourcImg.size());

    imshow("Image", wrapImg);
    waitKey(0);
 
    
}


