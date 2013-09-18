// opencv_win32_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>


#define CV_API __declspec(dllimport)

CV_API int test();

int main()
{
	test();

}

