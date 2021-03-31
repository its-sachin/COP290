#include <algorithm>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <pthread.h>
#include <cmath>
using namespace cv;
using namespace std;
using namespace std::chrono;

vector<Point2f> mapPoints;
vector<Point2f> srcPoints;
double xFactor=1;
double yFactor=1;



class Mode
{

    public:

    int getMethod() {
        return method;
    }
    int getSkipper() {
        return skipper;
    }

    void setMethod(int set_method) {
        method = set_method;
    }

    void setSkipper(int set_skipper) {
        skipper = set_skipper;
    }

    double xDimen;
    double yDimen;
    int noThread;
    private:

    int method;

    // skipper is method related variable
    // frames skipped for method 1
    // number of threads for method 3 and 4
    int skipper; 

    
};

void initialise(Mode m){
    if (m.getMethod()==2){
        xFactor = m.xDimen/1920;
        yFactor = m.yDimen/1080;    
    }
    mapPoints.push_back(Point2f(472*xFactor,52*yFactor));
    mapPoints.push_back(Point2f(800*xFactor,52*yFactor));
    mapPoints.push_back(Point2f(800*xFactor,830*yFactor));
    mapPoints.push_back(Point2f(472*xFactor,830*yFactor));
    srcPoints.push_back(Point2f(962*xFactor,213*yFactor));
    srcPoints.push_back(Point2f(1291*xFactor,211*yFactor));
    srcPoints.push_back(Point2f(1558*xFactor,978*yFactor));
    srcPoints.push_back(Point2f(338*xFactor,976*yFactor));
}


Mat changeHom(Mat in) {
    Mat wrapImg = Mat::zeros(in.size(),CV_8UC3);
    // auto start5=high_resolution_clock::now();
    Mat wrapedMatrix = findHomography(srcPoints, mapPoints);
    warpPerspective(in, wrapImg, wrapedMatrix, in.size());
    // auto stop5 = high_resolution_clock::now();
    // auto duration5 = duration_cast<microseconds>(stop5 - start5);
    // cout<<"time take "<<duration5.count()<<endl;
    int xdimension=329*xFactor;
    int ydimension=779*yFactor;

    Rect rec(472*xFactor,52*yFactor, xdimension, ydimension);

    Mat croppedRef(wrapImg, rec);

    Mat cropped;
    croppedRef.copyTo(cropped);

    return cropped;

}

Mat cropImage(Mat source,  int width, int start, int end){

    Rect rec(0,start, width, end-start);

    Mat croppedRef(source, rec);

    Mat cropped;
    croppedRef.copyTo(cropped);

    return cropped;
}





// ------------------------- method 0,1,2,5,6---------------------------------





bool thresD(Point2f a,Point2f b, double threshold){
    return sqrt(pow((double)(a.x-b.x),2.0)+pow((double)(a.y-b.y),2.0))>threshold;
}

