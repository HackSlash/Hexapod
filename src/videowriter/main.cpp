/* 
 * File:   main.cpp
 * Author: mark
 *
 * Created on 11 mei 2015, 23:25
 */


#include <opencv/cv.h>
#include "opencv2/imgproc/imgproc.hpp" 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string intToString(int number) {

    std::stringstream ss;
    ss << number;
    return ss.str();
}

int main(int argc, char* argv[]) {

    bool recording = false;
    bool startNewRecording = false;
    int videoNumber = 0;            // increment the jpeg file

    VideoCapture cap(0); // open the video camera no. 0

    VideoWriter writer;  // to write each frame from the webcam

    if (!cap.isOpened()) // if not success, exit program
    {
        cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
        return -1;
    }

    char* windowName = "Webcam Feed";
    namedWindow(windowName, CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed

    // four character code
    int fcc = CV_FOURCC('J', 'P', 'E', 'G');

    // frame per second interger
    int fps = 1;

    // frame size
    Size framesize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    Mat frame;      // capture each frame from the webcam

    while (1) {

        if (startNewRecording == true) {
            startNewRecording = false;
            recording = true;

            videoNumber++;              // when new recording is started, file name will be incremented
            
            string fileName = "img//myImg" + intToString(videoNumber) + ".jpeg";     // filename string
            writer = VideoWriter(fileName, fcc, fps, framesize);

            if (!writer.isOpened()) {
                cout << "Error opening file for write" << endl;
                getchar;
                return -1;
            }
        }

        bool bSuccess = cap.read(frame); // read a new frame from camera feed

        if (!bSuccess) //test if frame successfully read
        {
            cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
            break;
        }

        if (recording == true) // are recording
        {
            writer.write(frame);

            // show record sign
            putText(frame, "REC", Point(0, 60), 2, 2, Scalar(0, 0, 255));
        }

        imshow(windowName, frame); //show the frame in "MyVideo" window

        //listen for 10ms for a key to be pressed
        switch (waitKey(10)) {

            case 27:
                //'esc' has been pressed (ASCII value for 'esc' is 27)
                //exit program.
                return 0;

            case 114: // r button is pressed
                recording = !recording; // toggle recording
                if(recording==true) cout<<"Begin Recording"<<endl;
                else cout<<"Recording Paused"<<endl;
                break;

            case 110: // n button is pressed
                startNewRecording = true; // start new recording
                cout<<"New recording started"<<endl;
                break;
        }
    }
    return 0;
}

