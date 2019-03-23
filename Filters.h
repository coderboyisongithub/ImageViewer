#ifndef FILTERS_H
#define	FILTERS_H

#include <opencv2\opencv.hpp>
#include <iostream>
#include "BufferContainer.h"
#include <omp.h>



/*
				  (food!)
			-||-           -||-
            -||            -||-                          
            -\\   ((  ))  -//-
			 -\\ // 01 \\-//-
			    |0  1  0| -
                \0101010/- 
          =======|01010|=======
				/0101001\-
           -//-|101000100|-\\-
          -//- \\\\01////- -\\-
         -||-      \/       -||-
         -||-               -||-


*/

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

class Paint_Red //artify..
	{
		unsigned char *image,*processed_image;
		int h,w,c;
		int intensity;
		bool ready;

void init_env()
{
	intensity=0;
	image=NULL;
	processed_image=NULL;
	ready=false;

}

inline void extract_decimal(float src,int &integeral,float &decimal)
{
	int integer=(int)src;
	decimal=src-(float)integer;
	integeral=integer;
}
void kernel_operation(cv::Mat src,cv::Size patch_size,int loc_r,int loc_c,int value)
{
		
	/*cv::Mat clone;
	src.copyTo(clone);
	cv::rectangle(clone,cv::Rect(loc_c,loc_r,patch_size.width,patch_size.height),cv::Scalar(1,1,1),2);
	cv::imshow("clone",clone);
	cv::waitKey(0);
	*/
	uchar max=0;
//	uchar min=300;
	for(int row_anchor=loc_r;row_anchor<((loc_r)+patch_size.height);row_anchor++)
	{
		for(int col_anchor=loc_c;col_anchor<((loc_c)+patch_size.width);col_anchor++)
		{
			if(src.at<uchar>(row_anchor,col_anchor)>max)
			max=src.at<uchar>(row_anchor,col_anchor);
		//	if(src.at<uchar>(row_anchor,col_anchor)<min)
			//	min =src.at<uchar>(row_anchor,col_anchor);
			else
				continue;
		}

	}
	
	
	//pixle over-write.
	for(int row_anchor=loc_r;row_anchor<((loc_r)+patch_size.height);row_anchor++)
	{

		if(row_anchor>src.rows)
			break;
		else;
		for(int col_anchor=loc_c;col_anchor<((loc_c)+patch_size.width);col_anchor++)
		{
			if(col_anchor>src.cols)
				break;
			else;
			if(src.at<uchar>(row_anchor,col_anchor)>=(uchar)value)
				src.at<uchar>(row_anchor,col_anchor)=250;
			else
				src.at<uchar>(row_anchor,col_anchor)=(uchar)0;
			
		}

	
	}
	
}


/*
				  (food!)
			-||-           -||-
            -||            -||-                          
            -\\   ((  ))  -//-
			 -\\ // 01 \\-//-     
			    |0  1  0| -       
                \0101010/- 
          =======|01010|=======
				/0101001\-
           -//-|101000100|-\\-
          -//- \\\\01////- -\\-
         -||-      \/       -||-
         -||-               -||-


*/


void iter(cv::Mat src,cv::Size patch,int value)
{
	if(patch.area()==0)
return;
	else ;
	
	cv::Size patch_size(patch);//orignal patch size iteration over matrix
	float vertical_step=(float)src.rows/(float)patch_size.height;
	float horizantal_step=(float)src.cols/(float)patch_size.width;
	 int h_residual_pixles=src.cols-(horizantal_step*patch_size.width);
	  int v_residual_pixles=src.rows-(horizantal_step*patch_size.height);
	

	 // printf("\nimage resolution:%dx%d pixles covered:%d pixles remaining:%d  steps:%d",src.rows,src.cols,(horizantal_step*patch_size.width),h_residual_pixles,horizantal_step);

	  //determine weather to cover remaining region?
	  //Horizantal part..
	  int h_steps;float h_fraction;
	  int v_steps;float v_fraction;
	  extract_decimal(horizantal_step,h_steps,h_fraction);
	  extract_decimal(vertical_step,v_steps,v_fraction);
	  cv::Size fractional_patchsize;
	  fractional_patchsize.width=(int)(((int)(h_fraction*100))*patch_size.width/100);
	  fractional_patchsize.height=(int)(((int)(v_fraction*100))*patch_size.width/100);
	  //printf("%d %d\n",fractional_patchsize.width,fractional_patchsize.height);

	  //printf("\n%f %f",v_fraction,h_fraction);
	  bool _cover_horizantal,_cover_vertical;
	 if(v_fraction>0.0)
		 {v_steps+=1;
	 _cover_vertical=true;
	 }
	  else
		  _cover_vertical=false;

	  if(h_fraction>0.0)
	{	  h_steps+=1;
	  _cover_horizantal=true;
	  }
	  else
	  {
		  _cover_horizantal=false;
	  }

	  int anchor_row;
	  for(anchor_row=0;anchor_row<=(v_steps-1);anchor_row++)
	  {
		  for(int anchor_col=0;anchor_col<=(h_steps-1);anchor_col++)
		  {
			  if(_cover_vertical==true || _cover_horizantal==true)
			  {
			  if(anchor_col==(h_steps-1) && anchor_row<(v_steps-1))
			  {
				  //calculate space for fitting>>?
				  //calculating horizantal shift
				  int remain_pixles_count=(int)(((h_fraction*100)*patch_size.width)/100);//number of pixles in fractional part..
				  
				  //to calculate adjustment we do patch_size.width-fractional_part=part_outside_bound..

				  int shift_pixle_count=patch_size.width-remain_pixles_count;//number of pixles needed to step back the patch,to include fractional part of image


     				  kernel_operation(src,patch_size,anchor_row*patch_size.height, ((anchor_col*patch_size.width)-shift_pixle_count) ,value);
				  
			  }
			else if(anchor_row==(v_steps-1) && anchor_col<(h_steps-1))
				  {
					//calculate space for fitting>>?
				  //calculating horizantal shift
					  int remain_pixles_count=(int)(((v_fraction*100)*patch_size.height)/100);//number of pixles in fractional part..
				  
				  //to calculate adjustment we do patch_size.width-fractional_part=part_outside_bound..

				  int shift_pixle_count=patch_size.height-remain_pixles_count;//number of pixles needed to step back the patch,to include fractional part of image

				  
				  kernel_operation(src,patch_size, (anchor_row*patch_size.height-shift_pixle_count) , anchor_col*patch_size.width,value);
				

				  }
			else if(anchor_row==(v_steps-1) && anchor_col==(h_steps-1))
			{
				 int remain_pixles_count_horizantal=(int)(((h_fraction*100)*patch_size.width)/100);
					 int remain_pixles_count_vertical=(int)(((v_fraction*100)*patch_size.height)/100);

					 int shift_pixle_count_horizantal=patch_size.width-remain_pixles_count_horizantal;
					 int shift_pixle_count_vertical=patch_size.height-remain_pixles_count_vertical;

					 kernel_operation(src,patch_size, (anchor_row*patch_size.height-shift_pixle_count_vertical) , (anchor_col*patch_size.width-shift_pixle_count_horizantal),value);
					 
			}
				  
			  else
				  kernel_operation(src,patch_size,anchor_row*patch_size.height,anchor_col*patch_size.width,value);
			  }
			  else
				  kernel_operation(src,patch_size,anchor_row*patch_size.height,anchor_col*patch_size.width,value);
		  }
	  }
	

	
}
void _process()
{
	
	if(processed_image!=NULL)
	{
		free(processed_image);
		processed_image=NULL;
	}
	processed_image=(unsigned char*)malloc(sizeof(unsigned char)*h*w*4);
	memcpy(processed_image,image,sizeof(unsigned char)*h*w*4);
	std::vector<cv::Mat>channels;
	cv::Mat tmp(h,w,CV_8UC4,(void*)processed_image);
		
	cv::split(tmp,channels);
	for(int loop=0;loop<3;loop++)
	{
		iter(channels[loop],cv::Size(intensity,intensity),intensity);

	}

	cv::merge(channels,tmp);

}

	public:
		Paint_Red()
		{
			init_env();
			h=0;w=0;c=0;
		} 
		void setimage(unsigned char *source,int height,int width,int channels)
		{
			image=source;//8-bit unsigned matrix..
			h=height;
			w=width;
			c=channels;
			
		}
		unsigned char* getimage()
		{
			return processed_image;
		}
		void setvalue(int value)
		{
			intensity=value;

		}
		void process()
		{
			_process();
		}



	};

	class Tesselate
	{
		unsigned char *image,*processed_image;
		bool ready;
		int tesselation_parameter;

		int h,w,c;

		void init_param()
		{
			image=processed_image=NULL;
			bool ready=false;
			tesselation_parameter=0;

		}
				inline void extract_decimal(float src,int &integeral,float &decimal)
				{
					int integer=(int)src;
					decimal=src-(float)integer;
					integeral=integer;
				}
				void kernel_operation(cv::Mat src,cv::Size patch_size,int loc_r,int loc_c,int value)
				{
		
					/*cv::Mat clone;
					src.copyTo(clone);
					cv::rectangle(clone,cv::Rect(loc_c,loc_r,patch_size.width,patch_size.height),cv::Scalar(1,1,1),2);
					cv::imshow("clone",clone);
					cv::waitKey(0);
				*/
					uchar max1=0;
					uchar max2=0;
				//	uchar min=300;

					int transition_point=loc_c;
					for(int row_anchor=loc_r;row_anchor<((loc_r)+patch_size.height);row_anchor++)
					{
						for(int col_anchor=loc_c;col_anchor<((loc_c)+patch_size.width);col_anchor++)
						{
			
							if(col_anchor<transition_point)
							{
								if(src.at<uchar>(row_anchor,col_anchor)>max1)
								{
									max1=src.at<uchar>(row_anchor,col_anchor);
								}
								else;
							}

							else
							{
							if(src.at<uchar>(row_anchor,col_anchor)>max2)
								{
									max2=src.at<uchar>(row_anchor,col_anchor);
								}
								else;
							}
						}
						transition_point++;
		
					}

					transition_point=loc_c;
						for(int row_anchor=loc_r;row_anchor<((loc_r)+patch_size.height);row_anchor++)
					{
						for(int col_anchor=loc_c;col_anchor<((loc_c)+patch_size.width);col_anchor++)
						{
			
								if(col_anchor<transition_point)
								{
				
										src.at<uchar>(row_anchor,col_anchor)=max1;
				
								}

								else
								{
			
			
										src.at<uchar>(row_anchor,col_anchor)=max2;
		
			
								}
						}


						transition_point++;
		
					}
	
				/*	//pixle over-write.
					for(int row_anchor=loc_r;row_anchor<((loc_r)+patch_size.height);row_anchor++)
					{

						if(row_anchor>src.rows)
							break;
						else;
						for(int col_anchor=loc_c;col_anchor<((loc_c)+patch_size.width);col_anchor++)
						{
							if(col_anchor>src.cols)
								break;
							else;
							//if(src.at<uchar>(row_anchor,col_anchor)>=(uchar)value)
								src.at<uchar>(row_anchor,col_anchor)=max;
				//			else
								src.at<uchar>(row_anchor,col_anchor)=(uchar)0;
			
			
			
			
						}

	
					}
					*/
				}
				void iter(cv::Mat src,cv::Size patch,int value)
				{
					if(patch.area()==0)
				return;
					else ;
	
					cv::Size patch_size(patch);//orignal patch size iteration over matrix
					float vertical_step=(float)src.rows/(float)patch_size.height;
					float horizantal_step=(float)src.cols/(float)patch_size.width;
					 int h_residual_pixles=src.cols-(horizantal_step*patch_size.width);
					  int v_residual_pixles=src.rows-(horizantal_step*patch_size.height);
	

					 // printf("\nimage resolution:%dx%d pixles covered:%d pixles remaining:%d  steps:%d",src.rows,src.cols,(horizantal_step*patch_size.width),h_residual_pixles,horizantal_step);

					  //determine weather to cover remaining region?
					  //Horizantal part..
					  int h_steps;float h_fraction;
					  int v_steps;float v_fraction;
					  extract_decimal(horizantal_step,h_steps,h_fraction);
					  extract_decimal(vertical_step,v_steps,v_fraction);
					  cv::Size fractional_patchsize;
					  fractional_patchsize.width=(int)(((int)(h_fraction*100))*patch_size.width/100);
					  fractional_patchsize.height=(int)(((int)(v_fraction*100))*patch_size.width/100);
					  //printf("%d %d\n",fractional_patchsize.width,fractional_patchsize.height);

					  //printf("\n%f %f",v_fraction,h_fraction);
					  bool _cover_horizantal,_cover_vertical;
					 if(v_fraction>0.0)
						 {v_steps+=1;
					 _cover_vertical=true;
					 }
					  else
						  _cover_vertical=false;

					  if(h_fraction>0.0)
					{	  h_steps+=1;
					  _cover_horizantal=true;
					  }
					  else
					  {
						  _cover_horizantal=false;
					  }

					  int anchor_row;
					  for(anchor_row=0;anchor_row<=(v_steps-1);anchor_row++)
					  {
						  for(int anchor_col=0;anchor_col<=(h_steps-1);anchor_col++)
						  {
							  if(_cover_vertical==true || _cover_horizantal==true)
							  {
							  if(anchor_col==(h_steps-1) && anchor_row<(v_steps-1))
							  {
								  //calculate space for fitting>>?
								  //calculating horizantal shift
								  int remain_pixles_count=(int)(((h_fraction*100)*patch_size.width)/100);//number of pixles in fractional part..
				  
								  //to calculate adjustment we do patch_size.width-fractional_part=part_outside_bound..

								  int shift_pixle_count=patch_size.width-remain_pixles_count;//number of pixles needed to step back the patch,to include fractional part of image


     								  kernel_operation(src,patch_size,anchor_row*patch_size.height, ((anchor_col*patch_size.width)-shift_pixle_count) ,value);
				  
							  }
							else if(anchor_row==(v_steps-1) && anchor_col<(h_steps-1))
								  {
									//calculate space for fitting>>?
								  //calculating horizantal shift
									  int remain_pixles_count=(int)(((v_fraction*100)*patch_size.height)/100);//number of pixles in fractional part..
				  
								  //to calculate adjustment we do patch_size.width-fractional_part=part_outside_bound..

								  int shift_pixle_count=patch_size.height-remain_pixles_count;//number of pixles needed to step back the patch,to include fractional part of image

				  
								  kernel_operation(src,patch_size, (anchor_row*patch_size.height-shift_pixle_count) , anchor_col*patch_size.width,value);
				

								  }
							else if(anchor_row==(v_steps-1) && anchor_col==(h_steps-1))
							{
								 int remain_pixles_count_horizantal=(int)(((h_fraction*100)*patch_size.width)/100);
									 int remain_pixles_count_vertical=(int)(((v_fraction*100)*patch_size.height)/100);

									 int shift_pixle_count_horizantal=patch_size.width-remain_pixles_count_horizantal;
									 int shift_pixle_count_vertical=patch_size.height-remain_pixles_count_vertical;

									 kernel_operation(src,patch_size, (anchor_row*patch_size.height-shift_pixle_count_vertical) , (anchor_col*patch_size.width-shift_pixle_count_horizantal),value);
					 
							}
				  
							  else
								  kernel_operation(src,patch_size,anchor_row*patch_size.height,anchor_col*patch_size.width,value);
							  }
							  else
								  kernel_operation(src,patch_size,anchor_row*patch_size.height,anchor_col*patch_size.width,value);
						  }
					  }
	

	
				}
	void _process()
	{

		if(processed_image!=NULL)
		{
			free(processed_image);
				processed_image=NULL;
		}

		//cpy source memblock to processed image memblock..
		//pre-allocating destenation memory block..
		processed_image=(unsigned char*)malloc(sizeof(unsigned char)*h*w*4);

		memcpy(processed_image,image,sizeof(unsigned char)*h*w*4);
		if(tesselation_parameter==0)
			return;
		else;
		cv::Mat tmp(h,w,CV_8UC4,processed_image);	
		//splitting into seperate channels (R,G,B);

		std::vector<cv::Mat>channels;
		cv::split(tmp,channels);

		for(int loop=0;loop<3;loop++)
		{
			iter(channels[loop],cv::Size(tesselation_parameter,tesselation_parameter),NULL);

		}
			cv::merge(channels,tmp);


	}

	public:
		Tesselate()
		{
			init_param();


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
		
void setTesselationParam(int v0)
{
	tesselation_parameter=v0;
}
void process()
{
	_process();
}


	};

	class ChannelMixer
	{
		BufferContainer::imageContainer bucket; //structure containing image and its variables..binded
		void init_param()
		{
			bucket.image=NULL;
			bucket.processed_image=NULL;
			bucket.h=bucket.w=bucket.c=0;
		}
	public:
		ChannelMixer()
		{
			
		}
		void setImage(unsigned char *src,int h,int w ,int c)
		{
			bucket.setParamsWith(src,src,h,w,(c+1));
		}
		void setImage(BufferContainer::imageContainer src)
		{
			bucket.setParams(src);
		}

	};
	}
	namespace DataAbstractor
	{
		
//image histogram..
BufferContainer::Histogram_container histogram(unsigned char *image,int h,int w)
	{
	
	cv::Mat src(w,h,CV_8UC4,image);
	int histSize=255;
	float hrange[]={0 , 255};
	const float *range={hrange};

		cv::Mat histg,histb,histr;
	
		std::vector<cv::Mat>channel;

		split(src,channel); //splitting image into RBG planes;
		//calculating histogram for each plane...
	
		cv::calcHist( &channel[0], 1, 0, cv::Mat(),histr, 1, &histSize,&range, true,false);
		cv::calcHist( &channel[1], 1, 0, cv::Mat(),histb, 1, &histSize,&range, true,false);
		cv::calcHist( &channel[2], 1, 0, cv::Mat(),histg, 1, &histSize,&range, true,false);

		//int hist_w=512,hist_h=500;
		//int hist_buckets=cvRound((double)(hist_w/histSize));//scaling x axis into buckets over its size...

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
		/*cv::Mat histogram_r(hist_w,hist_h,CV_8UC3); //matrix holding histogram(RED);
		cv::Mat histogram_b(hist_w,hist_h,CV_8UC3); //matrix holding histogram(BLUE);
		cv::Mat histogram_g(hist_w,hist_h,CV_8UC3); //matrix holding histogram(GREEN);  
		*/
		
		float *arr=(float*)malloc(sizeof(float)*((histSize+1)*3));
	
		//calculation of mean--frequency distrubution..data;
		float mean[]={0.0,0.0,0.0};
		float total_freq[]={0,0,0};
		for(int loop=0;loop<255;loop++)
		{
			mean[0]+=(float)(loop+1)*histr.at<float>(loop,0);
			total_freq[0]+=histr.at<float>(loop,0);
			mean[1]+=(float)(loop+1)*histb.at<float>(loop,0);
			total_freq[1]+=histb.at<float>(loop,0);
			mean[2]+=(float)(loop+1)*histg.at<float>(loop,0);
			total_freq[2]+=histg.at<float>(loop,0);
		
		}

		mean[0]/=total_freq[0];
		mean[1]/=total_freq[1];
		mean[2]/=total_freq[2];

	

		for(int loop=0;loop<histSize;loop++)
		{
			arr[loop]=histr.at<float>(loop,0);
			arr[loop+256]=histg.at<float>(loop,0);
			arr[loop+(255*2)+1]=histb.at<float>(loop,0);
		}

		BufferContainer::Histogram_container bag;
		bag.setParam(arr,mean);
	
		return bag; //return R-G-B array..
	}
	//histogram of  oriented gradients...
void HOG()
{


}



	}
};

#endif
