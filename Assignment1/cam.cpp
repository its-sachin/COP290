#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


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
}

