#ifndef WIDGET_FILTER_BLUR
#define WIDGET_FILTER_BLUR

/*
This header file contains User interaction for Filter_agent(Blur_agent);

*/
#include "Filters.h"
#include "Widget_SliderInput.h"


class Widget_UI_blur
{
	ImageProcessor::Filters::Blur Blur_agent;
	Widget::SliderInput Blur_pannel;
	int saved_kernel_size;


	//widget flags...
	bool visible;				//Render window or not?
	bool kernel_size_updated; //weather user intrrupted an update or not?
	bool flag_process_green; //weather to process image during draw calls
	bool intrrupt;			//weather user intrrupted an update or not??
	
public:
	Widget_UI_blur()
	{
		Blur_pannel=Widget::SliderInput("kernel","Blur",0,50);
		visible=false;
		flag_process_green=false;
		intrrupt=false;
	}
	void processWith(unsigned char *image_input,int h,int w,int c)
	{
		Blur_agent.setimage(image_input,h,w,c);
		Blur_agent.process();
	}
	void render()
	{
		

		if(visible)
		{
			
		Blur_pannel.render();
		if(saved_kernel_size!=Blur_pannel.getvalue()) //intrrupted an update..
		{
			intrrupt=true;
			saved_kernel_size=Blur_pannel.getvalue();
			Blur_agent.setKernelSize(saved_kernel_size);
			//Blur_agent.process();
		}
		else if(Blur_pannel.isApplyButtonpressed())
		{intrrupt=true;}
		else;
		
		}
		else;	
	}
	unsigned char *getProcessed()
	{
		return Blur_agent.getimage();
	}
	/*
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
	void setVisiblity(bool _visiblity)
	{
		visible=_visiblity;
	}
	bool filterApply()
	{
		return Blur_pannel.isApplyButtonpressed();
	}
	bool isVisible()
	{
		return visible;
	}
	bool hasintrrupted()
	{
		if(intrrupt==true)
		{
			intrrupt=false;
			return true;
		}
		else
			return false;
	}
};
#endif