void show(VideoCapture video,String winName[],double fps, Mat bg, Mode mode) {

    auto start = high_resolution_clock::now(); 

    int i = 0;
    Mat frame1;
    Mat frame2;

    double QueueDensity =0;
    double DynamicDensity=0;
    
    double time=0;

    double timeP = 0;

    int height = bg.rows;
    int width = bg.cols;

    int pixel = height*width;

    cout<< "Analysis started" << endl;

    string filename="../analysis/graph.csv";
    ofstream myfile; 

    myfile.open(filename);
    myfile<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;

    // cout<<"Time(s)"<<","<<"Queue Density"<<","<<"Dynamic Density"<<endl;
    if (mode.getMethod()==1 || mode.getMethod()==2 || mode.getMethod() == 0){

        while (true) {
            time+=(1);
            // frame1 = frame2.clone();
            bool isOpened = video.read(frame2);

            if (isOpened == false) {
                cout << "Video has ended" << endl;
                break;
            } 

            if (mode.getMethod() == 1 && (int)(time-1)%mode.getSkipper() != 0) {
                myfile<<(time)/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                // cout<< (time)/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                continue;
            }

            auto startP = high_resolution_clock::now();

            if (mode.getMethod() == 2) {
                Mat temp = frame2.clone();
                resize(temp, frame2, Size(mode.xDimen,mode.yDimen), 0,0);
            }

            auto stopP = high_resolution_clock::now();
            auto durationP = duration_cast<microseconds>(stopP - startP);
            timeP += durationP.count();
        
            cvtColor(frame2, frame2, COLOR_BGR2GRAY);
            Mat birdEye2 = changeHom(frame2);
            // imshow(winName[0], birdEye2);

            Mat overallDiff;
            absdiff(bg, birdEye2,overallDiff);
            GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
            threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );
            QueueDensity = (double)countNonZero(overallDiff)/(double)pixel;




            myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        }
    }
    else {
        if (mode.getMethod()==5){
            Mat frames[3];
            int d=0;
            while (true) {
                time+=(1);
                bool isOpened = video.read(frame2);

                if (isOpened == false) {
                    cout << "Video has ended" << endl;
                    myfile.close();
                    break;
                } 
                cvtColor(frame2, frame2, COLOR_BGR2GRAY);
                Mat birdEye2 = changeHom(frame2);
                if ((int)time%3==1 && i!=0 && i!=4){
                    frame1 = frame11.clone();
                    frame11=birdEye2.clone();
                }
                Mat overallDiff;
                absdiff(bg, birdEye2,overallDiff);
                GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
                threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );


                if (i == 0) {
                    frames[0]=birdEye2.clone();
                    myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                }
                else if (i==4){
                    frames[1]=birdEye2.clone();
                    myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                }
                else {
                    if ((int)time%6==4){
                        Mat birdEye1 = frame1;
                        Mat flow(birdEye1.size(), CV_32FC2);
                        calcOpticalFlowFarneback(birdEye1, birdEye2, flow, 0.5, 10, 40, 5, 10, 1.5, 0);  
                        Mat flow_parts[2];
                        split(flow, flow_parts);
                        Mat magnitude, angle, magn_norm;
                        cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
                        normalize(magnitude, magn_norm, 0, 255, NORM_MINMAX);
                        threshold(magn_norm,magn_norm, 215, 255,THRESH_BINARY );
                        d=(d+(countNonZero(magn_norm)))/2;
                    }
                    QueueDensity=(double)countNonZero(overallDiff)/(double)256291;
                    DynamicDensity=(double)d/(double)256291;

                    myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                    cout<< time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                }
                i++;
            } 
        }
        else {
            vector<Point2f> p0,p1,p00;
            Mat nz;
            int count=0;
            Mat frame11;
            while (true) {
                time+=(1);
                bool isOpened = video.read(frame2);

                if (isOpened == false) {
                    cout << "Video has ended" << endl;
                    myfile.close();
                    break;
                } 
                cvtColor(frame2, frame2, COLOR_BGR2GRAY);
                Mat birdEye2 = changeHom(frame2);
                if ((int)time%3==1 && i!=0){
                    frame1 = frame11.clone();
                    frame11=birdEye2.clone();
                }
                Mat overallDiff;
                absdiff(bg, birdEye2,overallDiff);
                GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
                threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );

                if ((int)time%3==1 && i!=0){
                    p0=p00;
                    findNonZero(overallDiff,p00);
                }
                if (i == 0) {
                    i =1;
                    findNonZero(overallDiff,p00);
                    frame11=birdEye2.clone();
                    myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                }
                else {
                    if ((int)time%6==4){
                        Mat birdEye1 = frame1;
                        vector<uchar> status;
                        vector<float> err;
                        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
                        if (p0.size()!=0){
                            calcOpticalFlowPyrLK(birdEye2, birdEye1, p0, p1, status, err, Size(10,10), 2, criteria);
                            count=0;
                            for (int i=0;i<(int)p0.size();i++){
                                if (status[i]==1){
                                    if (thresD(p0[i],p1[i],3.0)){
                                        count+=1;
                                    }
                                }
                            }

                        }
                        p0.clear();
                        p1.clear();
                    }
                    QueueDensity=(double)countNonZero(overallDiff)/(double)256291;
                    DynamicDensity=(double)count/(double)256291;
                    myfile<<time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                    cout<< time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
                }
            }      
        }      
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if (mode.getMethod() == 2) {
        cout << "Time taken by process: "<<(int) (duration.count() - timeP)/1000000 << " seconds" << endl;
        myfile << "$$,"<< (int) (duration.count() - timeP)/1000000<<endl;
    }

    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
    myfile << "$,"<< duration.count()/1000000<<endl;

    myfile.close();
}






