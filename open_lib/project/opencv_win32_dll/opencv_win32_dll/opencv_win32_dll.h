

#include <cstdlib>
#include <cstdio>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>



using namespace cv;
using namespace std;
 
/* 

#ifdef __cplusplus
extern "C" {
#endif
*/
#define CV_API __declspec(dllexport)


CV_API int test();

/*

#ifdef __cplusplus
}
#endif
*/