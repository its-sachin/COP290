// #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct summer {
    long long limit;
    long long ans;
};

Mat changeHom(Mat in, int a) {

    double xFactor = in.size().width/1920.0;
    double yFactor = in.size().height/1080.0;


    vector<Point2f> mapPoints;
    vector<Point2f> srcPoints;
    

    if (a == -1) {
        mapPoints.push_back(Point2f(472,52));
        mapPoints.push_back(Point2f(800,52));
        mapPoints.push_back(Point2f(800,830));
        mapPoints.push_back(Point2f(472,830));

        
        srcPoints.push_back(Point2f(962,213));
        srcPoints.push_back(Point2f(1291,211));
        srcPoints.push_back(Point2f(1558,978));
        srcPoints.push_back(Point2f(338,976));
    }

    else {
        mapPoints.push_back(Point2f(472,52-a));
        mapPoints.push_back(Point2f(800,52-a));
        mapPoints.push_back(Point2f(800,830-a));
        mapPoints.push_back(Point2f(472,830-a));

        srcPoints.push_back(Point2f(962,213-a));
        srcPoints.push_back(Point2f(1291,211-a));
        srcPoints.push_back(Point2f(1558,978-a));
        srcPoints.push_back(Point2f(338,976-a));
    }

    Mat wrapImg = Mat::zeros(in.size(),CV_8UC3);
    Mat wrapedMatrix = findHomography(srcPoints, mapPoints);
    warpPerspective(in, wrapImg, wrapedMatrix, in.size());

    int xdimension=329;
    int ydimension=779;

    Mat out(ydimension,xdimension,CV_8UC3,Scalar(0,0,0));

    vector<Point2f> cropPoints;
    cropPoints.push_back(Point2f(0,0));  
    cropPoints.push_back(Point2f(xdimension-1,0));
    cropPoints.push_back(Point2f(xdimension-1,ydimension-1));
    cropPoints.push_back(Point2f(0,ydimension-1));

    wrapedMatrix = findHomography(mapPoints,cropPoints);

    warpPerspective(wrapImg, out, wrapedMatrix, out.size());

    return out;

}

void* sum(void* arg) {


    struct summer *arg_str = (struct summer*) arg;

    // cout<< "computation started for " << limitR << endl;

    long long sum = 0;
    for (long long i=0; i< arg_str->limit; i++) {
        sum += i;
    }

    arg_str->ans = sum;

    pthread_exit(0);
}

Mat cropImage(Mat source,  int width, int start, int end){

    Rect rec(0,start, width, end-start);

    Mat croppedRef(source, rec);

    Mat cropped;
    croppedRef.copyTo(cropped);

    return cropped;
}


int main(int argc, char* argv[])
{
    Mat im = imread("../Subtask1/empty.jpg");
    // Mat bg = imread("../Subtask1/wrapped-traffic.jpg");
    // double xDimen = stod(argv[1]);
    // double yDimen = stod(argv[2]);

    // cout << "image size before " << im.size() << endl;
    // resize(im, im, Size(xDimen,yDimen));
    // cout << "image size after " << im.size() << endl;
    
    // while (true) {
    //     // imshow("Image", im);
    //     Mat gray;
    //     cvtColor(im, gray, COLOR_BGR2GRAY);
    //     // im = gray;
    //     imshow("GrayImage", gray);
    //     if (waitKey(10) == 27){
    //         break;
    //     }
    // }

    // int numThread = argc -1;
    // struct summer args[numThread];

    // pthread_t tid[numThread];

    // for (int i=0; i< numThread; i++) {
    //     args[i].limit = atoll(argv[i+1]);

    //     pthread_attr_t attr;
    //     pthread_attr_init(&attr);

    //     pthread_create(&tid[i], &attr, sum, &args[i]);
    // }

    // for (int i=0; i< numThread; i++) {

    //     pthread_join(tid[i], NULL);
    //     cout<< "answer for " << args[i].limit<< " is " << args[i].ans << endl;
    // }


        int a = 8;
        double b = 5.75;
        Mat cropIm1 = cropImage(im, im.cols, 0, im.rows/2 - im.rows/a);
        Mat cropIm2 = cropImage(im, im.cols, im.rows/2 - im.rows/b, im.rows);
        // Mat cropbg = cropImage(bg, 329, 0, 389);

        // Mat overallDiff;
        // absdiff(bg, im ,overallDiff);
        // GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        // threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY);

        // Mat cropDiff;
        // absdiff(cropbg, cropIm ,cropDiff);
        // GaussianBlur(cropDiff,cropDiff, Size(5,5),0);
        // threshold(cropDiff,cropDiff, 50, 255,THRESH_BINARY);

        Mat changeFull = changeHom(im,-1);
        Mat changeCr1 = changeHom(cropIm1,0);
        Mat changeCr2 = changeHom(cropIm2,im.rows/2 - im.rows/b);

        circle(im, Point2f(stoi(argv[1]),stoi(argv[2])), 10, Scalar(0,0,255), FILLED);
        circle(cropIm2, Point2f(stoi(argv[1]),stoi(argv[2]) - im.rows/2), 10, Scalar(0,0,255), FILLED);

        while (true) {

            imshow("Image", im);
            imshow("Crop", cropIm2);
            imshow("Hom", changeFull);
            imshow("Cropped Hom Up", changeCr1);
            imshow("Cropped Hom Down", changeCr2);

            if (waitKey(1) == 27){
                break;
            }
        }


    return 0;

}