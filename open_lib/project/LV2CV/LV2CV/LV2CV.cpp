



#include <windows.h>

#include <string>
#include <vector>
//#include <opencv2/opencv.hpp>
//#include "extcode.h"
//#include <nivision.h>
#include "ImaqToMat.h"
#include "visionLib.h"
#include <math.h>


using namespace std;
using namespace cv;

/////////////////////////////////////////////////////////////////////////////////////////
//basic function

_declspec(dllexport) int imaq_ReadFile(IMAQ_Image *ImageSrc , char *path);
_declspec(dllexport) int imaq_to_opencv(IMAQ_Image *ImageSrc);
_declspec(dllexport) int imaq_RGBtoGray(IMAQ_Image *ImageSrc, IMAQ_Image *ImageDst);
_declspec(dllexport) int imaq_blur(IMAQ_Image *ImageSrc , int kernelSize);
_declspec(dllexport) int imaq_RGBtoYCrCb(IMAQ_Image *ImageSrc);
_declspec(dllexport) int imaq_RGBtoY(IMAQ_Image *ImageSrc,IMAQ_Image *ImageDst);
_declspec(dllexport) int imaq_thresholdU8(IMAQ_Image *ImageSrc , int value , int maxmal);
_declspec(dllexport) int imaq_thresholdU8(IMAQ_Image *ImageSrc , int min , int max ,int value);
_declspec(dllexport) int imaq_findCircles(IMAQ_Image *ImageSrc);
_declspec(dllexport) int imaq_RGBtoHSV(IMAQ_Image *ImageSrc);
_declspec(dllexport) int imaq_ExtractTOColorPlane(IMAQ_Image *ImageSrc, IMAQ_Image *ImageDst , int plane);
_declspec(dllexport) int imaq_overlay_line(IMAQ_Image *ImageSrc ,int *points, unsigned int color);
_declspec(dllexport) int imaq_overlay_rectangle(IMAQ_Image *ImageSrc ,int *points, unsigned int color);
_declspec(dllexport) int imaq_overlay_points(IMAQ_Image *ImageSrc ,int *points, int points_num, unsigned int color);



//connbine function

_declspec(dllexport) float templateMatch(IMAQ_Image *ImageSrc , IMAQ_Image *ImagePattern , IMAQ_Image *Imageresult); 

_declspec(dllexport) int ExtractColor(IMAQ_Image *ImageSrc);
_declspec(dllexport) int ExtractColorGetResult(float *x,float *y, float *radius);
vector<Vec3f> ExtractColorResult;
int ExtractColorResultIndex;


/////////////////////////////////////////////////////////////////////////////////////////
//global variable
double t1,t2; //for time caculate

/////////////////////////////////////////////////////////////////////////////////////////
//caculate function

_declspec(dllexport) int noiseFilter4line(int *data , int arraysize ,int *start , int *end);
_declspec(dllexport) float MTFcaculate(int *data , int data_size);
_declspec(dllexport) float getNextHorizontalPoints(float *points1);
_declspec(dllexport) float getOffsetPoints(float *points1 , float offset);
_declspec(dllexport) float getNextVerticalPoints(float *points1);
_declspec(dllexport) float getVerticalOffsetPoints(float *points1 ,float offset);
_declspec(dllexport) float getOffsetCircleCenter(float *points , float *points1D, float offset);
_declspec(dllexport) float getNextPoints(float *points);
_declspec(dllexport) float elimateCircleBoundary(float *points , float *points1D, float offset);
_declspec(dllexport) float elimateCircleBoundary_vertical(float *points , float *points1D, float offset);
_declspec(dllexport) float getDistance(float *points, float *points2);



