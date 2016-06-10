#include "mainWindow.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

 int main( int argc, char** argv )
 {
    Xbee *xbee;
    //xbee = new Xbee("/dev/ttyUSB0");
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }


    int iLowH = 5;
    int iHighH = 36;
    int iLowS = 111;
    int iHighS = 255;
    int iLowV = 132;
    int iHighV = 212;



    int conF = 0;
    int conB = 0;
    int conR = 0;
    int conL = 0;


    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);
    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);
    createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);


    int iLastX = -1;
    int iLastY = -1;

    //Capture a temporary image from the camera
    Mat imgTmp;
    cap.read(imgTmp);

    //Create a black image with the size as the camera output
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;


    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
        Mat imgThresholded;
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image


        //Mat imgThresholdedg;
        //inRange(imgHSV, Scalar(iLowHg, iLowSg, iLowVg), Scalar(iHighHg, iHighSg, iHighVg), imgThresholdedg);
        //Mat imgThresholdedb;
        //inRange(imgHSV, Scalar(iLowHb, iLowSb, iLowVb), Scalar(iHighHb, iHighSb, iHighVb), imgThresholdedb);

        //morphological opening (removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        //morphological closing (removes small holes from the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);

        //Moments oMomentsg = moments(imgThresholdedg);
        //Moments oMomentsb = moments(imgThresholdedb);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArear = oMoments.m00;

        //double dAreag = oMomentsg.m00;
        //double dAreab = oMomentsb.m00;

        xbee = new Xbee("/dev/ttyUSB0");

        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
        if (dArear > 10000)
        {
        //calculate the position of the ball
            int posX = dM10 / dArear;
            int posY = dM01 / dArear;
            if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
                //cout << posX <<endl;
                //cout << posY <<endl;
                //my control
                int dirX = iLastX - posX;
                int dirY = iLastY - posY;

                //cout << "--" <<endl;
                //cout << "dirX=" << dirX <<endl;
                cout << "--" <<endl;
                //cout << "dirY=" << dirY <<endl;
                /*
                if (dirX > 70)
                {
                    if (conR <2 )
                        conR = conR + 1;
                    else
                    {
                        cout << 'R' <<endl;
                        xbee->setDir('r');
                        xbee->start();
                        conR =0;
                    }
                }
                if (dirX < -70)
                {
                    if (conL <2 )
                        conL = conL + 1;
                    else
                    {
                        cout << 'L' <<endl;
                        xbee->setDir('l');
                        xbee->start();
                        conL =0;
                    }
                }
                if (dirY > 70)
                {
                    if (conF <2 )
                        conF = conF + 1;
                    else
                    {
                        cout << 'F' <<endl;
                        xbee->setDir('f');
                        xbee->start();
                        conF =0;
                    }
                }
                if (dirY < -70)
                {
                    if (conB <2 )
                        conB = conB + 1;
                    else
                    {
                        cout << 'B' <<endl;
                        xbee->setDir('b');
                        xbee->start();
                        conB =0;
                    }
                }
                */

                if (dirX > 50)
                {
                    cout << 'R' <<endl;
                    xbee->setDir('r');
                    xbee->start();
                    if (dirY > 50)
                    {
                        cout << 'F' <<endl;
                        xbee->setDir('f');
                        xbee->start();
                    }
                    if (dirY < -50)
                    {
                        cout << 'B' <<endl;
                        xbee->setDir('b');
                        xbee->start();
                    }
                }
                if (dirX < -50)
                {
                    cout << 'L' <<endl;
                    xbee->setDir('l');
                    xbee->start();
                    if (dirY > 50)
                    {
                        cout << 'F' <<endl;
                        xbee->setDir('f');
                        xbee->start();
                    }
                    if (dirY < -50)
                    {
                        cout << 'B' <<endl;
                        xbee->setDir('b');
                        xbee->start();
                    }
                }


            }

            iLastX = posX;
            iLastY = posY;
        }
        /*
        if (dAreag > 10000)
        {
        }
        if (dAreab > 10000)
        {
        }
        */
        imshow("Thresholded Image", imgThresholded); //show the thresholded image

        imgOriginal = imgOriginal + imgLines;
        imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
   }

   return 0;
}
