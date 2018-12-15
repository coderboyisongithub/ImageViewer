#ifndef FILTERS_H
#define	FILTERS_H

#include <opencv2\opencv.hpp>
#include <iostream>
#include <omp.h>

namespace ImageProcessor
{
	namespace Filters
	{
	class Blur
	{
		unsigned char *image;  //raw input image..
		unsigned char *processed_image; //processed image
		int h,w,c; //image discriptors..
		//flags
		bool ready;
		bool open;
		bool MP;
		int kernel_size;


		void _process()
		{

			
			//for(int loop=0;loop<kernel_size;loop++) 
			if(kernel_size>0)
			{
			/*
				if(processed_image!=NULL)
				{
					free(processed_image);
					processed_image=NULL;
				}
				else
					processed_image=(unsigned char*)malloc(sizeof(unsigned char)*w*h);
				
				strcpy_s((char*)processed_image,sizeof(unsigned char)*w*h,(char*)image);
				*/
				
				
				if(processed_image!=NULL) //de-allocate and then fire
				{
					free(processed_image);
					processed_image=NULL;
				}
				else;
					
				processed_image=(unsigned char*)malloc(sizeof(unsigned char)*w*h*4);
				memcpy(processed_image,image,sizeof(unsigned char)*w*h*4);
				cv::Mat IMG(h,w,CV_8UC4,processed_image);
				cv::blur(IMG,IMG,cv::Size(kernel_size,kernel_size));
				IMG.deallocate();
	
			}
			
			else
				return;
			

		}
	public:
		Blur()
		{
			
			image=NULL;
			processed_image=NULL;
			kernel_size=1;
			open=true;
			MP=false;
		}
/*
void render()
		{
			ImGui::Begin("Blue",&open);
			ImGui::BeginGroup();
			ImGui::SliderInt("Kernel Size:",&kernel_size,0,20);
			

			ImGui::EndGroup();
		if(saved_kernel_size!=kernel_size)
		{
				saved_kernel_size=kernel_size;
			if(ImGui::IsItemHovered())
			{
				printf("processing..\nBlur kernel(%dx%d)",kernel_size,kernel_size);
				_process();
			}
			else;
		}
			else;
		
			ImGui::End();


		}
	*/

void setimage(unsigned char *src,int height,int width,int channels)
		{
			image=src;
			//processed_image=image;
			h=height;
			w=width;
			c=channels;
	//		kernel_size=ksize;
//			_process();
			
		} 
unsigned char* getimage()
{
return processed_image;
//	return image;
}
void setKernelSize(int new_Size)
{
	kernel_size=new_Size;
}
void process()
{
	_process();


}
void enableMultiProcessing(bool descesion)
{
	MP=descesion;
}

	~Blur()
{

}

	};
	class Retro
	{
		unsigned char *image,*processed_image;
		int h,w,c;
		int filter_magnitude;

		bool ready;
		void _process()
		{
if(processed_image!=NULL)
	{
				free(processed_image);
				processed_image=NULL;
	}

			//new allocation for processed image...

processed_image=(unsigned char*)malloc(sizeof(unsigned char)*w*h*4);

memcpy(processed_image,image,sizeof(unsigned char)*w*h*4);
cv::Mat raw_image(h,w,CV_8UC4,(void*)processed_image);
 

//partion of image
cv::Mat part[4];
part[0]=raw_image.colRange(0,w/2); //pointer to raw_image
part[1]=raw_image.colRange(w/2,w); //pointer to raw_image

int loop=0;


#pragma omp parallel for shared(loop) schedule(dynamic)
for(loop=0;loop<2;loop++)
{

//instruction excuted in serial on each processor...

		std::vector<cv::Mat>channel;
		cv::split(part[loop],channel);
		int r,c;
for(int loop=0;loop<filter_magnitude;loop++)
		cv::GaussianBlur(channel[2],channel[2],cv::Size(3,3),0.5);
		cv::merge(channel,part[loop]);
}

/*

cv::Mat raw_image(h,w,CV_8UC4,(void*)processed_image);

std::vector<cv::Mat>channel;
cv::split(raw_image,channel);
int r,c;
for(int loop=0;loop<filter_magnitude;loop++)
	cv::GaussianBlur(channel[2],channel[2],cv::Size(5,5),0.5);

cv::merge(channel,raw_image);
*/
//raw_image.deallocate();

	}
		
	public:
		Retro()
		{
			image=processed_image=NULL;
			ready=false;
		}
		void setimage(unsigned char *src,int height,int width,int channels)
		{
			image=src;
			
			h=height;
			w=width;
			c=channels;
		} 
	unsigned char* getimage()
		{
			return processed_image;
		}
	void setFilterStrength(int strength)
	{
		filter_magnitude=strength;
	}
	void process()
	{
		_process();
	}
	};