///////////////////////////////////////////////////////////////////
int noiseFilter4line(int *data , int arraysize ,int *start , int *end)
{
	int a=0;
	int b=0;
	int c=0;          //--------------------DEBUG到一半
	int d=0;
	bool increase_start=false;
	bool decrease_end=false;
	int startIdx=(int)(arraysize*0.34);
	int endIdx=(int)(startIdx+arraysize*0.37);
	

	for(int i=startIdx+1 , j=endIdx ;i<endIdx+1;i++,j--)
	{	
		a=data[i-1];
		b=data[i];
		c=data[j-1];
		d=data[j];

		if(increase_start==false)
		{
			if((b-a+35) <= 0)
		{
			*start=i;
			increase_start=true;
		}
		}
		if(decrease_end==false)
		{
			
			if((d-c)>=35)
			{
			*end=j-1;
			decrease_end=true;
			}
		}
		
	}

	return 0;
}


float MTFcaculate(int *data , int data_size)
{
	int max=data[0];
	int min=data[0];
	for(int i=1;i<data_size;i++)
	{
		if(data[i]>max)
		{
			max=data[i];
		}
		if(data[i]<min)
		{
			min=data[i];
		}
	}

	return ((float)(max-min)/(float)(max+min));

}


float getNextHorizontalPoints(float *points1)//位移往上+1
{
	float x1=points1[0];
	float y1=points1[1];
	float x2=points1[2];
	float y2=points1[3];
	float x_out1;
	float y_out1=y1-1;
	float x_out2;
	float y_out2=y2-1;
	float m=(y2-y1)/(x2-x1);
	if(m==0)
	{
	points1[1]=y_out1;
	points1[3]=y_out2;
	}
	else
	{
	float b=y2-m*x2;
	float m_vertical=-(1/m);
	float b_vertical1=y1-m_vertical*x1;
	float b_vertical2=y2-m_vertical*x2;
	x_out1=((y_out1-b_vertical1)/m_vertical);
	x_out2=((y_out2-b_vertical2)/m_vertical);
	points1[0]=x_out1;
	points1[1]=y_out1;
	points1[2]=x_out2;
	points1[3]=y_out2;
	}

	return m;
}

float getNextVerticalPoints(float *points1)//位移往左-1
{
	float x1=points1[0];
	float y1=points1[1];
	float x2=points1[2];
	float y2=points1[3];
	float x_out1=x1-1;
	float y_out1=y1;
	float x_out2=x2-1;
	float y_out2=y2;
	float m;
	if((x2-x1)==0)
	{
		m=0;
	}
	else
	{
		m=(y2-y1)/(x2-x1);
	}

	if(m==0)
	{
	points1[0]=x_out1;
	points1[2]=x_out2;
	}
	else
	{
	float b=y2-m*x2;
	float m_vertical=-(1/m);
	float b_vertical1=y1-m_vertical*x1;
	float b_vertical2=y2-m_vertical*x2;
	y_out1 = (b_vertical1 + m_vertical * x_out1);
	y_out2 = (b_vertical2 + m_vertical * x_out2);
	points1[0]=x_out1;
	points1[1]=y_out1;
	points1[2]=x_out2;
	points1[3]=y_out2;
	}

	return m;
}



float getVerticalOffsetPoints(float *points1 ,float offset)//位移往右+offset
{
	float x1=points1[0];
	float y1=points1[1];
	float x2=points1[2];
	float y2=points1[3];
	float m;
	if((x2-x1)==0)
	{
		m=0;
	}
	else
	{
		m=(y2-y1)/(x2-x1);
	}

	if(m==0)
	{
	points1[0]=x1+offset;
	points1[2]=x2+offset;
	}
	else
	{
	float b=y2-m*x2;
	float m_vertical=-(1/m);
	float b_vertical1=y1-m_vertical*x1;
	float b_vertical2=y2-m_vertical*x2;
	y1=(m_vertical*(x1+offset)+b_vertical1);
	y2=(m_vertical*(x2+offset)+b_vertical2);
	points1[0]=x1+offset;
	points1[1]=y1;
	points1[2]=x2+offset;
	points1[3]=y2;
	}

	return m;
}

