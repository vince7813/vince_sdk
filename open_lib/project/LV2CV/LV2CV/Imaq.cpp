

#include <windows.h>
#include <opencv2/opencv.hpp>

#include<vector>
#include "Imaq.h"

using namespace std;
using namespace cv;

void Imaq::RGBtoImaq(cv::Mat &MatResult, IplImage *CVImageR, IplImage *CVImageG, IplImage *CVImageB)
{
	Mat MatImage(CVImageR);
		
	unsigned char * src, *dstR, *dstG, *dstB;
	src=(unsigned char*)MatResult.data;
	dstR=(unsigned char*) CVImageR->imageData;
	dstG=(unsigned char*) CVImageG->imageData;
	dstB=(unsigned char*) CVImageB->imageData;

	for( int i=0; i<MatImage.rows; i++)
	{
		unsigned char *src_tmp,*dstR_tmp, *dstG_tmp, *dstB_tmp;
		src_tmp=src+ i*MatResult.step;
		dstR_tmp= dstR + i*CVImageR->widthStep;
		dstG_tmp= dstG + i*CVImageG->widthStep;
		dstB_tmp= dstB + i*CVImageB->widthStep;
		for(int j=0;j < MatImage.cols;j++)
		{
			*dstB_tmp=*src_tmp;
			src_tmp++;
			dstB_tmp++;
			*dstG_tmp=*src_tmp;
			src_tmp++;
			dstG_tmp++;
			*dstR_tmp=*src_tmp;
			src_tmp++;
			dstR_tmp++;
		}
	}
}

