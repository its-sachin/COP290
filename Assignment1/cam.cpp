#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// function to be given to set mouse callback (PROBLEM HERE)
void selectingPoints(int event, int x, int y, int flag, void* points) {
    vector<Point2f> inPoints = *((vector<Point2f> *) points);
    if (event == EVENT_LBUTTONDOWN) {
        if (inPoints.size() < 4) {
            inPoints.push_back(Point2f(x,y));
            cout << x << endl;
        }

    }
}


int main(int argc, char* argv[]) {

    // reading the image (grayscale) 
    Mat sourcImg = imread("empty.jpg",0);

    if (sourcImg.empty()) {
        cout << "Unable to open the source image file - Check if empty.jpg present in the folder or not." << endl;
        cin.get(); //wait for any key press
        return -1;
    }
      
    // display grayscaled source image
    imshow("Original Frame", sourcImg);
    waitKey(0); // ---> to be changed.

    // maping points given on course website
    vector<Point2f> mapPoints;
    mapPoints.push_back(Point2f(472,52));
    mapPoints.push_back(Point2f(472,830));
    mapPoints.push_back(Point2f(800,830));
    mapPoints.push_back(Point2f(800,52));

    // points to be selected by user
    vector<Point2f> inPoints;
    setMouseCallback("Original Image", selectingPoints, &inPoints);

    // do homography
    Mat wrapedMatrix = findHomography(inPoints, mapPoints);
    Mat wrapImg = Mat::zeros(sourcImg.size(),CV_8UC3);
    warpPerspective(sourcImg, wrapImg, wrapedMatrix, sourcImg.size());

    imshow("Image", wrapImg);
    waitKey(0);


    // selecting the points 
    
}