float getOffsetPoints(float *points1 ,float offset)//位移往下+offset
{
	float x1=points1[0];
	float y1=points1[1];
	float x2=points1[2];
	float y2=points1[3];
	float m=(y2-y1)/(x2-x1);
	if(m==0)
	{
	points1[1]=y1+offset;
	points1[3]=y2+offset;
	}
	else
	{
	float b=y2-m*x2;
	float m_vertical=-(1/m);
	float b_vertical1=y1-m_vertical*x1;
	float b_vertical2=y2-m_vertical*x2;
	x1=((y1+offset-b_vertical1)/m_vertical);
	x2=((y2+offset-b_vertical2)/m_vertical);
	points1[0]=x1;
	points1[1]=y1+offset;
	points1[2]=x2;
	points1[3]=y2+offset;
	}

	return m;
}




float elimateCircleBoundary(float *points , float *points1D, float offset)
{
	float x1=points[0];
	float y1=points[1];
	float radius1=points[2];
	float x2=points[3];
	float y2=points[4];
	float radius2=points[5];
	float m=(y2-y1)/(x2-x1);
	if(m!=0)
	{
	float b=y2-m*x2;
	points1D[0]=x1+radius1+offset;
	points1D[1]=m*points1D[0]+b;
	points1D[2]=x2-radius2-offset;
	points1D[3]=m*points1D[2]+b;
	}
	else
	{
	points1D[0]=x1+radius1+offset;
	points1D[1]=points[1];
	points1D[2]=x2-radius2-offset;
	points1D[3]=points[4];
	}

	return m;
}





float elimateCircleBoundary_vertical(float *points , float *points1D, float offset)
{
	float x1=points[0];
	float y1=points[1];
	float radius1=points[2];
	float x2=points[3];
	float y2=points[4];
	float radius2=points[5];
	float m;
	if((x2-x1)==0)
	{
		m=0;
	}
	else
	{
		m=(y2-y1)/(x2-x1);
	}

	if(m!=0)
	{
	float b=y2-m*x2;
	points1D[1]=y1+radius1+offset;
	points1D[0]=(points1D[1]-b)/m;
	points1D[3]=y2-radius2-offset;
	points1D[2]=(points1D[3]-b)/m;
	}
	else
	{
	points1D[0]=points[0];
	points1D[1]=y1+radius1+offset;
	points1D[2]=points[3];
	points1D[3]=y2-radius2-offset;
	}

	return m;
}

float getDistance(float *points, float *points2)
{
	cv::Point2f p1,p2,p3,p4;
	p1.x=points[0];
	p1.y=points[1];
	p2.x=points[2];
	p2.y=points[3];
	p3.x=points2[0];
	p3.y=points2[1];
	p4.x=points2[2];
	p4.y=points2[3];

	float a1=sqrt((p1.x-p3.x)*(p1.x-p3.x)+(p1.y-p3.y)*(p1.y-p3.y));
	float a2=sqrt((p2.x-p4.x)*(p2.x-p4.x)+(p2.y-p4.y)*(p2.y-p4.y));

	if(((a1+a2)/2)<1.5) return -1;
	return 0;

	
}



float getOffsetCircleCenter(float *points , float *points1D, float offset)
{
	cv::Point2f p1,p2,p3;		    //input point
	cv::Point2f op1,op2,op3,op4;	//output point
	p1.x=points[0];       //B
	p1.y=points[1];					//              [3] R            3
	float radius1=points[2];		//               ^
	p2.x=points[3];		  //G		//               |
	p2.y=points[4];					//               |    vector
	float radius2=points[5];		//               |               4
	p3.x=points[6];       //R		//		[2]<----[1]
	p3.y=points[7];					//       G        B
	float radius3=points[8];		//         1      2

	//計算單位向量
	float v12_length=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
	cv::Point2f v12;
	v12.x=(p2.x-p1.x)/v12_length;
	v12.y=(p2.y-p1.y)/v12_length;

	float v13_length=sqrt((p3.x-p1.x)*(p3.x-p1.x)+(p3.y-p1.y)*(p3.y-p1.y));
	cv::Point2f v13;
	v13.x=(p3.x-p1.x)/v13_length;
	v13.y=(p3.y-p1.y)/v13_length;

	//計算offset 
	op1=p2+(-v13*offset);
	op2=p1+(-v13*offset);
	op3=p3+(-v12*offset);
	op4=p1+(-v12*offset);
	
	//填回座標
	points1D[0]=op1.x;
	points1D[1]=op1.y;
	points1D[2]=op2.x;
	points1D[3]=op2.y;
	points1D[4]=op3.x;
	points1D[5]=op3.y;
	points1D[6]=op4.x;
	points1D[7]=op4.y;

	return -1;

}

