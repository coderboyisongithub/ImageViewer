#pragma once

#include "Filters.h"
#include "BufferContainer.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>


namespace FaceDetector
{
	class cascadeDetector
	{
		BufferContainer::imageContainer pkg;
		
		
		//flags..
		bool pkg_avail;
	

		int _process(bool detailed)
		{
			

			return  faceMash(detailed);
		}
	protected:
int faceMash(bool fidelity=false)
{

	cv::Mat image_(pkg.h,pkg.w,CV_8UC4,pkg.image);
	
//cv::namedWindow("wind",CV_WINDOW_NORMAL);
//cv::imshow("wind",image_);
//cv::waitKey(500);

		cv::CascadeClassifier face("./classifier/haarcascade_frontalface_alt.xml");
		assert(!face.empty());

		cv::Mat tmp(image_.rows,image_.cols,image_.type());
		image_.copyTo(tmp);

		cv::Size size;

if(fidelity==false)
size=cv::Size(100,100);
else
size=cv::Size(50,50);

			cv::Mat image_grey;
			cvtColor(tmp,image_grey,cv::COLOR_BGR2GRAY);

//	cv::imshow("wind",image_grey);
//cv::waitKey(500);

			cv::equalizeHist(image_grey,image_grey);
			std::vector<cv::Rect>detectedfaces;
			face.detectMultiScale(image_grey,detectedfaces,1.2,3,0|cv::CASCADE_SCALE_IMAGE,size);
 
printf("\n\n%d",detectedfaces.size());
  
 return detectedfaces.size();

}

		public:
			cascadeDetector()
			{
				pkg_avail=false;
			}
			void setParam(BufferContainer::imageContainer src)
			{
				pkg.setParams(src);
				pkg_avail=true;


			}
		int detect(bool detail=false)
		{
			return _process(detail);
		}
		~cascadeDetector()
		{

		}
	};
}
