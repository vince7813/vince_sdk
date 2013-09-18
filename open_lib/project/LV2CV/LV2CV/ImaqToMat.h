
#include <opencv2/opencv.hpp>
#include "extcode.h"
#include <nivision.h>

using namespace cv;


	struct IMAQ_Image
{
  char *name;
  Image *address;
} ;


void connectU32(IMAQ_Image *ImageSrc, Mat &Matsrc);
void connectU8(IMAQ_Image *ImageSrc, Mat &Matsrc);
void connectU8(IMAQ_Image *ImageSrc, Mat &Matsrc, int width ,int height);
void connectF32(IMAQ_Image *ImageSrc, Mat &Matsrc, int width ,int height);

int GetImageType(IMAQ_Image *ImageSrc);
	
	