// -----------------------------------method 3----------------------------------





// method 3-t




struct modethree{
    Mat framePart;
    double partialSum;
    Mat bgPart;
    int start;
    int end;
    int width;

    void initFirst(Mat bg, int widthT) {
        bgPart = cropImage(bg, widthT, start, end);
        width = widthT;

    }

    void initialize(Mat frame){
        framePart = cropImage(frame, width, start, end);
    }
};

void* show2(void* arg ) {
    struct modethree *arg_struct =(struct modethree*) arg;

    double partialSum = 0;
    arg_struct->initialize(arg_struct->framePart);
    
    Mat overallDiff;
    absdiff(arg_struct->bgPart, arg_struct->framePart ,overallDiff);
    GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
    threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY);

    partialSum =(double)countNonZero(overallDiff);

    arg_struct->partialSum = partialSum;
    pthread_exit(0);
}



void show3t(VideoCapture video, Mat bg, int no) {

    auto start = high_resolution_clock::now();

    cout<< "Analysis started" << endl;

    string filename="../analysis/graph.csv";
    ofstream myfile; 

    myfile.open(filename);
    myfile<<"Time(s)"<<","<<"Queue Density"<<endl;

    int width=bg.cols;
    int height=bg.rows;

    double QueueDensity = 0;
    Mat frame2;

    int timeH=0;
    int timeT=0;
    int timeR =0;

    double time = 0;

    struct modethree args[no];

    int count= 0; 

    for (int i=0; i<no; i++){
        args[i].start = count;

        // cout<< "start " << start<< endl;
        count += height/no;
        if (i == no-1){
            args[i].end=height;
        }
        else{
            args[i].end=count;
        }
        args[i].initFirst(bg,width);
        
        // cout<< "end " << end<< endl;
        // cout<< "width " << width<< endl;
    }  

    while (true) {
        QueueDensity =0;
        time+=(1);

        auto startR = high_resolution_clock::now();
        bool isOpened = video.read(frame2);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            break;
        }

        auto stopR = high_resolution_clock::now(); 
        auto durationR = duration_cast<microseconds>(stopR - startR);
        timeR += durationR.count();

        auto startH = high_resolution_clock::now(); 

        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);

        auto stopH = high_resolution_clock::now(); 
        auto durationH = duration_cast<microseconds>(stopH - startH);
        timeH += durationH.count();


        auto startT = high_resolution_clock::now(); 

        pthread_t tids[no];

        for (int i=0; i<no;i++){
            args[i].framePart = birdEye2;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tids[i],&attr,show2,&args[i]);
        }

        for (int i=0; i<no;i++){
            pthread_join(tids[i],NULL);
        }

        auto stopT = high_resolution_clock::now(); 
        auto durationT = duration_cast<microseconds>(stopT- startT);
        timeT += durationT.count();


        for (int i=0; i<no;i++){
            QueueDensity += args[i].partialSum;
        }
        
        QueueDensity = QueueDensity/(double)256291;


        myfile<<time/15<<","<<QueueDensity<<endl;
        // cout<< time/15<<","<<QueueDensity<<","<<DynamicDensity<<endl;
        
        
        // if (waitKey(1) == 27){
        //     cout << "Esc key is pressed by user. Stopping the video" << endl;
        //     break;
        // }

        
    }

    cout<< "Time for homography " << timeH/1000000 << " seconds"<< endl;
    cout<< "Time for Threads " << timeT/1000000<< " seconds"<< endl;
    cout<< "Time for Reading " << timeR/1000000<< " seconds"<< endl;


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
    myfile << "$,"<< duration.count()/1000000<<endl;

    myfile.close();
}






// method 3-s


struct alternate{
    int threadno;
    Mat** arr;
    int frameT;
    Mat bg;
    map<int,double> data;
};

