
#include "visionLib.h"

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
