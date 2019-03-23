#ifndef _BUFFER_CONTAINER_H
#define _BUFFER_CONTAINER_H

#include "list.h"

namespace BufferContainer
{
struct imageContainer
{
		unsigned char *processed_image,*image;
		int h,w,c;

	void setParams(imageContainer src) //set variable values..
		{
			setParamsWith(src.image,src.processed_image,src.h,src.w,src.c);
		}

	void setParamsWith(unsigned char* src,unsigned char *_processed_image,int height,int width,int channel)
	{
		image=src;
		processed_image=_processed_image;
		h=height;
		c=channel;
		w=width;
	}

	
};
struct Histogram_container
{
	float *histo_dat;
	float histo_mean[3];

	void setParam(float *data,float histogram_mean[3])
	{
		histo_dat=data;
		histo_mean[0]=histogram_mean[0];
		histo_mean[1]=histogram_mean[1];
		histo_mean[2]=histogram_mean[2];
	}
};

}

#endif