Mat** cut(VideoCapture video, int no,int width,int height){
    Mat frame;
    int frameT= (int) video.get(CAP_PROP_FRAME_COUNT);
    Mat** arr;
    arr= new Mat*[no];
    for (int h=0;h<no;h++){
        arr[h]=new Mat[frameT];
    }
    int frameno=0;
    int count=0;
    int start;
    int end;
    while (true) {
        bool isOpened = video.read(frame);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            break;
        } 
        
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame);      
        for (int i=0; i<no; i++){
            start=count;
            count += height/no;
            if (i == no-1){
                end=height;
            }
            else{
                end=count;
            }
            arr[i][frameno]=cropImage(birdEye2,width,start,end);
        }
        count=0;
        frameno++;    
        // if (waitKey(1) == 27){
        //     cout << "Esc key is pressed by user. Stopping the video" << endl;
        //     break;
        // }
    }
    return arr;

}
void* showalt(void* arg ) {
    struct alternate *arg_struct =(struct alternate*) arg;

    double QueueDensity =0;

    Mat** arr = arg_struct->arr;
    Mat bg = arg_struct->bg;
    int frameno=0;
    map <int,double> data;
    int frameT = arg_struct->frameT;
    while (frameno<frameT) {
        Mat birdEye2=arr[arg_struct->threadno][frameno];
        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );

        QueueDensity=(double)countNonZero(overallDiff)/(double)256291;
        data.insert({frameno,QueueDensity});
        // if (waitKey(1) == 27){
        //     cout << "Esc key is pressed by user. Stopping the video" << endl;
        //     break;
        // }
        frameno++;
    }
    arg_struct->data=data;
    pthread_exit(0);
}




void show3s(VideoCapture video, Mat bg, int no, int frameT) {

    cout<< "Analysis started" << endl;

    auto start1 = high_resolution_clock::now();

    int width=bg.cols;
    int heigth=bg.rows;

    struct alternate args[no];
    pthread_t tids[no];
    auto starta= high_resolution_clock::now();
    Mat** arr =cut(video,no,width,heigth);
    auto stopa = high_resolution_clock::now();
    auto durationa = duration_cast<microseconds>(stopa - starta);
    cout << "Time taken by cut: "<< durationa.count()/1000000 << " seconds" << endl;
    int count=0;
    int start;
    int end;
    for (int i=0; i<no; i++){
        start=count;
        count += heigth/no;
        if (i == no-1){
            end=heigth;
        }
        else{
            end=count;
        }
        args[i].bg=cropImage(bg,width,start,end);
        args[i].threadno = i;
        args[i].arr=arr;
        args[i].frameT=frameT;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i],&attr,showalt,&args[i]);
    }
    ofstream myfile;
    myfile.open ("../analysis/graph.csv");
    myfile<<"Frame No.,Queue Density\n";
    for (int i=0; i<no;i++){
        pthread_join(tids[i],NULL);
    }
    
    for (int i=1; i<no;i++){
        for (int j=0;j<frameT;j++){
            args[0].data.at(j)+=args[i].data.at(j);
        }
    } 
    for (int j=0;j<frameT;j++){
        double k= (double) j /15.0;
        myfile<<k<<","<<args[0].data.at(j)<<endl;
    } 

    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Time taken by function: "<< duration1.count()/1000000 << " seconds" << endl;    
    myfile<<"$,"<<  duration1.count()/1000000 << endl;
    myfile.close(); 
}








// ------------------------------------------method 4---------------------------------



// method 4-t

struct mode4
{
    Mat frame;
    double QueueDensity;
    double frameNo;
    Mat bg;
};


void* show4Thread(void* arg) {

    struct mode4 *arg_struct =(struct mode4*) arg;

    Mat frame2 = arg_struct->frame;

    cvtColor(frame2, frame2, COLOR_BGR2GRAY);
    Mat birdEye2 = changeHom(frame2);
    // imshow(winName[0], birdEye2);

    Mat overallDiff;
    absdiff(arg_struct->bg, birdEye2,overallDiff);
    GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
    threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );
    arg_struct->QueueDensity = (double)countNonZero(overallDiff)/(double)256291;

    pthread_exit(0);
}