float getNextPoints(float *points)
{
	cv::Point2f p1,p2,p3,p4;
	p1.x=points[0];
	p1.y=points[1];
	p2.x=points[2];
	p2.y=points[3];
	p3.x=points[4];
	p3.y=points[5];
	p4.x=points[6];
	p4.y=points[7];

	//計算單位向量
	float v12_length=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	cv::Point2f v12;
	v12.x=(p1.x-p2.x)/v12_length;
	v12.y=(p1.y-p2.y)/v12_length;

	float v13_length=sqrt((p3.x-p4.x)*(p3.x-p4.x)+(p3.y-p4.y)*(p3.y-p4.y));
	cv::Point2f v13;
	v13.x=(p3.x-p4.x)/v13_length;
	v13.y=(p3.y-p4.y)/v13_length;

	//計算offset 
	p1+=(v13*1);
	p2+=(v13*1);
	p3+=(v12*1);
	p4+=(v12*1);

	//填回座標
	points[0]=p1.x;
	points[1]=p1.y;
	points[2]=p2.x;
	points[3]=p2.y;
	points[4]=p3.x;
	points[5]=p3.y;
	points[6]=p4.x;
	points[7]=p4.y;

	return v12_length;
}

///////////////////////////////////////////////////////////////////

int imaq_to_opencv(IMAQ_Image *ImageSrc){
	Mat Matsrc;

	return GetImageType(ImageSrc);

	connectU32(ImageSrc,Matsrc);

	//cvtColor(Matsrc, Matsrc, CV_RGB2GRAY);

	
	blur( Matsrc, Matsrc, Size( 17, 17 ) );
	return 0;
	
}

int imaq_blur(IMAQ_Image *ImageSrc , int kernelSize)
{
	Mat Matsrc;
	int type;
	type=GetImageType(ImageSrc);
	
	int ksize;
	ksize=(kernelSize%2==0?(kernelSize+1):kernelSize);


	if(type==0){
		connectU8(ImageSrc,Matsrc);
		blur( Matsrc, Matsrc, Size( ksize, ksize ) );
		return 0;
	}
	if(type==4)
	{
		connectU32(ImageSrc,Matsrc);
		blur( Matsrc, Matsrc, Size( ksize, ksize ) );
		return 0;
	}

	return -1;

}

int imaq_RGBtoY(IMAQ_Image *ImageSrc,IMAQ_Image *ImageDst)
{
	Mat Matsrc;
	Mat Matdst;
	Mat cvdst;
	
	connectU32(ImageSrc,Matsrc);
	connectU8(ImageDst,Matdst);

	cvtColor(Matsrc,cvdst,CV_BGRA2BGR);		//u32 轉 u24
	cvtColor(cvdst, cvdst,CV_BGR2YCrCb);   //src 轉Ycrcb
		
	for(int i=0;i<Matdst.rows;i++)
	{
		for(int j=0;j<Matdst.cols;j++)
		{
		//B G R
	Matdst.at<uchar>(i,j)=cvdst.at<cv::Vec3b>(i,j)[0]; 
		}
	}

	return 0;

}


int imaq_RGBtoYCrCb(IMAQ_Image *ImageSrc){

	Mat Matsrc;
	Mat cvdst;
	
	connectU32(ImageSrc,Matsrc);

	cvtColor(Matsrc,cvdst,CV_RGBA2BGR);		//u32 轉 u24
	cvtColor(cvdst, cvdst,CV_BGR2YCrCb);   //src 轉Ycrcb
		
	for(int i=0;i<Matsrc.rows;i++)
	{
		for(int j=0;j<Matsrc.cols;j++)
		{
		//B G R
	Matsrc.at<cv::Vec4b>(i,j)[0]=cvdst.at<cv::Vec3b>(i,j)[2]; 
	Matsrc.at<cv::Vec4b>(i,j)[1]=cvdst.at<cv::Vec3b>(i,j)[0];
	Matsrc.at<cv::Vec4b>(i,j)[2]=cvdst.at<cv::Vec3b>(i,j)[1];
		}
	}

	return 0;
}

