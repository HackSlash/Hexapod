#include "opencv2/core/core.hpp"
#include "iostream"
#include "Balloon.h"

using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;

///default values
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
const int MAX_NUM_OBJECTS = 50; //max number of objects to be detected in frame
const int MIN_OBJECT_AREA = 40 * 40; //minimum object area
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5; //maximum object area

///Converts Integer to String.

string intToString(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

///@DEBUG Draws the object.

void drawObject(vector<Balloon> theBalloons, Mat &frame) {

    for (int i = 0; i < theBalloons.size(); i++) {

        cv::circle(frame, cv::Point(theBalloons.at(i).getXPos(), theBalloons.at(i).getYPos()), 10, cv::Scalar(0, 0, 255));
        cv::putText(frame, intToString(theBalloons.at(i).getXPos()) + " , " + intToString(theBalloons.at(i).getYPos()), cv::Point(theBalloons.at(i).getXPos(), theBalloons.at(i).getYPos() + 20), 1, 1, Scalar(0, 255, 0));
        // optional, to show the user wich object is tracking
        cv::putText(frame, theBalloons.at(i).getType(), cv::Point(theBalloons.at(i).getXPos(), theBalloons.at(i).getYPos() - 20), 1, 2, theBalloons.at(i).getColour());
    }
}

///Calculates the distance to an object.

int getDistance(int hoogteObjectInPx) {
    int brandpuntAfstandMM = 29;
    int hoogteObjectInMM = 27;
    int relatieveAfstand = 0;

    return relatieveAfstand = (((hoogteObjectInPx - hoogteObjectInMM) * brandpuntAfstandMM) / hoogteObjectInMM);
}

///Removes noice from the image.

void morphOps(Mat &thresh) {
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3)); //Structuring element that is used to erode an image.
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8)); //Structuring element that is used to dilate an image.

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);
    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
}

///Finds the contour of a balloon.
///Extracts the balloon location in the image.

void getContour(Mat threshold, Mat HSV, Mat &cameraFeed) {

    //if the area is less than 20 px by 20px then it is probably just noise
    //if the area is the same as the 3/2 of the image size, probably just a bad filter
    //we only want the object with the largest area so we safe a reference area each
    //iteration and compare it to the area in the next iteration.

    vector<Balloon> blueBalloons;
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat temp;
    threshold.copyTo(temp);

    ///Find all contours in the image.
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    ///Find the contour we need.
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        if (numObjects < MAX_NUM_OBJECTS) {

            for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                if (area > MIN_OBJECT_AREA) {
                    Balloon blueBalloon;

                    blueBalloon.setXPos(moment.m10 / area);
                    blueBalloon.setYPos(moment.m01 / area);
                    blueBalloons.push_back(blueBalloon);

                    objectFound = true;
                } else objectFound = false;
            }
            ///Let user know you found an object.
            if (objectFound == true) {
                drawObject(blueBalloons, cameraFeed); //draw object location on screen
            }
        } else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
    }
}

///@Overload For multiple balloons.

void getContour(Balloon theBalloon, Mat threshold, Mat &thresholdFilter) {

    vector<Balloon> balloons;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat temp;
    threshold.copyTo(temp);

    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        if (numObjects < MAX_NUM_OBJECTS) {
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;
                if (area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA && area > refArea) {

                    Balloon balloon;
                    balloon.setXPos(moment.m10 / area);
                    balloon.setYPos(moment.m01 / area);
                    balloon.setType(theBalloon.getType());
                    balloon.setColour(theBalloon.getColour());

                    balloons.push_back(balloon);
                    objectFound = true;
                    refArea = area;
                    cout << "x:" << balloon.getXPos() << endl;
                    int relativeDistance = getDistance(balloon.getXPos());
                    cout << "afstand object:" + intToString(relativeDistance) << endl;
                } else objectFound = false;
            }
            if (objectFound == true) drawObject(balloons, thresholdFilter);
        }
    }
}

///Grabs a frame from the camerafeed.

bool getVideo(Mat &vidframe) {
    bool recording = false;
    bool startNewRecording = false;
    VideoCapture videoConnection(0);

    if (!videoConnection.isOpened()) // if no feed, exit program
    {
        cout << "ERROR COULD NOT CONNECT WITH WEBCAM!" << endl;
        return false;
    }

    VideoWriter writer; // Write each frame from the webcam to the matrix.

    ///foto-options
    int fcc = CV_FOURCC('J', 'P', 'E', 'G'); // four character code.
    int fps = 1; // frame per second interger. 
    Size framesize(videoConnection.get(CV_CAP_PROP_FRAME_WIDTH), videoConnection.get(CV_CAP_PROP_FRAME_HEIGHT)); // frame size

    while (1) {
        if (startNewRecording == true && waitKey(200)) {
            startNewRecording = false;
            recording = true;

            string filePath = "img//SNAPSHOT.jpeg"; // imagePath
            writer = VideoWriter(filePath, fcc, fps, framesize); //Writes the jpg-file to a path.

            if (!writer.isOpened()) {
                cout << "Error opening file for writer" << endl;
                getchar;
                return false;
            }
        }

        bool bSuccess = videoConnection.read(vidframe);
        if (!bSuccess) {
            cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
            return false;
        }

        if (recording == true) writer.write(vidframe);
        break;
    }
    return true;
}

int main(int argc, char* argv[]) {
    Mat cameraFeed;
    Mat cameraFrame;
    Mat HSV, threshold;

    //start an infinite loop where webcam feed is copied to cameraFeed matrix
    //all of our operations will be performed within this loop
    while (1) {
        bool balloon = getVideo(cameraFeed);

        if (!balloon) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        // Read the snapshots that have been taken
        // and stored into this file.
        cameraFrame = imread("img//SNAPSHOT.jpeg");

        Balloon redBalloon("red"), blueBalloon("blue");

        cvtColor(cameraFrame, HSV, CV_BGR2HSV);
        inRange(HSV, redBalloon.getHSVmin(), redBalloon.getHSVmax(), threshold);
        morphOps(threshold);
        getContour(redBalloon, HSV, cameraFrame);

        cvtColor(cameraFrame, HSV, CV_BGR2HSV);
        inRange(HSV, blueBalloon.getHSVmin(), blueBalloon.getHSVmax(), threshold);
        morphOps(threshold);
        getContour(blueBalloon, HSV, cameraFrame);

        string src_path = "img//Red&Blue.jpeg";
        imwrite(src_path, cameraFrame);

        waitKey(30);
    }
    return 0;
}