void show4t(VideoCapture video, Mat bg, int no) {

    cout<< "Analysis started" << endl;

    auto start = high_resolution_clock::now();

    Mat frames[no];    
    double frameCount = 0;
    string filename="../analysis/graph.csv";
    ofstream myfile; 

    int timeT=0;
    int timeR =0;

    myfile.open(filename);
    myfile<<"Time(s)"<<","<<"Queue Density"<<endl;

    while(true) {

        mode4 args[no];
        bool done = false;

        auto startR = high_resolution_clock::now();

        for (int i =0; i<no; i++) {
            bool isOpened = video.read(frames[i]);

            if (isOpened == false){
                
                int temp = no;
                no = i;
                i = temp;
                done = true;

            }

            else {
                frameCount += 1;
                args[i].frameNo = frameCount;
                args[i].frame = frames[i];
                args[i].bg = bg;
            }
        }

        auto stopR = high_resolution_clock::now(); 
        auto durationR = duration_cast<microseconds>(stopR - startR);
        timeR += durationR.count();

        auto startT = high_resolution_clock::now(); 

        pthread_t tids[no];

        for (int i=0; i<no;i++){
            
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tids[i],&attr,show4Thread,&args[i]);
        }

        for (int i=0; i<no;i++){
            pthread_join(tids[i],NULL);
        }

        auto stopT = high_resolution_clock::now(); 
        auto durationT = duration_cast<microseconds>(stopT- startT);
        timeT += durationT.count();

        for (int i=0; i< no; i++ ){
            myfile<<args[i].frameNo/15<<","<<args[i].QueueDensity<<endl;
            // cout<<args[i].frameNo/15<<","<<args[i].QueueDensity<<endl;
        }

        if (done) {
            cout<<"Video has ended" << endl;
            break;
        }

    }

    cout<< "Time for Threads " << timeT/1000000<< " seconds"<< endl;
    cout<< "Time for Reading " << timeR/1000000<< " seconds"<< endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;
    myfile << "$,"<< duration.count()/1000000<<endl;
}





// method 4-s

struct modefour{
    VideoCapture video;
    map<int,double> data;
    Mat bg;
    int start;
    int end;
};



void* show1(void* arg ) {
    struct modefour *arg_struct =(struct modefour*) arg;

    double QueueDensity =0;

    int count=arg_struct->start;
    VideoCapture video = arg_struct->video;
    video.set(CAP_PROP_POS_FRAMES,count-1);
    Mat frame2;
    Mat bg = arg_struct->bg;
    int end=arg_struct->end;
    while (count <= end) {
        bool isOpened = video.read(frame2);

        if (isOpened == false) {
            cout << "Video has ended" << endl;
            break;
        } 
        cvtColor(frame2, frame2, COLOR_BGR2GRAY);
        Mat birdEye2 = changeHom(frame2);
        Mat overallDiff;
        absdiff(bg, birdEye2,overallDiff);
        GaussianBlur(overallDiff,overallDiff, Size(5,5),0);
        threshold(overallDiff,overallDiff, 50, 255,THRESH_BINARY );

        QueueDensity=(double)countNonZero(overallDiff)/(double)256291;
        arg_struct->data.insert({count,QueueDensity});
        // if (waitKey(1) == 27){
        //     cout << "Esc key is pressed by user. Stopping the video" << endl;
        //     break;
        // }
        count++;
    }
    pthread_exit(0);
}


void show4s(String videopath, Mat bg, int no, int frameT) {

    struct modefour args[no];
    pthread_t tids[no];
    int count=0;

    cout<< "Analysis started" << endl;
    auto start = high_resolution_clock::now();
    for (int i=0; i<no; i++){
        args[i].start = count;
        count += frameT/no;
        if (i == no-1){
            args[i].end=frameT;
        }
        else{
            args[i].end=count;
        }
        args[i].bg = bg; 
        VideoCapture vid(videopath);
        args[i].video = vid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i],&attr,show1,&args[i]);
    }

    ofstream myfile;
    myfile.open ("../analysis/graph.csv");
    myfile<<"Time(s),Queue Density"<<endl;
    for (int i=0; i<no;i++){
        pthread_join(tids[i],NULL);
    }

    for (int i=0; i<no;i++){
        for (double j=(double) args[i].start;j<(double)args[i].end;j++){
            double k= j /15;
            if (j!=frameT-1){
                myfile<<k<<","<<args[i].data.at(j)<<endl;
            }
        }
    }  

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);  
    cout << "Time taken by function: "<< duration.count()/1000000 << " seconds" << endl;  

    myfile<<"$," <<duration.count()/1000000<<endl;  
    myfile.close();
}