int imaq_RGBtoHSV(IMAQ_Image *ImageSrc){

	Mat Matsrc;
	Mat cvdst;
	
	connectU32(ImageSrc,Matsrc);

	cvtColor(Matsrc,cvdst,CV_RGBA2BGR);		//u32 轉 u24
	cvtColor(cvdst, cvdst,CV_BGR2HSV);   //src 轉HSV
		
	for(int i=0;i<Matsrc.rows;i++)
	{
		for(int j=0;j<Matsrc.cols;j++)
		{
		//B G R
	Matsrc.at<cv::Vec4b>(i,j)[0]=cvdst.at<cv::Vec3b>(i,j)[2]; 
	Matsrc.at<cv::Vec4b>(i,j)[1]=cvdst.at<cv::Vec3b>(i,j)[1];
	Matsrc.at<cv::Vec4b>(i,j)[2]=cvdst.at<cv::Vec3b>(i,j)[0];
		}
	}

	return 0;
}

int imaq_ExtractTOColorPlane(IMAQ_Image *ImageSrc, IMAQ_Image *ImageDst , int plane){

	//plane:0 = R
	//plane:1 = G
	//plane:2 = B
	Mat Matsrc;
	Mat Matdst;
	Mat cvsrc;
	connectU32(ImageSrc,Matsrc);
	connectU8(ImageDst,Matdst,Matsrc.cols,Matsrc.rows);

	cvtColor(Matsrc,cvsrc,CV_RGBA2BGR);		//u32 轉 u24

	if(plane<0 && plane>2) //防止plane過大或過小
	{
		plane=0;
	}
			
	for(int i=0;i<Matsrc.rows;i++)
	{
		for(int j=0;j<Matsrc.cols;j++)
		{
	Matdst.at<uchar>(i,j)=cvsrc.at<cv::Vec3b>(i,j)[plane]; 
		}
	}

	return 0;
}




int imaq_thresholdU8(IMAQ_Image *ImageSrc , int min , int max ,int value)
{
	//可以只取指定的區間(min,max) ，將值指定為value
	Mat Matsrc;

	connectU8(ImageSrc,Matsrc);

	cv::threshold(Matsrc,Matsrc,max,255,THRESH_TOZERO_INV);//濾掉max以上的值
	cv::threshold(Matsrc,Matsrc,min,value,THRESH_BINARY);  //濾掉min以下的值 設成value
	return 0;

}



int imaq_thresholdU8(IMAQ_Image *ImageSrc , int value , int maxmal=255)
{
	Mat Matsrc;

	connectU8(ImageSrc,Matsrc);

	cv::threshold(Matsrc,Matsrc,value,maxmal,THRESH_BINARY);

	return 0;

}

