// opencv_dll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main()
{
    Mat image;

	image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);	// Read the file
  
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl;
		system("pause");
        return -1;
    }
 
    namedWindow( "Lena - Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Lena - Display window", image );                   // Show our image inside it.
 
    waitKey(0);											 // Wait for a keystroke in the window
    return 0;
}