// --------------------------get the backgorund image-------------------------------------

Mat getBack(VideoCapture video,int emptime, Mode mode) {
    video.set(CAP_PROP_POS_MSEC,emptime*1000) ;
    Mat frame;
    bool isOpened = video.read(frame);

    if (isOpened == false) {
        cout << "The time for empty frame is not correct\n" << endl;
    } 

    if (mode.getMethod() == 2){
        Mat bg;
        resize(frame, bg, Size(mode.xDimen, mode.yDimen), 0,0);
        cvtColor(bg, bg, COLOR_BGR2GRAY);

        video.set(CAP_PROP_POS_MSEC,0) ;
        Mat changed = changeHom(bg);
        return changed;

    }

    cvtColor(frame, frame, COLOR_BGR2GRAY);

    video.set(CAP_PROP_POS_MSEC,0) ;
    Mat changed = changeHom(frame);
    return changed;
}


// ----------------------------------------main function----------------------------------

int main(int argc, char** argv) {
    string videopath,videoname;
    
    double fps; 
    int frameT;
    if (argc==1){
        cout<<"Please provide an filname/filepath for source video\n";
        return 0;
    }

    videopath=argv[1];

    VideoCapture video(videopath);

    if (video.isOpened() == false) {
        cout << "Unable to open the video, Check if the file exists in this directory" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
    fps = video.get(CAP_PROP_FPS);
    frameT= (int) video.get(CAP_PROP_FRAME_COUNT);
    Mode mode;
    if (argc == 2) {
        cout<< "Method for optimization not provided" << endl;
        return 0;
    }
    int modeVal = stoi(argv[2]);
    mode.setMethod(modeVal);

    int emptime=345;
    Mat bg;
    
    if (modeVal == 0) {
        cout<< "Analysing normally" << endl;
        initialise(mode);
    }
    else if (modeVal ==1){
        if (argc == 3) {
            cout<< "Number of frames to skip not provided" << endl;
            return 0;
        }
        mode.setSkipper(stoi(argv[3]) + 1);
        initialise(mode);
        cout<< "Analysing by skipping " << stoi(argv[3])<< " frames"<< endl;
    }

    else if (modeVal == 2){
        if (argc <5) {
            cout<< "Both dimensions not provided" << endl;
            return 0;
        }
        mode.xDimen = stod(argv[3]);
        mode.yDimen = stod(argv[4]);
        initialise(mode);

        cout << "Analysing by resizing video to "<< argv[3] << "*" << argv[4] <<endl;
    }

    else if (modeVal==3 || modeVal == 31){
        if (argc==3){
            cout<<"No of threads not provided"<<endl;
            return 0;
        } 

        int no= stoi(argv[3]);
        mode.noThread =no;
        initialise(mode);

        cout << "Analysing each frame of video in " << no << " threads" << endl;
        bg = getBack(video,emptime, mode);
        if (modeVal == 3) {
            show3t(video, bg, no);
        }
        else {
            show3s(video, bg, no, frameT);
        }
        return 0;   
    }

    else if (modeVal == 4 || modeVal == 41){
        
        if (argc==3){
            cout<<"No of threads not provided"<<endl;
            return 0;
        }
        
        int no = stoi(argv[3]);

        cout << "Analysing video in " << no << " threads" << endl;
        initialise(mode);
        bg = getBack(video,emptime, mode);
        if (modeVal == 4) {
            show4t(video, bg, no);
        }
        else {
            show4s(videopath, bg, no, frameT);
        }
         
        return 0;
    }

    else if (modeVal==5 || modeVal==6){
        if (modeVal == 5) {
            cout<< "Optical Flow: Dense" << endl;
        }
        else {
            cout<< "Optical Flow: Sparse" << endl;
        }
        initialise(mode);
    }

    else {
        cout<< "INVALID Method!!" << endl;
        return 0; 
    }
    bg = getBack(video,emptime, mode);
    string winName[3] = {"Original Video","Overall Difference","Dynamic Difference"};  

    show(video,winName,fps,bg, mode);
    return 0;
    
}



