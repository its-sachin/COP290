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


int main(int argc, char* argv[])
{
    // Mat im = imread("empty.jpg");
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

    int numThread = argc -1;
    struct summer args[numThread];

    pthread_t tid[numThread];

    for (int i=0; i< numThread; i++) {
        args[i].limit = atoll(argv[i+1]);

        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&tid[i], &attr, sum, &args[i]);
    }

    for (int i=0; i< numThread; i++) {

        pthread_join(tid[i], NULL);
        cout<< "answer for " << args[i].limit<< " is " << args[i].ans << endl;
    }

    return 0;

}