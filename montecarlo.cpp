/*	Copyright (C) 2018, Victor G. Merino
	This is a basic implementation for calculating number Pi
	using Montecarlo estimation and representing graphically
	with OpenCV
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <iomanip>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

long double time(void){
	struct rusage usage;
	getrusage(RUSAGE_SELF,&usage);
	return( (long double) usage.ru_utime.tv_sec + (long double) usage.ru_utime.tv_usec/1e6);
}

void delay(long double t_d){

	long double start = time();
	long double t = time() - start;

	while(t < t_d) t = time() - start;
}


int main()
{
	int x = 0;
	int y = 0;
	int N = 0;
	int C = 0;

	long double PI = 0;

	Mat m(Size(500,500),CV_8UC3, Scalar(255,255,255));

	cout << "Drawing circle..." << endl;
	circle(m,Point(250,250),250,Scalar(0,0,0),2);

	cout << "Running Montecarlo Pi Estimation algorythm..." << endl;
	while(1)
	{
		x = rand()%500-250;
		y = rand()%500-250;

		N++;

		int module = sqrt(pow(x,2)+pow(y,2));
		//cout << "x: " << x << "  y: " << y << "  module: " << module << endl;

		x = x+250;
		y = y+250;

		if(module < 250){
			C++;
			circle(m,Point(x,y),1,Scalar(0,155,100),2);
		}else{
			circle(m,Point(x,y),1,Scalar(0,100,155),2);
		}

		PI = (4*float(C))/(float(N));

		imshow("Montecarlo",m);
		waitKey(1);

		if(N%100 == 0) cout << "pi = " << PI << endl;
	}
	
	return 0;	
}