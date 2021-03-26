// #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct summer {
    long long limit;
    long long ans;
};

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
    Mat im = imread("../Subtask1/wrapped-empty.jpg");
    Mat bg = imread("../Subtask1/wrapped-traffic.jpg");
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

        cout<< "width "<< im.cols<< endl;
        cout<< "height "<< im.rows<< endl;

        Mat cropIm = cropImage(im, 329, 0, 389);
        Mat cropbg = cropImage(bg, 329, 0, 389);

        Mat overallDiff;
        absdiff(bg, im ,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY);

        Mat cropDiff;
        absdiff(cropbg, cropIm ,cropDiff);
        GaussianBlur(cropDiff,cropDiff, Size(5,5),0);
        threshold(cropDiff,cropDiff, 50, 255,THRESH_BINARY);

        while (true) {
            imshow("Image", im);
            imshow("Cropped Image", cropIm);
            imshow("Cropped bg", cropbg);

            imshow("Difference", overallDiff);
            imshow("Cropped Difference", cropDiff);

            if (waitKey(1) == 27){
                break;
            }
        }


    return 0;

}