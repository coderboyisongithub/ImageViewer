#ifndef CV_
#define CV_

#include <opencv2\opencv.hpp>
#include <iostream>




class Insight_
{
	
public:
	cv::Mat image;
	Insight_()
	{

	}
	bool loadImage(std::string imagePath)
	{
		image=cv::imread(imagePath.c_str());
		if(image.empty())
		{
			//cv::cvtColor(image,image,CV_BGRA2BGR);
			return 0;
		}
		else
		{
			return 1;
		}

	}

	cv::Mat getImage()
	{
		return image;
	}
	unsigned char* getImageData()
	{
		if(!image.empty())
		{
			cv::flip(image,image,0);
			puts("NOPE");
			return ((unsigned char*)image.data);}
		else
			return NULL;
	}


};

#endif