int imaq_findCircles(IMAQ_Image *ImageSrc)
{
	Mat Matsrc;
	Mat MatsrcU8;

	vector<Vec3f> circles;
	connectU32(ImageSrc, Matsrc);
	cv::cvtColor(Matsrc, MatsrcU8,CV_RGBA2GRAY);
	
	HoughCircles(MatsrcU8,circles,CV_HOUGH_GRADIENT,2, MatsrcU8.rows/4, 10,60,10,50);
	//imshow( "circles", MatsrcU8 );
	
	//return (int)circles.size();

	for( size_t i = 0; i < circles.size(); i++ )
    {
         cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle(MatsrcU8, center, 3, Scalar(0,255,0), -1, 8, 0 );
         // draw the circle outline
         circle( MatsrcU8, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    namedWindow( "circles",CV_WINDOW_NORMAL );
    imshow( "circles", MatsrcU8 );

	return 0;


}


int imaq_overlay_points(IMAQ_Image *ImageSrc ,int *points, int points_num, unsigned int color)
{
	Mat Matsrc;
	int type;
	type=GetImageType(ImageSrc);
	int R_value=color/65535;
	int G_value=(color-(R_value*65535))/256;
	int B_value=color-(G_value*256)-(R_value*65535);
	
	cv::Point a;

	if(type==0){
		connectU8(ImageSrc,Matsrc);
		Scalar color_value=Scalar((B_value+G_value+R_value)/3);
		
		for(int i=0;i<points_num;i+=2)
	{
		a.x=points[i];
		a.y=points[i+1];
		cv::circle(Matsrc,a,3,color_value,2,8,0); 
	}
		

	}
	if(type==4)
	{
		connectU32(ImageSrc,Matsrc);
		Scalar color_value=Scalar(B_value,G_value,R_value);
		
		for(int i=0;i<points_num;i+=2)
	{
		a.x=points[i];
		a.y=points[i+1];
		cv::circle(Matsrc,a,3,color_value,2,8,0); 
	}

	}
	
	return R_value;

}


int imaq_overlay_line(IMAQ_Image *ImageSrc ,int *points, unsigned int color)
{
	Mat Matsrc;
	int type;
	type=GetImageType(ImageSrc);
	int R_value=color/65535;
	int G_value=(color-(R_value*65535))/256;
	int B_value=color-(G_value*256)-(R_value*65535);

	cv::Point start,end;
	start.x=points[0];
	start.y=points[1];
	end.x=points[2];
	end.y=points[3];
	

	if(type==0){
		connectU8(ImageSrc,Matsrc);
		Scalar color_value=Scalar((B_value+G_value+R_value)/3);
		cv::line(Matsrc,start,end,color_value,1);

	}
	if(type==4)
	{
		connectU32(ImageSrc,Matsrc);
		Scalar color_value=Scalar(B_value,G_value,R_value);
		cv::line(Matsrc,start,end,color_value,1);

	}
	
	return R_value;

}


int imaq_overlay_rectangle(IMAQ_Image *ImageSrc ,int *points, unsigned int color)
{
	Mat Matsrc;
	int type;
	type=GetImageType(ImageSrc);
	int R_value=color/65535;
	int G_value=(color-(R_value*65535))/256;
	int B_value=color-(G_value*256)-(R_value*65535);

	cv::Point start,end;
	start.x=points[0];
	start.y=points[1];
	end.x=points[2];
	end.y=points[3];
	cv::Rect aa(start,end);

	if(type==0){
		connectU8(ImageSrc,Matsrc);
		Scalar color_value=Scalar((B_value+G_value+R_value)/3);

		cv::rectangle(Matsrc,aa,color_value,1);

	}
	if(type==4)
	{
		connectU32(ImageSrc,Matsrc);
		Scalar color_value=Scalar(B_value,G_value,R_value);

		cv::rectangle(Matsrc,aa,color_value,1);

	}
	
	return R_value;

}





int imaq_ReadFile(IMAQ_Image *ImageSrc , char *path)//未完成 無法使用 須將Mat資料存入ImageSrc
{
	Mat Matsrc;
	int type;
	type=GetImageType(ImageSrc);
	
	Matsrc=cv::imread("path");

	return 0;
	if(type==0)
	{
		connectU8(ImageSrc,Matsrc);
	}
	if(type==4)
	{
		connectU32(ImageSrc,Matsrc);
		imshow("00",Matsrc);
	}
	
	return 0;

}

///////////////////////combine function////////////////////////////

int ExtractColorGetResult(float *x,float *y, float *radius)
{
	if(ExtractColorResult.size()==0) return 1;

	*x=(ExtractColorResult[ExtractColorResultIndex][0]);
	*y=(ExtractColorResult[ExtractColorResultIndex][1]);
	*radius=(ExtractColorResult[ExtractColorResultIndex][2]);

	ExtractColorResultIndex++;
	if(ExtractColorResultIndex == ExtractColorResult.size())
	{
		return 1;
	}
	else
	{		
		return 0;
	}

}
int ExtractColor(IMAQ_Image *ImageSrc){

	Mat Matsrc;
	Mat cvsrc;
	Mat HSVsrc;
	Mat Matresult;
	Mat Matcircle;  
	
	Mat biR(Matsrc.size(),CV_32FC1);
	Mat biB(Matsrc.size(),CV_32FC1); 
	Mat biG(Matsrc.size(),CV_32FC1); 


	Mat biAdd;

	connectU32(ImageSrc,Matsrc);

	cvtColor(Matsrc,cvsrc,CV_RGBA2RGB);		//u32 轉 u24
	cvtColor(cvsrc, HSVsrc,CV_RGB2HSV);   //src 轉Ycrcb
	/*
	H_value:
	Red=120    Blue=0    Green=60    Yellow=90
	*/
	cv::Rect roi(260, 480, 130, 130);
		
	cv::inRange(HSVsrc,cv::Scalar(105,136,136), cv::Scalar(135,255,255),biR);
	cv::inRange(HSVsrc,cv::Scalar(0  ,105,105), cv::Scalar(25,255,255),biB);
	cv::inRange(HSVsrc,cv::Scalar(42 ,83, 83), cv::Scalar(78,255,255),biG);

	biAdd=biR+biB+biG;

	imshow("circle threshold",biAdd);  //debug用 看過threshold的圓是否完整

/* 測試用，看HSV值
		for(int i=0;i<Matsrc.rows;i++)
	{
		for(int j=0;j<Matsrc.cols;j++)
		{
		//B G R
	Matsrc.at<cv::Vec4b>(i,j)[0]=HSVsrc.at<cv::Vec3b>(i,j)[0]; 
	Matsrc.at<cv::Vec4b>(i,j)[1]=HSVsrc.at<cv::Vec3b>(i,j)[1];
	Matsrc.at<cv::Vec4b>(i,j)[2]=HSVsrc.at<cv::Vec3b>(i,j)[2];
		}
	}
		return -2;
*/
	//imshow("circle threshold",biAdd);

	//cvsrc.copyTo(Matresult,biAdd);//可顯示過MASK後的原圖

	//imshow("color mask",Matresult);

	GaussianBlur(biB, biB, Size(5, 5), 3, 3 );
	GaussianBlur(biG, biG, Size(5, 5), 3, 3 );
	GaussianBlur(biR, biR, Size(5, 5), 3, 3 );

	vector<vector<cv::Point> > contoursB;
	vector<vector<cv::Point> > contoursG;
	vector<vector<cv::Point> > contoursR;
	vector<Vec4i> hierarchyB;
	vector<Vec4i> hierarchyG;
	vector<Vec4i> hierarchyR;

	findContours( biB, contoursB, hierarchyB, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
    findContours( biG, contoursG, hierarchyG, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	findContours( biR, contoursR, hierarchyR, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
 
	vector<vector<cv::Point> > contours_polyB( contoursB.size() );
    vector<vector<cv::Point> > contours_polyG( contoursG.size() );
	vector<vector<cv::Point> > contours_polyR( contoursG.size() );
	
	vector<Point2f>centerB( contoursB.size() );
    vector<Point2f>centerG( contoursG.size() );
	vector<Point2f>centerR( contoursR.size() );
	
	vector<float>radiusB( contoursB.size() );
    vector<float>radiusG( contoursG.size() );
	vector<float>radiusR( contoursR.size() );

	ExtractColorResult.clear();
	Scalar color = Scalar(50,255,50 );
	cv::Vec3f circlePoints;

	 for(unsigned int i = 0; i < contoursB.size(); i++ )
		 { 
			approxPolyDP( Mat(contoursB[i]), contours_polyB[i], 3, true );
			approxPolyDP( Mat(contoursG[i]), contours_polyG[i], 3, true );
			approxPolyDP( Mat(contoursR[i]), contours_polyR[i], 3, true );
			minEnclosingCircle( (Mat)contours_polyB[i], centerB[i], radiusB[i] );
			minEnclosingCircle( (Mat)contours_polyG[i], centerG[i], radiusG[i] );
			minEnclosingCircle( (Mat)contours_polyR[i], centerR[i], radiusR[i] );
				if(radiusB[i]<5 || radiusG[i]<5  ||  radiusR[i]<5) //判斷找到的圓半徑是否過小
				{
					return -5;
				}
		
			circlePoints[0]=centerB[i].x;
			circlePoints[1]=centerB[i].y;
			circlePoints[2]=radiusB[i];
			ExtractColorResult.push_back(circlePoints);

			circlePoints[0]=centerG[i].x;
			circlePoints[1]=centerG[i].y;
			circlePoints[2]=radiusG[i];
			ExtractColorResult.push_back(circlePoints);

			circlePoints[0]=centerR[i].x;
			circlePoints[1]=centerR[i].y;
			circlePoints[2]=radiusR[i];
			ExtractColorResult.push_back(circlePoints);
		
			drawContours( cvsrc, contours_polyB, i, color, 1, 8, vector<Vec4i>(), 0, cv::Point() );
			drawContours( cvsrc, contours_polyG, i, color, 1, 8, vector<Vec4i>(), 0, cv::Point() );
			drawContours( cvsrc, contours_polyR, i, color, 1, 8, vector<Vec4i>(), 0, cv::Point() );
		    circle( cvsrc, centerB[i], (int)radiusB[i], color, 2, 8, 0 );
			circle( cvsrc, centerG[i], (int)radiusG[i], color, 2, 8, 0 );
			circle( cvsrc, centerR[i], (int)radiusR[i], color, 2, 8, 0 );
		 }


  	if(centerB.size() !=1 || centerG.size() !=1 || centerR.size() !=1) //判斷是否三個圓都有
		{
			return -1;
		}


	for(int i=0;i<Matsrc.rows;i++)
	{
		for(int j=0;j<Matsrc.cols;j++)
		{
		//B G R
		Matsrc.at<cv::Vec4b>(i,j)[0]=cvsrc.at<cv::Vec3b>(i,j)[0]; 
		Matsrc.at<cv::Vec4b>(i,j)[1]=cvsrc.at<cv::Vec3b>(i,j)[1];
		Matsrc.at<cv::Vec4b>(i,j)[2]=cvsrc.at<cv::Vec3b>(i,j)[2];
		}
	}
			
	ExtractColorResultIndex=0;
	return 0;

}


float templateMatch(IMAQ_Image *ImageSrc , IMAQ_Image *ImagePattern , IMAQ_Image *Imageresult)
{
	Mat Src;
	Mat Pattern;
	Mat Res;
	int type=GetImageType(ImageSrc);
	double maxVal;
	
	if(type==0)
	{
		connectU8(ImageSrc,Src);
		connectU8(ImagePattern,Pattern);
	}
	if(type==4)
	{
		connectU32(ImageSrc,Src);
		connectU32(ImagePattern,Pattern);

	}

	//Res.create( Src.cols-Pattern.cols+1, Src.rows-Pattern.rows+1, CV_32FC1 );

	/*
	還沒解出來~~~~~~~~~~~~~~
		
	*/

	connectF32(Imageresult, Res , Src.cols-Pattern.cols+1 , Src.rows-Pattern.rows+1);
	float k;
	for(int i=0;i<Src.rows-Pattern.rows+1;i++)
	{
		for(int j=0;j<Src.cols-Pattern.cols+1;j++)
		{
			k=(float)(i*(Src.cols-Pattern.cols+1)+j);
			Res.at<float>(i,j)=k;
		}
		//Imageresult->pixelsPerLine-MatResult_cols
	}



	//return Res.step;

	//return Res.cols*10000+Res.rows;
	
	cv::matchTemplate(Src,Pattern,Res,CV_TM_CCOEFF_NORMED);

	minMaxLoc(Res, NULL, &maxVal, NULL,NULL); 

	imshow("123",Res);



	return (float)(Res.channels());

}