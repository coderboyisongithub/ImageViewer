#ifndef _WIDGET_FILTER_TESSELATE_
#define _WIDGET_FILTER_TESSELATE_
#include "Filters.h"
#include "Widget_SliderInput.h"

class Widget_UI_Tesselate
{
	ImageProcessor::Filters::Tesselate Tesselator;
	Widget::SliderInput uipannel;
	
	//runtime flags
	bool visible; //render UI true:flase;
	int tesselation_parameter; //magnitude of tesselation
	bool intrrupt;  //UI intrrupt log
public:
	Widget_UI_Tesselate()
	{
		visible=false;
		intrrupt=false;
		
		uipannel=Widget::SliderInput("effect","Tesselator",0,140);
		Tesselator=ImageProcessor::Filters::Tesselate();
	}

	void render()
	{
		if(visible)
		{

			uipannel.render();

			
			if(tesselation_parameter!=uipannel.getvalue())
			{
	
				tesselation_parameter=uipannel.getvalue();
				Tesselator.setTesselationParam(tesselation_parameter);
				intrrupt=true;
			}
			else if(uipannel.isApplyButtonpressed())
			{
				intrrupt=true;
			}
			else
			{
				intrrupt=false;
			}
		}
		else
			return;

	}

	void processWith(unsigned char *src,int h,int w,int c)
	{
		
		Tesselator.setimage(src,h,w,4);
		Tesselator.process();
		

	}
	void setVisiblity(bool _visiblity)
	{
		visible=_visiblity;
	}
	bool filterApply()
	{
		return uipannel.isApplyButtonpressed();
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
	unsigned char *getProcessed()
	{
		unsigned char * im_=Tesselator.getimage();
		if(im_!=NULL)
			return im_;
		else
		return NULL;
	}
};

#endif