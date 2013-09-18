
#include "ImaqToMat.h"
#include <time.h>

using namespace cv;

void connectU32(IMAQ_Image *ImageSrc, Mat &Matsrc)
{
	ImageInfo *src; 
	int width, height;
	src = (ImageInfo *) ImageSrc->address;
	imaqGetImageSize((Image *)src, &width, &height);
	Matsrc=Mat(height, width, CV_8UC4, (void*)src->imageStart,src->pixelsPerLine*4);
	
}


void connectU8(IMAQ_Image *ImageSrc, Mat &Matsrc)
{
	ImageInfo *src; 
	int width, height;
	src = (ImageInfo *) ImageSrc->address;
	imaqGetImageSize((Image *)src, &width, &height);
	Matsrc=Mat(height, width, CV_8UC1, (void*)src->imageStart,src->pixelsPerLine*1);
		
}

void connectU8(IMAQ_Image *ImageSrc, Mat &Matsrc, int width ,int height)
{
	ImageInfo *src; 
	src = (ImageInfo *) ImageSrc->address;
	Matsrc=Mat(height, width, CV_8UC1, (void*)src->imageStart,src->pixelsPerLine*1);
		
}


void connectF32(IMAQ_Image *ImageSrc, Mat &Matsrc, int width ,int height)
{
	ImageInfo *src; 
	src = (ImageInfo *) ImageSrc->address;
	imaqSetImageSize((Image *)src, width, height);
	Matsrc=Mat(height, width, CV_32FC1, (void*)src->imageStart,src->pixelsPerLine*1);
		
}


int GetImageType(IMAQ_Image *ImageSrc)
{
	/*image type:
	u8 = 0
	u32 = 4
	*/

	ImageInfo *src; 
	src = (ImageInfo *) ImageSrc->address;
	return (src->imageType);
}

int getLinePoints(vector<cv::Point>  linePoints , int x1 ,int y1 ,int x2, int y2 ,int x_start, int x_end)
{
	float m=(float)(y2-y1)/(float)(x2-x1);
	float b=y1-m*x1;
	
	//vector<cv::Point>  linePoints;
	cv::Point p;
	int j=0;
	for(int i=0, j=x_start;j<=x_end;i++,j++)
	{
		p.x=j;
		p.y=(int)(m*j+b);
		linePoints.push_back(p);
	}

	return 0;
}