	//#sharpness filter...


	class Sharp
	{
		unsigned char *image,*processed_image;
		int w,h,c;
		//flags.
		bool ready;       //ready or not.
		float sharpness; //amount of sharpness to be done..
		void init_parameters()
		{
			image=processed_image=NULL;
			ready=false;
			sharpness=0.0;


		}
		void _process()
		{
			if(processed_image!=NULL)
	{
				free(processed_image);
				processed_image=NULL;
	}

			//new allocation for processed image...
processed_image=(unsigned char*)malloc(sizeof(unsigned char)*w*h*4);
memcpy(processed_image,image,sizeof(unsigned char)*w*h*4);

cv::Mat img(h,w,CV_8UC4,(void*)processed_image);
std::vector<cv::Mat>channel;
cv::split(img,channel);

cv::Mat laplace_r,laplace_b,laplace_g;

//calculation of lapelace edge..
cv::Laplacian(channel[0],laplace_r,0);
cv::Laplacian(channel[1],laplace_g,0);
cv::Laplacian(channel[2],laplace_b,0);

//edge enhance...
///////////////////////
laplace_b*=sharpness;//
laplace_r*=sharpness;//
laplace_g*=sharpness;//
//////////////////////

//Image substraction...

channel[0]-=laplace_r;
channel[1]-=laplace_g;
channel[2]-=laplace_b;

cv::merge(channel,img);



		}
	public:
		Sharp()
		{
			init_parameters();
		}
		void setimage(unsigned char *src,int height,int width,int channels)
		{
			image=src;
			h=height;
			w=width;
			c=channels;

			
		}  

	void process()
	{
		

		_process();
	}
	float getSharpnessParameter()
	{
		return sharpness;
	}

unsigned char* getimage()
{
return processed_image;

}
void setSharpnessParameter(float _sharpness)
{
	sharpness=_sharpness;
}
	};

	}
	namespace DataAbstractor
	{
		
//image histogram..
float* histogram(unsigned char *image,int h,int w)
{
	
cv::Mat src(w,h,CV_8UC4,image);
int histSize=255;
float hrange[]={0,255};
const float *range={hrange};

	cv::Mat histg,histb,histr;
	
	std::vector<cv::Mat>channel;

	split(src,channel); //splitting image into RBG planes;
	//calculating histogram for each plane...
	
	cv::calcHist( &channel[0], 1, 0, cv::Mat(),histr, 1, &histSize,&range, true,false);
	cv::calcHist( &channel[1], 1, 0, cv::Mat(),histb, 1, &histSize,&range, true,false);
	cv::calcHist( &channel[2], 1, 0, cv::Mat(),histg, 1, &histSize,&range, true,false);

	int hist_w=512,hist_h=500;
	int hist_buckets=cvRound((double)(hist_w/histSize));//scaling x axis into buckets over its size...

	//normalization of histogram..
	cv::normalize(histr,histr,0,histr.rows,cv::NORM_MINMAX,-1,cv::Mat());
	cv::normalize(histb,histb,0,histb.rows,cv::NORM_MINMAX,-1,cv::Mat());
	cv::normalize(histg,histg,0,histg.rows,cv::NORM_MINMAX,-1,cv::Mat());	
	//now to plot histogram of each planes 
	/*in the matrix we have intensity values of each buckets.Total no of buckets is 256;
	To represent 256 buckets over x axis,we need to divide x axis in to these buckets, to do so we divide its length with buckets.
	By doing so we obtain a correct scale of each buckets over x axis.And then we are going to plot values in each buckets over y axis..
	each row in matrix represent bucket.so we are actually itrating over each buckets in a matrix..
	|   |    |   | |   |    | |||||||  ||| |||  |||||||||!@$#%^$%%^%^&^%&^*&**(&$#%#%#$%$#^#$@^%$
	||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||j|||||||||||||||||||||||||||||
	*/
	cv::Mat histogram_r(hist_w,hist_h,CV_8UC3); //matrix holding histogram(RED);
	cv::Mat histogram_b(hist_w,hist_h,CV_8UC3); //matrix holding histogram(BLUE);
	cv::Mat histogram_g(hist_w,hist_h,CV_8UC3); //matrix holding histogram(GREEN);  

	float *arr=(float*)malloc(sizeof(float)*(256*3));
	
	
	for(int loop=0;loop<255;loop++)
	{
		arr[loop]=histr.at<float>(loop,0);
		arr[loop+256]=histg.at<float>(loop,0);
		arr[loop+(255*2)+1]=histb.at<float>(loop,0);
	}
	return arr; //return R-G-B array..
}
//histogram of  oriented gradients...
void HOG()
{


}

	}
};

#endif