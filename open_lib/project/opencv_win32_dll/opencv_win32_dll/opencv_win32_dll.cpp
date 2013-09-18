// opencv_win32_dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "opencv_win32_dll.h"


using namespace cv;
using namespace std;
 

/*

#ifdef __cplusplus
extern "C" {
#endif
*/
int test()
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
	return 0;
}

/*


#ifdef __cplusplus
}
#endif
*/